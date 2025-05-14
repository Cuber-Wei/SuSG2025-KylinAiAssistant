# 麒麟AI助手

基于银河麒麟操作系统的多功能AI交互助手，支持文本对话、语音交互和角色定制功能。通过整合麒麟AI SDK，实现了便捷、智能的用户交互体验。

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

## 系统要求

- **操作系统**：银河麒麟操作系统 V2503 或更高版本
- **开发环境**：Qt 5.15+ 环境
- **依赖组件**：麒麟AI SDK (包含语音识别、语音合成、大语言模型等组件)
- **硬件需求**：
  - 处理器：建议Intel Core i5-8代或更高性能
  - 内存：4GB+ 内存 (推荐8GB及以上)
  - 存储：10GB+ 可用磁盘空间
  - 外设：麦克风和扬声器（用于语音交互）

## 功能特性

### 文本对话
- 基于大语言模型的自然语言理解
- 多轮对话支持，记忆上下文
- 智能回答各类问题，提供专业建议
- 支持自定义系统提示词，增强回答质量

### 语音交互
- 实时语音识别，支持普通话
- 高品质语音合成，流畅自然

### 角色系统
- 内置专业角色（律师、教师、程序员、作家）
- 完全自定义角色，设置专属提示词
- 一键切换角色，满足不同场景需求
- 角色配置数据自动保存和加载

## 项目结构

```
.
├── resources/        # 资源文件
│   ├── icons/       # 图标文件
│   └── styles/      # 样式文件
├── src/              # 源代码
│   ├── core/        # 核心功能
│   │   ├── chat/   # 聊天相关
│   │   ├── role/   # 角色管理
│   │   └── voice/  # 语音处理
│   └── ui/          # 界面相关
├── include/          # 头文件目录
└── docs/             # 文档目录
```

## 安装说明

### 前提条件

1. 确保您的系统为银河麒麟操作系统 V2503 或更高版本
2. 安装必要的麒麟AI SDK组件：
   ```bash
   sudo apt update
   sudo apt install libkysdk-coreai-vision-dev libkysdk-coreai-speech-dev libkysdk-genai-nlp-dev libkysdk-genai-vision-dev
   ```
3. 安装Qt开发环境：
   ```bash
   sudo apt install qt5-default qtmultimedia5-dev qtdeclarative5-dev
   ```
4. 安装其他依赖库：
   ```bash
   sudo apt install libssl-dev libcurl4-openssl-dev
   ```

### 从源码构建

1. 克隆仓库：
   ```bash
   git clone https://github.com/Cuber-Wei/SuSG2025-KylinAiAssistant.git
   cd SuSG2025-KylinAiAssistant
   ```

2. 使用qmake构建项目：
   ```bash
   qmake
   make -j$(nproc)
   ```

3. 运行程序：
   ```bash
   ./SuSG2025-KylinAiAssistant
   ```
   
> 或使用一键式编译运行脚本：
>   ```bash
>   ./run.sh
>   ```

### 开发环境配置

1. 使用Qt Creator打开项目：
   ```bash
   qtcreator SuSG2025-KylinAiAssistant.pro
   ```

2. 在IDE中配置构建环境并运行项目
   - 打开项目后，在Qt Creator左侧选择"项目"
   - 配置构建路径和构建步骤
   - 点击左下方的"运行"按钮编译并运行项目

### 配置AI模型

1. 本地模型配置
   - 打开应用后进入"设置"菜单
   - 在"模型管理"选项卡下选择要使用的本地模型
   - 应用支持银河麒麟操作系统提供的本地大语言模型

2. 云服务配置
   - 在"设置"菜单中导航至"云服务设置"
   - 输入有效的API密钥和终端URL
   - 保存配置后重启应用

## 使用指南

### 基本交互
1. 打开应用后默认进入聊天界面
2. 在文本框中输入您的问题，点击发送按钮发送
3. 点击麦克风按钮可切换到语音输入模式
4. 对话历史会自动保存

### 角色管理
1. 点击"新建角色"创建自定义角色
2. 设置角色名称、描述和提示词后保存
3. 内置角色不可删除，但可以自定义同类型角色

### 语音功能
1. 点击录音按钮开始语音输入
2. 再次点击结束录音，语音将自动转换为文字
3. 编辑文字内容确认无误后点击发送
4. 需确保系统已正确配置麦克风设备

### 高级功能
1. 自定义系统提示词
   - 在角色管理中可为每个角色设置系统提示词
   - 良好的提示词能显著提高回答质量

2. 模型切换
   - 在设置中可选择不同的本地或云端模型
   - 不同模型有各自的特点，可根据需求选择

## 许可证

本项目采用MIT许可证 - 详见 [LICENSE](LICENSE) 文件

## 联系方式

- 项目维护者: L0v3ch4n, LongziJasonyang, heimaliu
- 项目仓库: [Cuber-Wei/SuSG2025-KylinAiAssistant](https://github.com/Cuber-Wei/SuSG2025-KylinAiAssistant)
- 问题反馈: 请通过GitHub Issues提交问题或功能建议
- 技术支持: 可在项目讨论区或通过提交Issue获取帮助
