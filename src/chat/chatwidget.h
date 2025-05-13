#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include "roles/rolemanager.h"

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);

private slots:
    void sendMessage();
    void onRoleChanged(int index);
    void onMessageReceived(const QString &message);

private:
    void setupUI();
    void setupConnections();

    QTextEdit *m_chatDisplay;
    QLineEdit *m_messageInput;
    QPushButton *m_sendButton;
    QListWidget *m_roleList;
    RoleManager *m_roleManager;
};

#endif // CHATWIDGET_H 