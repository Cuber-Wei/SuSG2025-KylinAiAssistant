#include "mainwindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    createMenus();
    createStatusBar();
    setWindowTitle(tr("麒麟AI助手"));
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_tabWidget = new QTabWidget(this);
    setCentralWidget(m_tabWidget);

    m_chatWidget = new ChatWidget(this);
    m_voiceWidget = new VoiceWidget(this);
    m_roleManager = new RoleManager(this);

    m_tabWidget->addTab(m_chatWidget, tr("文本对话"));
    m_tabWidget->addTab(m_voiceWidget, tr("语音对话"));
    m_tabWidget->addTab(m_roleManager, tr("角色管理"));
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("文件"));
    QAction *exitAction = fileMenu->addAction(tr("退出"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    QMenu *helpMenu = menuBar()->addMenu(tr("帮助"));
    QAction *aboutAction = helpMenu->addAction(tr("关于"));
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox::about(this, tr("关于麒麟AI助手"),
            tr("麒麟AI助手 v1.0\n\n"
               "一个功能强大的AI交互助手，支持文本和语音对话，"
               "并提供多种内置角色和自定义角色功能。"));
    });
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("就绪"));
} 