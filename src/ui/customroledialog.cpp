#include "customroledialog.h"
#include "ui_customroledialog.h"
#include <QMessageBox>

CustomRoleDialog::CustomRoleDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomRoleDialog)
{
    ui->setupUi(this);
    setWindowTitle("新建角色");
    
    // 连接按钮信号
    connect(ui->confirmButton, &QPushButton::clicked, this, &CustomRoleDialog::on_confirmButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &CustomRoleDialog::on_cancelButton_clicked);
}

CustomRoleDialog::~CustomRoleDialog()
{
    delete ui;
}

QString CustomRoleDialog::getRoleName() const
{
    return ui->nameEdit->text().trimmed();
}

QString CustomRoleDialog::getRoleDescription() const
{
    return ui->descriptionEdit->text().trimmed();
}

QString CustomRoleDialog::getRolePrompt() const
{
    return ui->promptEdit->toPlainText().trimmed();
}

void CustomRoleDialog::validateInput()
{
    if (getRoleName().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入角色名称");
        ui->nameEdit->setFocus();
        return;
    }
    
    if (getRolePrompt().isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入角色设定");
        ui->promptEdit->setFocus();
        return;
    }
    
    accept();
}

void CustomRoleDialog::on_confirmButton_clicked()
{
    validateInput();
}

void CustomRoleDialog::on_cancelButton_clicked()
{
    reject();
} 