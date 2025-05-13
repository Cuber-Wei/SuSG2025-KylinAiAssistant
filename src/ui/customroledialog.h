#ifndef CUSTOMROLEDIALOG_H
#define CUSTOMROLEDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CustomRoleDialog;
}

class CustomRoleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomRoleDialog(QWidget *parent = nullptr);
    ~CustomRoleDialog();

    QString getRoleName() const;
    QString getRoleDescription() const;
    QString getRolePrompt() const;

private slots:
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::CustomRoleDialog *ui;
    void validateInput();
};

#endif // CUSTOMROLEDIALOG_H 