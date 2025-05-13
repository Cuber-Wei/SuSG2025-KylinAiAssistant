#include "voicehandler.h"
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QFile>
#include <QDir>

VoiceHandler::VoiceHandler(QObject *parent)
    : QObject(parent)
    , audioInput(nullptr)
    , audioOutput(nullptr)
    , audioBuffer(new QBuffer(this))
{
    initializeAudioDevices();
}

VoiceHandler::~VoiceHandler()
{
    if (audioInput) {
        audioInput->stop();
        delete audioInput;
    }
    if (audioOutput) {
        audioOutput->stop();
        delete audioOutput;
    }
    delete audioBuffer;
}

void VoiceHandler::startRecording()
{
    if (!audioInput) {
        emit errorOccurred("音频输入设备未初始化");
        return;
    }
    
    audioBuffer->open(QIODevice::WriteOnly);
    audioInput->start(audioBuffer);
    emit recordingStarted();
}

void VoiceHandler::stopRecording()
{
    if (!audioInput) {
        return;
    }
    
    audioInput->stop();
    audioBuffer->close();
    
    // 处理录制的音频数据
    QByteArray audioData = audioBuffer->data();
    QString text = speechToText(audioData);
    emit textRecognized(text);
    emit recordingStopped();
}

void VoiceHandler::playText(const QString &text)
{
    // 将文本转换为语音
    QByteArray audioData = textToSpeech(text);
    
    if (audioData.isEmpty()) {
        emit errorOccurred("语音合成失败");
        return;
    }
    
    // 播放语音
    audioBuffer->setData(audioData);
    audioBuffer->open(QIODevice::ReadOnly);
    audioOutput->start(audioBuffer);
}

QString VoiceHandler::speechToText(const QByteArray &audioData)
{
    // TODO: 实现语音识别功能
    // 这里需要调用麒麟AI SDK的语音识别API
    
    // 临时返回一个模拟的识别结果
    return "这是语音识别的结果";
}

QByteArray VoiceHandler::textToSpeech(const QString &text)
{
    // TODO: 实现语音合成功能
    // 这里需要调用麒麟AI SDK的语音合成API
    
    // 临时返回一个空的音频数据
    return QByteArray();
}

void VoiceHandler::initializeAudioDevices()
{
    // 设置音频格式
    QAudioFormat format;
    format.setSampleRate(16000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    
    // 检查音频设备是否支持该格式
    QAudioDeviceInfo inputInfo = QAudioDeviceInfo::defaultInputDevice();
    if (!inputInfo.isFormatSupported(format)) {
        format = inputInfo.nearestFormat(format);
    }
    
    // 初始化音频输入设备
    audioInput = new QAudioInput(format, this);
    
    // 初始化音频输出设备
    audioOutput = new QAudioOutput(format, this);
    
    // 连接信号
    connect(audioOutput, &QAudioOutput::stateChanged, [this](QAudio::State state) {
        if (state == QAudio::IdleState) {
            audioBuffer->close();
            emit playbackFinished();
        }
    });
}

void VoiceHandler::processAudioData(const QByteArray &data)
{
    // TODO: 实现音频数据处理
    // 这里可以对录制的音频数据进行预处理
} 