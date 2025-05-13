#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
    setupConnections();
    
    // 设置菜单图标
    ui->actionSwitchToChat->setIcon(QIcon(":/resources/icons/chat.png"));
    ui->actionSwitchToRole->setIcon(QIcon(":/resources/icons/role.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    stackedWidget = ui->stackedWidget;
    chatWindow = ui->chatWindow;
    roleManager = ui->roleManager;
}

void MainWindow::setupConnections()
{
    // 连接菜单动作
    connect(ui->actionSwitchToChat, &QAction::triggered, this, &MainWindow::switchToChat);
    connect(ui->actionSwitchToRole, &QAction::triggered, this, &MainWindow::switchToRoleManager);
    
    // 连接角色选择信号
    connect(roleManager, &RoleManager::roleSelected, this, &MainWindow::handleRoleSelected);
    connect(roleManager, &RoleManager::roleAdded, this, &MainWindow::updateRoleList);
    connect(roleManager, &RoleManager::roleRemoved, this, &MainWindow::updateRoleList);
    connect(roleManager, &RoleManager::roleModified, this, &MainWindow::updateRoleList);
    
    // 初始化角色列表
    updateRoleList();
}

void MainWindow::updateRoleList()
{
    QStringList roles = roleManager->getRoleList();
    chatWindow->updateRoleList(roles);
}

void MainWindow::switchToChat()
{
    stackedWidget->setCurrentWidget(chatWindow);
}

void MainWindow::switchToRoleManager()
{
    stackedWidget->setCurrentWidget(roleManager);
}

void MainWindow::handleRoleSelected(const QString &roleName)
{
    // 切换到聊天窗口并设置选中的角色
    switchToChat();
    chatWindow->setCurrentRole(roleName);
} 