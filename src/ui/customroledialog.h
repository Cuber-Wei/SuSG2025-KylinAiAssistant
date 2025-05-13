#ifndef CUSTOMROLEDIALOG_H
#define CUSTOMROLEDIALOG_H

#include <QDialog>
#include <QString>

// 使用简单结构体来传递角色数据，避免 QObject 派生类复制问题
struct RoleData {
    QString name;
    QString description;
    QString prompt;
};

namespace Ui {
class CustomRoleDialog;
}

class CustomRoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomRoleDialog(QWidget *parent = nullptr);
    ~CustomRoleDialog();

    // 获取编辑后的角色
    RoleData getRoleData() const;
    
    // 设置当前编辑的角色
    void setRoleData(const RoleData &data);
    
    // 设置对话框为编辑模式
    void setEditMode(bool isEdit);

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

signals:
    // 添加或编辑角色完成后发出信号
    void roleConfirmed(const RoleData &data);

private:
    Ui::CustomRoleDialog *ui;
    bool isEditMode;
};

#endif // CUSTOMROLEDIALOG_H 