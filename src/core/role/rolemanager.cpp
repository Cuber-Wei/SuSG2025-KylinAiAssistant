#include "rolemanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QDebug>

#define ROLES_FILE "roles.json" // Define ROLES_FILE here

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

void RoleManager::addCustomRole(const QString &name, const QString &description, const QString &prompt)
{
    if (roles.contains(name)) {
        emit errorOccurred("角色名称已存在");
        return;
    }
    
    CustomRole *role = new CustomRole(name, description, prompt, this);
    roles[name] = role;
    emit roleAdded(name);
}

bool RoleManager::addRole(const QString &name, const QString &description, const QString &prompt)
{
    if (roles.contains(name)) {
        return false;
    }
    CustomRole* newRole = new CustomRole(name, description, prompt, this);
    roles.insert(name, newRole);
    saveCustomRoles();
    emit roleAdded(name);
    return true;
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

void RoleManager::editRole(const QString &name, const QString &description, const QString &prompt)
{
    if (!roles.contains(name)) {
        emit errorOccurred("角色不存在");
        return;
    }
    
    CustomRole *role = roles[name];
    role->setDescription(description);
    role->setPrompt(prompt);
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
    addCustomRole("默认", "通用助手", "");
    addCustomRole("律师", "法律顾问", "请你扮演一位专业的律师，用词严谨、专业。");
    addCustomRole("教师", "教育辅导", "请你扮演一位有耐心的教师，耐心细致地为我解答问题。");
    addCustomRole("程序员", "技术顾问", "请你扮演一位资深程序员，能为我解答各种技术问题。");
    addCustomRole("作家", "创作指导", "请你扮演一位富有创意的作家，为我的写作提供一些灵感。");
}

void RoleManager::saveCustomRoles()
{
    QFile file(ROLES_FILE);

    QJsonArray roleArray;
    for (auto it = roles.begin(); it != roles.end(); ++it) {
        CustomRole *role = it.value();
        QJsonObject roleObj;
        roleObj["name"] = role->getName();
        roleObj["description"] = role->getDescription();
        roleObj["prompt"] = role->getPrompt();
        roleArray.append(roleObj);
    }
    
    QJsonDocument doc(roleArray);
    QFile file2("roles.json"); // Renamed to file2 to avoid redeclaration if first file was open
    if (file2.open(QIODevice::WriteOnly)) {
        file2.write(doc.toJson());
        file2.close();
    } else {
        qWarning() << "RoleManager::saveCustomRoles - Failed to open roles.json for writing:" << file2.errorString(); // Keep qWarning
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
                QString prompt = roleObj["prompt"].toString();
                
                if (!roles.contains(name)) {
                    CustomRole *role = new CustomRole(name, description, prompt, this);
                    roles[name] = role;
                }
            }
        }
    }
}

void RoleManager::initializeDefaultRoles()
{
    loadBuiltInRoles();
} 