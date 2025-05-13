#ifndef VOICEWIDGET_H
#define VOICEWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QAudioInput>
#include <QAudioOutput>
#include <QMediaRecorder>
#include <QAudioRecorder>
#include <QAudioFormat>

class VoiceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VoiceWidget(QWidget *parent = nullptr);

private slots:
    void startRecording();
    void stopRecording();
    void playResponse();
    void onRecordingStateChanged(QAudioRecorder::State state);
    void onRecordingError(QAudioRecorder::Error error);

private:
    void setupUI();
    void setupAudio();
    void setupConnections();

    QTextEdit *m_voiceDisplay;
    QPushButton *m_recordButton;
    QPushButton *m_playButton;
    QAudioRecorder *m_audioRecorder;
    QString m_currentRecording;
};

#endif // VOICEWIDGET_H 