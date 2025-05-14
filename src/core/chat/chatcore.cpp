#include "chatcore.h"
#include <QDateTime>

class ChatCore::ChatCorePrivate {
public:
    QVector<Message> messageHistory;
    QString currentRole;
    QString currentModel;
    GenAiTextSession* session;
    ChatModelConfig* modelConfig;
    bool isInitialized;
    bool isProcessing;
    QString currentResponse; // 用于收集完整的回答
    
    ChatCorePrivate() 
        : session(nullptr)
        , modelConfig(nullptr)
        , isInitialized(false)
        , isProcessing(false)
    {}
    
    ~ChatCorePrivate() {
        if (session) {
            genai_text_destroy_session(&session);
        }
        if (modelConfig) {
            chat_model_config_destroy(&modelConfig);
        }
    }
};

ChatCore::ChatCore(QObject *parent)
    : QObject(parent)
    , d(std::make_unique<ChatCorePrivate>())
{
    d->currentRole = "default";
    d->currentModel = "Qwen-2.5-3b_1.0"; // 使用本地的 Qwen 模型
}

ChatCore::~ChatCore() = default;

bool ChatCore::initialize()
{
    try {
        // 创建会话
        d->session = genai_text_create_session();
        if (!d->session) {
            handleSDKError(-1, "创建会话失败");
            return false;
        }

        // 创建模型配置
        d->modelConfig = chat_model_config_create();
        if (!d->modelConfig) {
            handleSDKError(-1, "创建模型配置失败");
            return false;
        }

        // 设置默认模型配置
        chat_model_config_set_name(d->modelConfig, d->currentModel.toUtf8().constData());
        chat_model_config_set_deploy_type(d->modelConfig, ModelDeployType::OnDevice);
        genai_text_set_model_config(d->session, d->modelConfig);

        // 设置回调函数
        genai_text_result_set_callback(d->session, &ChatCore::handleChatResult, this);

        // 初始化会话
        int result = genai_text_init_session(d->session);
        if (result != 0) {
            handleSDKError(result, "会话初始化失败");
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

    if (d->isProcessing) {
        emit errorOccurred("正在处理上一条消息");
        return;
    }

    try {
        // 创建用户消息
        Message userMsg;
        userMsg.content = message;
        userMsg.isUser = true;
        userMsg.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        userMsg.role = role;
        userMsg.model = d->currentModel;
        
        // 添加到历史记录
        d->messageHistory.append(userMsg);
        
        // 设置处理状态
        d->isProcessing = true;
        emit chatStateChanged(true);
        
        // 发送消息
        genai_text_chat_async(d->session, message.toUtf8().constData());
        
    } catch (const std::exception& e) {
        d->isProcessing = false;
        emit chatStateChanged(false);
        handleSDKError(-1, QString("消息处理异常: %1").arg(e.what()));
    }
}

void ChatCore::handleChatResult(ChatResult *result, void *userData)
{
    ChatCore *self = static_cast<ChatCore*>(userData);
    if (!self) return;

    try {
        // 检查错误
        int errorCode = chat_result_get_error_code(result);
        if (errorCode != 0) {
            const char* errorMsg = chat_result_get_error_message(result);
            self->handleSDKError(errorCode, QString::fromUtf8(errorMsg));
            return;
        }

        // 获取AI回复
        const char* response = chat_result_get_assistant_message(result);
        bool isEnd = chat_result_get_is_end(result);

        if (response) {
            // 将新的回复添加到当前回复中
            self->d->currentResponse += QString::fromUtf8(response);
        }

        // 如果是最后一条消息，发送完整的回复
        if (isEnd) {
            // 创建AI回复消息
            Message aiMsg;
            aiMsg.content = self->d->currentResponse;
            aiMsg.isUser = false;
            aiMsg.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            aiMsg.role = self->d->currentRole;
            aiMsg.model = self->d->currentModel;

            // 添加到历史记录
            self->d->messageHistory.append(aiMsg);
            
            // 发出消息接收信号
            emit self->messageReceived(aiMsg);

            // 重置当前回复和处理状态
            self->d->currentResponse.clear();
            self->d->isProcessing = false;
            emit self->chatStateChanged(false);
        }

    } catch (const std::exception& e) {
        self->d->isProcessing = false;
        self->d->currentResponse.clear();
        emit self->chatStateChanged(false);
        self->handleSDKError(-1, QString("结果处理异常: %1").arg(e.what()));
    }
}

QVector<Message> ChatCore::getHistory() const
{
    return d->messageHistory;
}

void ChatCore::clearHistory()
{
    d->messageHistory.clear();
    if (d->session) {
        genai_text_clear_chat_history_messages(d->session);
    }
}

void ChatCore::setCurrentRole(const QString &role)
{
    d->currentRole = role;
}

void ChatCore::setModelConfig(const QString &modelName, ModelDeployType deployType)
{
    if (!d->modelConfig) return;

    d->currentModel = modelName;
    chat_model_config_set_name(d->modelConfig, modelName.toUtf8().constData());
    chat_model_config_set_deploy_type(d->modelConfig, deployType);
    
    if (d->session) {
        genai_text_set_model_config(d->session, d->modelConfig);
    }
}

void ChatCore::setSystemPrompt(const QString &prompt)
{
    if (d->session) {
        genai_text_set_chat_system_prompt(d->session, prompt.toUtf8().constData());
    }
}

void ChatCore::stopChat()
{
    if (d->session && d->isProcessing) {
        genai_text_stop_chat(d->session);
        d->isProcessing = false;
        emit chatStateChanged(false);
    }
}

void ChatCore::handleSDKError(int errorCode, const QString &errorMessage)
{
    QString fullMessage = QString("错误 [%1]: %2").arg(errorCode).arg(errorMessage);
    emit errorOccurred(fullMessage);
} 