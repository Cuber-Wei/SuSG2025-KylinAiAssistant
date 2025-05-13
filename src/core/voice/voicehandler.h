#ifndef VOICEHANDLER_H
#define VOICEHANDLER_H

#include <QObject>
#include <QString>
#include <QAudioInput>
#include <QAudioOutput>
#include <QBuffer>

class VoiceHandler : public QObject
{
    Q_OBJECT

public:
    explicit VoiceHandler(QObject *parent = nullptr);
    ~VoiceHandler();

    // 开始录音
    bool startRecording();
    
    // 停止录音
    void stopRecording();
    
    // 是否正在录音
    bool isRecording() const;
    
    // 播放文本
    void playText(const QString &text);
    
    // 将语音转换为文本
    QString speechToText(const QByteArray &audioData);
    
    // 将文本转换为语音
    QByteArray textToSpeech(const QString &text);

signals:
    void recordingStarted();
    void recordingStopped();
    void textRecognized(const QString &text);
    void playbackFinished();
    void errorOccurred(const QString &error);

private:
    QAudioInput *audioInput;
    QAudioOutput *audioOutput;
    QBuffer audioBuffer;
    bool recording;
    
    // 初始化音频设备
    void initializeAudioDevices();
    
    // 处理录音数据
    void processAudioData();
};

#endif // VOICEHANDLER_H 