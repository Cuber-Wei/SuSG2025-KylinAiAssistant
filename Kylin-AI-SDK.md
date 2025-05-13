# 麒麟AI SDK 精华指南

## 一、SDK简介
麒麟AI SDK 统一封装了多种AI能力，提供标准C语言接口，屏蔽不同大模型的差异，便于开发者集成。主要分为：
- 传统AI能力：文字识别、语音识别/合成、向量化等
- 生成式AI能力：文本生成、图像生成

## 二、支持环境与前提条件
- 仅支持银河麒麟操作系统（2503版本），x86/arm 架构
- 需在"设置->AI模块管理"下载安装AI子系统及各能力开发包
- 端侧能力仅适配部分整机型号（详见原文档）

## 三、API使用流程
1. 创建会话实例
2. 初始化会话，设置回调函数
3. 调用具体业务接口
4. 任务串行执行，需并发时可多会话
5. 需全局配置模型参数（如文本/图像/语音）

## 四、主要能力与典型用法

### 1. 文字识别（OCR）
- 安装：`sudo apt install libkysdk-coreai-vision-dev`
- 典型流程：
  1. 创建/初始化会话
  2. 设置模型配置（可选）
  3. 设置结果回调
  4. 调用 `text_recognition_recognize_text_from_image_file_async` 或 `text_recognition_recognize_text_from_image_data_async`
- 结果可获取文本内容、坐标、错误码等

### 2. 语音识别/合成
- 安装：
  - 识别：`sudo apt install libkysdk-coreai-speech-dev`
  - 合成：`sudo apt install libkysdk-coreai-speech-dev`
- 典型流程：
  1. 创建/初始化会话
  2. 设置音频/模型配置
  3. 设置回调
  4. 调用识别/合成接口（支持流式/一次性/异步）
- 结果可获取文本、音频数据、错误码等

### 3. 向量化（Embedding）
- 安装：`sudo apt install libkylin-coreai-embedding-dev`
- 支持文本和图像向量化，接口同步/异步均可
- 典型流程：
  1. 创建/初始化会话
  2. 设置模型配置
  3. 调用向量化接口，获取向量结果

### 4. 生成式AI能力
#### 4.1 文本生成/对话
- 安装：`sudo apt install libkysdk-genai-nlp-dev`
- 支持多模型/多部署类型（云端/端侧/自定义）
- 典型流程：
  1. 创建/初始化会话
  2. 设置模型配置（如模型名、top_k、部署类型）
  3. 设置回调
  4. 调用 `genai_text_generate_content_async` 或 `genai_text_chat_async`
- 支持历史消息缓存、系统提词等

#### 4.2 图像生成
- 安装：`sudo apt install libkysdk-genai-vision-dev`
- 支持多风格、多分辨率、多语种，当前仅云端
- 典型流程：
  1. 创建/初始化会话
  2. 设置图像生成配置（风格、尺寸、数量等）
  3. 设置回调
  4. 调用 `genai_image_generate_image_async`

## 五、常见错误码
- AISDK_NO_ERROR = 0：无错误
- AISDK_NET_ERROR：网络错误
- AISDK_AUTHENTICATION_FAILURE：鉴权失败
- AISDK_RUNTIME_ERROR：服务运行时错误
- AISDK_TOO_MANY_REQUESTS：请求过多
- AISDK_SERVICE_TIMEOUT：服务超时
- AISDK_BAD_REQUEST：参数错误
- AISDK_MODEL_RUN_FAILED：模型运行失败
- 具体能力模块有专属错误码（如OCR/生成式NLP/图像生成等）

## 六、重点注意事项
- 使用前务必安装AI子系统及各能力开发包
- 端侧能力仅支持部分机型，云端需配置账号
- 每个会话实例仅支持串行任务，需并发请多实例
- 模型/能力配置建议在"设置->AI模块管理"中统一管理

---

如需详细API参数、完整示例代码、错误码列表等，请参考[原始开发指南文档](./Kylin_AI_SDK.md)。 