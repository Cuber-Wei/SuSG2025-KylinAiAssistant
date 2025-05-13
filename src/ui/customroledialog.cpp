#include "customroledialog.h"
#include "ui_customroledialog.h"
#include <QMessageBox>
#include <QDebug>

CustomRoleDialog::CustomRoleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomRoleDialog)
    , isEditMode(false)
{
    ui->setupUi(this);
    
    // 设置窗口属性
    setWindowTitle("新建角色");
    setModal(true);
}

CustomRoleDialog::~CustomRoleDialog()
{
    delete ui;
}

RoleData CustomRoleDialog::getRoleData() const
{
    RoleData data;
    data.name = ui->nameLineEdit->text();
    data.description = ui->descriptionLineEdit->text();
    data.prompt = ui->promptTextEdit->toPlainText();
    return data;
}

void CustomRoleDialog::setRoleData(const RoleData &data)
{
    ui->nameLineEdit->setText(data.name);
    ui->descriptionLineEdit->setText(data.description);
    ui->promptTextEdit->setText(data.prompt);
}

void CustomRoleDialog::setEditMode(bool isEdit)
{
    isEditMode = isEdit;
    if (isEdit) {
        setWindowTitle("编辑角色");
    } else {
        setWindowTitle("新建角色");
    }
}

void CustomRoleDialog::on_confirmButton_clicked()
{
    // 验证输入
    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "请输入角色名称");
        return;
    }
    
    emit roleConfirmed(getRoleData());
    accept();
}

void CustomRoleDialog::on_cancelButton_clicked()
{
    // 直接关闭对话框
    reject();
} 