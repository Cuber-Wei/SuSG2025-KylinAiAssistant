#include "voicehandler.h"
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <kylin-ai/common/enums.h>

VoiceHandler::VoiceHandler(QObject *parent)
    : QObject(parent)
    , audioOutput(nullptr)
    , recording(false)
    , recognitionSession(nullptr)
    , synthesisSession(nullptr)
    , audioConfig(nullptr)
    , modelConfig(nullptr)
{
    initializeAudioDevices();
}

VoiceHandler::~VoiceHandler()
{

    if (audioOutput) {
        audioOutput->stop();
        delete audioOutput;
    }
    
    // 清理语音识别和合成会话
    if (recognitionSession) {
        speech_recognizer_destroy_session(&recognitionSession); 
    }
    if (synthesisSession) {
        speech_synthesizer_destroy_session(&synthesisSession); 
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
    // 1. 创建并设置语音识别器的音频配置
    audioConfig = audio_config_create_continuous_audio_input_from_default_microphone();
    if (!audioConfig) {
        emit errorOccurred("创建连续音频输入配置失败");
        return false;
    }
    // 设置采样率为16kHz
    audio_config_set_input_audio_rate(audioConfig, 16000);

    // 2. 创建并设置模型配置
    modelConfig = speech_model_config_create();
    if (!modelConfig) {
        emit errorOccurred("创建语音模型配置失败");
        return false;
    }

    // 配置讯飞语音大模型
    const char* xunfeiAsrModelName = "讯⻜-语⾳⼤模型"; 
    speech_model_config_set_name(modelConfig, xunfeiAsrModelName); 
    speech_model_config_set_deploy_type(modelConfig, PublicCloud);

    // 3. 初始化语音识别会话
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

    speech_recognizer_set_audio_config(recognitionSession, audioConfig);
    speech_recognizer_set_model_config(recognitionSession, modelConfig);
    speech_recognizer_result_set_callback(recognitionSession, recognitionCallback, this);

    // 4. 初始化语音合成会话
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

    // 配置合成器
    AudioConfig *synthAudioOutputConfig = audio_config_create_audio_output_from_default_speaker();
    if (!synthAudioOutputConfig) {
        emit errorOccurred("创建语音合成默认扬声器输出配置失败");
    } else {
        speech_synthesizer_set_audio_config(synthesisSession, synthAudioOutputConfig);
        audio_config_destroy(&synthAudioOutputConfig);
    }
    
    speech_synthesizer_set_model_config(synthesisSession, modelConfig);
    speech_synthesizer_result_set_callback(synthesisSession, synthesisCallback, this);

    return true;
}

bool VoiceHandler::startRecording()
{
    if (recording) {
        return false;
    }
    if (!recognitionSession) {
        emit errorOccurred("语音识别服务未初始化，无法开始录音");
        return false;
    }

    accumulatedRecognizedText.clear();
    speech_recognizer_start_continuous_recognition_async(recognitionSession);
    recording = true;
    emit recordingStarted();
    return true;
}

void VoiceHandler::stopRecording()
{
    if (!recording) {
        return;
    }
    if (!recognitionSession) {
        emit errorOccurred("语音识别服务未初始化，无法停止录音");
        return;
    }

    speech_recognizer_stop_continuous_recognition_async(recognitionSession); 
    recording = false;

    if (!accumulatedRecognizedText.isEmpty()) {
        emit textRecognized(accumulatedRecognizedText);
    }

    emit recordingStopped();
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

    if (reason == SPEECH_RECOGNIZED) {
        if (text) {
            QString recognizedSegment = QString::fromUtf8(text);
            if (!recognizedSegment.isEmpty()) {
                if (!handler->accumulatedRecognizedText.isEmpty()) {
                    handler->accumulatedRecognizedText.append(" ");
                }
                handler->accumulatedRecognizedText.append(recognizedSegment);
            }
        }
    } else if (reason == SPEECH_ERROR_OCCURRED) {
        int error_code = speech_recognition_result_get_error_code(result);
        const char* error_msg = speech_recognition_result_get_error_message(result);
        QString errorMessage = QString("语音识别错误: %1 (代码: %2)")
            .arg(QString::fromUtf8(error_msg ? error_msg : "Unknown error"))
            .arg(error_code);
        emit handler->errorOccurred(errorMessage);
    }
}

void VoiceHandler::synthesisCallback(SpeechSynthesisResult *result, void *userData)
{
    VoiceHandler *handler = static_cast<VoiceHandler*>(userData);
    if (!handler || !result) return;

    SpeechResultReason reason = speech_synthesis_result_get_reason(result);

    if (reason == SPEECH_SYNTHESIZING) {
        uint32_t data_size = 0;
        const uint8_t *audio_data = speech_synthesis_result_get_data(result, &data_size);
        
        if (audio_data && data_size > 0) {
            if (!handler->audioOutput) { 
                QAudioFormat format;
                format.setSampleRate(speech_synthesis_result_get_audio_rate(result)); 
                format.setChannelCount(speech_synthesis_result_get_audio_channel(result));
                format.setSampleSize(16);
                format.setCodec("audio/pcm");
                format.setByteOrder(QAudioFormat::LittleEndian);
                format.setSampleType(QAudioFormat::SignedInt);

                QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
                if (!info.isFormatSupported(format)) {
                    format = info.nearestFormat(format);
                }
                if (format.sampleRate() == 0) {
                    format.setSampleRate(16000);
                }
                if (format.channelCount() == 0) {
                    format.setChannelCount(1);
                }

                handler->audioOutput = new QAudioOutput(format, handler);
                handler->connect(handler->audioOutput, &QAudioOutput::stateChanged, 
                    [handler](QAudio::State state){
                    if (state == QAudio::IdleState) {
                        emit handler->playbackFinished();
                    }
                });
            }
            
            QIODevice *device = handler->audioOutput->start(); 
            if (device) {
                device->write(reinterpret_cast<const char*>(audio_data), data_size);
            } else {
                emit handler->errorOccurred("无法播放语音合成音频");
            }
        }
    } else if (reason == SPEECH_SYNTHESIS_COMPLETED) {
        emit handler->playbackFinished(); 
    } else if (reason == SPEECH_ERROR_OCCURRED) {
        int error_code = speech_synthesis_result_get_error_code(result);
        const char* error_msg = speech_synthesis_result_get_error_message(result);
        QString errorMessage = QString("语音合成错误: %1 (代码: %2)")
            .arg(QString::fromUtf8(error_msg ? error_msg : "Unknown error"))
            .arg(error_code);
        emit handler->errorOccurred(errorMessage);
        emit handler->playbackFinished();
    }
    // Note: SDK does not seem to require explicit destruction of SpeechSynthesisResult in callback
}

void VoiceHandler::playText(const QString &text)
{
    if (text.isEmpty()) {
        return;
    }
    if (!synthesisSession) {
        emit errorOccurred("语音合成服务未初始化，无法播放文本");
        return;
    }

    speech_synthesizer_synthesize_text_async(synthesisSession, text.toUtf8().constData(), text.toUtf8().length());
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
        emit errorOccurred("正在进行连续录音，请先停止后再进行单次识别");
        return QString();
    }

    AudioConfig *onceAudioConfig = audio_config_create_once_audio_input_from_pcm_data(
        reinterpret_cast<const uint8_t*>(audioData.constData()),
        audioData.size()
    );
    if (!onceAudioConfig) {
        emit errorOccurred("创建单次音频输入配置失败");
        return QString();
    }

    audio_config_set_input_audio_rate(onceAudioConfig, 16000);
    speech_recognizer_set_audio_config(recognitionSession, onceAudioConfig);
    speech_recognizer_recognize_once_async(recognitionSession);
    audio_config_destroy(&onceAudioConfig);

    return QString();
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

    speech_synthesizer_synthesize_text_async(synthesisSession, text.toUtf8().constData(), text.toUtf8().length());
    return QByteArray();
}

void VoiceHandler::initializeAudioDevices()
{
    if (QAudioDeviceInfo::defaultInputDevice().isNull()) {
        emit errorOccurred("未找到默认音频输入设备");
    }
    if (QAudioDeviceInfo::defaultOutputDevice().isNull()) {
        emit errorOccurred("未找到默认音频输出设备");
    }
} 