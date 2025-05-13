#include "rolemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QDebug>

RoleManager::RoleManager(QWidget *parent)
    : QWidget(parent)
{
    initializeDefaultRoles();
    loadCustomRoles();
}

RoleManager::~RoleManager()
{
    saveCustomRoles();
    qDeleteAll(roles);
}

void RoleManager::addCustomRole(const QString &name, const QString &description, const QString &style)
{
    if (roles.contains(name)) {
        emit errorOccurred("角色名称已存在");
        return;
    }
    
    CustomRole *role = new CustomRole(name, description, style, this);
    roles[name] = role;
    emit roleAdded(name);
}

void RoleManager::removeRole(const QString &name)
{
    if (!roles.contains(name)) {
        emit errorOccurred("角色不存在");
        return;
    }
    
    // 不允许删除内置角色
    if (name == "默认" || name == "律师" || name == "教师" || 
        name == "程序员" || name == "作家") {
        emit errorOccurred("不能删除内置角色");
        return;
    }
    
    delete roles.take(name);
    emit roleRemoved(name);
}

void RoleManager::editRole(const QString &name, const QString &description, const QString &style)
{
    if (!roles.contains(name)) {
        emit errorOccurred("角色不存在");
        return;
    }
    
    CustomRole *role = roles[name];
    role->setDescription(description);
    role->setStyle(style);
    emit roleModified(name);
}

QStringList RoleManager::getRoleList() const
{
    return roles.keys();
}

CustomRole* RoleManager::getRole(const QString &name) const
{
    return roles.value(name);
}

void RoleManager::loadBuiltInRoles()
{
    // 添加内置角色
    addCustomRole("默认", "通用助手", "友好、专业的对话风格");
    addCustomRole("律师", "法律顾问", "严谨、专业的法律咨询风格");
    addCustomRole("教师", "教育辅导", "耐心、细致的教学风格");
    addCustomRole("程序员", "技术顾问", "逻辑清晰、技术导向的对话风格");
    addCustomRole("作家", "创作指导", "富有创意、文学性的对话风格");
}

void RoleManager::saveCustomRoles()
{
    QJsonArray roleArray;
    for (auto it = roles.begin(); it != roles.end(); ++it) {
        CustomRole *role = it.value();
        QJsonObject roleObj;
        roleObj["name"] = role->getName();
        roleObj["description"] = role->getDescription();
        roleObj["style"] = role->getStyle();
        roleArray.append(roleObj);
    }
    
    QJsonDocument doc(roleArray);
    QFile file("roles.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void RoleManager::loadCustomRoles()
{
    QFile file("roles.json");
    if (!file.exists()) {
        return;
    }
    
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();
        
        if (doc.isArray()) {
            QJsonArray roleArray = doc.array();
            for (const QJsonValue &value : roleArray) {
                QJsonObject roleObj = value.toObject();
                QString name = roleObj["name"].toString();
                QString description = roleObj["description"].toString();
                QString style = roleObj["style"].toString();
                
                if (!roles.contains(name)) {
                    addCustomRole(name, description, style);
                }
            }
        }
    }
}

void RoleManager::initializeDefaultRoles()
{
    loadBuiltInRoles();
} 