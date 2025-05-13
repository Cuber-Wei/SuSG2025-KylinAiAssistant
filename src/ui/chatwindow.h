#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QString>
#include "../core/chat/chatcore.h"
#include "../core/voice/voicehandler.h"

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

    void setCurrentRole(const QString &roleName);

public slots:
    void handleMessageReceived(const Message &message);
    void handleError(const QString &error);
    void handleTextRecognized(const QString &text);

private slots:
    void on_sendButton_clicked();
    void handleVoiceButtonClicked();
    void onRoleSelected(const QString &roleName);

private:
    Ui::ChatWindow *ui;
    ChatCore *chatCore;
    VoiceHandler *voiceHandler;
    QString currentRole;
    
    void setupConnections();
    void appendMessage(const QString &sender, const QString &message);
    void updateRoleList();
};

#endif // CHATWINDOW_H 