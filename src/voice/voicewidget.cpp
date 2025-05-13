#include "voicewidget.h"
#include <QDateTime>
#include <QMessageBox>
#include <QAudioDeviceInfo>

VoiceWidget::VoiceWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupAudio();
    setupConnections();
}

void VoiceWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    m_voiceDisplay = new QTextEdit(this);
    m_voiceDisplay->setReadOnly(true);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_recordButton = new QPushButton(tr("开始录音"), this);
    m_playButton = new QPushButton(tr("播放回复"), this);
    m_playButton->setEnabled(false);

    buttonLayout->addWidget(m_recordButton);
    buttonLayout->addWidget(m_playButton);

    mainLayout->addWidget(m_voiceDisplay);
    mainLayout->addLayout(buttonLayout);
}

void VoiceWidget::setupAudio()
{
    m_audioRecorder = new QAudioRecorder(this);

    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioSettings.setSampleRate(16000);
    audioSettings.setChannelCount(1);
    audioSettings.setBitRate(128000);

    m_audioRecorder->setEncodingSettings(audioSettings);
    m_audioRecorder->setContainerFormat("wav");
}

void VoiceWidget::setupConnections()
{
    connect(m_recordButton, &QPushButton::clicked, this, &VoiceWidget::startRecording);
    connect(m_playButton, &QPushButton::clicked, this, &VoiceWidget::playResponse);
    connect(m_audioRecorder, &QAudioRecorder::stateChanged,
            this, &VoiceWidget::onRecordingStateChanged);
    connect(m_audioRecorder, &QAudioRecorder::error,
            this, &VoiceWidget::onRecordingError);
}

void VoiceWidget::startRecording()
{
    if (m_audioRecorder->state() == QAudioRecorder::RecordingState) {
        stopRecording();
        return;
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    m_currentRecording = QString("recording_%1.wav").arg(timestamp);
    m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(m_currentRecording));
    m_audioRecorder->record();

    m_recordButton->setText(tr("停止录音"));
    m_voiceDisplay->append(tr("<p style='color:blue;'>开始录音...</p>"));
}

void VoiceWidget::stopRecording()
{
    m_audioRecorder->stop();
    m_recordButton->setText(tr("开始录音"));
    m_voiceDisplay->append(tr("<p style='color:blue;'>录音结束</p>"));

    // TODO: 发送录音文件到语音识别服务
    // 这里需要实现语音识别和AI响应的处理
}

void VoiceWidget::playResponse()
{
    // TODO: 实现语音合成和播放功能
    m_voiceDisplay->append(tr("<p style='color:green;'>播放AI回复...</p>"));
}

void VoiceWidget::onRecordingStateChanged(QAudioRecorder::State state)
{
    switch (state) {
        case QAudioRecorder::RecordingState:
            m_playButton->setEnabled(false);
            break;
        case QAudioRecorder::StoppedState:
            m_playButton->setEnabled(true);
            break;
        default:
            break;
    }
}

void VoiceWidget::onRecordingError(QAudioRecorder::Error error)
{
    QString errorMessage;
    switch (error) {
        case QAudioRecorder::ResourceError:
            errorMessage = tr("录音设备被占用或不可用");
            break;
        case QAudioRecorder::FormatError:
            errorMessage = tr("不支持的音频格式");
            break;
        default:
            errorMessage = tr("未知错误");
            break;
    }

    QMessageBox::warning(this, tr("录音错误"), errorMessage);
    m_recordButton->setText(tr("开始录音"));
    m_playButton->setEnabled(false);
} 