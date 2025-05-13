#include "chatcore.h"
#include <QDateTime>
#include <QDebug>

class ChatCore::ChatCorePrivate {
public:
    QVector<Message> messageHistory;
    QString currentRole;
    KylinAISDK* sdk;  // 麒麟AI SDK实例
    bool isInitialized;
    
    ChatCorePrivate() : sdk(nullptr), isInitialized(false) {}
    ~ChatCorePrivate() {
        if (sdk) {
            sdk->cleanup();
            delete sdk;
        }
    }
};

ChatCore::ChatCore(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ChatCorePrivate>())
{
    d->currentRole = "default";
}

ChatCore::~ChatCore() = default;

bool ChatCore::initialize()
{
    try {
        // 创建SDK实例
        d->sdk = new KylinAISDK();
        
        // 初始化SDK
        int result = d->sdk->initialize();
        if (result != 0) {
            handleSDKError(result, "SDK初始化失败");
            return false;
        }
        
        d->isInitialized = true;
        emit initializationStatus(true, "SDK初始化成功");
        return true;
    } catch (const std::exception& e) {
        handleSDKError(-1, QString("SDK初始化异常: %1").arg(e.what()));
        return false;
    }
}

void ChatCore::sendMessage(const QString &message, const QString &role)
{
    if (!d->isInitialized) {
        emit errorOccurred("SDK未初始化");
        return;
    }

    try {
        // 创建用户消息
        Message userMsg;
        userMsg.content = message;
        userMsg.isUser = true;
        userMsg.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        userMsg.role = role;
        
        // 添加到历史记录
        d->messageHistory.append(userMsg);
        
        // 准备发送给SDK的消息
        KylinAIMessage aiMessage;
        aiMessage.content = message.toStdString();
        aiMessage.role = role.toStdString();
        
        // 调用SDK处理消息
        KylinAIResponse response;
        int result = d->sdk->processMessage(aiMessage, response);
        
        if (result != 0) {
            handleSDKError(result, "消息处理失败");
            return;
        }
        
        // 创建AI回复消息
        Message aiMsg;
        aiMsg.content = QString::fromStdString(response.content);
        aiMsg.isUser = false;
        aiMsg.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        aiMsg.role = d->currentRole;
        
        // 添加到历史记录
        d->messageHistory.append(aiMsg);
        
        // 发出消息接收信号
        emit messageReceived(aiMsg);
        
    } catch (const std::exception& e) {
        handleSDKError(-1, QString("消息处理异常: %1").arg(e.what()));
    }
}

QVector<Message> ChatCore::getHistory() const
{
    return d->messageHistory;
}

void ChatCore::clearHistory()
{
    d->messageHistory.clear();
}

void ChatCore::setCurrentRole(const QString &role)
{
    d->currentRole = role;
}

void ChatCore::handleSDKError(int errorCode, const QString &errorMessage)
{
    QString fullMessage = QString("错误代码: %1, 错误信息: %2").arg(errorCode).arg(errorMessage);
    qWarning() << fullMessage;
    emit errorOccurred(fullMessage);
} 