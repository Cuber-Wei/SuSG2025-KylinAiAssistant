#ifndef CHATCORE_H
#define CHATCORE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <memory>

// 麒麟AI SDK头文件
#include <genai/text/chat.h>
#include <genai/text/config.h>
#include <genai/text/result.h>

// 消息结构体
struct Message {
    QString content;
    bool isUser;
    QString timestamp;
    QString role;  // 用于标识消息来源的角色
    QString model;  // 使用的模型名称
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

    // 设置模型配置
    void setModelConfig(const QString &modelName, ModelDeployType deployType = ModelDeployType::PublicCloud);
    
    // 设置系统提示词
    void setSystemPrompt(const QString &prompt);
    
    // 停止当前对话
    void stopChat();

signals:
    // 收到新消息时发出信号
    void messageReceived(const Message &message);
    // 发生错误时发出信号
    void errorOccurred(const QString &error);
    // SDK初始化状态
    void initializationStatus(bool success, const QString &message);
    // 对话状态变化
    void chatStateChanged(bool isProcessing);

private:
    class ChatCorePrivate;
    std::unique_ptr<ChatCorePrivate> d;
    
    // 处理SDK错误
    void handleSDKError(int errorCode, const QString &errorMessage);
    
    // 回调处理函数
    static void handleChatResult(ChatResult *result, void *userData);
};

#endif // CHATCORE_H 