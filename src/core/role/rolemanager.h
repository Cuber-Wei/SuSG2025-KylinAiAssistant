#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <QWidget>
#include <QMap>
#include <QString>
#include "customrole.h"

class RoleManager : public QWidget
{
    Q_OBJECT

public:
    explicit RoleManager(QWidget *parent = nullptr);
    ~RoleManager();

    // 添加自定义角色
    void addCustomRole(const QString &name, const QString &description, const QString &style);
    
    // 删除角色
    void removeRole(const QString &name);
    
    // 编辑角色
    void editRole(const QString &name, const QString &description, const QString &style);
    
    // 获取角色列表
    QStringList getRoleList() const;
    
    // 获取角色信息
    CustomRole* getRole(const QString &name) const;

signals:
    void roleAdded(const QString &name);
    void roleRemoved(const QString &name);
    void roleModified(const QString &name);
    void roleSelected(const QString &name);
    void errorOccurred(const QString &error);

private:
    QMap<QString, CustomRole*> roles;
    
    // 加载内置角色
    void loadBuiltInRoles();
    
    // 保存自定义角色
    void saveCustomRoles();
    
    // 加载自定义角色
    void loadCustomRoles();
    
    // 初始化默认角色
    void initializeDefaultRoles();
};

#endif // ROLEMANAGER_H 