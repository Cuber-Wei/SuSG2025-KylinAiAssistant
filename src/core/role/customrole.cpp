#include "customrole.h"

CustomRole::CustomRole(QObject *parent)
    : QObject(parent)
    , name("")
    , description("")
    , prompt("")
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
    // 这里可以根据prompt做更复杂的处理，目前直接返回message
    return message;
}

QString CustomRole::applyStyle(const QString &message) const
{
    // TODO: 根据角色风格处理消息
    // 这里需要根据麒麟AI SDK的能力来实现
    
    // 临时返回一个简单的处理结果
    return QString("[%1] %2").arg(name, message);
} 