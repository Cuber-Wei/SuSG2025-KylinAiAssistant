#ifndef VOICEHANDLER_H
#define VOICEHANDLER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QByteArray>
// #include <QtMultimedia/QAudioInput> // Commented out
#include <QtMultimedia/QAudioOutput> // For TTS playback
// #include <QtCore/QBuffer> // Commented out

// Kylin AI SDK Headers
#include <kylin-ai/coreai/speech/recognizer.h>
#include <kylin-ai/coreai/speech/synthesizer.h>
#include <kylin-ai/coreai/speech/audioconfig.h> // Defines AudioConfig
#include <kylin-ai/coreai/speech/config.h>      // Defines SpeechModelConfig
#include <kylin-ai/common/enums.h>            // For ModelDeployType etc.
#include <kylin-ai/coreai/speech/result.h>      // For SpeechRecognitionResult, SpeechSynthesisResult

// class QAudioInput; // Commented out: Forward declaration not needed if member is removed
// class QBuffer;     // Commented out: Forward declaration not needed if member is removed
class QAudioOutput; // Forward declaration for TTS audio output

class VoiceHandler : public QObject
{
    Q_OBJECT
public:
    explicit VoiceHandler(QObject *parent = nullptr);
    ~VoiceHandler();

    // Q_INVOKABLE methods for UI interaction
    Q_INVOKABLE bool startRecording();
    Q_INVOKABLE void stopRecording();
    Q_INVOKABLE bool isRecording() const;
    Q_INVOKABLE void playText(const QString &text); // For TTS

    // These synchronous wrappers might need review for thread-safety and SDK usage patterns,
    // especially if recognitionSession is used for continuous ASR.
    Q_INVOKABLE QString speechToText(const QByteArray &audioData); // One-shot STT
    Q_INVOKABLE QByteArray textToSpeech(const QString &text);     // One-shot TTS

signals:
    void recordingStarted();
    void recordingStopped();
    void textRecognized(const QString &text); // From continuous ASR
    void errorOccurred(const QString &errorMessage);
    void playbackFinished(); // For TTS

private slots:
    void initializeAudioDevices(); // General check for audio device availability
    // void processAudioData(); // Removed: Was tied to QAudioInput data chunks

private:
    bool initializeSpeechServices(); // Initializes SDK sessions

    // Static Callbacks for SDK
    static void recognitionCallback(SpeechRecognitionResult *result, void *userData);
    static void synthesisCallback(SpeechSynthesisResult *result, void *userData);

    // Member Variables
    // QAudioInput *audioInput;    // Commented out: No longer using QAudioInput for continuous ASR
    // QBuffer audioBuffer;        // Commented out: No longer using QBuffer for continuous ASR
    QAudioOutput *audioOutput;  // For TTS audio playback
    bool recording;             // State flag for recording status

    // Kylin AI SDK Sessions and Configurations
    SpeechRecognitionSession *recognitionSession;
    SpeechSynthesizerSession *synthesisSession;
    AudioConfig *audioConfig;       // Configuration for recognizer (continuous from mic)
    SpeechModelConfig *modelConfig; // Configuration for speech models (ASR & TTS)
    QString accumulatedRecognizedText; // Added to accumulate recognized text
};

#endif // VOICEHANDLER_H 