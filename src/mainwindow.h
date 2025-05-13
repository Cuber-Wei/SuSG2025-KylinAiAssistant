#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include "chat/chatwidget.h"
#include "voice/voicewidget.h"
#include "roles/rolemanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createMenus();
    void createStatusBar();

    QTabWidget *m_tabWidget;
    ChatWidget *m_chatWidget;
    VoiceWidget *m_voiceWidget;
    RoleManager *m_roleManager;
};

#endif // MAINWINDOW_H 