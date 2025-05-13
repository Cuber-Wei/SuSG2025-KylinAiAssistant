#include "rolemanager.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

RoleManager::RoleManager(QWidget *parent)
    : QWidget(parent)
    , m_isEditing(false)
{
    setupUI();
    setupConnections();
    loadBuiltinRoles();
    loadCustomRoles();
}

void RoleManager::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 左侧角色列表
    QWidget *leftPanel = new QWidget(this);
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    m_roleList = new QListWidget(this);
    m_createButton = new QPushButton(tr("创建角色"), this);
    m_editButton = new QPushButton(tr("编辑角色"), this);
    m_deleteButton = new QPushButton(tr("删除角色"), this);

    leftLayout->addWidget(m_roleList);
    leftLayout->addWidget(m_createButton);
    leftLayout->addWidget(m_editButton);
    leftLayout->addWidget(m_deleteButton);

    // 右侧编辑区域
    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);

    m_roleName = new QLineEdit(this);
    m_roleName->setPlaceholderText(tr("角色名称"));
    m_roleName->setEnabled(false);

    m_roleDescription = new QTextEdit(this);
    m_roleDescription->setPlaceholderText(tr("角色描述"));
    m_roleDescription->setEnabled(false);

    m_saveButton = new QPushButton(tr("保存"), this);
    m_saveButton->setEnabled(false);

    rightLayout->addWidget(m_roleName);
    rightLayout->addWidget(m_roleDescription);
    rightLayout->addWidget(m_saveButton);

    mainLayout->addWidget(leftPanel);
    mainLayout->addWidget(rightPanel);
}

void RoleManager::setupConnections()
{
    connect(m_createButton, &QPushButton::clicked, this, &RoleManager::createCustomRole);
    connect(m_editButton, &QPushButton::clicked, this, &RoleManager::editRole);
    connect(m_deleteButton, &QPushButton::clicked, this, &RoleManager::deleteRole);
    connect(m_saveButton, &QPushButton::clicked, this, &RoleManager::saveRole);
    connect(m_roleList, &QListWidget::currentRowChanged, this, &RoleManager::onRoleSelected);
}

void RoleManager::loadBuiltinRoles()
{
    // 添加内置角色
    m_roles["律师"] = "我是一个专业的律师，可以为您解答法律问题，提供法律建议。";
    m_roles["教师"] = "我是一个经验丰富的教师，可以为您讲解知识，辅导学习。";
    m_roles["程序员"] = "我是一个资深程序员，可以帮您解决代码问题，提供编程建议。";
    m_roles["作家"] = "我是一个专业作家，可以帮您进行创意写作，润色文章。";

    for (auto it = m_roles.begin(); it != m_roles.end(); ++it) {
        m_roleList->addItem(it.key());
    }
}

void RoleManager::loadCustomRoles()
{
    QFile file("custom_roles.json");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isArray()) {
        QJsonArray roles = doc.array();
        for (const QJsonValue &role : roles) {
            QJsonObject roleObj = role.toObject();
            QString name = roleObj["name"].toString();
            QString description = roleObj["description"].toString();
            m_roles[name] = description;
            m_roleList->addItem(name);
        }
    }
}

void RoleManager::saveCustomRoles()
{
    QJsonArray roles;
    for (auto it = m_roles.begin(); it != m_roles.end(); ++it) {
        if (it.key() != "律师" && it.key() != "教师" && 
            it.key() != "程序员" && it.key() != "作家") {
            QJsonObject roleObj;
            roleObj["name"] = it.key();
            roleObj["description"] = it.value();
            roles.append(roleObj);
        }
    }

    QFile file("custom_roles.json");
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(roles);
        file.write(doc.toJson());
    }
}

void RoleManager::createCustomRole()
{
    m_isEditing = true;
    m_roleName->clear();
    m_roleDescription->clear();
    m_roleName->setEnabled(true);
    m_roleDescription->setEnabled(true);
    m_saveButton->setEnabled(true);
    m_roleList->clearSelection();
}

void RoleManager::editRole()
{
    int currentRow = m_roleList->currentRow();
    if (currentRow < 0)
        return;

    QString roleName = m_roleList->currentItem()->text();
    if (roleName == "律师" || roleName == "教师" || 
        roleName == "程序员" || roleName == "作家") {
        QMessageBox::warning(this, tr("警告"), tr("不能编辑内置角色！"));
        return;
    }

    m_isEditing = true;
    m_roleName->setText(roleName);
    m_roleDescription->setText(m_roles[roleName]);
    m_roleName->setEnabled(true);
    m_roleDescription->setEnabled(true);
    m_saveButton->setEnabled(true);
}

void RoleManager::deleteRole()
{
    int currentRow = m_roleList->currentRow();
    if (currentRow < 0)
        return;

    QString roleName = m_roleList->currentItem()->text();
    if (roleName == "律师" || roleName == "教师" || 
        roleName == "程序员" || roleName == "作家") {
        QMessageBox::warning(this, tr("警告"), tr("不能删除内置角色！"));
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this,
        tr("确认删除"), tr("确定要删除角色 %1 吗？").arg(roleName),
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_roles.remove(roleName);
        delete m_roleList->takeItem(currentRow);
        saveCustomRoles();
    }
}

void RoleManager::saveRole()
{
    QString name = m_roleName->text().trimmed();
    QString description = m_roleDescription->toPlainText().trimmed();

    if (name.isEmpty() || description.isEmpty()) {
        QMessageBox::warning(this, tr("警告"), tr("角色名称和描述不能为空！"));
        return;
    }

    m_roles[name] = description;
    if (!m_isEditing) {
        m_roleList->addItem(name);
    }
    saveCustomRoles();

    m_roleName->setEnabled(false);
    m_roleDescription->setEnabled(false);
    m_saveButton->setEnabled(false);
    m_isEditing = false;
}

void RoleManager::onRoleSelected(int index)
{
    if (index < 0) {
        m_roleName->clear();
        m_roleDescription->clear();
        return;
    }

    QString roleName = m_roleList->item(index)->text();
    m_roleName->setText(roleName);
    m_roleDescription->setText(m_roles[roleName]);
} 