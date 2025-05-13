#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>

class RoleManager : public QWidget
{
    Q_OBJECT

public:
    explicit RoleManager(QWidget *parent = nullptr);

private slots:
    void createCustomRole();
    void editRole();
    void deleteRole();
    void saveRole();
    void onRoleSelected(int index);

private:
    void setupUI();
    void setupConnections();
    void loadBuiltinRoles();
    void loadCustomRoles();
    void saveCustomRoles();

    QListWidget *m_roleList;
    QTextEdit *m_roleDescription;
    QLineEdit *m_roleName;
    QPushButton *m_createButton;
    QPushButton *m_editButton;
    QPushButton *m_deleteButton;
    QPushButton *m_saveButton;

    QMap<QString, QString> m_roles; // 角色名称 -> 角色描述
    bool m_isEditing;
};

#endif // ROLEMANAGER_H 