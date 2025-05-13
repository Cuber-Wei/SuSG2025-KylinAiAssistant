#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIcon>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , chatPage(nullptr)
    , rolePage(nullptr)
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
    // chatPage 和 rolePage 是 stackedWidget 直接管理的页面
    chatPage = ui->chatPage; 
    rolePage = ui->rolePage;
    // chatWindow 和 roleManager 是各自页面的子控件
    chatWindow = ui->chatWindow;
    roleManager = ui->roleManager;

    stackedWidget->addWidget(rolePage);

    switchToChat(); 
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
    
    // 连接聊天窗口的新建角色信号
    connect(chatWindow, &ChatWindow::newRoleCreated, this, &MainWindow::handleNewRole);
    
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
    if (stackedWidget && chatPage) {
        stackedWidget->setCurrentWidget(chatPage);
    }
}

void MainWindow::switchToRoleManager()
{
    if (stackedWidget && rolePage) {
        stackedWidget->setCurrentWidget(rolePage);
    }
}

void MainWindow::handleRoleSelected(const QString &roleName)
{
    // 切换到聊天窗口并设置选中的角色
    switchToChat();
    chatWindow->setCurrentRole(roleName);
}

void MainWindow::handleNewRole(const RoleData &data)
{
    if (roleManager->addRole(data.name, data.description, data.prompt)) {
        updateRoleList();
        chatWindow->setCurrentRole(data.name);
        switchToChat();
        QMessageBox::information(this, "成功", "新角色创建成功！");
    } else {
        QMessageBox::critical(this, "错误", "创建角色失败，请重试！\n可能原因：角色名称已存在。");
    }
} 