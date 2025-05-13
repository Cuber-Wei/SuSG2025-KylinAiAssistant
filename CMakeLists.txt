cmake_minimum_required(VERSION 3.16)
project(KylinAiAssistant VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    Network
    Multimedia
    REQUIRED
)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/chat/chatwidget.cpp
    src/chat/chatwidget.h
    src/voice/voicewidget.cpp
    src/voice/voicewidget.h
    src/roles/rolemanager.cpp
    src/roles/rolemanager.h
    src/roles/builtinroles.cpp
    src/roles/builtinroles.h
    src/roles/customrole.cpp
    src/roles/customrole.h
    resources/resources.qrc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Multimedia
) 