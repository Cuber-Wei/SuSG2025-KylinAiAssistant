#include "ui/mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // 设置应用程序信息
    QApplication::setApplicationName("麒麟AI助手");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("SuSG2025");
    
    // 加载翻译文件
    QTranslator translator;
    if (translator.load(QLocale(), "SuSG2025-KylinAiAssistant", "_", ":/translations")) {
        app.installTranslator(&translator);
    }
    
    // 创建并显示主窗口
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
} 