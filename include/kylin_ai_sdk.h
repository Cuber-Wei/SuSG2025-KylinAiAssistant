#ifndef KYLIN_AI_SDK_H
#define KYLIN_AI_SDK_H

#include <string>

// 消息结构
struct KylinAIMessage {
    std::string content;
    std::string role;
};

// 响应结构
struct KylinAIResponse {
    std::string content;
    int status;
};

// SDK类
class KylinAISDK {
public:
    KylinAISDK() = default;
    ~KylinAISDK() = default;

    // 初始化SDK
    int initialize() { return 0; }

    // 清理SDK
    void cleanup() {}

    // 处理消息
    int processMessage(const KylinAIMessage& message, KylinAIResponse& response) {
        response.content = "这是一个临时的SDK响应。";
        response.status = 0;
        return 0;
    }
};

#endif // KYLIN_AI_SDK_H 