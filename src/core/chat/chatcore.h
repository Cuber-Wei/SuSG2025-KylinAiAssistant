#ifndef CHATCORE_H
#define CHATCORE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>
#include <kylin_ai_sdk.h>  // 麒麟AI SDK头文件

// 消息结构体
struct Message {
    QString content;
    bool isUser;
    QString timestamp;
    QString role;  // 用于标识消息来源的角色
};

class ChatCore : public QObject
{
    Q_OBJECT

public:
    explicit ChatCore(QObject *parent = nullptr);
    ~ChatCore();

    // 初始化SDK
    bool initialize();
    
    // 发送消息并获取回复
    void sendMessage(const QString &message, const QString &role = "default");
    
    // 获取历史消息
    QVector<Message> getHistory() const;
    
    // 清空历史消息
    void clearHistory();
    
    // 设置当前角色
    void setCurrentRole(const QString &role);

signals:
    // 收到新消息时发出信号
    void messageReceived(const Message &message);
    // 发生错误时发出信号
    void errorOccurred(const QString &error);
    // SDK初始化状态
    void initializationStatus(bool success, const QString &message);

private:
    class ChatCorePrivate;
    std::unique_ptr<ChatCorePrivate> d;
    
    // 处理SDK错误
    void handleSDKError(int errorCode, const QString &errorMessage);
};

#endif // CHATCORE_H 