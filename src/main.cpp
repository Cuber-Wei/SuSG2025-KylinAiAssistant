#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("麒麟AI助手");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("Kylin");
    QApplication::setOrganizationDomain("kylin.com");

    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
} 