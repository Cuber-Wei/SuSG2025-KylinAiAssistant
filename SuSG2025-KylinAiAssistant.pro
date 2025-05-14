QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# 禁用SDK版本检查
CONFIG += sdk_no_version_check

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 项目名称
TARGET = SuSG2025-KylinAiAssistant
TEMPLATE = app

# 源文件
SOURCES += \
    src/main.cpp \
    src/ui/mainwindow.cpp \
    src/ui/chatwindow.cpp \
    src/ui/customroledialog.cpp \
    src/core/chat/chatcore.cpp \
    src/core/role/rolemanager.cpp \
    src/core/role/customrole.cpp \
    src/core/voice/voicehandler.cpp

# 头文件
HEADERS += \
    src/ui/mainwindow.h \
    src/ui/chatwindow.h \
    src/ui/customroledialog.h \
    src/core/chat/chatcore.h \
    src/core/role/rolemanager.h \
    src/core/role/customrole.h \
    src/core/voice/voicehandler.h

# UI文件
FORMS += \
    src/ui/mainwindow.ui \
    src/ui/chatwindow.ui \
    src/ui/rolemanager.ui \
    src/ui/customroledialog.ui

# 默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# 包含目录
INCLUDEPATH += \
    $$PWD/src \
    $$PWD/src/core \
    $$PWD/src/ui \
    $$PWD/include \
    /usr/include/kylin-ai \
    /usr/include/x86_64-linux-gnu/qt5 \
    /usr/include/x86_64-linux-gnu/qt5/QtCore \
    /usr/include/x86_64-linux-gnu/qt5/QtGui \
    /usr/include/x86_64-linux-gnu/qt5/QtWidgets \
    /usr/include/x86_64-linux-gnu/qt5/QtMultimedia \
    /usr/include/x86_64-linux-gnu/qt5/QtNetwork

# 链接库
LIBS += \
    -lkysdk-genai-nlp \
    -lkysdk-coreai-speech \
    -lkysdk-coreai-vision \
    -lkysdk-genai-vision \
    -lkysdk-ai-common

# 资源文件
RESOURCES += \
    resources.qrc

# 翻译文件
TRANSLATIONS += \
    SuSG2025-KylinAiAssistant_zh_CN.ts

# 样式文件
QMAKE_RESOURCE_PREFIX = /qt-project.org

# 麒麟AI SDK 依赖配置
unix {
    # 传统AI能力
    INCLUDEPATH += /usr/include/kysdk-coreai-vision
    LIBS += -lkysdk-coreai-vision
    INCLUDEPATH += /usr/include/kysdk-coreai-speech
    LIBS += -lkysdk-coreai-speech
    # 生成式AI能力
    INCLUDEPATH += /usr/include/kysdk-genai-nlp
    LIBS += -lkysdk-genai-nlp
    INCLUDEPATH += /usr/include/kysdk-genai-vision
    LIBS += -lkysdk-genai-vision
    # 依赖GIO
    CONFIG += link_pkgconfig
    PKGCONFIG += gio-unix-2.0
}
