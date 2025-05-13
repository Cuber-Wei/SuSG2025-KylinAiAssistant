#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QMap>
#include <QString>
#include "customrole.h"

namespace Ui {
class RoleManager;
}

class RoleManager : public QWidget
{
    Q_OBJECT

public:
    explicit RoleManager(QWidget *parent = nullptr);
    ~RoleManager();

    QStringList getRoleList() const;
    bool addCustomRole(const QString &name, const QString &description, const QString &prompt);
    bool removeRole(const QString &name);
    bool modifyRole(const QString &oldName, const QString &newName, const QString &description, const QString &prompt);
    CustomRole* getRole(const QString &name) const;

signals:
    void roleSelected(const QString &roleName);
    void roleAdded(const QString &roleName);
    void roleRemoved(const QString &roleName);
    void roleModified(const QString &roleName);

private slots:
    void on_addRoleButton_clicked();
    void on_removeRoleButton_clicked();
    void on_modifyRoleButton_clicked();
    void on_roleListWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::RoleManager *ui;
    QMap<QString, CustomRole*> roles;
    
    void loadRoles();
    void saveRoles();
    void updateRoleList();
    void setupConnections();
};

#endif // ROLEMANAGER_H 