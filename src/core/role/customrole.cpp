#include "customrole.h"

CustomRole::CustomRole(QObject *parent)
    : QObject(parent)
{
}

CustomRole::CustomRole(const QString &name, const QString &description, const QString &style, QObject *parent)
    : QObject(parent)
    , name(name)
    , description(description)
    , style(style)
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

QString CustomRole::getStyle() const
{
    return style;
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

void CustomRole::setStyle(const QString &newStyle)
{
    if (style != newStyle) {
        style = newStyle;
    }
}

QString CustomRole::processMessage(const QString &message) const
{
    // 根据角色风格处理消息
    return applyStyle(message);
}

QString CustomRole::applyStyle(const QString &message) const
{
    // TODO: 根据角色风格处理消息
    // 这里需要根据麒麟AI SDK的能力来实现
    
    // 临时返回一个简单的处理结果
    return QString("[%1] %2").arg(name, message);
} 