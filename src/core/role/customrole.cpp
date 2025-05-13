#include "customrole.h"

CustomRole::CustomRole(QObject *parent)
    : QObject(parent)
{
}

CustomRole::CustomRole(const QString &name, const QString &description, const QString &prompt, QObject *parent)
    : QObject(parent)
    , name(name)
    , description(description)
    , prompt(prompt)
{
}

CustomRole::~CustomRole()
{
}

QString CustomRole::getName() const
{
    return name;
}

QString CustomRole::getDescription() const
{
    return description;
}

QString CustomRole::getPrompt() const
{
    return prompt;
}

void CustomRole::setName(const QString &newName)
{
    if (name != newName) {
        name = newName;
    }
}

void CustomRole::setDescription(const QString &newDescription)
{
    if (description != newDescription) {
        description = newDescription;
    }
}

void CustomRole::setPrompt(const QString &newPrompt)
{
    if (prompt != newPrompt) {
        prompt = newPrompt;
    }
}

QString CustomRole::processMessage(const QString &message) const
{
    // 根据角色提示词处理消息
    return applyPrompt(message);
}

QString CustomRole::applyPrompt(const QString &message) const
{
    // TODO: 根据角色提示词处理消息
    // 这里需要根据麒麟AI SDK的能力来实现
    
    // 临时返回一个简单的处理结果
    if (!prompt.isEmpty()) {
        // 使用提示词来引导AI回应
        return QString("[%1] %2").arg(name, message);
    } else {
        return QString("[%1] %2").arg(name, message);
    }
} 