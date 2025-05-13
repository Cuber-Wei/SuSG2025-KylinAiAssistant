#ifndef CUSTOMROLE_H
#define CUSTOMROLE_H

#include <QString>
#include <QObject>

class CustomRole : public QObject
{
    Q_OBJECT

public:
    explicit CustomRole(QObject *parent = nullptr);
    CustomRole(const QString &name, const QString &description, const QString &prompt = "", QObject *parent = nullptr);
    ~CustomRole();

    // 获取角色名称
    QString getName() const;
    
    // 获取角色描述
    QString getDescription() const;
    
    // 获取角色提示词
    QString getPrompt() const;
    
    // 设置角色名称
    void setName(const QString &name);
    
    // 设置角色描述
    void setDescription(const QString &description);
    
    // 设置角色提示词
    void setPrompt(const QString &prompt);
    
    // 处理消息
    QString processMessage(const QString &message) const;

private:
    QString name;
    QString description;
    QString prompt;
    
    // 根据角色提示词处理消息
    QString applyPrompt(const QString &message) const;
};

#endif // CUSTOMROLE_H 