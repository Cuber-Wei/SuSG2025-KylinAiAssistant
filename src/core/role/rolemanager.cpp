#include "rolemanager.h"
#include "ui_rolemanager.h"
#include "../ui/customroledialog.h"
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>

RoleManager::RoleManager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RoleManager)
{
    ui->setupUi(this);
    setupConnections();
    loadRoles();
    updateRoleList();
}

RoleManager::~RoleManager()
{
    saveRoles();
    qDeleteAll(roles);
    delete ui;
}

void RoleManager::setupConnections()
{
    connect(ui->addRoleButton, &QPushButton::clicked, this, &RoleManager::on_addRoleButton_clicked);
    connect(ui->removeRoleButton, &QPushButton::clicked, this, &RoleManager::on_removeRoleButton_clicked);
    connect(ui->modifyRoleButton, &QPushButton::clicked, this, &RoleManager::on_modifyRoleButton_clicked);
    connect(ui->roleListWidget, &QListWidget::itemClicked, this, &RoleManager::on_roleListWidget_itemClicked);
}

QStringList RoleManager::getRoleList() const
{
    return roles.keys();
}

bool RoleManager::addCustomRole(const QString &name, const QString &description, const QString &prompt)
{
    if (roles.contains(name)) {
        QMessageBox::warning(this, "错误", "角色名称已存在");
        return false;
    }

    CustomRole *role = new CustomRole(name, description, prompt);
    roles[name] = role;
    saveRoles();
    updateRoleList();
    emit roleAdded(name);
    return true;
}

bool RoleManager::removeRole(const QString &name)
{
    if (name == "默认") {
        QMessageBox::warning(this, "错误", "不能删除默认角色");
        return false;
    }

    if (!roles.contains(name)) {
        return false;
    }

    delete roles.take(name);
    saveRoles();
    updateRoleList();
    emit roleRemoved(name);
    return true;
}

bool RoleManager::modifyRole(const QString &oldName, const QString &newName, const QString &description, const QString &prompt)
{
    if (oldName == "默认") {
        QMessageBox::warning(this, "错误", "不能修改默认角色");
        return false;
    }

    if (!roles.contains(oldName)) {
        return false;
    }

    if (oldName != newName && roles.contains(newName)) {
        QMessageBox::warning(this, "错误", "新角色名称已存在");
        return false;
    }

    CustomRole *role = roles.take(oldName);
    role->setName(newName);
    role->setDescription(description);
    role->setPrompt(prompt);
    roles[newName] = role;

    saveRoles();
    updateRoleList();
    emit roleModified(newName);
    return true;
}

CustomRole* RoleManager::getRole(const QString &name) const
{
    return roles.value(name);
}

void RoleManager::loadRoles()
{
    // 清空现有角色
    qDeleteAll(roles);
    roles.clear();

    // 添加默认角色
    CustomRole *defaultRole = new CustomRole("默认", "默认AI助手", "你是一个智能AI助手，可以帮助用户解答问题。");
    roles["默认"] = defaultRole;

    // 从文件加载自定义角色
    QFile file("roles.json");
    if (file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        file.close();

        if (doc.isArray()) {
            QJsonArray array = doc.array();
            for (const QJsonValue &value : array) {
                if (value.isObject()) {
                    QJsonObject obj = value.toObject();
                    QString name = obj["name"].toString();
                    QString description = obj["description"].toString();
                    QString prompt = obj["prompt"].toString();

                    if (!name.isEmpty() && !roles.contains(name)) {
                        CustomRole *role = new CustomRole(name, description, prompt);
                        roles[name] = role;
                    }
                }
            }
        }
    }
}

void RoleManager::saveRoles()
{
    QJsonArray array;
    for (auto it = roles.begin(); it != roles.end(); ++it) {
        if (it.key() != "默认") {  // 不保存默认角色
            CustomRole *role = it.value();
            QJsonObject obj;
            obj["name"] = role->getName();
            obj["description"] = role->getDescription();
            obj["prompt"] = role->getPrompt();
            array.append(obj);
        }
    }

    QJsonDocument doc(array);
    QFile file("roles.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void RoleManager::updateRoleList()
{
    ui->roleListWidget->clear();
    for (const QString &name : roles.keys()) {
        ui->roleListWidget->addItem(name);
    }
}

void RoleManager::on_addRoleButton_clicked()
{
    CustomRoleDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getRoleName();
        QString description = dialog.getRoleDescription();
        QString prompt = dialog.getRolePrompt();
        
        if (addCustomRole(name, description, prompt)) {
            QMessageBox::information(this, "成功", "角色添加成功");
        }
    }
}

void RoleManager::on_removeRoleButton_clicked()
{
    QListWidgetItem *currentItem = ui->roleListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "错误", "请先选择要删除的角色");
        return;
    }

    QString name = currentItem->text();
    if (QMessageBox::question(this, "确认", "确定要删除角色 \"" + name + "\" 吗？") == QMessageBox::Yes) {
        if (removeRole(name)) {
            QMessageBox::information(this, "成功", "角色删除成功");
        }
    }
}

void RoleManager::on_modifyRoleButton_clicked()
{
    QListWidgetItem *currentItem = ui->roleListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "错误", "请先选择要修改的角色");
        return;
    }

    QString oldName = currentItem->text();
    CustomRole *role = getRole(oldName);
    if (!role) return;

    CustomRoleDialog dialog(this);
    dialog.setWindowTitle("修改角色");
    // TODO: 设置当前值到对话框
    
    if (dialog.exec() == QDialog::Accepted) {
        QString newName = dialog.getRoleName();
        QString description = dialog.getRoleDescription();
        QString prompt = dialog.getRolePrompt();
        
        if (modifyRole(oldName, newName, description, prompt)) {
            QMessageBox::information(this, "成功", "角色修改成功");
        }
    }
}

void RoleManager::on_roleListWidget_itemClicked(QListWidgetItem *item)
{
    if (item) {
        emit roleSelected(item->text());
    }
} 