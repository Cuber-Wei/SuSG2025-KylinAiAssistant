# 麒麟AI SDK开发指南精要

## 1. 概述

麒麟AI SDK是一个统一的AI能力接口封装，提供C语言接口，主要包含两大类能力：

- 传统AI能力：文字识别、音频处理、向量化等
- 生成式AI能力：文本生成、图像生成等

## 2. 系统要求

### 硬件支持
- 仅支持x86和arm架构
- 已适配机型：
  - 联想开天M90fG1s (D3000/16G/Arise-GT10C0t)
  - 联想开天M90hG1t (HygonC86-3G/16GB/Arise-GT10C0t)
  - 联想开天P90zG1t (ZHAOXIN KaiXian KX-7000/16GB/Arise-GT10C0t)

### 软件要求
使用前需要在"设置->AI模块管理"中下载安装AI子系统。

## 3. 核心功能

### 3.1 文字识别 (OCR)
```bash
# 安装依赖
sudo apt install libkysdk-coreai-vision-dev
```
- 支持图片文字识别
- 提供文本内容和位置信息
- 支持同步和异步接口
- 目前仅支持端侧模型

### 3.2 语音处理
```bash
# 安装依赖
sudo apt install libkysdk-coreai-speech-dev
```
- 语音识别：
  - 支持中文识别
  - 支持流式和非流式模式
  - 支持说话人识别
  - 仅支持云端服务

- 语音合成：
  - 支持中英文
  - 支持多种音色
  - 支持调节语速和音量
  - 仅支持云端服务

### 3.3 向量化
```bash
# 安装依赖
sudo apt install libkylin-coreai-embedding-dev
```
- 支持文本向量化
- 支持图像向量化
- 提供同步和异步接口

### 3.4 文本生成
```bash
# 安装依赖
sudo apt install libkysdk-genai-nlp-dev
```
- 支持文本生成和对话
- 内置多种提示词
- 支持云端、端侧和自定义模型

### 3.5 图像生成
```bash
# 安装依赖
sudo apt install libkysdk-genai-vision-dev
```
- 支持文本生成图片
- 支持多种风格和分辨率
- 支持多语言
- 仅支持云端服务

## 4. 通用错误码

主要错误类型：
- AISDK_NO_ERROR (0): 未发生错误
- AISDK_NET_ERROR: 网络错误
- AISDK_AUTHENTICATION_FAILURE: 鉴权错误
- AISDK_RUNTIME_ERROR: 运行时服务错误
- AISDK_TOO_MANY_REQUESTS: 请求次数过多
- AISDK_SERVICE_ERROR: 云端服务错误
- AISDK_MODEL_NOT_FOUND: 未找到可用模型

## 5. 开发最佳实践

1. 会话管理
   - 每个会话同时只能处理一个任务
   - 并发需要创建多个会话

2. 错误处理
   - 初始化失败需要重新创建会话
   - 注意检查错误码和错误信息

3. 资源管理
   - 使用完及时销毁会话
   - 注意释放结果资源

4. 配置管理
   - 使用前确保AI模块管理中已配置相应服务
   - 根据需求选择合适的部署方式（云端/端侧） 