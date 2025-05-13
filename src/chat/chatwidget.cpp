#include "chatwidget.h"
#include <QScrollBar>
#include <QDateTime>

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupConnections();
}

void ChatWidget::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 左侧角色列表
    m_roleList = new QListWidget(this);
    m_roleList->setMaximumWidth(200);
    m_roleList->addItems({"律师", "教师", "程序员", "作家"});

    // 右侧聊天区域
    QWidget *chatArea = new QWidget(this);
    QVBoxLayout *chatLayout = new QVBoxLayout(chatArea);

    m_chatDisplay = new QTextEdit(this);
    m_chatDisplay->setReadOnly(true);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    m_messageInput = new QLineEdit(this);
    m_sendButton = new QPushButton(tr("发送"), this);

    inputLayout->addWidget(m_messageInput);
    inputLayout->addWidget(m_sendButton);

    chatLayout->addWidget(m_chatDisplay);
    chatLayout->addLayout(inputLayout);

    mainLayout->addWidget(m_roleList);
    mainLayout->addWidget(chatArea);
}

void ChatWidget::setupConnections()
{
    connect(m_sendButton, &QPushButton::clicked, this, &ChatWidget::sendMessage);
    connect(m_messageInput, &QLineEdit::returnPressed, this, &ChatWidget::sendMessage);
    connect(m_roleList, &QListWidget::currentRowChanged, this, &ChatWidget::onRoleChanged);
}

void ChatWidget::sendMessage()
{
    QString message = m_messageInput->text().trimmed();
    if (message.isEmpty())
        return;

    // 显示用户消息
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_chatDisplay->append(QString("<p style='color:blue;'>[%1] 我: %2</p>")
                         .arg(timestamp, message));

    // 清空输入框
    m_messageInput->clear();

    // TODO: 发送消息到AI服务并获取响应
    // 这里需要实现与AI服务的通信
}

void ChatWidget::onRoleChanged(int index)
{
    // TODO: 切换角色时的处理逻辑
    QString roleName = m_roleList->item(index)->text();
    m_chatDisplay->append(QString("<p style='color:gray;'>已切换到%1角色</p>").arg(roleName));
}

void ChatWidget::onMessageReceived(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_chatDisplay->append(QString("<p style='color:green;'>[%1] AI: %2</p>")
                         .arg(timestamp, message));

    // 自动滚动到底部
    m_chatDisplay->verticalScrollBar()->setValue(
        m_chatDisplay->verticalScrollBar()->maximum()
    );
} 