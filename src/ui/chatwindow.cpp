#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QMessageBox>

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatWindow)
    , chatCore(new ChatCore(this))
    , voiceHandler(new VoiceHandler(this))
{
    ui->setupUi(this);
    setupConnections();
    updateRoleList();
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::setCurrentRole(const QString &roleName)
{
    currentRole = roleName;
    // 更新UI显示当前选中的角色
    QList<QListWidgetItem*> items = ui->roleList->findItems(roleName, Qt::MatchExactly);
    if (!items.isEmpty()) {
        ui->roleList->setCurrentItem(items.first());
    }
}

void ChatWindow::setupConnections()
{
    // 连接按钮信号
    connect(ui->sendButton, &QPushButton::clicked, this, &ChatWindow::onSendButtonClicked);
    connect(ui->voiceButton, &QPushButton::clicked, this, &ChatWindow::onVoiceButtonClicked);
    
    // 连接角色列表信号
    connect(ui->roleList, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        onRoleSelected(item->text());
    });
    
    // 连接核心功能信号
    connect(chatCore, &ChatCore::messageReceived, this, &ChatWindow::handleMessageReceived);
    connect(chatCore, &ChatCore::errorOccurred, this, &ChatWindow::handleError);
    
    // 连接语音处理信号
    connect(voiceHandler, &VoiceHandler::textRecognized, this, &ChatWindow::handleTextRecognized);
}

void ChatWindow::onSendButtonClicked()
{
    QString message = ui->messageInput->text().trimmed();
    if (message.isEmpty()) {
        return;
    }
    
    // 显示用户消息
    appendMessage("我", message);
    ui->messageInput->clear();
    
    // 发送消息到核心处理
    QString response = chatCore->sendMessage(message, currentRole);
    appendMessage(currentRole, response);
}

void ChatWindow::onVoiceButtonClicked()
{
    if (voiceHandler->isRecording()) {
        voiceHandler->stopRecording();
        ui->voiceButton->setText("语音");
    } else {
        voiceHandler->startRecording();
        ui->voiceButton->setText("停止");
    }
}

void ChatWindow::onRoleSelected(const QString &roleName)
{
    currentRole = roleName;
}

void ChatWindow::handleMessageReceived(const QString &message)
{
    appendMessage(currentRole, message);
}

void ChatWindow::handleError(const QString &error)
{
    QMessageBox::warning(this, "错误", error);
}

void ChatWindow::handleTextRecognized(const QString &text)
{
    ui->messageInput->setText(text);
}

void ChatWindow::appendMessage(const QString &sender, const QString &message)
{
    ui->chatDisplay->append(QString("<b>%1:</b> %2").arg(sender, message));
}

void ChatWindow::updateRoleList()
{
    // TODO: 从角色管理器获取角色列表并更新UI
    ui->roleList->clear();
    ui->roleList->addItem("默认");
    ui->roleList->addItem("律师");
    ui->roleList->addItem("教师");
    ui->roleList->addItem("程序员");
    ui->roleList->addItem("作家");
} 