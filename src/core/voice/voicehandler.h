#ifndef VOICEHANDLER_H
#define VOICEHANDLER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtMultimedia/QAudioOutput> 

// 麒麟AI SDK头文件
#include <kylin-ai/coreai/speech/recognizer.h>
#include <kylin-ai/coreai/speech/synthesizer.h>
#include <kylin-ai/coreai/speech/audioconfig.h> 
#include <kylin-ai/coreai/speech/config.h>      
#include <kylin-ai/common/enums.h>            
#include <kylin-ai/coreai/speech/result.h>      

class QAudioOutput;

class VoiceHandler : public QObject
{
    Q_OBJECT
public:
    explicit VoiceHandler(QObject *parent = nullptr);
    ~VoiceHandler();

    // UI交互方法
    Q_INVOKABLE bool startRecording();         // 开始录音
    Q_INVOKABLE void stopRecording();          // 停止录音
    Q_INVOKABLE bool isRecording() const;      // 检查是否在录音
    Q_INVOKABLE void playText(const QString &text); // 语音合成播放文本

    // 单次语音识别和合成方法
    Q_INVOKABLE QString speechToText(const QByteArray &audioData); // 单次语音识别
    Q_INVOKABLE QByteArray textToSpeech(const QString &text);      // 单次语音合成

signals:
    void recordingStarted();      // 录音开始信号
    void recordingStopped();      // 录音停止信号
    void textRecognized(const QString &text); // 语音识别结果信号
    void errorOccurred(const QString &errorMessage); // 错误信号
    void playbackFinished(); // 播放完成信号

private slots:
    void initializeAudioDevices(); // 初始化音频设备

private:
    bool initializeSpeechServices(); // 初始化语音服务

    // SDK回调函数
    static void recognitionCallback(SpeechRecognitionResult *result, void *userData);
    static void synthesisCallback(SpeechSynthesisResult *result, void *userData);

    // 成员变量
    QAudioOutput *audioOutput;  // 音频输出设备
    bool recording;             // 录音状态标志

    // 麒麟AI SDK会话和配置
    SpeechRecognitionSession *recognitionSession; // 语音识别会话
    SpeechSynthesizerSession *synthesisSession;   // 语音合成会话
    AudioConfig *audioConfig;       // 语音识别的音频配置 
    SpeechModelConfig *modelConfig; // 语音模型配置
    QString accumulatedRecognizedText; // 累积的识别文本
};

#endif // VOICEHANDLER_H 