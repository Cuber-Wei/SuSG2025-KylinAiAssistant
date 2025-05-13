# 麒麟AI助手

一个基于Qt框架开发的多功能AI交互助手，支持文本和语音对话，并提供多种内置角色和自定义角色功能。

## 功能特点

- 文本对话：支持自然语言理解和多轮对话
- 语音对话：支持语音识别和语音合成
- 内置角色：包含律师、教师、程序员、作家等专业角色
- 自定义角色：允许用户创建和管理自定义角色

## 系统要求

- Qt 6.0或更高版本
- C++17或更高版本
- CMake 3.16或更高版本
- 支持C++17的编译器（如GCC 7+、Clang 5+、MSVC 2017+）

## 构建步骤

1. 克隆仓库：
```bash
git clone https://github.com/yourusername/KylinAiAssistant.git
cd KylinAiAssistant
```

2. 创建构建目录：
```bash
mkdir build
cd build
```

3. 配置项目：
```bash
cmake ..
```

4. 编译项目：
```bash
cmake --build .
```

## 运行

在构建目录中运行：
```bash
./KylinAiAssistant
```

## 项目结构

```
KylinAiAssistant/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── chat/
│   │   ├── chatwidget.cpp
│   │   └── chatwidget.h
│   ├── voice/
│   │   ├── voicewidget.cpp
│   │   └── voicewidget.h
│   └── roles/
│       ├── rolemanager.cpp
│       ├── rolemanager.h
│       ├── builtinroles.cpp
│       ├── builtinroles.h
│       ├── customrole.cpp
│       └── customrole.h
└── resources/
    └── resources.qrc
```

## 许可证

本项目采用MIT许可证。详见[LICENSE](LICENSE)文件。
