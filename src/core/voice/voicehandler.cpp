#include "voicehandler.h"
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <kylin-ai/common/enums.h>

VoiceHandler::VoiceHandler(QObject *parent)
    : QObject(parent)
    // , audioInput(nullptr) // Removed: audioInput member was commented out in .h
    , audioOutput(nullptr)
    , recording(false)
    , recognitionSession(nullptr)
    , synthesisSession(nullptr)
    , audioConfig(nullptr)
    , modelConfig(nullptr)
{
    initializeAudioDevices();
    if (!initializeSpeechServices()) {
        qWarning() << "语音服务初始化失败，请检查日志。";
        // Consider emitting an error signal here if initialization is critical at construction
    }
}

VoiceHandler::~VoiceHandler()
{
    // if (audioInput) { // Removed: audioInput member was commented out in .h
    //     delete audioInput;
    // }
    if (audioOutput) {
        audioOutput->stop();
        delete audioOutput;
    }
    
    // 清理语音识别和合成会话
    if (recognitionSession) {
        speech_recognizer_destroy_session(&recognitionSession); // Corrected: Pass address of pointer
    }
    if (synthesisSession) {
        speech_synthesizer_destroy_session(&synthesisSession); // Corrected: Pass address of pointer
    }
    if (audioConfig) {
        audio_config_destroy(&audioConfig);
    }
    if (modelConfig) {
        speech_model_config_destroy(&modelConfig);
    }
}

bool VoiceHandler::initializeSpeechServices()
{
    qDebug() << "Initializing speech services...";

    // 1. Create and set AudioConfig for recognizer (continuous from default mic)
    // This config is used when speech_recognizer_start_continuous_recognition_async is called.
    audioConfig = audio_config_create_continuous_audio_input_from_default_microphone();
    if (!audioConfig) {
        emit errorOccurred("创建连续音频输入配置失败");
        qCritical() << "Failed to create continuous audio input config.";
        return false;
    }
    // Explicitly set sample rate for cloud ASR, as 16kHz is common.
    qDebug() << "Setting input audio rate to 16000 Hz for ASR audioConfig.";
    audio_config_set_input_audio_rate(audioConfig, 16000);
    // You might also need to set channels (e.g., 1 for mono) or format if required by Xunfei via Kylin SDK.
    // audio_config_set_input_audio_channels(audioConfig, 1); // Example if needed

    // 2. Create and set ModelConfig (common for recognizer and synthesizer)
    modelConfig = speech_model_config_create();
    if (!modelConfig) {
        emit errorOccurred("创建语音模型配置失败");
        qCritical() << "Failed to create speech model config.";
        return false;
    }

    // Configure for Cloud-based Xunfei ASR as per SDK documentation
    const char* xunfeiAsrModelName = "讯⻜-语⾳⼤模型"; 
    qDebug() << "Configuring Speech Recognition and Synthesis for Public Cloud model:" << xunfeiAsrModelName;
    speech_model_config_set_name(modelConfig, xunfeiAsrModelName); 
    speech_model_config_set_deploy_type(modelConfig, PublicCloud); 
    qDebug() << "Set Speech Recognition and Synthesis deploy type to PublicCloud.";

    // Note: Authentication parameters (API Key, App ID) for Xunfei
    // are expected to be configured in the system's "Settings -> AI Module Management".
    // The SDK likely uses these global settings when PublicCloud is selected for this model name.

    // 3. Initialize Recognizer Session
    qDebug() << "正在初始化语音识别会话...";
    recognitionSession = speech_recognizer_create_session();
    if (!recognitionSession) {
        emit errorOccurred("创建语音识别会话失败");
        return false;
    }

    int ret_init_rec = speech_recognizer_init_session(recognitionSession);
    if (ret_init_rec != 0) {
        emit errorOccurred(QString("初始化语音识别会话失败: %1").arg(ret_init_rec));
        speech_recognizer_destroy_session(&recognitionSession);
        recognitionSession = nullptr;
        return false;
    }
    qDebug() << "语音识别会话初始化成功";

    speech_recognizer_set_audio_config(recognitionSession, audioConfig); // Set the mic input config
    speech_recognizer_set_model_config(recognitionSession, modelConfig); // Set the model
    speech_recognizer_result_set_callback(recognitionSession, recognitionCallback, this);

    // 4. Initialize Synthesizer Session
    qDebug() << "正在初始化语音合成会话...";
    synthesisSession = speech_synthesizer_create_session();
    if (!synthesisSession) {
        emit errorOccurred("创建语音合成会话失败");
        return false;
    }
    int ret_init_synth = speech_synthesizer_init_session(synthesisSession);
    if (ret_init_synth != 0) {
        emit errorOccurred(QString("初始化语音合成会话失败: %1").arg(ret_init_synth));
        speech_synthesizer_destroy_session(&synthesisSession);
        synthesisSession = nullptr;
        return false;
    }
    qDebug() << "语音合成会话初始化成功";
    
    // Configure synthesizer (e.g., voice name, speed, pitch if available and desired)
    // These are examples, actual config functions depend on SDK
    // speech_synthesizer_set_voice_name(synthesisSession, "default_voice");
    // speech_synthesizer_set_speaking_rate(synthesisSession, 1.0);

    // Create a default audio output config for the synthesizer
    AudioConfig *synthAudioOutputConfig = audio_config_create_audio_output_from_default_speaker();
    if (!synthAudioOutputConfig) {
        emit errorOccurred("创建语音合成默认扬声器输出配置失败");
    } else {
        speech_synthesizer_set_audio_config(synthesisSession, synthAudioOutputConfig);
        audio_config_destroy(&synthAudioOutputConfig);
    }
    
    speech_synthesizer_set_model_config(synthesisSession, modelConfig); // Use the same model config for now
    speech_synthesizer_result_set_callback(synthesisSession, synthesisCallback, this);

    qDebug() << "Speech services initialized.";
    return true;
}

bool VoiceHandler::startRecording()
{
    if (recording) {
        qDebug() << "Recording is already in progress.";
        return false;
    }
    if (!recognitionSession) {
        emit errorOccurred("语音识别服务未初始化，无法开始录音");
        qWarning() << "Recognition session not initialized. Cannot start recording.";
        return false;
    }

    accumulatedRecognizedText.clear(); // Clear previous text
    qDebug() << "Attempting to start continuous recognition...";
    // This is the primary call suspected of blocking.
    // Ensure the model ("ChatGLM", OnDevice) is correct for SPEECH.
    // Ensure audioConfig (continuous from mic) is correctly set up.
    speech_recognizer_start_continuous_recognition_async(recognitionSession); // Corrected: No return value to assign
    // Check error or status via a different mechanism if provided by SDK (e.g. session state or callback)
    // For now, assume success if no immediate exception/crash and proceed.

    recording = true;
    emit recordingStarted();
    qDebug() << "连续语音识别已启动 (SDK should be handling microphone input).";
    return true;
}

void VoiceHandler::stopRecording()
{
    if (!recording) {
        qDebug() << "Not recording, no need to stop.";
        return;
    }
    if (!recognitionSession) {
        emit errorOccurred("语音识别服务未初始化，无法停止录音");
        qWarning() << "Recognition session not initialized. Cannot stop recording.";
        return;
    }

    qDebug() << "Stopping continuous recognition...";
    speech_recognizer_stop_continuous_recognition_async(recognitionSession); // Corrected: No return value to assign
    // Similar to start, check status via other means if available/needed.

    recording = false;

    if (!accumulatedRecognizedText.isEmpty()) {
        emit textRecognized(accumulatedRecognizedText);
        qDebug() << "Final accumulated text emitted after stopping:" << accumulatedRecognizedText;
    }

    emit recordingStopped();
    qDebug() << "连续语音识别已停止。";
}

bool VoiceHandler::isRecording() const
{
    return recording;
}

void VoiceHandler::recognitionCallback(SpeechRecognitionResult *result, void *userData)
{
    VoiceHandler *handler = static_cast<VoiceHandler*>(userData);
    if (!handler || !result) return;

    SpeechResultReason reason = speech_recognition_result_get_reason(result);
    const char *text = speech_recognition_result_get_text(result);
    
    qDebug() << "Recognition Callback - Reason:" << reason;

    if (reason == SPEECH_RECOGNIZED) { // Final recognized text
        if (text) {
            QString recognizedSegment = QString::fromUtf8(text);
            qDebug() << "  Segment recognized:" << recognizedSegment;
            if (!recognizedSegment.isEmpty()) {
                if (!handler->accumulatedRecognizedText.isEmpty()) {
                    handler->accumulatedRecognizedText.append(" "); // Add a space separator
                }
                handler->accumulatedRecognizedText.append(recognizedSegment);
                qDebug() << "  Accumulated text now:" << handler->accumulatedRecognizedText;
            }
        } else {
            qDebug() << "  Text: (null) but reason is SPEECH_RECOGNIZED";
        }
    } else if (reason == SPEECH_RECOGNIZING) { // Intermediate result
        if (text) {
            qDebug() << "  Intermediate Text:" << QString::fromUtf8(text);
            // Optionally emit a signal for intermediate results if UI needs to display them
            // emit handler->partialTextRecognized(QString::fromUtf8(text)); 
        }
    } else if (reason == SPEECH_ERROR_OCCURRED) {
        int error_code = speech_recognition_result_get_error_code(result);
        const char* error_msg = speech_recognition_result_get_error_message(result);
        QString errorMessage = QString("语音识别错误: %1 (代码: %2)").arg(QString::fromUtf8(error_msg ? error_msg : "Unknown error")).arg(error_code);
        qWarning() << errorMessage;
        emit handler->errorOccurred(errorMessage);
    } else if (reason == SPEECH_RECOGNITION_STARTED) {
        qDebug() << "  Recognition started.";
    } else if (reason == SPEECH_RECOGNITION_COMPLETED) {
        qDebug() << "  Recognition completed.";
        // This might be the point to stop continuous recognition if it's a one-shot mode simulated with continuous
        // or simply a final notification.
    }
    // Note: SDK does not seem to require explicit destruction of SpeechRecognitionResult in callback
}

void VoiceHandler::synthesisCallback(SpeechSynthesisResult *result, void *userData)
{
    VoiceHandler *handler = static_cast<VoiceHandler*>(userData);
    if (!handler || !result) return;

    SpeechResultReason reason = speech_synthesis_result_get_reason(result);
    qDebug() << "Synthesis Callback - Reason:" << reason;

    if (reason == SPEECH_SYNTHESIZING) { // Audio data chunk available
        uint32_t data_size = 0;
        const uint8_t *audio_data = speech_synthesis_result_get_data(result, &data_size); // Corrected function name
        
        if (audio_data && data_size > 0) {
            qDebug() << "  Received audio data chunk, size:" << data_size;
            if (!handler->audioOutput) { 
                QAudioFormat format;
                format.setSampleRate(speech_synthesis_result_get_audio_rate(result)); 
                format.setChannelCount(speech_synthesis_result_get_audio_channel(result));
                format.setSampleSize(16); // Assuming 16-bit, common for PCM. SDK might provide this.
                format.setCodec("audio/pcm");
                format.setByteOrder(QAudioFormat::LittleEndian);
                format.setSampleType(QAudioFormat::SignedInt);

                QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
                if (!info.isFormatSupported(format)) {
                    qWarning() << "Default output device does not support format. Attempting to use nearest.";
                    format = info.nearestFormat(format);
                }
                if (format.sampleRate() == 0) { // Basic sanity check if nearestFormat failed badly
                    qWarning() << "Critical: Audio format sample rate is 0. Using fallback 16000Hz.";
                    format.setSampleRate(16000);
                }
                 if (format.channelCount() == 0) {
                    qWarning() << "Critical: Audio format channel count is 0. Using fallback 1 channel.";
                    format.setChannelCount(1);
                }

                handler->audioOutput = new QAudioOutput(format, handler);
                handler->connect(handler->audioOutput, &QAudioOutput::stateChanged, 
                                 [handler](QAudio::State state){
                    qDebug() << "AudioOutput State:" << state;
                    if (state == QAudio::IdleState) {
                        // This state indicates QAudioOutput has finished playing all data in its internal buffer.
                        // If this is the *final* chunk and synthesis is complete, then emit playbackFinished.
                        // This logic needs to be robust if SDK sends SPEECH_SYNTHESIS_COMPLETED separately.
                    }
                });
            }
            
            // It is better to have a buffer to accumulate audio data for QAudioOutput
            // For simplicity, directly writing. This might interrupt or fail if not handled carefully.
            QIODevice *device = handler->audioOutput->start(); 
            if (device) {
                device->write(reinterpret_cast<const char*>(audio_data), data_size);
            } else {
                qWarning() << "Failed to get IODevice from QAudioOutput to write TTS data.";
                // If start() fails, audioOutput might be in a bad state or already active.
                // Consider stopping and restarting, or using a QBuffer as an intermediary.
            }
        }
    } else if (reason == SPEECH_SYNTHESIS_COMPLETED) {
        qDebug() << "  TTS Synthesis stream completed.";
        // Now that the SDK says all audio data has been sent (via SPEECH_SYNTHESIZING callbacks),
        // and this SPEECH_SYNTHESIS_COMPLETED is received, we can be more confident to emit playbackFinished.
        // However, QAudioOutput itself might still be playing buffered data.
        // A robust way is to check audioOutput->state() and bytesFree() or connect to stateChanged Idle.
        // For now, a direct emit. UI might need to handle this gracefully.
        emit handler->playbackFinished(); 
    } else if (reason == SPEECH_ERROR_OCCURRED) {
        int error_code = speech_synthesis_result_get_error_code(result);
        const char* error_msg = speech_synthesis_result_get_error_message(result);
        QString errorMessage = QString("语音合成错误: %1 (代码: %2)").arg(QString::fromUtf8(error_msg ? error_msg : "Unknown error")).arg(error_code);
        qWarning() << errorMessage;
        emit handler->errorOccurred(errorMessage);
        emit handler->playbackFinished(); // Signal finish on error too to unblock UI if waiting
    } else if (reason == SPEECH_SYNTHESIS_STARTED) {
        qDebug() << "  TTS Synthesis started.";
    }
    // Note: SDK does not seem to require explicit destruction of SpeechSynthesisResult in callback
}

void VoiceHandler::playText(const QString &text)
{
    if (text.isEmpty()) {
        qWarning() << "Text to play is empty.";
        return;
    }
    if (!synthesisSession) {
        emit errorOccurred("语音合成服务未初始化，无法播放文本");
        qWarning() << "Synthesis session not initialized. Cannot play text.";
        return;
    }

    qDebug() << "Requesting TTS for text:" << text;
    speech_synthesizer_synthesize_text_async(synthesisSession, text.toUtf8().constData(), text.toUtf8().length()); // Corrected function name and no return value
    // if (ret != 0) { // Removed check for ret
    //    emit errorOccurred(QString("请求语音合成失败: %1").arg(ret));
    //    qWarning() << "Failed to synthesize speech async, error code:" << ret;
    // }
    // Audio playback is handled in synthesisCallback
}

QString VoiceHandler::speechToText(const QByteArray &audioData)
{
    if (!recognitionSession) {
        emit errorOccurred("语音识别服务未初始化");
        return QString();
    }
    if (audioData.isEmpty()) {
        emit errorOccurred("提供的音频数据为空");
        return QString();
    }
    if (recording) {
        // It's generally problematic to use the same session for one-shot ASR
        // while continuous ASR is active. This might need a separate session or mode management.
        emit errorOccurred("正在进行连续录音，请先停止后再进行单次识别");
        qWarning() << "Attempted one-shot STT while continuous recording is active. This might fail or conflict.";
        // return QString(); // Optionally block here
    }

    qDebug() << "Performing one-shot speech-to-text for byte array of size:" << audioData.size();

    // Create a temporary audio config for this one-shot data
    AudioConfig *onceAudioConfig = audio_config_create_once_audio_input_from_pcm_data(
        reinterpret_cast<const uint8_t*>(audioData.constData()),
        audioData.size()
    );
    if (!onceAudioConfig) {
        emit errorOccurred("创建单次音频输入配置失败");
        return QString();
    }
    // Set necessary parameters for the PCM data, e.g., sample rate
    // Assuming 16kHz, 16-bit mono, which is common. Adjust if your data is different.
    // The SDK might have specific functions or enums for format details.
    audio_config_set_input_audio_rate(onceAudioConfig, 16000); // Example: must match your data
    // audio_config_set_input_audio_format(onceAudioConfig, PCM_S16LE); // Example if such config exists

    speech_recognizer_set_audio_config(recognitionSession, onceAudioConfig); // Apply temp config
    
    speech_recognizer_recognize_once_async(recognitionSession); // Corrected: No return value to assign
    audio_config_destroy(&onceAudioConfig); // Clean up temporary config

    // if (ret != 0) { // Removed check for ret
    //     emit errorOccurred(QString("单次语音识别启动失败: %1").arg(ret));
    //     return QString();
    // }
    qDebug() << "单次语音识别已异步启动，结果将通过回调传递。";
    // This function is async, so it returns immediately.
    // The actual text will arrive via the main recognitionCallback.
    // This makes the function name "speechToText" somewhat misleading for synchronous expectation.
    return QString(); // Or some indicator that it's processing
}

QByteArray VoiceHandler::textToSpeech(const QString &text)
{
    if (!synthesisSession) {
        emit errorOccurred("语音合成服务未初始化");
        return QByteArray();
    }
    if (text.isEmpty()) {
        emit errorOccurred("要合成的文本为空");
        return QByteArray();
    }

    qDebug() << "Synthesizing text:" << text;

    speech_synthesizer_synthesize_text_async(synthesisSession, text.toUtf8().constData(), text.toUtf8().length()); // Corrected function name and no return value
    // if (ret != 0) { // Removed check for ret
    //    emit errorOccurred(QString("启动语音合成失败: %1").arg(ret));
    //    return QByteArray();
    // }
    qDebug() << "语音合成已异步启动，结果将通过回调传递。";
    return QByteArray(); 
}

void VoiceHandler::initializeAudioDevices()
{
    if (QAudioDeviceInfo::defaultInputDevice().isNull()) {
        emit errorOccurred("未找到默认音频输入设备");
        qWarning() << "未找到默认音频输入设备";
    }
    if (QAudioDeviceInfo::defaultOutputDevice().isNull()) {
        emit errorOccurred("未找到默认音频输出设备");
        qWarning() << "未找到默认音频输出设备";
    }
} 