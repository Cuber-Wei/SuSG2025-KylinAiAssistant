# 麒麟 AI SDK 开发指南

麒麟AI SDK开发指南
## 1. 概述
## 1. 麒麟AI SDK将AI能力统一抽象封装为C语言接口，屏蔽了各个大模型的接口差异，降低了应用集
成AI能力的门槛。麒麟AI SDK主要分为传统AI能力接口和生成式AI能力接口。传统AI能力接口
包括文字识别、音频处理和向量化等能力，生成式AI能力接口包括文本生成和图像生成等能力接
口；
## 2. 当前为1.1版本。
## 2. 前提条件
## 1. 基于已发布的银河麒麟操作系统（2503版本）；
## 2. 端侧能力目前只能在x86和arm机器上运行，对于其他的机型效果无法保证，已适配的具体机型
如下：
整机型号 具体配置
联想开天M90fG1s CPU:D3000内存：16G独立显卡：Arise-GT10C0t硬盘：512G
联想开天M90hG1t CPU:HygonC86-3G(OPN:3350)内存：16GB独立显卡：Arise-GT10C0t硬盘：
512GB
联想开天P90zG1t CPU:ZHAOXINKaiXianKX-7000内存：16GB独立显卡：Arise-GT10C0t硬盘：
1TB
## 3. 在使用任何接口之前需要在"设置->AI模块管理"中下载安装AI子系统。其次需要安装每种能力的
开发包，具体参考每种能力的接口说明。
## 3. API使用流程说明
## 3.1 使用流程说明
## 1. 使用任何接口之前需要创建会话实例；
## 2. 初始化会话实例，如果发生错误，初始化接口会返回具体的错误码；
## 3. 初始化成功之后设置结果回调函数，然后调用具体的业务接口；
## 4. 如果初始化失败并处理完错误，需要重新初始化会话实例；

## 5. 每个会话同时只能处理一个任务，如果同时调用多次业务接口，任务将串行执行，结果也是按照顺
序返回；
## 6. 如果要执行并发，可创建多个会话进行实现。
## 3.2 模型配置
## 1. 模型配置是全局的，调用文本对话、文生图和语音相关接口之前，需要对模型配置进行相关的配
置；
## 2. 模型配置可以在"设置->AI模块管理"中进行配置。
## 4. API详细说明

## 4.1 传统AI能力接口
## 4.1 .1文字识别
## 1. 文字识别接口将图像中的文字转换为文本，并提供文本行数和坐标等信息；
## 2. 目前仅支持使用AI子系统自带的端侧模型进行识别；
## 3. 通过"设置->AI模块管理"下载AI子系统之后，不需要进行任何配置即可使用。 
## 4.1 .1.1开发环境部署
```bash
sudo apt install libkysdk-coreai-vision-dev
```
## 4.1 .1.2文字识别会话
## 4.1 .1.2.1创建会话
头件 <coreai/vision/textrecognition.h>
函数 TextRecognitionSession*text_recognition_create_session()
描述 创建文字识别会话
参数 无
返回值 TextRecognitionSession类型的指针
## 4.1 .1.2.2初始化会话
头件 <coreai/vision/textrecognition.h>
函数 int text_recognition_init_session(TextRecognitionSession*session)
描述 初始化文字识别会话
参数 session：文字识别会话的指针
返回值 返回初始化的结果，初始化成功返回0，否则返回对应的错误码
## 4.1 .1.2.3销毁会话
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_destroy_session(TextRecognitionSession**session)

描述 销毁文字识别会话
参数 session：文字识别会话的指针地址
返回值 无
## 4.1 .1.2.4设置文字识别结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_result_set_callback(TextRecognitionSession*session,
TextRecognitionResultCallback callback,
void*user_data)
描述 设置文字识别结果的回调函数
参数 session：文字识别会话的指针
callback：TextRecognitionResultCallback类型的结果回调函数
user_data：调用者自定义的数据
返回值 无
## 4.1 .1.2.5设置模型配置信息
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_set_model_config(
TextRecognitionSession*session,
TextRecognitionModelConfig*config)
描述 设置文字识别的模型配置信息
参数 session：文字识别会话的指针
config：模型配置
返回值 无
## 4.1 .1.2.6图片文件文字识别
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_recognize_text_from_image_file_async(
TextRecognitionSession*session,
const char*image_file)
描述 进行图片文件的文字识别

参数 session：文字识别会话的指针
image_file：图片文件的路径
返回值 无
## 4.1 .1.2.7图片数据文字识别
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_recognize_text_from_image_data_async(
TextRecognitionSession*session,
const char*image_data,
unsigned int image_data_length)
描述 进行图片数据的文字识别
参数 session：文字识别会话的指针
image_data：待识别的图片数据指针，不需要转码，图片格式数据即可
image_data_length：待识别的图片数据长度
返回值 无
## 4.1 .1.3设置配置信息
可以明确指定要使用的模型或者部署类型，当前版本可以无需关注，默认会使 AI 系统集成的模型。
## 4.1 .1.3.1创建模型配置
头件 <coreai/vision/config.h>
函数 TextRecognitionModelConfig*text_recognition_model_config_create()
描述 创建模型配置实例
参数 无
返回值 模型配置实例指针
## 4.1 .1.3.2销毁模型配置实例
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_destroy(TextRecognitionModelConfig**config)

描述 销毁模型配置实例
参数 config：模型配置实例指针的地址
返回值 无
## 4.1 .1.3.3设置使用的模型名称
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_set_name(TextRecognitionModelConfig*config,
const char*name)
描述 设置要使用的模型名称，不指定时使用默认的模型
参数 config：模型配置实例的指针
name：设置的模型名字
返回值 无
## 4.1 .1.3.4设置使用的模型的部署类型
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_set_deploy_type(
TextRecognitionModelConfig*config,
ModelDeployType type)
描述 设置使用的模型的部署类型，不指定时使用默认部署类型的模型
参数 config：模型配置实例的指针
type：指定的模型部署类型
返回值 无
## 4.1 .1.4结果处理
## 4.1 .1.4.1结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 typedef void (*TextRecognitionResultCallback)(TextRecognitionResult*result, void*user_data)
描述 进行图片数据的文字识别

参数 result：TextRecognitionResult类型的识别结果指针
user_data：定义的数据
返回值 无
## 4.1 .1.4.2结果解析
## 1. 获取一行文本中的内容
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_line_get_value(TextLine*text_line)
描述 获取一行文本中的内容
参数 text_line：TextLine类型的指针
返回值 返回该行文本的指针
## 2. 获取一行文本的角点位置信息（四个角的位置信息）
头件 <coreai/vision/textrecognitionresult.h>
函数 PixelPoint*text_line_get_corner_points(TextLine*text_line, int*point_number)
描述 获取一行文本的角点位置信息（四个角的位置信息）
参数 text_line：TextLine类型的指针
point_number：角点个数，固定输出为4
返回值 返回四个点的坐标，顺序为左上、左下、右上、右下。
## 3. 获取识别结果的整体文本信息
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_recognition_result_get_value(TextRecognitionResult*result)
描述 获取识别结果的整体文本信息，不带格式
参数 result：TextRecognitionResult类型的识别结果指针
返回值 返回所有文本的内容

## 4. 获取识别的文本结果和行数
头件 <coreai/vision/textrecognitionresult.h>
函数 TextLine**text_recognition_result_get_text_lines(TextRecognitionResult*result, int*line_count)
描述 获取识别的文本结果和行数
参数 result：TextRecognitionResult类型的识别结果
line_count：文本行数
返回值 返回 TextLine*类型的数组的地址，TextLine结果中包含文本信息和坐标信息
## 5. 获取错误码
头件 <coreai/vision/textrecognitionresult.h>
函数 int text_recognition_result_get_error_code(TextRecognitionResult*result)
描述 获取识别结果中的错误码
参数 result：TextRecognitionResult类型的识别结果
返回值 返回具体的错误码，参考通用错误码和文字识别专有错误码
## 6. 获取错误信息
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_recognition_result_get_error_message(TextRecognitionResult*result)
描述 获取识别结果中的错误信息
参数 result：TextRecognitionResult类型的识别结果
返回值 如果发生错误则返回具体的错误信息，否则返回空
## 4.1 .1.5错误码
通用错误码可参考4.3章节，文字识别专有错误码如下：
头件 <coreai/vision/error.h>

枚举 OcrErrorCode {
OCR_IMAGE_ERROR = 100,
OCR_PARAM_INVALID,
} OcrErrorCode;
描述 文字识别相关的错误码
成员 OCR_IMAGE_ERROR：数据文件无效
OCR_PARAM_INVALID：参数无效
## 4.1 .1.6示例
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
include_directories(${GIO_INCLUDE_DIRS})
pkg_check_modules(KYSDK_AI_VISION kysdk-coreai-vision)
include_directories(${KYSDK_AI_VISION_INCLUDE_DIRS})
target_link_libraries(
XXXX
pthread
${GIO_LIBRARIES}
${KYSDK_AI_VISION_LIBRARIES}
)
从图像文件识别
```c
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <iostream>
# include <thread>
const char *TEST_FILE_PATH = "/home/kylin/Kylinproject/test2.png";
void callback(TextRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing results.\n");
int textLineNum = 0, pointsNum = 0;

fprintf(stdout, "text        : %s\n",
text_recognition_result_get_value(result));
fprintf(stdout, "err code    : %i\n",
text_recognition_result_get_error_code(result));
fprintf(stdout, "err message : %s\n",
text_recognition_result_get_error_message(result));
_TextLine **textline =
text_recognition_result_get_text_lines(result, &textLineNum);
if (textline == nullptr) {
fprintf(stderr, "The result is invalid, please check image\n");
return;
}
for (int i = 0; i < textLineNum; ++i) {
PixelPoint *point =
text_line_get_corner_points(textline[i], &pointsNum);
if (point == nullptr) {
fprintf(stderr, "No point\n");
return;
}
fprintf(stdout, "The %i line text: %s\n", i,
text_line_get_value(textline[i]));
for (int i = 0; i < pointsNum; i++) {
printf("The corner points text %d: (%d, %d)\n", i, point[i].x,
point[i].y);
}
}
if (user_data != nullptr) {
const char *userData = static_cast<const char *>(user_data);
fprintf(stdout, "%s\n", userData);
} else {
fprintf(stdout, "user data is nullptr\n");
}
fprintf(stdout, "Printing result completed.\n");
}
void test01_OcrFromFile() {
const char *userData = "Test genai vision from image file\n";
TextRecognitionSession *session = text_recognition_create_session();
TextRecognitionModelConfig *config =
text_recognition_model_config_create();

text_recognition_model_config_set_name(config, "vision");
text_recognition_model_config_set_deploy_type(config,
ModelDeployType::OnDevice);
text_recognition_set_model_config(session, config);
text_recognition_init_session(session);
text_recognition_result_set_callback(session, callback, (void *)userData);
text_recognition_recognize_text_from_image_file_async(session,
TEST_FILE_PATH);
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, &config, pMainLoop] {
while (std::getchar() != '\n') {
}
text_recognition_destroy_session(&session);
text_recognition_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
});
ctrlThread.detach();
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}
从图像数据识别
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
const char *TEST_DATA_PATH = "/home/kylin/Kylinproject/test1";
void callback(TextRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing results.\n");
int textLineNum = 0, pointsNum = 0;
fprintf(stdout, "text        : %s\n",
text_recognition_result_get_value(result));
fprintf(stdout, "err code    : %i\n",
text_recognition_result_get_error_code(result));
fprintf(stdout, "err message : %s\n",
text_recognition_result_get_error_message(result));
_TextLine **textline =
text_recognition_result_get_text_lines(result, &textLineNum);
if (textline == nullptr) {
fprintf(stderr, "The result is invalid, please check image\n");
return;
}
for (int i = 0; i < textLineNum; ++i) {
PixelPoint *point =
text_line_get_corner_points(textline[i], &pointsNum);
if (point == nullptr) {
fprintf(stderr, "No point\n");
return;
}
fprintf(stdout, "The %i line text: %s\n", i,
text_line_get_value(textline[i]));
for (int i = 0; i < pointsNum; i++) {
printf("The corner points text %d: (%d, %d)\n", i, point[i].x,
point[i].y);
}
}
if (user_data != nullptr) {
const char *userData = static_cast<const char *>(user_data);
fprintf(stdout, "%s\n", userData);
} else {
fprintf(stdout, "user data is nullptr\n");
}
fprintf(stdout, "Printing result completed.\n");
}
std::vector<char> readImageData(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary);
if (!file.is_open()) {
fprintf(stderr, "Failed to open file: %s\n", filePath.c_str());
return {};
}
file.seekg(0, std::ios::end);
std::streampos fileSize = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<char> imageData(fileSize);
file.read(reinterpret_cast<char *>(imageData.data()), fileSize);
return imageData;
}
void test02_OcrFromData() {
namespace fs = std::filesystem;
if (not fs::exists(TEST_DATA_PATH)) {
fprintf(stderr, "error\n");
return;
}
const char *userData = "Test genai vision from image data\n";
const std::vector<char> imageData = readImageData(TEST_DATA_PATH);
TextRecognitionSession *session = text_recognition_create_session();
TextRecognitionModelConfig *config =
text_recognition_model_config_create();
text_recognition_set_model_config(session, config);
text_recognition_init_session(session);
text_recognition_result_set_callback(session, callback, (void*)userData);
text_recognition_recognize_text_from_image_data_async(
session, imageData.data(), imageData.size());
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, &config, pMainLoop] {
while (std::getchar() != '\n') {
}
text_recognition_model_config_destroy(&config);
text_recognition_destroy_session(&session);
g_main_loop_quit(pMainLoop);
});
ctrlThread.detach();
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}

## 4.1 .2频处理
## 4.1 .2.1开发环境部署
```bash
sudo apt install libkysdk-coreai-speech-dev
```
## 4.1 .2.2语识别
## 1. 将语识别接将频信息转换为本；
## 2. 前仅持中；
## 3. 持流式和流式语识别；
## 4. 持识别发（如果云端服务持的话）；
## 5. 前仅持云端服务的形式，端侧模型咱不持；
## 6. 需要在设置->AI模块管理中进配置才能使。
## 4.1 .2.2.1创建会话
头件 <coreai/speech/recognizer.h>
函数 SpeechRecognitionSession*speech_recognizer_create_session()
描述创建语识别会话
参数
返回值 SpeechRecognitionSession类型的指针
## 4.1 .2.2.2初始化会话
头件 <coreai/speech/recognizer.h>
函数 intspeech_recognizer_init_session(SpeechRecognitionSession*session)
描述初始化语识别会话
参数 session：语识别会话的指针
返回值返回初始化的结果，初始化成功返回0，否则返回对应的错误码
## 4.1 .2.2.3销毁会话
头件 <coreai/speech/recognizer.h>

函数 voidspeech_recognizer_destroy_session(SpeechRecognitionSession**session)
描述销毁语识别会话
参数 session：语识别会话指针的地址
返回值
## 4.1 .2.2.4设置语识别结果回调函数
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_result_set_callback(SpeechRecognitionSession*session,
SpeechRecognitionResultCallbackcallback,void*user_data)
描述设置语识别的结果回调函数
参数 session：语识别会话的指针
callback:SpeechRecognitionResultCallback类型的结果回调函数
user_data:调者定义的数据
返回值
## 4.1 .2.2.5设置输频配置信息
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_set_audio_config(SpeechRecognitionSession*session,
AudioConfig*audio_config)
描述设置频相关的配置，如输频的来源等
参数 session：语识别会话的指针
audio_config:语相关的配置
返回值
## 4.1 .2.2.6设置模型配置信息
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_set_model_config(SpeechRecognitionSession*session,
SpeechModelConfig*config)

描述设置模型配置信息
参数 session：字识别会话的指针
config：模型配置
返回值
## 4.1 .2.2.7开始异步流式语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_start_continuous_recognition_async(SpeechRecognitionSession
- session)
描述开始流式异步语识别，如果使的频流，建议每40ms发送1280个字节。结果通过callback
异步返回。
参数 session：语识别会话的指针
返回值
## 4.1 .2.2.8停异步流式语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_stop_continuous_recognition_async(SpeechRecognitionSession
- session)
描述停异步流式语识别
参数 session：语识别会话的指针
返回值
## 4.1 .2.2.9进次性语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_recognize_once_async(
SpeechRecognitionSession*session)
描述进次性语识别，识别完整个件或者整段数据时返回结果。结果通过callback异步返回。
参数 session：语识别会话的指针

返回值
## 4.1 .2.2.10结果处理
## 4.1 .2.2.10.1结果回调函数
头件 <coreai/speech/result.h>
类型 typedefvoid(*SpeechRecognitionResultCallback)(
SpeechRecognitionResult*result,void*user_data)
描述语识别结果回调函数类型
参数 result：SpeechRecognitionResult类型的指针
user_data:数据
返回值
## 4.1 .2.2.10.2结果解析
## 1. 获取识别结果状态
头件 <coreai/speech/result.h>
函数 SpeechResultReasonspeech_recognition_result_get_reason(
SpeechRecognitionResult*result);
描述获取语识别结果的状态
参数语识别结果的指针
返回值语识别结果的状态
## 2. 获取识别的本数据
头件 <coreai/speech/result.h>
函数 constchar*speech_recognition_result_get_text(
SpeechRecognitionResult*result)
描述获取语识别结果中的本数据
参数语识别结果的指针

返回值语识别结果的本数据
## 3. 获取发的id
头件 <coreai/speech/result.h>
函数 intspeech_recognition_result_get_speaker_id(
SpeechRecognitionResult*result)
描述获取语识别结果中的说话id
参数语识别结果的指针
返回值 如果识别到发，返回于0的id
否则返回-1
## 4. 获取错误码
头件 <coreai/speech/result.h>
函数 intspeech_recognition_result_get_error_code(
SpeechRecognitionResult*result)
描述获取语识别结果中的错误码
参数语识别结果的指针
返回值具体的错误码
## 5. 获取具体错误信息
头件 <coreai/speech/result.h>
函数 constchar*speech_recognition_result_get_error_message(
SpeechRecognitionResult*result);
描述获取语识别结果中的具体错误信息
参数语识别结果的指针
返回值具体的错误信息

## 4.1 .2.3语合成
## 1. 将纯本内容合成为频；
## 2. 暂时不持设置发；
## 3. 暂时仅持中；
## 4. 前仅持云端服务的形式；
## 5. 需要在设置->AI模块管理中进配置之后才能使。
## 4.1 .2.3.1创建会话
头件 <coreai/speech/synthesizer.h>
函数 SpeechSynthesizerSession*speech_synthesizer_create_session()
描述创建语合成的会话
参数
返回值语合成会话的指针
## 4.1 .2.3.2初始化会话
头件 <coreai/speech/synthesizer.h>
函数 intspeech_synthesizer_init_session(
SpeechSynthesizerSession*session)
描述初始化语合成的会话
参数语合成会话的指针
返回值初始化结果，0表成功；于0时表具体的错误码
## 4.1 .2.3.3销毁会话
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_destroy_session(SpeechSynthesizerSession**session)
描述销毁语合成会话
参数语合成会话指针的地址

返回值
## 4.1 .2.3.4设置语合成结果回调函数
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_result_set_callback(SpeechSynthesizerSession*session,
SpeechSynthesisResultCallbackcallback,
void*user_data)
描述设置语合成的结果回调函数
参数 session:语合成会话的指针
callback:语合成的结果回调函数
返回值
## 4.1 .2.3.5设置输出频配置信息
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_set_audio_config(SpeechSynthesizerSession*session,
AudioConfig*audio_config)
描述设置语合成输出频的相关配置
参数 session:语合成会话的指针
audio_config:具体的频配置
返回值
## 4.1 .2.3.6设置模型配置信息
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_set_model_config(SpeechRecognitionSession*session,
SpeechModelConfig*config)
描述设置模型配置信息
参数 session：字识别会话的指针
config：模型配置
返回值

## 4.1 .2.3.7进语合成
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_synthesize_text_async(SpeechSynthesizerSession*session,const
char*text,uint32_ttext_length)
描述将本内容合成为语数据
参数 session：语合成会话的指针
text:本数据指针
text_length:本度
返回值
## 4.1 .2.3.8停播放频
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_stop_speaking(SpeechSynthesizerSession*session)
描述停语播放，当频输出配置为系统播放器时该接效
参数 session：语合成会话的指针
返回值
## 4.1 .2.3.9结果处理
## 4.1 .2.3.9.1结果回调函数
头件 <coreai/speech/result.h>
类型 typedefvoid(*SpeechSynthesisResultCallback)(SpeechSynthesisResult*result,void
- user_data)
描述语合成结果回调函数类型
参数 result：SpeechSynthesisResult类型的指针
user_data:数据
返回值

## 4.1 .2.3.9.2结果解析
## 1. 获取语合成结果的状态
头件 <coreai/speech/result.h>
函数 SpeechResultReasonspeech_synthesis_result_get_reason(SpeechSynthesisResult*result)
描述获取语合成结果的状态
参数语合成结果的指针
返回值语合成结果的状态
## 2. 获取语合成结果的数据
头件 <coreai/speech/result.h>
函数 constuint8_t*speech_synthesis_result_get_data(SpeechSynthesisResult*result,uint8_t
- data_length)
描述获取语合成的数据
参数 result:语合成结果的指针
data_length:输出参数，频数据的度
返回值语合成的频数据的指针
## 3. 获取语合成结果的频数据格式
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_audio_format(SpeechSynthesisResult*result)
描述获取语合成结果的频数据格式
参数语合成结果的指针
返回值具体的频数据格式
## 4. 获取语合成结果的频数据采样率
头件 <coreai/speech/result.h>

函数 intspeech_synthesis_result_get_audio_rate(SpeechSynthesisResult*result)
描述获取语合成结果的频数据采样率
参数语合成结果的指针
返回值具体的频数据采样率
## 5. 获取语合成结果的频数据通道数
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_audio_channel(SpeechSynthesisResult*result)
描述获取语合成结果的频数据通道数
参数语合成结果的指针
返回值具体的频数据通道数
## 6. 获取语合成结果的错误码
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_error_code(SpeechSynthesisResult*result)
描述获取语合成结果的错误码
参数语合成结果的指针
返回值具体的错误码
## 7. 获取语合成结果的错误信息
头件 <coreai/speech/result.h>
函数 constchar*speech_synthesis_result_get_error_message(SpeechSynthesisResult*result)
描述获取语合成结果的具体错误信息
参数语合成结果的指针
返回值具体的错误信息

## 4.1 .2.4频结果状态
头件<coreai/speech/result.h>
枚举 typedefenum{
SPEECH_ERROR_OCCURRED=1，
SPEECH_RECOGNITION_STARTED=2，
SPEECH_RECOGNIZING=3，
SPEECH_RECOGNIZED=4，
SPEECH_RECOGNITION_COMPLETED=5，
SPEECH_SYNTHESIS_STARTED=6，
SPEECH_SYNTHESIZING=7，
SPEECH_SYNTHESIS_COMPLETED=8
}SpeechResultReason;
描述 SPEECH_ERROR_OCCURRED：语识别或者合成过程中出错
SPEECH_RECOGNITION_STARTED：语识别已启动
SPEECH_RECOGNIZING：正在进语识别，中间结果
SPEECH_RECOGNIZED：语识别的最终结果，在SPEECH_RECOGNIZING的基础上经过修正
的结果
SPEECH_RECOGNITION_COMPLETED：语识别完成
SPEECH_SYNTHESIS_STARTED：语合成已启动
SPEECH_SYNTHESIZING：正在进语合成
SPEECH_SYNTHESIS_COMPLETED：语合成已完成
## 4.1 .2.5频配置
## 4.1 .2.5.1输频配置-语识别
## 1. 配置输频数据系统默认克获取，适于流式语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_continuous_audio_input_from_default_microphone()
描述创建频配置，输频数据从默认克中获取
参数

返回值频配置实例指针
## 2. 配置输频数据从数据流中获取，适于流式语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_continuous_audio_input_from_audio_data_stream(
AudioDataStream*stream)
描述创建频配置，使频数据流作为输频
参数 stream:频数据流
返回值频配置实例指针
## 3. 配置输频从pcm数据中获取，适于次性语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_once_audio_input_from_pcm_data(constuint8_t
- audio_data,uint32_tdata_length)
描述创建频配置，使pcm频数据作为输频
参数 audio_data:pcm频数据指针
data_length:pcm频数据度
返回值频配置指针
## 4. 配置输频从pcm件中获取数据，适于次性语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_once_audio_input_from_pcm_file(constchar*pcm_file)
描述创建频配置，使pcm件作为输频
参数 pcm_file:pcm件
返回值频配置指针
## 4.1 .2.5.2输出频配置-语合成
## 1. 配置语以原始数据输出

头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_pcm_data()
描述创建频配置，将合成的频以原始数据形式输出。结果通过callback异步返回。
参数
返回值频配置实例指针
## 2. 配置语输出到pcm件
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_pcm_file_name(constchar
- pcm_file)
描述创建频配置，将合成的频输出到pcm件
参数 pcm_file:输出保存的pcm件
返回值频配置实例指针
## 3. 配置语输出到系统默认扬声器
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_default_speaker()
描述创建频配置，使系统默认的扬声器作为频输出
参数
返回值频配置实例指针
## 4.1 .2.6模型配置信息
## 4.1 .2.6.1创建模型配置
头件 <coreai/speech/config.h>
函数 SpeechModelConfig*speech_model_config_create()
描述创建模型配置实例

参数
返回值模型配置实例指针
## 4.1 .2.6.2销毁模型配置实例
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_destroy(SpeechModelConfig**config)
描述销毁模型配置实例
参数 config：模型配置的级指针
返回值
## 4.1 .2.6.3设置使的模型名称
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_set_name(SpeechModelConfig*config,constchar*name)
描述设置模型名称
参数 config：模型配置的实例指针
name：设置的模型名字
返回值
## 4.1 .2.6.4设置使的模型类型
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_set_deploy_type(SpeechModelConfig*config,ModelDeployType
type)
描述设置模型类型
参数 config：模型配置的实例指针
ModelDeployType：设置的模型类型
返回值
## 4.1 .2.7错误码

通错误码参考4.3节，语处理专有错误码如下：
头件 <coreai/speech/error.h>
枚举 typedefenum{
SPEECH_RECOGNITION_AUDIO_DATA_SIZE_INVALID=100,
SPEECH_SYNTHESIS_TEXT_LENGTH_INVALID,
SPEECH_PARAM_INVALID,
SPEECH_DEFAULT_MICROPHONE_INVALID,
SPEECH_UNKNOWN_ERROR,
SPEECH_UNSUPPORTED_LANGUAGE
}SpeechErrorCode;
描述 语相关的错误码
成员 SPEECH_RECOGNITION_AUDIO_DATA_SIZE_INVALID：频超限
SPEECH_SYNTHESIS_TEXT_LENGTH_INVALID：输本度超限
SPEECH_PARAM_INVALID：配置参数不合法
SPEECH_DEFAULT_MICROPHONE_INVALID：未配置默认克
SPEECH_UNKNOWN_ERROR：未知错误
SPEECH_UNSUPPORTED_LANGUAGE：不持的语
其余通错误码，具体参考3.3节
## 4.1 .2.8例
## 4.1 .2.8.1前提条件
在设置->AI模块管理中已经对语相关的模型进了配置。
## 4.1 .2.8.2语识别
配置CMakeLists.txt
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
include_directories(${GIO_INCLUDE_DIRS})
pkg_check_modules(KYAISPEECH kysdk-coreai-speech)
include_directories(${KYAISPEECH_INCLUDE_DIRS})
target_link_libraries(
xxx1

pthread
${GIO_LIBRARIES}
${KYAISPEECH_LIBRARIES}
)
具体demo：
# include <filesystem>
# include <fstream>
# include <vector>
// glib header
# include <gio/gio.h>
// kysdk-ai header
# include <coreai/speech/recognizer.h>
const char *PCM_FILE_PATH = "xxx.pcm";
std::vector<uint8_t> readAudioData(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary);
if (!file.is_open()) {
return {};
}
file.seekg(0, std::ios::end);
std::streampos fileSize = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> audioData(fileSize);
file.read(reinterpret_cast<char *>(audioData.data()), fileSize);
return audioData;
}
void callback(SpeechRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing speech recognition results.\n");
fprintf(stdout, "Speech recognition errorcode: %d\n",
speech_recognition_result_get_error_code(result));
fprintf(stdout, "Speech recognition error message: %s\n",
speech_recognition_result_get_error_message(result));
int resultType = speech_recognition_result_get_reason(result);
const char *resultData = speech_recognition_result_get_text(result);
fprintf(stdout, "Speech recognition result: %s\n", resultData);
int resultErrorCode = speech_recognition_result_get_error_code(result);
fprintf(stdout, "Printing speech recognition result completed.\n");
}
void Test_RecognitionOnce() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
if (not std::filesystem::exists(PCM_FILE_PATH)) {
fprintf(stderr, "Flie not exists !\n");
return;
}
std::vector<uint8_t> audioData = readAudioData(PCM_FILE_PATH);
SpeechRecognitionSession *session = speech_recognizer_create_session();
SpeechModelConfig *modelconfig = speech_model_config_create();
speech_model_config_set_name(modelconfig,
"讯-语模型 ");  //或"百度 - 语模型 "
speech_model_config_set_deploy_type(modelconfig,
ModelDeployType::PublicCloud);
speech_recognizer_set_model_config(session, modelconfig);
speech_recognizer_init_session(session);
speech_recognizer_result_set_callback(session, callback, nullptr);
auto *config = audio_config_create_once_audio_input_from_pcm_data(
audioData.data(), audioData.size());
speech_recognizer_set_audio_config(session, config);
speech_recognizer_recognize_once_async(session);
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}
# include <fstream>
# include <filesystem>
# include <vector>
# include <coreai/speech/synthesizer.h>
# include <gio/gio.h>
static void writeBinaryDataToFile(const std::string &filename,
const std::vector<char> &data) {
if (data.size() == 0) {
fprintf(stderr, "Data is empty!\n");
return;
}
std::ofstream outputFile(filename, std::ios::out | std::ios::binary |
std::ios::app);
if (!outputFile.is_open()) {
fprintf(stderr, "File open failed!\n");
return;
}
outputFile.write(reinterpret_cast<const char*>(data.data()), data.size());
outputFile.close();
}
void onSynthesisResult(SpeechSynthesisResult *result, void *userData) {
fprintf(stdout, "Start writing the synthesized results to a file.\n");
const char *userdata = static_cast<const char*>(userData);
uint32_t audioDataLength;
const uint8_t* audioData = speech_synthesis_result_get_data(result,
&audioDataLength);
SpeechResultReason resultType =
speech_synthesis_result_get_reason(result);
std::fprintf(
stdout,
"test Synthesis result reason=%i audioDataLength=%i userData=%s \n",
(int)resultType, (int)audioDataLength, userdata);
std::vector<char> data {audioData, audioData + audioDataLength };
writeBinaryDataToFile("../testsynthesis.pcm", data);
fprintf(stdout, "Write completed.\n");
}
void testSynthesisOutputPcmData() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
auto *synthesizerConfig =
audio_config_create_audio_output_from_pcm_data();
SpeechSynthesizerSession *synSession =
speech_synthesizer_create_session();
SpeechModelConfig *modelconfig = speech_model_config_create();
speech_model_config_set_name(modelconfig, "讯-语模型 ");//或"百度 - 语
模型"
speech_model_config_set_deploy_type(modelconfig,
ModelDeployType::PublicCloud);
speech_synthesizer_set_model_config(synSession, modelconfig);
speech_synthesizer_result_set_callback(synSession, onSynthesisResult,
nullptr);
speech_synthesizer_init_session(synSession);
audio_config_set_input_audio_rate(synthesizerConfig, 16000);
speech_synthesizer_set_audio_config(synSession, synthesizerConfig);
speech_synthesizer_synthesize_text_async(synSession, "你好", 100);
int stopErrorCode = speech_synthesizer_stop_speaking(synSession);
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}
find_package(PkgConfig REQUIRED)
pkg_check_modules(Embedding REQUIRED IMPORTED_TARGET kysdk-coreai-embedding)
target_link_libraries(
xxx
pthread
${GIO_LIBRARIES}
PkgConfig::Embedding
)
# include <coreai/embedding/embedding.h>
# include <iostream>
void textEmbeddingSync() {
TextEmbeddingSession *session = text_embedding_create_session();
int initSession = text_embedding_init_session(session);
if (initSession != 0) {
std::cout << "init session failed" << std::endl;
}
// 同步接
EmbeddingResult *result = nullptr;
bool sucess = text_embedding(session, "12345", &result);
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << ",";
}
std::cout << std::endl;
char *info = nullptr;
text_embedding_get_model_info(session, &info);
std::cout << "print model info:" << info << std::endl;
std::cout << "释放结果资源 " << std::endl;
embedding_result_destroy(&result);
embedding_model_info_destroy(info);
text_embedding_destroy_session(&session);
}
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <gio/gio.h>
# include <thread>
void callback(EmbeddingResult *result, void *callback_user_data) {
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << " ";
}
std::cout << std::endl;
if (callback_user_data != nullptr) {
int *a = static_cast<int *>(callback_user_data);
std::cout << "user_data :" << *a << std::endl;
}
}
void textEmbeddingAsync() {
TextEmbeddingSession *session = text_embedding_create_session();
if (text_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
text_embedding_async(session, "热爱学习 ", callback, nullptr);
auto *loop_ = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, loop_] {
while (std::getchar() != '\n') {
}
g_main_loop_quit(loop_);
});
ctrlThread.detach();
g_main_loop_run(loop_);
text_embedding_destroy_session(&session);
}
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <filesystem>
# include <vector>
# include <fstream>
std::vector<uint8_t> readFile(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary | std::ios::ate);
if (!file.is_open()) {
throw std::runtime_error("Failed to open file");
}
std::streamsize size = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> buffer(size);
if (file.read(reinterpret_cast<char *>(buffer.data()), size)) {
return buffer;
} else {
throw std::runtime_error("Failed to read file");
}
}
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64Encode(const std::vector<uint8_t> &buffer) {
std::string encodedData;
int i = 0;
uint8_t char_array_3[3];
uint8_t char_array_4[4];
while (i < buffer.size()) {
char_array_3[0] = buffer[i++];
char_array_3[1] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_3[2] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
char_array_4[1] =
((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
char_array_4[2] =
((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
char_array_4[3] = (char_array_3[2] & 0x3f);
for (int j = 0; (j < 4); ++j) {
encodedData += base64_chars[char_array_4[j]];
}
}
while ((encodedData.size() % 4) != 0) {
encodedData += '=';
}
return encodedData;
}
void imageEmbeddingSync() {
ImageEmbeddingSession *session = image_embedding_create_session();
if (image_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
namespace fs = std::filesystem;
fs::path dir = fs::path(__FILE__).parent_path();
fs::path path = dir / " 微信图 _20240709181353.jpg";
std::string imagePath = path.string();
std::vector<uint8_t> imageData = readFile(imagePath);
std::string base64Data = base64Encode(imageData);
unsigned int length = base64Data.length();
const char *charPtr = base64Data.c_str();
const unsigned char *ucharPtr =
reinterpret_cast<const unsigned char *>(charPtr);
# if 1  // 同步向量化本
EmbeddingResult *result = nullptr;
text_embedding_by_image_model(session, "do you love working?", &result);
# elif
// 同步向量化图
EmbeddingResult *result = nullptr;
image_embedding_by_image_file(session, path.string().c_str(),
&result);  // 换成路径的图
# else
// 同步向量化 base64 图
EmbeddingResult *result = nullptr;
image_embedding_by_base64_image_data(session, ucharPtr, length, &result);
# endif
}
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <gio/gio.h>
# include <thread>
# include <vector>
# include <fstream>
void callback(EmbeddingResult *result, void *callback_user_data) {
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << " ";
}
std::cout << std::endl;
if (callback_user_data != nullptr) {
int *a = static_cast<int *>(callback_user_data);
std::cout << "user_data :" << *a << std::endl;
}
}
std::vector<uint8_t> readFile(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary | std::ios::ate);
if (!file.is_open()) {
throw std::runtime_error("Failed to open file");
}
std::streamsize size = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> buffer(size);
if (file.read(reinterpret_cast<char *>(buffer.data()), size)) {
return buffer;
} else {
throw std::runtime_error("Failed to read file");
}
}
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64Encode(const std::vector<uint8_t> &buffer) {
std::string encodedData;
int i = 0;
uint8_t char_array_3[3];
uint8_t char_array_4[4];
while (i < buffer.size()) {
char_array_3[0] = buffer[i++];
char_array_3[1] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_3[2] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
char_array_4[1] =
((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
char_array_4[2] =
((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
char_array_4[3] = (char_array_3[2] & 0x3f);
for (int j = 0; (j < 4); ++j) {
encodedData += base64_chars[char_array_4[j]];
}
}
while ((encodedData.size() % 4) != 0) {
encodedData += '=';
}
return encodedData;
}
void imageEmbeddingAsync() {
ImageEmbeddingSession *session = image_embedding_create_session();
if (image_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
namespace fs = std::filesystem;
f f ( ) ()
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <iostream>
# include <thread>
# include <vector>
# include <fstream>
const char *TEST_FILE_PATH = "/home/kylin/Kylinproject/test2.png";
void callback(TextRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing results.\n");
int textLineNum = 0, pointsNum = 0;

fprintf(stdout, "text        : %s\n",
text_recognition_result_get_value(result));
fprintf(stdout, "err code    : %i\n",
text_recognition_result_get_error_code(result));
fprintf(stdout, "err message : %s\n",
text_recognition_result_get_error_message(result));
_TextLine **textline =
text_recognition_result_get_text_lines(result, &textLineNum);
if (textline == nullptr) {
fprintf(stderr, "The result is invalid, please check image\n");
return;
}
for (int i = 0; i < textLineNum; ++i) {
PixelPoint *point =
text_line_get_corner_points(textline[i], &pointsNum);
if (point == nullptr) {
fprintf(stderr, "No point\n");
return;
}
fprintf(stdout, "The %i line text: %s\n", i,
text_line_get_value(textline[i]));
for (int i = 0; i < pointsNum; i++) {
printf("The corner points text %d: (%d, %d)\n", i, point[i].x,
point[i].y);
}
}
if (user_data != nullptr) {
const char *userData = static_cast<const char *>(user_data);
fprintf(stdout, "%s\n", userData);
} else {
fprintf(stdout, "user data is nullptr\n");
}
fprintf(stdout, "Printing result completed.\n");
}
void test01_OcrFromFile() {
const char *userData = "Test genai vision from image file\n";
TextRecognitionSession *session = text_recognition_create_session();
TextRecognitionModelConfig *config =
text_recognition_model_config_create();

text_recognition_model_config_set_name(config, "vision");
text_recognition_model_config_set_deploy_type(config,
ModelDeployType::OnDevice);
text_recognition_set_model_config(session, config);
text_recognition_init_session(session);
text_recognition_result_set_callback(session, callback, (void *)userData);
text_recognition_recognize_text_from_image_file_async(session,
TEST_FILE_PATH);
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, &config, pMainLoop] {
while (std::getchar() != '\n') {
}
text_recognition_destroy_session(&session);
text_recognition_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
});
ctrlThread.detach();
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}

## 4.1 .3向量化
## 1. 将本、图（结构化数据）转换为数值向量。
## 4.1 .3.1开发环境部署
```bash
sudo apt install libkylin-coreai-embedding-dev
```
## 4.1 .3.2本向量化
## 4.1 .3.2.1创建会话
头件 <coreai/embedding/embedding.h>
函数 TextEmbeddingSession*text_embedding_create_session();
描述 创建本向量化会话
参数 
返回值 本向量化会话指针
## 4.1 .3.2.2初始化会话

头件 <coreai/embedding/embedding.h>
函数 inttext_embedding_init_session(TextEmbeddingSession*session);
描述 初始化会话
参数 session:本向量化会话指针
返回值 成功时返回0，否则返回具体的错误码
## 4.1 .3.2.3销毁对话
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_destroy_session(TextEmbeddingSession**session);
描述 销毁会话
参数 session:本向量化会话指针的地址
返回值 
## 4.1 .3.2.4获取本向量化模型信息
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding_get_model_info(TextEmbeddingSession*session,char
- *model_info);
描述 获取本向量化模型信息，需要调embedding_model_info_destroy销毁资源
参数 session:本向量化会话指针
model_info:模型信息指针的地址
返回值 true:成功，false:失败
## 4.1 .3.2.5向量化本（同步）
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding(TextEmbeddingSession*session,constchar*text,
EmbeddingResult**result);
描述 向量化本同步接，需要调embedding_result_destroy销毁资源

参数 session:本向量化会话指针
text:本
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.2.6向量化本（异步）
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_async(TextEmbeddingSession*session,constchar*text,
TextEmbeddingResultCallbackcallback,void*callback_user_data);
描述 向量化本异步接
参数 session:本向量化会话指针
text:本
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3图像向量化
## 4.1 .3.3.1创建会话
头件 <coreai/embedding/embedding.h>
函数 ImageEmbeddingSession*image_embedding_create_session();
描述 创建图像向量化会话
参数 
返回值 图像向量化会话指针
## 4.1 .3.3.2初始化会话
头件 <coreai/embedding/embedding.h>
函数 intimage_embedding_init_session(ImageEmbeddingSession*session);
描述 初始化会话

参数 session:图像向量化会话指针
返回值 成功时返回0，否则返回具体的错误码
## 4.1 .3.3.3销毁对话
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_destroy_session(ImageEmbeddingSession**session);
描述 销毁会话
参数 session:图像向量化会话指针的地址
返回值 
## 4.1 .3.3.4获取图像向量化模型信息
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_get_model_info(ImageEmbeddingSession*session,char
- *model_info);
描述 获取图像向量化模型信息，需要调embedding_model_info_destroy销毁资源
参数 session:图像向量化会话指针
model_info:模型信息指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.5图像向量化模型向量化本（同步）
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding_by_image_model(ImageEmbeddingSession*session,const
char*text,EmbeddingResult**result);
描述 通过同步的式图像向量化模型向量化本，需要调embedding_result_destroy销毁
资源
参数 session:图像向量化会话指针
text:本
result:EmbeddingResult类型指针的地址

返回值 true:成功，false:失败
## 4.1 .3.3.6向量化图（同步）
## 4.1 .3.3.6.1通过传图件路径的式
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_by_image_file(ImageEmbeddingSession*session,const
char*image_file,EmbeddingResult**result);
描述 通过同步的式向量化图，需要调embedding_result_destroy销毁资源
参数 session:图像向量化会话指针
image_file:图路径
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.6.2通过传base64图数据的式
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_by_base64_image_data(ImageEmbeddingSession
- session,constunsignedchar*image_data,unsignedintimage_data_length,
EmbeddingResult**result);
描述 通过同步的式向量化图，需要调embedding_result_destroy销毁资源
参数 session:图像向量化会话指针
image_data:base64图数据
image_data_length:base64图数据的度
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.7图像向量化模型向量化本（异步）
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_by_image_model_async(ImageEmbeddingSession*session,
constchar*text,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);

描述 通过异步的式图像向量化模型向量化本
参数 session:图像向量化会话指针
text:本
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3.8向量化图（异步）
## 4.1 .3.3.8.1通过传图件路径的式
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_from_by_file_async(ImageEmbeddingSession*session,
constchar*file_path,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);
描述 通过异步的式向量化图
参数 session:图像向量化会话指针
image_file:图路径
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3.8.2通过传base64图数据的式
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_by_base64_image_data_async(ImageEmbeddingSession
- session,constunsignedchar*image_data,
unsignedintimage_data_length,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);
描述 通过异步的式向量化图
参数 session:图像向量化会话指针
image_data:base64图数据
image_data_length:base64图数据的度

callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.4结果解析
## 4.1 .3.4.1获取向量化结果数据
头件 <coreai/embedding/embedding.h>
函数 float*embedding_result_get_vector_data(EmbeddingResult*result);
描述 获取向量化结果数据
参数 result:向量化结果的指针
返回值 float类型指针
## 4.1 .3.4.2获取向量化结果数据的度
头件 <coreai/embedding/embedding.h>
函数 intembedding_result_get_vector_length(EmbeddingResult*result);
描述 获取向量化结果数据的度
参数 result:向量化结果的指针
返回值 embedding_result_get_vector_data返回float指针数据的度
## 4.1 .3.4.3获取向量化错误码
头件 <coreai/embedding/embedding.h>
函数 intembedding_result_get_error_code(EmbeddingResult*result);
描述 获取错误码
参数 result:向量化结果的指针
返回值 具体的错误码
## 4.1 .3.4.4向量化错误信息

头件 <coreai/embedding/embedding.h>
函数 constchar*embedding_result_get_error_message(EmbeddingResult*result);
描述 获取错误信息
参数 result:向量化结果的指针
返回值 具体的错误信息
## 4.1 .3.4.5销毁向量化结果
头件 <coreai/embedding/embedding.h>
函数 voidembedding_result_destroy(EmbeddingResult**result);
描述 销毁向量化结果
参数 result:向量化结果指针的地址
返回值 
## 4.1 .3.4.6销毁模型信息结果
头件 <coreai/embedding/embedding.h>
函数 voidembedding_model_info_destroy(char*result);
描述 销毁模型信息结果
参数 result:模型信息结果的指针
返回值 
## 4.1 .3.4.7错误码
头件 <coreai/embedding/error.h>
枚举 typedefenum:int{
COREAI_EMBEDDING_SUCESS=0,
COREAI_EMBEDDING_INPUT_ERROR,
COREAI_EMBEDDING_INIT_ERROR,
COREAI_EMBEDDING_CONNECTION_ERROR,

COREAI_EMBEDDING_RUNTIME_ERROR,
COREAI_EMBEDDING_ERROR_UNKNOWN=99,
}CoreAiEmbeddingErrorCode;
描述 向量化相关的错误码
成员 COREAI_EMBEDDING_SUCESS：成功
COREAI_EMBEDDING_INPUT_ERROR：参数错误
COREAI_EMBEDDING_INIT_ERROR：向量化会话初始化错误
COREAI_EMBEDDING_CONNECTION_ERROR：向量化服务连接错误
COREAI_EMBEDDING_RUNTIME_ERROR：向量化解析runtime结果错误
COREAI_EMBEDDING_ERROR_UNKNOWN：向量化未知错误
## 4.1 .3.5例
## 4.1 .3.5.1先决条件
## 1. 仅x86和arm架构的机器上使向量化能；
配置CMakeLists.txt
```c
find_package(PkgConfig REQUIRED)
pkg_check_modules(Embedding REQUIRED IMPORTED_TARGET kysdk-coreai-embedding)
target_link_libraries(
xxx
pthread
${GIO_LIBRARIES}
PkgConfig::Embedding
)
```
## 4.1 .3.5.2本向量化
## 4.1 .3.5.2.1同步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
void textEmbeddingSync() {
TextEmbeddingSession *session = text_embedding_create_session();
int initSession = text_embedding_init_session(session);
if (initSession != 0) {
std::cout << "init session failed" << std::endl;
}
// 同步接
EmbeddingResult *result = nullptr;
bool sucess = text_embedding(session, "12345", &result);
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << ",";
}
std::cout << std::endl;
char *info = nullptr;
text_embedding_get_model_info(session, &info);
std::cout << "print model info:" << info << std::endl;
std::cout << "释放结果资源 " << std::endl;
embedding_result_destroy(&result);
embedding_model_info_destroy(info);
text_embedding_destroy_session(&session);
}
## 4.1 .3.5.2.2异步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <gio/gio.h>
# include <thread>
void callback(EmbeddingResult *result, void *callback_user_data) {
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << " ";
}
std::cout << std::endl;
if (callback_user_data != nullptr) {
int *a = static_cast<int *>(callback_user_data);
std::cout << "user_data :" << *a << std::endl;
}
}
void textEmbeddingAsync() {
TextEmbeddingSession *session = text_embedding_create_session();
if (text_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
text_embedding_async(session, "热爱学习 ", callback, nullptr);
auto *loop_ = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, loop_] {
while (std::getchar() != '\n') {
}
g_main_loop_quit(loop_);
});
ctrlThread.detach();
g_main_loop_run(loop_);
text_embedding_destroy_session(&session);
}
## 4.1 .3.5.3图像向量化
## 4.1 .3.5.3.1同步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <filesystem>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# include <thread>
# include <vector>
# include <fstream>
# 麒麟 AI SDK 开发指南

麒麟AI SDK开发指南
## 1. 概述
## 1. 麒麟AI SDK将AI能力统一抽象封装为C语言接口，屏蔽了各个大模型的接口差异，降低了应用集
成AI能力的门槛。麒麟AI SDK主要分为传统AI能力接口和生成式AI能力接口。传统AI能力接口
包括文字识别、音频处理和向量化等能力，生成式AI能力接口包括文本生成和图像生成等能力接
口；
## 2. 当前为1.1版本。
## 2. 前提条件
## 1. 基于已发布的银河麒麟操作系统（2503版本）；
## 2. 端侧能力目前只能在x86和arm机器上运行，对于其他的机型效果无法保证，已适配的具体机型
如下：
整机型号 具体配置
联想开天M90fG1s CPU:D3000内存：16G独立显卡：Arise-GT10C0t硬盘：512G
联想开天M90hG1t CPU:HygonC86-3G(OPN:3350)内存：16GB独立显卡：Arise-GT10C0t硬盘：
512GB
联想开天P90zG1t CPU:ZHAOXINKaiXianKX-7000内存：16GB独立显卡：Arise-GT10C0t硬盘：
1TB
## 3. 在使用任何接口之前需要在"设置->AI模块管理"中下载安装AI子系统。其次需要安装每种能力的
开发包，具体参考每种能力的接口说明。
## 3. API使用流程说明
## 3.1 使用流程说明
## 1. 使用任何接口之前需要创建会话实例；
## 2. 初始化会话实例，如果发生错误，初始化接口会返回具体的错误码；
## 3. 初始化成功之后设置结果回调函数，然后调用具体的业务接口；
## 4. 如果初始化失败并处理完错误，需要重新初始化会话实例；

## 5. 每个会话同时只能处理一个任务，如果同时调用多次业务接口，任务将串行执行，结果也是按照顺
序返回；
## 6. 如果要执行并发，可创建多个会话进行实现。
## 3.2 模型配置
## 1. 模型配置是全局的，调用文本对话、文生图和语音相关接口之前，需要对模型配置进行相关的配
置；
## 2. 模型配置可以在"设置->AI模块管理"中进行配置。
## 4. API详细说明

## 4.1 传统AI能力接口
## 4.1 .1文字识别
## 1. 文字识别接口将图像中的文字转换为文本，并提供文本行数和坐标等信息；
## 2. 目前仅支持使用AI子系统自带的端侧模型进行识别；
## 3. 通过"设置->AI模块管理"下载AI子系统之后，不需要进行任何配置即可使用。 
## 4.1 .1.1开发环境部署
```bash
sudo apt install libkysdk-coreai-vision-dev
```
## 4.1 .1.2文字识别会话
## 4.1 .1.2.1创建会话
头件 <coreai/vision/textrecognition.h>
函数 TextRecognitionSession*text_recognition_create_session()
描述 创建文字识别会话
参数 无
返回值 TextRecognitionSession类型的指针
## 4.1 .1.2.2初始化会话
头件 <coreai/vision/textrecognition.h>
函数 int text_recognition_init_session(TextRecognitionSession*session)
描述 初始化文字识别会话
参数 session：文字识别会话的指针
返回值 返回初始化的结果，初始化成功返回0，否则返回对应的错误码
## 4.1 .1.2.3销毁会话
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_destroy_session(TextRecognitionSession**session)

描述 销毁文字识别会话
参数 session：文字识别会话的指针地址
返回值 无
## 4.1 .1.2.4设置文字识别结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_result_set_callback(TextRecognitionSession*session,
TextRecognitionResultCallback callback,
void*user_data)
描述 设置文字识别结果的回调函数
参数 session：文字识别会话的指针
callback：TextRecognitionResultCallback类型的结果回调函数
user_data：调用者自定义的数据
返回值 无
## 4.1 .1.2.5设置模型配置信息
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_set_model_config(
TextRecognitionSession*session,
TextRecognitionModelConfig*config)
描述 设置文字识别的模型配置信息
参数 session：文字识别会话的指针
config：模型配置
返回值 无
## 4.1 .1.2.6图片文件文字识别
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_recognize_text_from_image_file_async(
TextRecognitionSession*session,
const char*image_file)
描述 进行图片文件的文字识别

参数 session：文字识别会话的指针
image_file：图片文件的路径
返回值 无
## 4.1 .1.2.7图片数据文字识别
头件 <coreai/vision/textrecognition.h>
函数 void text_recognition_recognize_text_from_image_data_async(
TextRecognitionSession*session,
const char*image_data,
unsigned int image_data_length)
描述 进行图片数据的文字识别
参数 session：文字识别会话的指针
image_data：待识别的图片数据指针，不需要转码，图片格式数据即可
image_data_length：待识别的图片数据长度
返回值 无
## 4.1 .1.3设置配置信息
可以明确指定要使用的模型或者部署类型，当前版本可以无需关注，默认会使 AI 系统集成的模型。
## 4.1 .1.3.1创建模型配置
头件 <coreai/vision/config.h>
函数 TextRecognitionModelConfig*text_recognition_model_config_create()
描述 创建模型配置实例
参数 无
返回值 模型配置实例指针
## 4.1 .1.3.2销毁模型配置实例
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_destroy(TextRecognitionModelConfig**config)

描述 销毁模型配置实例
参数 config：模型配置实例指针的地址
返回值 无
## 4.1 .1.3.3设置使用的模型名称
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_set_name(TextRecognitionModelConfig*config,
const char*name)
描述 设置要使用的模型名称，不指定时使用默认的模型
参数 config：模型配置实例的指针
name：设置的模型名字
返回值 无
## 4.1 .1.3.4设置使用的模型的部署类型
头件 <coreai/vision/config.h>
函数 void text_recognition_model_config_set_deploy_type(
TextRecognitionModelConfig*config,
ModelDeployType type)
描述 设置使用的模型的部署类型，不指定时使用默认部署类型的模型
参数 config：模型配置实例的指针
type：指定的模型部署类型
返回值 无
## 4.1 .1.4结果处理
## 4.1 .1.4.1结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 typedef void (*TextRecognitionResultCallback)(TextRecognitionResult*result, void*user_data)
描述 进行图片数据的文字识别

参数 result：TextRecognitionResult类型的识别结果指针
user_data：定义的数据
返回值 无
## 4.1 .1.4.2结果解析
## 1. 获取一行文本中的内容
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_line_get_value(TextLine*text_line)
描述 获取一行文本中的内容
参数 text_line：TextLine类型的指针
返回值 返回该行文本的指针
## 2. 获取一行文本的角点位置信息（四个角的位置信息）
头件 <coreai/vision/textrecognitionresult.h>
函数 PixelPoint*text_line_get_corner_points(TextLine*text_line, int*point_number)
描述 获取一行文本的角点位置信息（四个角的位置信息）
参数 text_line：TextLine类型的指针
point_number：角点个数，固定输出为4
返回值 返回四个点的坐标，顺序为左上、左下、右上、右下。
## 3. 获取识别结果的整体文本信息
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_recognition_result_get_value(TextRecognitionResult*result)
描述 获取识别结果的整体文本信息，不带格式
参数 result：TextRecognitionResult类型的识别结果指针
返回值 返回所有文本的内容

## 4. 获取识别的文本结果和行数
头件 <coreai/vision/textrecognitionresult.h>
函数 TextLine**text_recognition_result_get_text_lines(TextRecognitionResult*result, int*line_count)
描述 获取识别的文本结果和行数
参数 result：TextRecognitionResult类型的识别结果
line_count：文本行数
返回值 返回 TextLine*类型的数组的地址，TextLine结果中包含文本信息和坐标信息
## 5. 获取错误码
头件 <coreai/vision/textrecognitionresult.h>
函数 int text_recognition_result_get_error_code(TextRecognitionResult*result)
描述 获取识别结果中的错误码
参数 result：TextRecognitionResult类型的识别结果
返回值 返回具体的错误码，参考通用错误码和文字识别专有错误码
## 6. 获取错误信息
头件 <coreai/vision/textrecognitionresult.h>
函数 const char*text_recognition_result_get_error_message(TextRecognitionResult*result)
描述 获取识别结果中的错误信息
参数 result：TextRecognitionResult类型的识别结果
返回值 如果发生错误则返回具体的错误信息，否则返回空
## 4.1 .1.5错误码
通用错误码可参考4.3章节，文字识别专有错误码如下：
头件 <coreai/vision/error.h>

枚举 OcrErrorCode {
OCR_IMAGE_ERROR = 100,
OCR_PARAM_INVALID,
} OcrErrorCode;
描述 文字识别相关的错误码
成员 OCR_IMAGE_ERROR：数据文件无效
OCR_PARAM_INVALID：参数无效
## 4.1 .1.6示例
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
include_directories(${GIO_INCLUDE_DIRS})
pkg_check_modules(KYSDK_AI_VISION kysdk-coreai-vision)
include_directories(${KYSDK_AI_VISION_INCLUDE_DIRS})
target_link_libraries(
XXXX
pthread
${GIO_LIBRARIES}
${KYSDK_AI_VISION_LIBRARIES}
)
从图像文件识别
```c
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <iostream>
# include <thread>
麒麟AISDK开发指南
## 1. 概述
## 1. 麒麟AISDK将AI能统抽象封装为C语接，屏蔽了各个模型的接差异，降低了应集
成AI能的槛。麒麟AISDK主要分为传统AI能接和成式AI能接。传统 AI能接
包括字识别、频处理和向量化等能，成式AI能接包括本成和图像成等能接
；
## 2. 当前为1.1版本。
## 2. 前提条件
## 1. 基于已发布的银河麒麟操作系统（2503版本）；
## 2. 端侧能前只能在x86和arm机器上运，对于其他的机型效果法保证，已适配的具体机型
如下：
整机型号 具体配置
联想开天M90fG1s CPU:D3000内存：16G独显卡：Arise-GT10C0t硬盘：512G
联想开天M90hG1t CPU:HygonC86-3G(OPN:3350)内存：16GB独显卡：Arise-GT10C0t硬盘：
512GB
联想开天P90zG1t CPU:ZHAOXINKaiXianKX-7000内存：16GB独显卡：Arise-GT10C0t硬盘：
1TB
## 3. 在使任何接之前需要在设置->AI模块管理中下载安装AI系统。其次需要安装每种能的
开发包，具体参考每种能的接说明。
## 3. API使流程说明
## 3.1 使流程说明
## 1. 使任何接之前需要创建会话实例；
## 2. 初始化会话实例，如果发错误，初始化接会返回具体的错误码；
## 3. 初始化成功之后设置结果回调函数，然后调具体的业务接；
## 4. 如果初始化失败并处理完错误，需要重新初始化会话实例；

## 5. 每个会话同时只能处理个任务，如果同时调多次业务接，任务将串执，结果也是按照顺
序返回；
## 6. 如果要执并发，可创建多个会话进实现。
## 3.2 模型配置
## 1. 模型配置是全局的，调本对话、图和语相关接之前，需要对模型配置进相关的配
置；
## 2. 模型配置可以在设置->AI模块管理中进配置。
## 4. API详细说明

## 4.1 传统AI能接
## 4.1 .1字识别
## 1. 字识别接将图像中的字转换为本，并提供本数和坐标等信息；
## 2. 前仅持使AI系统带的端侧模型进识别；
## 3. 通过设置->AI模块管理下载AI系统之后，不需要进任何配置即可使。 
## 4.1 .1.1开发环境部署
```bash
sudo apt install libkysdk-coreai-vision-dev
```
## 4.1 .1.2字识别会话
## 4.1 .1.2.1创建会话
头件 <coreai/vision/textrecognition.h>
函数 TextRecognitionSession*text_recognition_create_session()
描述 创建字识别会话
参数 
返回值 TextRecognitionSession类型的指针
## 4.1 .1.2.2初始化会话
头件 <coreai/vision/textrecognition.h>
函数 inttext_recognition_init_session(TextRecognitionSession*session)
描述 初始化字识别会话
参数 session：字识别会话的指针
返回值 返回初始化的结果，初始化成功返回0，否则返回对应的错误码
## 4.1 .1.2.3销毁会话
头件 <coreai/vision/textrecognition.h>
函数 voidtext_recognition_destroy_session(TextRecognitionSession**session)

描述 销毁字识别会话
参数 session：字识别会话的指针地址
返回值 
## 4.1 .1.2.4设置字识别结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 voidtext_recognition_result_set_callback(TextRecognitionSession*session,
TextRecognitionResultCallbackcallback,void*user_data)
描述 设置字识别结果的回调函数
参数 session：字识别会话的指针
callback：TextRecognitionResultCallback类型的结果回调函数
user_data：调者定义的数据
返回值 
## 4.1 .1.2.5设置模型配置信息
头件 <coreai/vision/textrecognition.h>
函数 voidtext_recognition_set_model_config(
TextRecognitionSession*session,TextRecognitionModelConfig*config)
描述 设置字识别的模型配置信息
参数 session：字识别会话的指针
config：模型配置
返回值 
## 4.1 .1.2.6图件字识别
头件 <coreai/vision/textrecognition.h>
函数 voidtext_recognition_recognize_text_from_image_file_async(
TextRecognitionSession*session,constchar*image_file)
描述 进图件的字识别

参数 session：字识别会话的指针
image_file：图件的路径
返回值 
## 4.1 .1.2.7图数据字识别
头件 <coreai/vision/textrecognition.h>
函数 voidtext_recognition_recognize_text_from_image_data_async(
TextRecognitionSession*session,constchar*image_data,unsignedint
image_data_length)
描述 进图数据的字识别
参数 session：字识别会话的指针
image_data：待识别的图数据指针，不需要转码，图格式数据即可
image_data_length：待识别的图数据度
返回值 
## 4.1 .1.3设置配置信息
可以明确指定要使的模型或者部署类型，当前版本可以需关注，默认会使 AI系统集成的模
型。
## 4.1 .1.3.1创建模型配置
头件 <coreai/vision/config.h>
函数 TextRecognitionModelConfig*text_recognition_model_config_create()
描述 创建模型配置实例
参数 
返回值 模型配置实例指针
## 4.1 .1.3.2销毁模型配置例
头件 <coreai/vision/config.h>
函数 voidtext_recognition_model_config_destroy(TextRecognitionModelConfig**config)

描述 销毁模型配置实例
参数 config：模型配置实例指针的地址
返回值 
## 4.1 .1.3.3设置使的模型名称
头件 <coreai/vision/config.h>
函数 voidtext_recognition_model_config_set_name(TextRecognitionModelConfig*config,
constchar*name)
描述 设置要使的模型名称，不指定时使默认的模型
参数 config：模型配置实例的指针
name：设置的模型名字
返回值 
## 4.1 .1.3.4设置使的模型的部署类型
头件 <coreai/vision/config.h>
函数 voidtext_recognition_model_config_set_deploy_type(
TextRecognitionModelConfig*config,ModelDeployTypetype)
描述 设置使的模型的部署类型，不指定时使默认部署类型的模型
参数 config：模型配置实例的指针
type：指定的模型部署类型
返回值 
## 4.1 .1.4结果处理
## 4.1 .1.4.1结果回调函数
头件 <coreai/vision/textrecognition.h>
函数 typedefvoid(*TextRecognitionResultCallback)(TextRecognitionResult*result,void
- user_data)
描述 进图数据的字识别

参数 result：TextRecognitionResult类型的识别结果指针
user_data：定义的数据
返回值 
## 4.1 .1.4.2结果解析
## 1. 获取本中的内容
头件 <coreai/vision/textrecognitionresult.h>
函数 constchar*text_line_get_value(TextLine*text_line)
描述 获取本中的内容
参数 text_line：TextLine类型的指针
返回值 返回该本的指针
## 2. 获取本的点位置信息（四个的位置信息）
头件 <coreai/vision/textrecognitionresult.h>
函数 PixelPoint*text_line_get_corner_points(TextLine*text_line,int*point_number)
描述 获取本的点位置信息（四个的位置信息）
参数 text_line：TextLine类型的指针
point_number：点个数，固定输出为4
返回值 返回四个点的坐标，顺序为左上、左下、右上、右下。
## 3. 获取识别结果的整体本信息
头件 <coreai/vision/textrecognitionresult.h>
函数 constchar*text_recognition_result_get_value(TextRecognitionResult*result)
描述 获取识别结果的整体本信息，不带格式
参数 result：TextRecognitionResult类型的识别结果指针
返回值 返回所有本的内容

## 4. 获取识别的本结果和数
头件 <coreai/vision/textrecognitionresult.h>
函数 TextLine**text_recognition_result_get_text_lines(TextRecognitionResult*result,int
- line_count)
描述 获取识别的本结果和数
参数 result：TextRecognitionResult类型的识别结果
line_count：本数
返回值 返回TextLine*类型的数组的地址，TextLine结果中包含本信息和坐标信息
## 5. 获取错误码
头件 <coreai/vision/textrecognitionresult.h>
函数 inttext_recognition_result_get_error_code(TextRecognitionResult*result)
描述 获取识别结果中的错误码
参数 result：TextRecognitionResult类型的识别结果
返回值 返回具体的错误码，参考通错误码和字识别专有错误码
## 6. 获取错误信息
头件 <coreai/vision/textrecognitionresult.h>
函数 constchar*text_recognition_result_get_error_message(TextRecognitionResult*result)
描述 获取识别结果中的错误信息
参数 result：TextRecognitionResult类型的识别结果
返回值 如果发错误则返回具体的错误信息，否则返回空
## 4.1 .1.5错误码
通错误码可参考4.3章节，字识别专有错误码如下：
头件 <coreai/vision/error.h>

枚举 typedefenum{
OCR_IMAGE_ERROR=100,
OCR_PARAM_INVALID,
}OcrErrorCode;
描述 字识别相关的错误码
成员 OCR_IMAGE_ERROR：数据件效
OCR_PARAM_INVALID：参数效
## 4.1 .1.6例
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
include_directories(${GIO_INCLUDE_DIRS})
pkg_check_modules(KYSDK_AI_VISION kysdk-coreai-vision)
include_directories(${KYSDK_AI_VISION_INCLUDE_DIRS})
target_link_libraries(
XXXX
pthread
${GIO_LIBRARIES}
${KYSDK_AI_VISION_LIBRARIES}
)
从图像件识别
```c
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <iostream>
# include <thread>
const char *TEST_FILE_PATH = "/home/kylin/Kylinproject/test2.png";
void callback(TextRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing results.\n");
int textLineNum = 0, pointsNum = 0;1

fprintf(stdout, "text        : %s\n",
text_recognition_result_get_value(result));
fprintf(stdout, "err code    : %i\n",
text_recognition_result_get_error_code(result));
fprintf(stdout, "err message : %s\n",
text_recognition_result_get_error_message(result));
_TextLine **textline =
text_recognition_result_get_text_lines(result, &textLineNum);
if (textline == nullptr) {
fprintf(stderr, "The result is invalid, please check image\n");
return;
}
for (int i = 0; i < textLineNum; ++i) {
PixelPoint *point =
text_line_get_corner_points(textline[i], &pointsNum);
if (point == nullptr) {
fprintf(stderr, "No point\n");
return;
}
fprintf(stdout, "The %i line text: %s\n", i,
text_line_get_value(textline[i]));
for (int i = 0; i < pointsNum; i++) {
printf("The corner points text %d: (%d, %d)\n", i, point[i].x,
point[i].y);
}
}
if (user_data != nullptr) {
const char *userData = static_cast<const char *>(user_data);
fprintf(stdout, "%s\n", userData);
} else {
fprintf(stdout, "user data is nullptr\n");
}
fprintf(stdout, "Printing result completed.\n");
}
void test01_OcrFromFile() {
const char *userData = "Test genai vision from image file\n";
TextRecognitionSession *session = text_recognition_create_session();
TextRecognitionModelConfig *config =
text_recognition_model_config_create();14

text_recognition_model_config_set_name(config, "vision");
text_recognition_model_config_set_deploy_type(config,
ModelDeployType::OnDevice);
text_recognition_set_model_config(session, config);
text_recognition_init_session(session);
text_recognition_result_set_callback(session, callback, (void *)userData);
text_recognition_recognize_text_from_image_file_async(session,
TEST_FILE_PATH);
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, &config, pMainLoop] {
while (std::getchar() != '\n') {
}
text_recognition_destroy_session(&session);
text_recognition_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
});
ctrlThread.detach();
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}
从图像数据识别
# include <coreai/vision/textrecognition.h>
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
const char *TEST_DATA_PATH = "/home/kylin/Kylinproject/test1";
void callback(TextRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing results.\n");1

int textLineNum = 0, pointsNum = 0;
fprintf(stdout, "text        : %s\n",
text_recognition_result_get_value(result));
fprintf(stdout, "err code    : %i\n",
text_recognition_result_get_error_code(result));
fprintf(stdout, "err message : %s\n",
text_recognition_result_get_error_message(result));
_TextLine **textline =
text_recognition_result_get_text_lines(result, &textLineNum);
if (textline == nullptr) {
fprintf(stderr, "The result is invalid, please check image\n");
return;
}
for (int i = 0; i < textLineNum; ++i) {
PixelPoint *point =
text_line_get_corner_points(textline[i], &pointsNum);
if (point == nullptr) {
fprintf(stderr, "No point\n");
return;
}
fprintf(stdout, "The %i line text: %s\n", i,
text_line_get_value(textline[i]));
for (int i = 0; i < pointsNum; i++) {
printf("The corner points text %d: (%d, %d)\n", i, point[i].x,
point[i].y);
}
}
if (user_data != nullptr) {
const char *userData = static_cast<const char *>(user_data);
fprintf(stdout, "%s\n", userData);
} else {
fprintf(stdout, "user data is nullptr\n");
}
fprintf(stdout, "Printing result completed.\n");
}
std::vector<char> readImageData(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary);
if (!file.is_open()) {
fprintf(stderr, "Failed to open file: %s\n", filePath.c_str());
return {};
}16

file.seekg(0, std::ios::end);
std::streampos fileSize = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<char> imageData(fileSize);
file.read(reinterpret_cast<char *>(imageData.data()), fileSize);
return imageData;
}
void test02_OcrFromData() {
namespace fs = std::filesystem;
if (not fs::exists(TEST_DATA_PATH)) {
fprintf(stderr, "error\n");
return;
}
const char *userData = "Test genai vision from image data\n";
const std::vector<char> imageData = readImageData(TEST_DATA_PATH);
TextRecognitionSession *session = text_recognition_create_session();
TextRecognitionModelConfig *config =
text_recognition_model_config_create();
text_recognition_set_model_config(session, config);
text_recognition_init_session(session);
text_recognition_result_set_callback(session, callback, (void*)userData);
text_recognition_recognize_text_from_image_data_async(
session, imageData.data(), imageData.size());
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, &config, pMainLoop] {
while (std::getchar() != '\n') {
}
text_recognition_model_config_destroy(&config);
text_recognition_destroy_session(&session);
g_main_loop_quit(pMainLoop);
});
ctrlThread.detach();
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}63

## 4.1 .2频处理
## 4.1 .2.1开发环境部署
```bash
sudo apt install libkysdk-coreai-speech-dev
```
## 4.1 .2.2语识别
## 1. 将语识别接将频信息转换为本；
## 2. 前仅持中；
## 3. 持流式和流式语识别；
## 4. 持识别发（如果云端服务持的话）；
## 5. 前仅持云端服务的形式，端侧模型咱不持；
## 6. 需要在设置->AI模块管理中进配置才能使。
## 4.1 .2.2.1创建会话
头件 <coreai/speech/recognizer.h>
函数 SpeechRecognitionSession*speech_recognizer_create_session()
描述创建语识别会话
参数
返回值 SpeechRecognitionSession类型的指针
## 4.1 .2.2.2初始化会话
头件 <coreai/speech/recognizer.h>
函数 intspeech_recognizer_init_session(SpeechRecognitionSession*session)
描述初始化语识别会话
参数 session：语识别会话的指针
返回值返回初始化的结果，初始化成功返回0，否则返回对应的错误码
## 4.1 .2.2.3销毁会话
头件 <coreai/speech/recognizer.h>

函数 voidspeech_recognizer_destroy_session(SpeechRecognitionSession**session)
描述销毁语识别会话
参数 session：语识别会话指针的地址
返回值
## 4.1 .2.2.4设置语识别结果回调函数
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_result_set_callback(SpeechRecognitionSession*session,
SpeechRecognitionResultCallbackcallback,void*user_data)
描述设置语识别的结果回调函数
参数 session：语识别会话的指针
callback:SpeechRecognitionResultCallback类型的结果回调函数
user_data:调者定义的数据
返回值
## 4.1 .2.2.5设置输频配置信息
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_set_audio_config(SpeechRecognitionSession*session,
AudioConfig*audio_config)
描述设置频相关的配置，如输频的来源等
参数 session：语识别会话的指针
audio_config:语相关的配置
返回值
## 4.1 .2.2.6设置模型配置信息
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_set_model_config(SpeechRecognitionSession*session,
SpeechModelConfig*config)

描述设置模型配置信息
参数 session：字识别会话的指针
config：模型配置
返回值
## 4.1 .2.2.7开始异步流式语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_start_continuous_recognition_async(SpeechRecognitionSession
- session)
描述开始流式异步语识别，如果使的频流，建议每40ms发送1280个字节。结果通过callback
异步返回。
参数 session：语识别会话的指针
返回值
## 4.1 .2.2.8停异步流式语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_stop_continuous_recognition_async(SpeechRecognitionSession
- session)
描述停异步流式语识别
参数 session：语识别会话的指针
返回值
## 4.1 .2.2.9进次性语识别
头件 <coreai/speech/recognizer.h>
函数 voidspeech_recognizer_recognize_once_async(
SpeechRecognitionSession*session)
描述进次性语识别，识别完整个件或者整段数据时返回结果。结果通过callback异步返回。
参数 session：语识别会话的指针

返回值
## 4.1 .2.2.10结果处理
## 4.1 .2.2.10.1结果回调函数
头件 <coreai/speech/result.h>
类型 typedefvoid(*SpeechRecognitionResultCallback)(
SpeechRecognitionResult*result,void*user_data)
描述语识别结果回调函数类型
参数 result：SpeechRecognitionResult类型的指针
user_data:数据
返回值
## 4.1 .2.2.10.2结果解析
## 1. 获取识别结果状态
头件 <coreai/speech/result.h>
函数 SpeechResultReasonspeech_recognition_result_get_reason(
SpeechRecognitionResult*result);
描述获取语识别结果的状态
参数语识别结果的指针
返回值语识别结果的状态
## 2. 获取识别的本数据
头件 <coreai/speech/result.h>
函数 constchar*speech_recognition_result_get_text(
SpeechRecognitionResult*result)
描述获取语识别结果中的本数据
参数语识别结果的指针

返回值语识别结果的本数据
## 3. 获取发的id
头件 <coreai/speech/result.h>
函数 intspeech_recognition_result_get_speaker_id(
SpeechRecognitionResult*result)
描述获取语识别结果中的说话id
参数语识别结果的指针
返回值 如果识别到发，返回于0的id
否则返回-1
## 4. 获取错误码
头件 <coreai/speech/result.h>
函数 intspeech_recognition_result_get_error_code(
SpeechRecognitionResult*result)
描述获取语识别结果中的错误码
参数语识别结果的指针
返回值具体的错误码
## 5. 获取具体错误信息
头件 <coreai/speech/result.h>
函数 constchar*speech_recognition_result_get_error_message(
SpeechRecognitionResult*result);
描述获取语识别结果中的具体错误信息
参数语识别结果的指针
返回值具体的错误信息

## 4.1 .2.3语合成
## 1. 将纯本内容合成为频；
## 2. 暂时不持设置发；
## 3. 暂时仅持中；
## 4. 前仅持云端服务的形式；
## 5. 需要在设置->AI模块管理中进配置之后才能使。
## 4.1 .2.3.1创建会话
头件 <coreai/speech/synthesizer.h>
函数 SpeechSynthesizerSession*speech_synthesizer_create_session()
描述创建语合成的会话
参数
返回值语合成会话的指针
## 4.1 .2.3.2初始化会话
头件 <coreai/speech/synthesizer.h>
函数 intspeech_synthesizer_init_session(
SpeechSynthesizerSession*session)
描述初始化语合成的会话
参数语合成会话的指针
返回值初始化结果，0表成功；于0时表具体的错误码
## 4.1 .2.3.3销毁会话
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_destroy_session(SpeechSynthesizerSession**session)
描述销毁语合成会话
参数语合成会话指针的地址

返回值
## 4.1 .2.3.4设置语合成结果回调函数
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_result_set_callback(SpeechSynthesizerSession*session,
SpeechSynthesisResultCallbackcallback,
void*user_data)
描述设置语合成的结果回调函数
参数 session:语合成会话的指针
callback:语合成的结果回调函数
返回值
## 4.1 .2.3.5设置输出频配置信息
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_set_audio_config(SpeechSynthesizerSession*session,
AudioConfig*audio_config)
描述设置语合成输出频的相关配置
参数 session:语合成会话的指针
audio_config:具体的频配置
返回值
## 4.1 .2.3.6设置模型配置信息
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_set_model_config(SpeechRecognitionSession*session,
SpeechModelConfig*config)
描述设置模型配置信息
参数 session：字识别会话的指针
config：模型配置
返回值

## 4.1 .2.3.7进语合成
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_synthesize_text_async(SpeechSynthesizerSession*session,const
char*text,uint32_ttext_length)
描述将本内容合成为语数据
参数 session：语合成会话的指针
text:本数据指针
text_length:本度
返回值
## 4.1 .2.3.8停播放频
头件 <coreai/speech/synthesizer.h>
函数 voidspeech_synthesizer_stop_speaking(SpeechSynthesizerSession*session)
描述停语播放，当频输出配置为系统播放器时该接效
参数 session：语合成会话的指针
返回值
## 4.1 .2.3.9结果处理
## 4.1 .2.3.9.1结果回调函数
头件 <coreai/speech/result.h>
类型 typedefvoid(*SpeechSynthesisResultCallback)(SpeechSynthesisResult*result,void
- user_data)
描述语合成结果回调函数类型
参数 result：SpeechSynthesisResult类型的指针
user_data:数据
返回值

## 4.1 .2.3.9.2结果解析
## 1. 获取语合成结果的状态
头件 <coreai/speech/result.h>
函数 SpeechResultReasonspeech_synthesis_result_get_reason(SpeechSynthesisResult*result)
描述获取语合成结果的状态
参数语合成结果的指针
返回值语合成结果的状态
## 2. 获取语合成结果的数据
头件 <coreai/speech/result.h>
函数 constuint8_t*speech_synthesis_result_get_data(SpeechSynthesisResult*result,uint8_t
- data_length)
描述获取语合成的数据
参数 result:语合成结果的指针
data_length:输出参数，频数据的度
返回值语合成的频数据的指针
## 3. 获取语合成结果的频数据格式
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_audio_format(SpeechSynthesisResult*result)
描述获取语合成结果的频数据格式
参数语合成结果的指针
返回值具体的频数据格式
## 4. 获取语合成结果的频数据采样率
头件 <coreai/speech/result.h>

函数 intspeech_synthesis_result_get_audio_rate(SpeechSynthesisResult*result)
描述获取语合成结果的频数据采样率
参数语合成结果的指针
返回值具体的频数据采样率
## 5. 获取语合成结果的频数据通道数
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_audio_channel(SpeechSynthesisResult*result)
描述获取语合成结果的频数据通道数
参数语合成结果的指针
返回值具体的频数据通道数
## 6. 获取语合成结果的错误码
头件 <coreai/speech/result.h>
函数 intspeech_synthesis_result_get_error_code(SpeechSynthesisResult*result)
描述获取语合成结果的错误码
参数语合成结果的指针
返回值具体的错误码
## 7. 获取语合成结果的错误信息
头件 <coreai/speech/result.h>
函数 constchar*speech_synthesis_result_get_error_message(SpeechSynthesisResult*result)
描述获取语合成结果的具体错误信息
参数语合成结果的指针
返回值具体的错误信息

## 4.1 .2.4频结果状态
头件<coreai/speech/result.h>
枚举 typedefenum{
SPEECH_ERROR_OCCURRED=1，
SPEECH_RECOGNITION_STARTED=2，
SPEECH_RECOGNIZING=3，
SPEECH_RECOGNIZED=4，
SPEECH_RECOGNITION_COMPLETED=5，
SPEECH_SYNTHESIS_STARTED=6，
SPEECH_SYNTHESIZING=7，
SPEECH_SYNTHESIS_COMPLETED=8
}SpeechResultReason;
描述 SPEECH_ERROR_OCCURRED：语识别或者合成过程中出错
SPEECH_RECOGNITION_STARTED：语识别已启动
SPEECH_RECOGNIZING：正在进语识别，中间结果
SPEECH_RECOGNIZED：语识别的最终结果，在SPEECH_RECOGNIZING的基础上经过修正
的结果
SPEECH_RECOGNITION_COMPLETED：语识别完成
SPEECH_SYNTHESIS_STARTED：语合成已启动
SPEECH_SYNTHESIZING：正在进语合成
SPEECH_SYNTHESIS_COMPLETED：语合成已完成
## 4.1 .2.5频配置
## 4.1 .2.5.1输频配置-语识别
## 1. 配置输频数据系统默认克获取，适于流式语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_continuous_audio_input_from_default_microphone()
描述创建频配置，输频数据从默认克中获取
参数

返回值频配置实例指针
## 2. 配置输频数据从数据流中获取，适于流式语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_continuous_audio_input_from_audio_data_stream(
AudioDataStream*stream)
描述创建频配置，使频数据流作为输频
参数 stream:频数据流
返回值频配置实例指针
## 3. 配置输频从pcm数据中获取，适于次性语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_once_audio_input_from_pcm_data(constuint8_t
- audio_data,uint32_tdata_length)
描述创建频配置，使pcm频数据作为输频
参数 audio_data:pcm频数据指针
data_length:pcm频数据度
返回值频配置指针
## 4. 配置输频从pcm件中获取数据，适于次性语识别
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_once_audio_input_from_pcm_file(constchar*pcm_file)
描述创建频配置，使pcm件作为输频
参数 pcm_file:pcm件
返回值频配置指针
## 4.1 .2.5.2输出频配置-语合成
## 1. 配置语以原始数据输出

头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_pcm_data()
描述创建频配置，将合成的频以原始数据形式输出。结果通过callback异步返回。
参数
返回值频配置实例指针
## 2. 配置语输出到pcm件
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_pcm_file_name(constchar
- pcm_file)
描述创建频配置，将合成的频输出到pcm件
参数 pcm_file:输出保存的pcm件
返回值频配置实例指针
## 3. 配置语输出到系统默认扬声器
头件 <coreai/speech/audioconfig.h>
函数 AudioConfig*audio_config_create_audio_output_from_default_speaker()
描述创建频配置，使系统默认的扬声器作为频输出
参数
返回值频配置实例指针
## 4.1 .2.6模型配置信息
## 4.1 .2.6.1创建模型配置
头件 <coreai/speech/config.h>
函数 SpeechModelConfig*speech_model_config_create()
描述创建模型配置实例

参数
返回值模型配置实例指针
## 4.1 .2.6.2销毁模型配置实例
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_destroy(SpeechModelConfig**config)
描述销毁模型配置实例
参数 config：模型配置的级指针
返回值
## 4.1 .2.6.3设置使的模型名称
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_set_name(SpeechModelConfig*config,constchar*name)
描述设置模型名称
参数 config：模型配置的实例指针
name：设置的模型名字
返回值
## 4.1 .2.6.4设置使的模型类型
头件 <coreai/speech/config.h>
函数 voidspeech_model_config_set_deploy_type(SpeechModelConfig*config,ModelDeployType
type)
描述设置模型类型
参数 config：模型配置的实例指针
ModelDeployType：设置的模型类型
返回值
## 4.1 .2.7错误码

通错误码参考4.3节，语处理专有错误码如下：
头件 <coreai/speech/error.h>
枚举 typedefenum{
SPEECH_RECOGNITION_AUDIO_DATA_SIZE_INVALID=100,
SPEECH_SYNTHESIS_TEXT_LENGTH_INVALID,
SPEECH_PARAM_INVALID,
SPEECH_DEFAULT_MICROPHONE_INVALID,
SPEECH_UNKNOWN_ERROR,
SPEECH_UNSUPPORTED_LANGUAGE
}SpeechErrorCode;
描述 语相关的错误码
成员 SPEECH_RECOGNITION_AUDIO_DATA_SIZE_INVALID：频超限
SPEECH_SYNTHESIS_TEXT_LENGTH_INVALID：输本度超限
SPEECH_PARAM_INVALID：配置参数不合法
SPEECH_DEFAULT_MICROPHONE_INVALID：未配置默认克
SPEECH_UNKNOWN_ERROR：未知错误
SPEECH_UNSUPPORTED_LANGUAGE：不持的语
其余通错误码，具体参考3.3节
## 4.1 .2.8例
## 4.1 .2.8.1前提条件
在设置->AI模块管理中已经对语相关的模型进了配置。
## 4.1 .2.8.2语识别
配置CMakeLists.txt
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
include_directories(${GIO_INCLUDE_DIRS})
pkg_check_modules(KYAISPEECH kysdk-coreai-speech)
include_directories(${KYAISPEECH_INCLUDE_DIRS})
target_link_libraries(
xxx1

pthread
${GIO_LIBRARIES}
${KYAISPEECH_LIBRARIES}
)
具体demo：
# include <filesystem>
# include <fstream>
# include <vector>
// glib header
# include <gio/gio.h>
// kysdk-ai header
# include <coreai/speech/recognizer.h>
const char *PCM_FILE_PATH = "xxx.pcm";
std::vector<uint8_t> readAudioData(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary);
if (!file.is_open()) {
return {};
}
file.seekg(0, std::ios::end);
std::streampos fileSize = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> audioData(fileSize);
file.read(reinterpret_cast<char *>(audioData.data()), fileSize);
return audioData;
}
void callback(SpeechRecognitionResult *result, void *user_data) {
fprintf(stdout, "Start printing speech recognition results.\n");
fprintf(stdout, "Speech recognition errorcode: %d\n",
speech_recognition_result_get_error_code(result));
fprintf(stdout, "Speech recognition error message: %s\n",
speech_recognition_result_get_error_message(result));
int resultType = speech_recognition_result_get_reason(result);
const char *resultData = speech_recognition_result_get_text(result);
fprintf(stdout, "Speech recognition result: %s\n", resultData);
int resultErrorCode = speech_recognition_result_get_error_code(result);1

fprintf(stdout, "Printing speech recognition result completed.\n");
}
void Test_RecognitionOnce() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
if (not std::filesystem::exists(PCM_FILE_PATH)) {
fprintf(stderr, "Flie not exists !\n");
return;
}
std::vector<uint8_t> audioData = readAudioData(PCM_FILE_PATH);
SpeechRecognitionSession *session = speech_recognizer_create_session();
SpeechModelConfig *modelconfig = speech_model_config_create();
speech_model_config_set_name(modelconfig,
"讯-语模型 ");  //或"百度 - 语模型 "
speech_model_config_set_deploy_type(modelconfig,
ModelDeployType::PublicCloud);
speech_recognizer_set_model_config(session, modelconfig);
speech_recognizer_init_session(session);
speech_recognizer_result_set_callback(session, callback, nullptr);
auto *config = audio_config_create_once_audio_input_from_pcm_data(
audioData.data(), audioData.size());
speech_recognizer_set_audio_config(session, config);
speech_recognizer_recognize_once_async(session);
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}39
## 4.1 .2.8.3语合成
# include <fstream>
# include <filesystem>
# include <vector>
# include <coreai/speech/synthesizer.h>
# include <gio/gio.h>
static void writeBinaryDataToFile(const std::string &filename,1

const std::vector<char> &data) {
if (data.size() == 0) {
fprintf(stderr, "Data is empty!\n");
return;
}
std::ofstream outputFile(filename, std::ios::out | std::ios::binary |
std::ios::app);
if (!outputFile.is_open()) {
fprintf(stderr, "File open failed!\n");
return;
}
outputFile.write(reinterpret_cast<const char*>(data.data()), data.size());
outputFile.close();
}
void onSynthesisResult(SpeechSynthesisResult *result, void *userData) {
fprintf(stdout, "Start writing the synthesized results to a file.\n");
const char *userdata = static_cast<const char*>(userData);
uint32_t audioDataLength;
const uint8_t* audioData = speech_synthesis_result_get_data(result,
&audioDataLength);
SpeechResultReason resultType =
speech_synthesis_result_get_reason(result);
std::fprintf(
stdout,
"test Synthesis result reason=%i audioDataLength=%i userData=%s \n",
(int)resultType, (int)audioDataLength, userdata);
std::vector<char> data {audioData, audioData + audioDataLength };
writeBinaryDataToFile("../testsynthesis.pcm", data);
fprintf(stdout, "Write completed.\n");
}
void testSynthesisOutputPcmData() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
auto *synthesizerConfig =
audio_config_create_audio_output_from_pcm_data();
SpeechSynthesizerSession *synSession =
speech_synthesizer_create_session();
SpeechModelConfig *modelconfig = speech_model_config_create();8

speech_model_config_set_name(modelconfig, "讯-语模型 ");//或"百度 - 语
模型"
speech_model_config_set_deploy_type(modelconfig,
ModelDeployType::PublicCloud);
speech_synthesizer_set_model_config(synSession, modelconfig);
speech_synthesizer_result_set_callback(synSession, onSynthesisResult,
nullptr);
speech_synthesizer_init_session(synSession);
audio_config_set_input_audio_rate(synthesizerConfig, 16000);
speech_synthesizer_set_audio_config(synSession, synthesizerConfig);
speech_synthesizer_synthesize_text_async(synSession, "你好", 100);
int stopErrorCode = speech_synthesizer_stop_speaking(synSession);
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
}50
## 4.1 .3向量化
## 1. 将本、图（结构化数据）转换为数值向量。
## 4.1 .3.1开发环境部署
```bash
sudo apt install libkylin-coreai-embedding-dev
```
## 4.1 .3.2本向量化
## 4.1 .3.2.1创建会话
头件 <coreai/embedding/embedding.h>
函数 TextEmbeddingSession*text_embedding_create_session();
描述 创建本向量化会话
参数 
返回值 本向量化会话指针
## 4.1 .3.2.2初始化会话

头件 <coreai/embedding/embedding.h>
函数 inttext_embedding_init_session(TextEmbeddingSession*session);
描述 初始化会话
参数 session:本向量化会话指针
返回值 成功时返回0，否则返回具体的错误码
## 4.1 .3.2.3销毁对话
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_destroy_session(TextEmbeddingSession**session);
描述 销毁会话
参数 session:本向量化会话指针的地址
返回值 
## 4.1 .3.2.4获取本向量化模型信息
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding_get_model_info(TextEmbeddingSession*session,char
- *model_info);
描述 获取本向量化模型信息，需要调embedding_model_info_destroy销毁资源
参数 session:本向量化会话指针
model_info:模型信息指针的地址
返回值 true:成功，false:失败
## 4.1 .3.2.5向量化本（同步）
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding(TextEmbeddingSession*session,constchar*text,
EmbeddingResult**result);
描述 向量化本同步接，需要调embedding_result_destroy销毁资源

参数 session:本向量化会话指针
text:本
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.2.6向量化本（异步）
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_async(TextEmbeddingSession*session,constchar*text,
TextEmbeddingResultCallbackcallback,void*callback_user_data);
描述 向量化本异步接
参数 session:本向量化会话指针
text:本
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3图像向量化
## 4.1 .3.3.1创建会话
头件 <coreai/embedding/embedding.h>
函数 ImageEmbeddingSession*image_embedding_create_session();
描述 创建图像向量化会话
参数 
返回值 图像向量化会话指针
## 4.1 .3.3.2初始化会话
头件 <coreai/embedding/embedding.h>
函数 intimage_embedding_init_session(ImageEmbeddingSession*session);
描述 初始化会话

参数 session:图像向量化会话指针
返回值 成功时返回0，否则返回具体的错误码
## 4.1 .3.3.3销毁对话
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_destroy_session(ImageEmbeddingSession**session);
描述 销毁会话
参数 session:图像向量化会话指针的地址
返回值 
## 4.1 .3.3.4获取图像向量化模型信息
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_get_model_info(ImageEmbeddingSession*session,char
- *model_info);
描述 获取图像向量化模型信息，需要调embedding_model_info_destroy销毁资源
参数 session:图像向量化会话指针
model_info:模型信息指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.5图像向量化模型向量化本（同步）
头件 <coreai/embedding/embedding.h>
函数 booltext_embedding_by_image_model(ImageEmbeddingSession*session,const
char*text,EmbeddingResult**result);
描述 通过同步的式图像向量化模型向量化本，需要调embedding_result_destroy销毁
资源
参数 session:图像向量化会话指针
text:本
result:EmbeddingResult类型指针的地址

返回值 true:成功，false:失败
## 4.1 .3.3.6向量化图（同步）
## 4.1 .3.3.6.1通过传图件路径的式
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_by_image_file(ImageEmbeddingSession*session,const
char*image_file,EmbeddingResult**result);
描述 通过同步的式向量化图，需要调embedding_result_destroy销毁资源
参数 session:图像向量化会话指针
image_file:图路径
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.6.2通过传base64图数据的式
头件 <coreai/embedding/embedding.h>
函数 boolimage_embedding_by_base64_image_data(ImageEmbeddingSession
- session,constunsignedchar*image_data,unsignedintimage_data_length,
EmbeddingResult**result);
描述 通过同步的式向量化图，需要调embedding_result_destroy销毁资源
参数 session:图像向量化会话指针
image_data:base64图数据
image_data_length:base64图数据的度
result:EmbeddingResult类型指针的地址
返回值 true:成功，false:失败
## 4.1 .3.3.7图像向量化模型向量化本（异步）
头件 <coreai/embedding/embedding.h>
函数 voidtext_embedding_by_image_model_async(ImageEmbeddingSession*session,
constchar*text,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);

描述 通过异步的式图像向量化模型向量化本
参数 session:图像向量化会话指针
text:本
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3.8向量化图（异步）
## 4.1 .3.3.8.1通过传图件路径的式
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_from_by_file_async(ImageEmbeddingSession*session,
constchar*file_path,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);
描述 通过异步的式向量化图
参数 session:图像向量化会话指针
image_file:图路径
callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.3.8.2通过传base64图数据的式
头件 <coreai/embedding/embedding.h>
函数 voidimage_embedding_by_base64_image_data_async(ImageEmbeddingSession
- session,constunsignedchar*image_data,
unsignedintimage_data_length,ImageEmbeddingResultCallbackcallback,void
- callback_user_data);
描述 通过异步的式向量化图
参数 session:图像向量化会话指针
image_data:base64图数据
image_data_length:base64图数据的度

callback:结果回调函数
callback_user_data:数据
返回值 
## 4.1 .3.4结果解析
## 4.1 .3.4.1获取向量化结果数据
头件 <coreai/embedding/embedding.h>
函数 float*embedding_result_get_vector_data(EmbeddingResult*result);
描述 获取向量化结果数据
参数 result:向量化结果的指针
返回值 float类型指针
## 4.1 .3.4.2获取向量化结果数据的度
头件 <coreai/embedding/embedding.h>
函数 intembedding_result_get_vector_length(EmbeddingResult*result);
描述 获取向量化结果数据的度
参数 result:向量化结果的指针
返回值 embedding_result_get_vector_data返回float指针数据的度
## 4.1 .3.4.3获取向量化错误码
头件 <coreai/embedding/embedding.h>
函数 intembedding_result_get_error_code(EmbeddingResult*result);
描述 获取错误码
参数 result:向量化结果的指针
返回值 具体的错误码
## 4.1 .3.4.4向量化错误信息

头件 <coreai/embedding/embedding.h>
函数 constchar*embedding_result_get_error_message(EmbeddingResult*result);
描述 获取错误信息
参数 result:向量化结果的指针
返回值 具体的错误信息
## 4.1 .3.4.5销毁向量化结果
头件 <coreai/embedding/embedding.h>
函数 voidembedding_result_destroy(EmbeddingResult**result);
描述 销毁向量化结果
参数 result:向量化结果指针的地址
返回值 
## 4.1 .3.4.6销毁模型信息结果
头件 <coreai/embedding/embedding.h>
函数 voidembedding_model_info_destroy(char*result);
描述 销毁模型信息结果
参数 result:模型信息结果的指针
返回值 
## 4.1 .3.4.7错误码
头件 <coreai/embedding/error.h>
枚举 typedefenum:int{
COREAI_EMBEDDING_SUCESS=0,
COREAI_EMBEDDING_INPUT_ERROR,
COREAI_EMBEDDING_INIT_ERROR,
COREAI_EMBEDDING_CONNECTION_ERROR,

COREAI_EMBEDDING_RUNTIME_ERROR,
COREAI_EMBEDDING_ERROR_UNKNOWN=99,
}CoreAiEmbeddingErrorCode;
描述 向量化相关的错误码
成员 COREAI_EMBEDDING_SUCESS：成功
COREAI_EMBEDDING_INPUT_ERROR：参数错误
COREAI_EMBEDDING_INIT_ERROR：向量化会话初始化错误
COREAI_EMBEDDING_CONNECTION_ERROR：向量化服务连接错误
COREAI_EMBEDDING_RUNTIME_ERROR：向量化解析runtime结果错误
COREAI_EMBEDDING_ERROR_UNKNOWN：向量化未知错误
## 4.1 .3.5例
## 4.1 .3.5.1先决条件
## 1. 仅x86和arm架构的机器上使向量化能；
配置CMakeLists.txt
```c
find_package(PkgConfig REQUIRED)
pkg_check_modules(Embedding REQUIRED IMPORTED_TARGET kysdk-coreai-embedding)
target_link_libraries(
xxx
pthread
${GIO_LIBRARIES}
PkgConfig::Embedding
)
```
## 4.1 .3.5.2本向量化
## 4.1 .3.5.2.1同步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
void textEmbeddingSync() {
TextEmbeddingSession *session = text_embedding_create_session();
int initSession = text_embedding_init_session(session);1

if (initSession != 0) {
std::cout << "init session failed" << std::endl;
}
// 同步接
EmbeddingResult *result = nullptr;
bool sucess = text_embedding(session, "12345", &result);
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << ",";
}
std::cout << std::endl;
char *info = nullptr;
text_embedding_get_model_info(session, &info);
std::cout << "print model info:" << info << std::endl;
std::cout << "释放结果资源 " << std::endl;
embedding_result_destroy(&result);
embedding_model_info_destroy(info);
text_embedding_destroy_session(&session);
}
## 4.1 .3.5.2.2异步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <gio/gio.h>
# include <thread>
void callback(EmbeddingResult *result, void *callback_user_data) {
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);7

std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << " ";
}
std::cout << std::endl;
if (callback_user_data != nullptr) {
int *a = static_cast<int *>(callback_user_data);
std::cout << "user_data :" << *a << std::endl;
}
}
void textEmbeddingAsync() {
TextEmbeddingSession *session = text_embedding_create_session();
if (text_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
text_embedding_async(session, "热爱学习 ", callback, nullptr);
auto *loop_ = g_main_loop_new(nullptr, false);
std::thread ctrlThread([&session, loop_] {
while (std::getchar() != '\n') {
}
g_main_loop_quit(loop_);
});
ctrlThread.detach();
g_main_loop_run(loop_);
text_embedding_destroy_session(&session);
}
## 4.1 .3.5.3图像向量化
## 4.1 .3.5.3.1同步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <filesystem>
# include <vector>
# include <fstream>11

std::vector<uint8_t> readFile(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary | std::ios::ate);
if (!file.is_open()) {
throw std::runtime_error("Failed to open file");
}
std::streamsize size = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> buffer(size);
if (file.read(reinterpret_cast<char *>(buffer.data()), size)) {
return buffer;
} else {
throw std::runtime_error("Failed to read file");
}
}
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64Encode(const std::vector<uint8_t> &buffer) {
std::string encodedData;
int i = 0;
uint8_t char_array_3[3];
uint8_t char_array_4[4];
while (i < buffer.size()) {
char_array_3[0] = buffer[i++];
char_array_3[1] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_3[2] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
char_array_4[1] =
((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
char_array_4[2] =
((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
char_array_4[3] = (char_array_3[2] & 0x3f);
for (int j = 0; (j < 4); ++j) {
encodedData += base64_chars[char_array_4[j]];
}
}
while ((encodedData.size() % 4) != 0) {
encodedData += '=';6

}
return encodedData;
}
void imageEmbeddingSync() {
ImageEmbeddingSession *session = image_embedding_create_session();
if (image_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
namespace fs = std::filesystem;
fs::path dir = fs::path(__FILE__).parent_path();
fs::path path = dir / " 微信图 _20240709181353.jpg";
std::string imagePath = path.string();
std::vector<uint8_t> imageData = readFile(imagePath);
std::string base64Data = base64Encode(imageData);
unsigned int length = base64Data.length();
const char *charPtr = base64Data.c_str();
const unsigned char *ucharPtr =
reinterpret_cast<const unsigned char *>(charPtr);
# if 1  // 同步向量化本
EmbeddingResult *result = nullptr;
text_embedding_by_image_model(session, "do you love working?", &result);
# elif
// 同步向量化图
EmbeddingResult *result = nullptr;
image_embedding_by_image_file(session, path.string().c_str(),
&result);  // 换成路径的图
# else
// 同步向量化 base64 图
EmbeddingResult *result = nullptr;
image_embedding_by_base64_image_data(session, ucharPtr, length, &result);
## 4.1 .3.5.3.2异步式
```c
```
# include <coreai/embedding/embedding.h>
# include <iostream>
# include <gio/gio.h>
# include <thread>
# include <vector>
# include <fstream>53

void callback(EmbeddingResult *result, void *callback_user_data) {
// 结果信息
int error_code = embedding_result_get_error_code(result);
std::cout << "error_code: " << error_code << std::endl;
const char *error_message = embedding_result_get_error_message(result);
std::cout << "error_message :" << error_message << std::endl;
float *vector_result = embedding_result_get_vector_data(result);
int len = embedding_result_get_vector_length(result);
std::cout << "vector_result :" << std::endl;
for (int i = 0; i < len; i++) {
std::cout << vector_result[i] << " ";
}
std::cout << std::endl;
if (callback_user_data != nullptr) {
int *a = static_cast<int *>(callback_user_data);
std::cout << "user_data :" << *a << std::endl;
}
}
std::vector<uint8_t> readFile(const std::string &filePath) {
std::ifstream file(filePath, std::ios::binary | std::ios::ate);
if (!file.is_open()) {
throw std::runtime_error("Failed to open file");
}
std::streamsize size = file.tellg();
file.seekg(0, std::ios::beg);
std::vector<uint8_t> buffer(size);
if (file.read(reinterpret_cast<char *>(buffer.data()), size)) {
return buffer;
} else {
throw std::runtime_error("Failed to read file");
}
}
const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
std::string base64Encode(const std::vector<uint8_t> &buffer) {
std::string encodedData;
int i = 0;
uint8_t char_array_3[3];8

uint8_t char_array_4[4];
while (i < buffer.size()) {
char_array_3[0] = buffer[i++];
char_array_3[1] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_3[2] = (i < buffer.size()) ? buffer[i++] : 0;
char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
char_array_4[1] =
((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
char_array_4[2] =
((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
char_array_4[3] = (char_array_3[2] & 0x3f);
for (int j = 0; (j < 4); ++j) {
encodedData += base64_chars[char_array_4[j]];
}
}
while ((encodedData.size() % 4) != 0) {
encodedData += '=';
}
return encodedData;
}
void imageEmbeddingAsync() {
ImageEmbeddingSession *session = image_embedding_create_session();
if (image_embedding_init_session(session) != 0) {
std::cout << "init session failed" << std::endl;
}
namespace fs = std::filesystem;
f f ( ) ()
## 4.2 成式AI能接
## 4.2 .1本成
## 1. 持本成、本对话；
## 2. 内置多种默认提词；
## 3. 持云端、端侧和定义的模型，具体可在设置->AI模块管理中进配置。 
## 4.2 .1.1开发环境部署
```bash
sudo apt install libkysdk-genai-nlp-dev55
```

## 4.2 .1.2会话
## 4.2 .1.2.1创建会话
头件 <genai/text/chat.h>
函数 GenAiTextSession*genai_text_create_session()
描述 创建本成会话
参数 
返回值 本成会话的指针
## 4.2 .1.2.2初始化会话
头件 <genai/text/chat.h>
函数 intgenai_text_init_session(GenAiTextSession*session)
描述 初始化会话
参数 session:本成会话指针
返回值 成功时返回0，否则返回具体的错误码
## 4.2 .1.2.3销毁会话
头件 <genai/text/chat.h>
函数 voidgenai_text_destroy_session(GenAiTextSession**session)
描述 销毁本成会话
参数 session:本成会话指针的地址
返回值 
## 4.2 .1.2.4设置结果回调函数
头件 <genai/text/chat.h>
函数 voidgenai_text_result_set_callback(GenAiTextSession*session,
ChatResultCallbackcallback,void*user_data)

描述 设置对话结果回调函数
参数 session:本成会话的指针
callback:结果回调函数
user_data:的数据
返回值 
## 4.2 .1.2.5设置模型配置
头件 <genai/text/chat.h>
函数 voidgenai_text_set_model_config(GenAiTextSession*session,ChatModelConfig
- config)
描述 设置模型配置
参数 session:本成会话指针
config:模型配置
返回值 
## 4.2 .1.2.6本成
头件 <genai/text/chat.h>
函数 voidgenai_text_generate_content_async(GenAiTextSession*session,constchar
- prompt)
描述 根据提内容成本
参数 session:本成会话指针
prompt:输提词本
返回值 
## 4.2 .1.2.7本对话-持缓存历史消息
头件 <genai/text/chat.h>
函数 voidgenai_text_chat_async(GenAiTextSession*session,constchar*question)

描述 进本对话，持缓存历史消息
参数 -session:本成会话
- question:具体的问题
返回值 
## 4.2 .1.2.8本对话-不持缓存历史消息
头件 <genai/text/chat.h>
函数 voidgenai_text_chat_with_history_messages_async(GenAiTextSession*session,
ChatMessage*history_messages)
描述 进本对话，需要传历史消息
参数 session:本成会话
history_messages:历史消息
返回值 
## 4.2 .1.2.9设置提词-定义提词
头件 <genai/text/chat.h>
函数 voidgenai_text_set_chat_system_prompt(GenAiTextSession*session,constchar
- prompt)
描述 设置系统提词
参数 session:本成会话
prompt:具体的系统提词
返回值 
## 4.2 .1.2.10设置提词-使系统内置提词
头件 <genai/text/chat.h>
函数 voidgenai_text_set_chat_system_prompt_id(GenAiTextSession*session,PromptId
prompt_id)
描述 设置系统提词id，使内置提词

参数 session:本成会话
prompt_id:提词id
返回值 
## 4.2 .1.2.11清除历史消息
头件 <genai/text/chat.h>
函数 voidgenai_text_clear_chat_history_messages(GenaiTextSession*session)
描述 清除对话历史消息
参数 session:本成会话
返回值 
## 4.2 .1.2.12停会话
头件 <genai/text/chat.h>
函数 voidgenai_text_stop_chat(GenaiTextSession*session)
描述 停对话
参数 session:本成会话
返回值 
## 4.2 .1.3模型参数配置
## 4.2 .1.3.1创建模型配置实例
头件 <genai/text/config.h>
函数 ChatModelConfig*chat_model_config_create()
描述 创建模型配置实例
参数 
返回值 模型配置实例指针
## 4.2 .1.3.2销毁模型配置实例

头件 <genai/text/config.h>
函数 voidchat_model_config_destroy(ChatModelConfig**config)
描述 销毁模型配置实例
参数 config:模型配置的级指针
返回值 
## 4.2 .1.3.3设置使的模型
头件 <genai/text/config.h>
函数 voidchat_model_config_set_name(ChatModelConfig*config,constchar
- model_name)
描述 设置模型的名称
参数 config:模型配置实例指针
model_name:模型的名称
返回值 
## 4.2 .1.3.4设置模型的参数
头件 <genai/text/config.h>
函数 voidchat_model_config_set_top_k(ChatModelConfig*config,doubletop_k)
描述 设置模型的top_k参数
参数 config:模型配置实例的指针
top_k:top_k参数的数值
返回值 
## 4.2 .1.3.5设置模型的部署类型
## 1. 指定要使的模型的部署类型；
## 2. 如果未指定部署类型，则会根据设置->AI模块管理中配置的优先级进选择。 
头件 <genai/text/config.h>

函数 voidchat_model_config_set_deploy_type(ChatModelConfig*config,
ModelDeployTypetype)
描述 设置模型的部署类型
参数 config:模型配置实例的指针
type:模型类型
返回值 
## 4.2 .1.3.6设置模型的名称
## 1. 名称是是指设置->AI模块管理中配置的名称；
## 2. 如果同时指定了部署类型和名称，会优先匹配名称，如果法匹配，则匹配对应的部署类型；
## 3. 如果未指定名称，则会根据设置->AI模块管理中配置的优先级进选择。
头件 <genai/text/config.h>
函数 voidchat_model_config_set_name(ChatModelConfig*config,constchar*name);
描述 设置模型的名称
参数 config:模型配置实例的指针
name:模型的名称
返回值 
## 4.2 .1.4结果解析
## 4.2 .1.4.1获取模型成的消息
头件 <genai/text/result.h>
函数 constchar*chat_result_get_assistant_message(ChatResult*result)
描述 获取模型成的本结果
参数 result:本成结果实例指针
返回值 本字符串
## 4.2 .1.4.2获取成结束的原因
头件 <genai/text/result.h>

函数 constchar*chat_result_get_finish_reason_message(ChatResult*result)
描述 获取对话结束的原因
参数 result:本成的结果的指针
返回值 具体的原因
## 4.2 .1.4.3获取成结果的错误码
头件 <genai/text/result.h>
函数 intchat_result_get_error_code(ChatResult*result)
描述 获取具体的错误码
参数 result:本成的结果的指针
返回值 具体的错误码
## 4.2 .1.4.4获取成结果的具体错误信息
头件 <genai/text/result.h>
函数 constchar*chat_result_get_error_message(ChatResult*result)
描述 获取具体的错信息
参数 result:本成的结果的指针
返回值 具体错误信息
## 4.2 .1.4.5获取成结果的结束标志
头件 <genai/text/result.h>
函数 constchar*chat_result_get_is_end(ChatResult*result)
描述 获取是否是最后结果的标志
参数 result:本成的结果的指针
返回值 是否为结束消息

## 4.2 .1.5错误码
通错误码可参考4.3节，本成专错误码如下：
头件 <genai/text/error.h>
枚举 typedefenum{
NLP_INPUT_INVALID=100,
NLP_PARAM_ERROR
}GenAiTextErrorCode;
描述 本成相关的错误码
成员 NLP_INPUT_INVALID：输本效
NLP_PARAM_ERROR：参数错误
## 4.2 .1.6例
## 4.2 .1.6.1前提条件
## 1. 仅x86和arm架构的机器上可使端侧模型；
## 2. 如果想使云端模型或者定义模型需要在设置->AI模块管理中进配置。 
配置CMakeLists.txt
```c
find_package(PkgConfig REQUIRED)
pkg_check_modules(KYAINLP kysdk-genai-nlp)
include_directories(${KYAINLP_INCLUDE_DIRS})
target_link_libraries(
xxx
pthread
${GIO_LIBRARIES}
${KYAINLP_LIBRARIES}
)
```
## 4.2 .1.6.2回调函数设置
后续测试如果没有特殊说明，都使该回调
void callback(ChatResult *result, void *user_data) {
auto getBool = [](bool value) { return value ? "true" : "false"; };1

fprintf(stdout, "%s\n", chat_result_get_assistant_message(result));
fprintf(stdout, "%s\n", chat_result_get_finish_reason_message(result));
fprintf(stdout, "%d\n", chat_result_get_error_code(result));
fprintf(stdout, "%s\n", chat_result_get_error_message(result));
fprintf(stdout, "%s\n", getBool(chat_result_get_is_end(result)));
if (user_data != nullptr) {
int *a = static_cast<int *>(user_data);
fprintf(stdout, "%d\n", *a);
}
}3
## 4.2 .1.6.3基本会话
// 此样例未设置提词
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/text/chat.h>
void chat() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([pMainLoop] {
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
});
ctrlThread.detach();
ChatModelConfig *config = chat_model_config_create();
chat_model_config_set_name(config, "百度-ERNIE-Bot-4");
chat_model_config_set_top_k(config, 0.5);
chat_model_config_set_deploy_type(config, ModelDeployType::PublicCloud);
GenAiTextSession *session = genai_text_create_session();
genai_text_set_model_config(session, config);
genai_text_init_session(session);
int a = 100;1

genai_text_result_set_callback(session, callback, &a);
genai_text_chat_async(session, "加等于 ");
while (std::getchar() != '\n') {
}
genai_text_chat_async(session, "你说的不对 ");
while (std::getchar() != '\n') {
}
genai_text_stop_chat(session);
genai_text_destroy_session(&session);
chat_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
}33
## 4.2 .1.6.4使历史消息会话
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/text/chat.h>
void chatHistoryMessages() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([pMainLoop] {
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
});
ctrlThread.detach();
ChatModelConfig *config = chat_model_config_create();
chat_model_config_set_name(config, "百度-ERNIE-Bot-4");
chat_model_config_set_top_k(config, 0.5);
chat_model_config_set_deploy_type(config, ModelDeployType::PublicCloud);
GenAiTextSession *session = genai_text_create_session();
genai_text_set_model_config(session, config);1

genai_text_init_session(session);
genai_text_result_set_callback(session, callback, nullptr);
ChatMessage *chatMessage = chat_message_create();
chat_message_add_system_message(chatMessage, "");
chat_message_add_user_message(chatMessage, "加等于 ");
chat_message_add_system_message(chatMessage,
"这是个常基础的数学问题， "
"、涉及到的是加法运算。题问 "
"的是1+1 等于。 \n\n 在数学中， "
"加法是种基本的运算式，表 "
"两个数量的和。当我们把两个 1"
"加在起时，就是在计算这两个 "
"数量的总和。 \n\n 所以， 1 + 1 ="
" 2。\n\n 因此，答案是 2 。这个问 "
"题常直接，没有涉及到复杂的 "
"数学概念或技巧，只需要理解加 "
"法的基本定义即可。 ");
chat_message_add_user_message(chatMessage, "你说的不对 ");
genai_text_chat_with_history_messages_async(session, chatMessage);
while (std::getchar() != '\n') {
}
chat_message_destroy(&chatMessage);
genai_text_stop_chat(session);
genai_text_destroy_session(&session);
chat_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
}28
## 4.2 .1.6.5清理消息
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/text/chat.h>1

void clearChatMessage() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([pMainLoop] {
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
});
ctrlThread.detach();
ChatModelConfig *config = chat_model_config_create();
chat_model_config_set_name(config, "百度-ERNIE-Bot-4");
chat_model_config_set_top_k(config, 0.5);
chat_model_config_set_deploy_type(config, ModelDeployType::PublicCloud);
GenAiTextSession *session = genai_text_create_session();
genai_text_set_model_config(session, config);
genai_text_init_session(session);
genai_text_result_set_callback(session, callback, nullptr);
genai_text_chat_async(session, "加等于 ");
while (std::getchar() != '\n') {
}
genai_text_clear_chat_history_messages(session);
while (std::getchar() != '\n') {
}
genai_text_chat_async(session, "你说的不对 ");
while (std::getchar() != '\n') {
}
genai_text_stop_chat(session);
genai_text_destroy_session(&session);
chat_model_config_destroy(&config);
g_main_loop_quit(pMainLoop);
}12
## 4.2 .1.6.6内容成
# include <gio/gio.h>
# include <gio/giotypes.h>1

# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/text/chat.h>
void generateContent() {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([pMainLoop] {
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
});
ctrlThread.detach();
ChatModelConfig *config = chat_model_config_create();
chat_model_config_set_top_k(config, 0.5);
// 使云端模型
chat_model_config_set_deploy_type(config, ModelDeployType::PublicCloud);// 使端侧模型
// chat_model_config_set_deploy_type(config, ModelDeployType::OnDevice);GenAiTextSession *session = genai_text_create_session();
genai_text_set_model_config(session, config);
genai_text_init_session(session);
genai_text_result_set_callback(session, callback, nullptr);
genai_text_generate_content_async(session, "今天天不错 ");
while (std::getchar() != '\n') {
}
genai_text_stop_chat(session);
genai_text_destroy_session(&session);
g_main_loop_quit(pMainLoop);
}4
## 4.2 .1.6.7使系统内置提词对话
# include <gio/gio.h>
# include <gio/giotypes.h>
# include <filesystem>1

# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/text/chat.h>
void chatSystemPromptId(PromptId promptId, const std::string &question) {
GMainLoop *pMainLoop = g_main_loop_new(nullptr, false);
std::thread ctrlThread([pMainLoop] {
g_main_loop_run(pMainLoop);
g_main_loop_unref(pMainLoop);
});
ctrlThread.detach();
ChatModelConfig *config = chat_model_config_create();
chat_model_config_set_name(config, "百度-ERNIE-Bot-4");
chat_model_config_set_top_k(config, 0.5);
chat_model_config_set_deploy_type(config, ModelDeployType::PublicCloud);
GenAiTextSession *session = genai_text_create_session();
genai_text_set_model_config(session, config);
genai_text_init_session(session);
genai_text_result_set_callback(session, callback, nullptr);
genai_text_set_chat_system_prompt_id(session, promptId);
genai_text_chat_async(session, question.c_str());
while (std::getchar() != '\n') {
}
genai_text_stop_chat(session);
genai_text_destroy_session(&session);
g_main_loop_quit(pMainLoop);
}
void chatSystemPromptId_SUMMARY() {
chatSystemPromptId(
SUMMARY,
"模型是智能领域的热研究向。专家认为，智能进 "
"产业级模型时代。模型将是未来段时间科技领域最重要的事情之 "
"。模型将开启智能的  统时代  。 ");
}
void chatSystemPromptId_TEXT_EXPANSION() {
chatSystemPromptId(TEXT_EXPANSION, "今天天不错 ");
}5

void chatSystemPromptId_TRANSLATE_CHINESE_TO_ENGLISH() {
chatSystemPromptId(TRANSLATE_CHINESE_TO_ENGLISH,"今天天不错 ");
}52
## 4.2 .2图像成
## 1. 根据本描述图；
## 2. 持多种格；
## 3. 持多种分辨率；
## 4. 持多种语；
## 5. 具体参数依赖云端服务；
## 6. 前仅持云端服务。
## 4.2 .2.1开发环境部署
```bash
sudo apt install libkysdk-genai-vision-dev
```
## 4.2 .2.2会话
## 4.2 .2.2.1创建会话
头件 <genai/vision/image.h>
函数 GenAiImageSession*genai_image_create_session()
描述 创建图成会话
参数 
返回值 图成会话的指针
## 4.2 .2.2.2初始化会话
头件 <genai/vision/image.h>
函数 intgenai_image_init_session(GenAiImageSession*session)
描述 初始化会话
参数 session:图成会话指针
返回值 成功时返回0，否则返回具体的错误码

## 4.2 .2.2.3销毁会话
头件 <genai/vision/image.h>
函数 voidgenai_image_destroy_session(GenAiImageSession**session)
描述 销毁图成会话
参数 session:图成会话指针的地址
返回值 
## 4.2 .2.2.4设置图像成的相关配置
头件 <genai/vision/image.h>
函数 voidgenai_image_set_config(GenAiImageSession*session,ImageConfig*config)
描述 设置图像成的相关配置
参数 session:本成会话指针
config:配置实例的指针
返回值 
## 4.2 .2.2.5设置结果回调函数
头件 <genai/vision/image.h>
函数 voidgenai_image_result_set_callback(GenAiTextSession*session,
ImageResultCallbackcallback,void*user_data)
描述 设置对话结果回调函数
参数 session:图成会话的指针
callback:结果回调函数
user_data:的数据
返回值 
## 4.2 .2.2.6获取持图格
头件 <genai/vision/image.h>

函数 constchar**genai_image_get_supported_image_style(GenAiImageSession
- session,int*number)
描述 获取持的图样格，如古，次元等
参数 session:图成会话的指针
number:持的图格数，输出参数
返回值 返回字符串数组的地址（constchar**）
## 4.2 .2.2.7获取持的图尺
头件 <genai/vision/image.h>
函数 constImageSize*genai_image_get_supported_image_size(GenAiImageSession
- session,int*number)
描述 获取持的图尺，如1280*720，1920*1080等
参数 session:图成会话的指针
number:持的图尺的数量
返回值 返回ImageSize数组的地址地址，ImageSize包含两个参数（width和height）
## 4.2 .2.2.8获取持成图的数量
头件 <genai/vision/image.h>
函数 intgenai_image_get_supported_image_number(GenAiImageSession*session)
描述 获取持成图数量
参数 session:图成会话的指针
返回值 返回持成图数量
## 4.2 .2.2.9成图
头件 <genai/vision/image.h>
函数 voidgenai_image_generate_image_async(GenAiImageSession*session,constchar
- prompt)
描述 根据提词成图

参数 session:图成会话的指针
返回值 
## 4.2 .2.3图配置
## 4.2 .2.3.1图尺结构体
头件 <genai/vision/imageconfig.h>
结构体名称 typedefstruct_ImageSize{
intwidth;
intheight;
}ImageSize
描述 图尺
公有成员变量：
width类型：int；描述：宽度
公有成员变量：
height类型：int；描述：度
## 4.2 .2.3.2图配置结构体创建
头件 <genai/vision/imageconfig.h>
函数 ImageConfig*image_config_create()
描述 创建图配置相关的结构体实例
参数 
返回值 图配置结构体指针
## 4.2 .2.3.3图配置结构体销毁
头件 <genai/vision/imageconfig.h>
函数 voidimage_config_destroy(ImageConfig**config)
描述 销毁图配置结构体
参数 config:图配置结构体指针的地址

返回值 
## 4.2 .2.3.4图配置结构体设置成数量
头件 <genai/vision/imageconfig.h>
函数 voidimage_config_set_generation_number(ImageConfig*config,intnumber)
描述 图配置结构体设置成数量
参数 config:图配置结构体指针
number:成数量
返回值 
## 4.2 .2.3.5图配置结构体设置格
头件 <genai/vision/imageconfig.h>
函数 voidimage_config_set_style(ImageConfig*config,constchar*style)
描述 图配置结构体设置格
参数 config:图配置结构体指针
style:格（如古、次元等）
返回值 
## 4.2 .2.3.6图配置结构体设置图尺
头件 <genai/vision/imageconfig.h>
函数 voidimage_config_set_size(ImageConfig*config,ImageSizeimage_size)
描述 图配置结构体设置图尺
参数 config:图配置结构体指针
image_size:图尺
返回值 
## 4.2 .2.4错误码

通错误码参考4.3节，图专有错误码如下：
头件 <genai/vision/error.h>
枚举 typedefenum{
VISION_INPUT_TEXT_LENGTH_INVALID=100，
VISION_IMAGE_STYLE_INVALID，
VISION_IMAGE_SIZE_INVALID，
VISION_IMAGE_NUMBER_INVALID，
VISION_IMAGE_GENERATION_BLOCKED，
VISION_IMAGE_GENERATION_FAILED，
}GenAiVisionErrorCode;
描述 本成相关的错误码
成员 VISION_INPUT_TEXT_LENGTH_INVALID：输的提词本过
VISION_IMAGE_STYLE_INVALID：不持的格
VISION_IMAGE_SIZE_INVALID：不持的图
VISION_IMAGE_NUMBER_INVALID：不持的图数量
VISION_IMAGE_GENERATION_BLOCKED：成的图未过审
VISION_IMAGE_GENERATION_FAILED：成图失败
## 4.2 .2.5结果解析
## 4.2 .2.5.1获取成图格式
头件 <genai/vision/imageresult.h>
函数 ImageFormatimage_result_get_format(VisionImageResult*image_result)
描述 获取图格式（jpg、png等）
参数 image_result:图配结果结构体指针
返回值 图格式（jpg、png等）
## 4.2 .2.5.2获取成图尺
头件 <genai/vision/imageresult.h>

函数 ImageSizeimage_result_get_size(VisionImageResult*image_result)
描述 获取图尺
参数 image_result:图结果结构体指针
返回值 图尺结构体
## 4.2 .2.5.3获取成图总数量
头件 <genai/vision/imageresult.h>
函数 intimage_result_get_total(VisionImageResult*image_result)
描述 获取成图总数量
参数 image_result:图结果结构体指针
返回值 成图总数量
## 4.2 .2.5.4获取成图序号
头件 <genai/vision/imageresult.h>
函数 intimage_result_get_index(VisionImageResult*image_result)
描述 获取成图序号
参数 image_result:图结果结构体指针
返回值 成图序号
## 4.2 .2.5.5获取成图数据
头件 <genai/vision/imageresult.h>
函数 constuint8_t*image_result_get_data(VisionImageResult*image_result,int
- data_length)
描述 获取成图数据
参数 image_result:图结果结构体指针
data_length:图数据度
返回值 图数据地址

## 4.2 .2.5.6获取成图结果错误码
头件 <genai/vision/imageresult.h>
函数 intimage_result_get_error_code(VisionImageResult*image_result)
描述 获取图尺获取成图结果错误码
参数 image_result:图结果结构体指针
返回值 成图结果错误码
## 4.2 .2.5.7获取成图结果错误信息
头件 <genai/vision/imageresult.h>
函数 constchar*image_result_get_error_message(VisionImageResult*image_result)
描述 获取成图结果错误信息
参数 image_result:图结果结构体指针
返回值 成图结果错误信息
## 4.2 .2.6代码例
## 4.2 .2.6.1前提条件
需要在设置->AI模块管理中配置图相关的账号。
## 4.2 .2.6.2例
配置CMakeLists.txt
```c
find_package(PkgConfig REQUIRED)
pkg_check_modules(KYAIVISION kysdk-genai-vision)
include_directories(${KYAIVISION_INCLUDE_DIRS})
target_link_libraries(
xxx
pthread
${GIO_LIBRARIES}
${KYAIVISION_LIBRARIES}
)
```

具体demo：
# include <cstdio>
# include <filesystem>
# include <fstream>
# include <iostream>
# include <thread>
# include <vector>
# include <genai/vision/image.h>
# include <gio/gio.h>
static void writeBinaryDataToFile(const std::string &filename,
const std::vector<char> &data) {
std::ofstream outputFile(filename, std::ios::out | std::ios::binary |
std::ios::trunc);
if (!outputFile.is_open()) {
std::cerr << "Failed to open file for writing." << std::endl;
return;
}
// 写数据到件
outputFile.write(data.data(), data.size());
// 检查是否写成功
if (!outputFile.good()) {
std::cerr << "Error occurred while writing to file." << std::endl;
} else {
std::cout << "Binary data has been written to file: " << filename
<< std::endl;
}
// 关闭件
outputFile.close();
}
void callback(VisionImageResult *image_data, void *user_data) {
int imageDataLength;
const uint8_t* imageData = image_result_get_data(image_data,
&imageDataLength);
int imageWidth = image_result_get_size(image_data).width;
int imageHeight = image_result_get_size(image_data).height;
ImageFormat format = image_result_get_format(image_data);
int index = image_result_get_index(image_data);
int total = image_result_get_total(image_data);
int errorcode = image_result_get_error_code(image_data);1

std::string errorMsg = image_result_get_error_message(image_data);
std::vector<char> imagedata { imageData, imageData + imageDataLength };
writeBinaryDataToFile("../test3.png", imagedata);
int userData = *(int*)user_data;
std::cout << "length " << imageDataLength
<< " width " << imageWidth
<< " height " << imageHeight
<< " format " << format << std::endl;
std::cout << "index " << index
<< " total " << total
<< " errorCode " << errorcode
<< " errorMag " << errorMsg
<< " userdata " << userData << std::endl;
}
void test() {
auto *loop_ = g_main_loop_new(nullptr, false);
GenAiImageSession *session = genai_image_create_session();
int initRet = genai_image_init_session(session);
fprintf(stderr, "init return value %i\n", initRet);
ImageConfig *config = image_config_create();
image_config_set_generation_number(config, 1);
image_config_set_style(config, "写实格 ");
image_config_set_size(config, ImageSize{1280, 720});
genai_image_set_config(session, config);
bool imageNumber = genai_image_get_supported_image_number(session);
std::cout << "supported image number " << imageNumber << std::endl;
int sizeNumber;
const ImageSize* imageSize =
genai_image_get_supported_image_size(session, &sizeNumber);
int i = 0;
while (i < sizeNumber) {
std::cout << "supported image size width " << imageSize[i].width
<< " height " << imageSize[i].height << std::endl;
++i;
}
int styleNumber;
int j = 0;43

const char** imageStyle = genai_image_get_supported_image_style(session,
&styleNumber);
while (j < styleNumber) {
std::cout << "supported image style " << imageStyle[j] << std::endl;
++j;
}
int *a = new int();
- a = 100;
genai_image_result_set_callback(session, callback, a);
genai_image_generate_image_async(session, "成张狗的图 ");
g_main_loop_run(loop_);
}88
## 4.3 通错误码
typedef enum {
// 未发错误
AISDK_NO_ERROR = 0,
// 络错误，如络断开或者速较慢等
AISDK_NET_ERROR,
// 鉴权错误，如云端服务的账号信息填写有误
AISDK_AUTHENTICATION_FAILURE,
// 运时服务错误，后端服务发错误，可重试或者进反馈
AISDK_RUNTIME_ERROR,
// 请求次数过多，多于云端服务的场景
AISDK_TOO_MANY_REQUESTS,
// 云端服务错误
AISDK_SERVICE_ERROR,
// 云端服务超时
AISDK_SERVICE_TIMEOUT,
// 参数错误，请求格式错误
AISDK_BAD_REQUEST,
// 模型运失败
AISDK_MODEL_RUN_FAILED,
// 模型运超时
AISDK_MODEL_RUN_TIME_OUT,
// 未找到可的模型
AISDK_MODEL_NOT_FOUND,
} AiSdkCommonErrorCode;1
