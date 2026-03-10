# WatchFaceSDK-ObjC 集成指南

**版本**: v1.0.1
**发布日期**: 2026-01-14
**SDK 类型**: 纯 Objective-C 动态库
**最低支持**: iOS 13.0+

---

## 📋 目录

- [SDK 简介](#sdk-简介)
- [系统要求](#系统要求)
- [快速集成](#快速集成)
- [API 文档](#api-文档)
- [代码示例](#代码示例)
- [动态库依赖说明](#动态库依赖说明)
- [常见问题](#常见问题)
- [故障排查](#故障排查)

---

## SDK 简介

WatchFaceSDK-ObjC 是一个纯 Objective-C 的智能手表表盘管理 SDK，提供完整的表盘上传、自定义表盘制作和实时进度监控功能。本版本采用**纯动态库架构**，需要配合 WatchProtocolSDK 动态库使用。

### ✨ 主要功能

- ✅ **市场表盘上传** - 支持从本地文件或 NSData 上传市场表盘
- ✅ **自定义表盘制作** - 从任意图片创建个性化表盘
- ✅ **智能图片处理** - 自动裁剪、压缩、RGB565 和 PAR 格式转换
- ✅ **屏幕自动适配** - 圆形/方形屏幕自动检测和适配
- ✅ **实时进度监控** - 精确的传输进度回调
- ✅ **传输控制** - 支持暂停、取消和重试
- ✅ **纯动态库** - 运行时加载，减小应用体积
- ✅ **无 Swift 依赖** - 完全兼容 Objective-C 项目

### 🎯 技术特点

| 特性 | 说明 |
|-----|------|
| **语言** | 纯 Objective-C |
| **架构** | 动态库 (Dynamic Framework) |
| **大小** | 312KB |
| **依赖** | WatchProtocolSDK (动态库)<br>ABParTool (动态库) |
| **架构支持** | arm64 (真机)<br>arm64 + x86_64 (模拟器) |

---

## 系统要求

### 基础要求

| 项目 | 要求 |
|------|------|
| iOS 版本 | iOS 13.0+ |
| Xcode | Xcode 12.0+ |
| 开发语言 | Objective-C / Swift |
| 蓝牙 | Bluetooth 4.0 (BLE) |

### 依赖框架

**必需的系统框架：**
- `Foundation.framework`
- `UIKit.framework`
- `CoreGraphics.framework`
- `CoreBluetooth.framework`

**必需的第三方动态库：**
- `WatchProtocolSDK.xcframework` (来自 Output-ObjC-Dynamic)
- `ABParTool.xcframework`

---

## 快速集成

### 步骤 1：准备 Framework 文件

确保你有以下三个 XCFramework：

```
WatchFaceSDK_ObjC.xcframework    (主 SDK)
WatchProtocolSDK.xcframework     (依赖 - 从 Output-ObjC-Dynamic 获取)
ABParTool.xcframework            (依赖)
```

⚠️ **重要**: 必须使用 **Output-ObjC-Dynamic** 目录中的 `WatchProtocolSDK.xcframework`，这是动态库版本。

### 步骤 2：添加到 Xcode 项目

1. 将三个 XCFramework 拖入 Xcode 项目
2. 在弹出的对话框中：
   - ✅ 勾选 **Copy items if needed**
   - ✅ 选择正确的 Target

### 步骤 3：配置 Framework 嵌入方式

**这是最关键的一步！**

打开 Xcode 项目，选择 **Target** → **General** → **Frameworks, Libraries, and Embedded Content**

将所有三个 Framework 设置为 **Embed & Sign**：

```
✅ WatchFaceSDK_ObjC.xcframework        → Embed & Sign
✅ WatchProtocolSDK.xcframework         → Embed & Sign
✅ ABParTool.xcframework                → Embed & Sign
```

⚠️ **错误示例**（会导致运行时崩溃）：
```
❌ WatchFaceSDK_ObjC.xcframework        → Embed & Sign
❌ WatchProtocolSDK.xcframework         → Do Not Embed  ← 错误！
❌ ABParTool.xcframework                → Do Not Embed  ← 错误！
```

### 步骤 4：配置 Build Settings

在 **Build Settings** 中搜索并配置：

**Framework Search Paths:**
```
$(PROJECT_DIR)/Frameworks
```

或者，如果你将 Framework 放在其他位置：
```
$(PROJECT_DIR)/YourCustomPath
```

### 步骤 5：添加蓝牙权限

在 `Info.plist` 中添加：

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>

<key>NSBluetoothPeripheralUsageDescription</key>
<string>需要使用蓝牙与智能手表进行数据交互</string>
```

### 步骤 6：导入头文件

**Objective-C 项目：**

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
```

**Swift 项目：**

在 Bridging Header 中添加：

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
```

---

## API 文档

### WFManager - 主管理类

#### 单例方法

```objc
/// 获取单例实例
+ (instancetype)sharedInstance;
```

---

### 设备信息查询

#### 获取当前设备屏幕信息

```objc
/// @return 设备屏幕信息，如果设备未连接则返回 nil
- (nullable WFDeviceScreenInfo *)getCurrentDeviceScreenInfo;
```

**示例：**
```objc
WFManager *manager = [WFManager sharedInstance];
WFDeviceScreenInfo *screenInfo = [manager getCurrentDeviceScreenInfo];

if (screenInfo) {
    NSLog(@"屏幕尺寸: %ldx%ld", screenInfo.width, screenInfo.height);
    NSLog(@"屏幕形状: %@", screenInfo.shape == WFScreenShapeRound ? @"圆形" : @"方形");
    NSLog(@"MTU: %ld", screenInfo.mtu);
}
```

#### 检查设备是否连接

```objc
/// @return 是否连接
- (BOOL)isDeviceConnected;
```

**示例：**
```objc
if ([manager isDeviceConnected]) {
    NSLog(@"设备已连接");
} else {
    NSLog(@"设备未连接，请先连接设备");
}
```

#### 获取推荐的图片尺寸

```objc
/// @return 推荐尺寸，如果设备未连接则返回 CGSizeZero
- (CGSize)getRecommendedImageSize;
```

**示例：**
```objc
CGSize recommendedSize = [manager getRecommendedImageSize];
NSLog(@"推荐图片尺寸: %.0fx%.0f", recommendedSize.width, recommendedSize.height);
```

---

### 上传市场表盘

#### 从 NSData 上传

```objc
/// @param data 表盘文件数据
/// @param delegate 传输进度代理
/// @param error 错误信息
/// @return 是否成功开始传输
- (BOOL)uploadMarketWatchFaceWithData:(NSData *)data
                             delegate:(nullable id<WFTransferDelegate>)delegate
                                error:(NSError **)error;
```

**示例：**
```objc
NSData *watchFaceData = [NSData dataWithContentsOfURL:fileURL];
NSError *error = nil;

BOOL success = [manager uploadMarketWatchFaceWithData:watchFaceData
                                              delegate:self
                                                 error:&error];
if (!success) {
    NSLog(@"上传失败: %@", error.localizedDescription);
}
```

#### 从文件 URL 上传

```objc
/// @param fileURL 表盘文件路径
/// @param delegate 传输进度代理
/// @param error 错误信息
/// @return 是否成功开始传输
- (BOOL)uploadMarketWatchFaceWithFileURL:(NSURL *)fileURL
                                delegate:(nullable id<WFTransferDelegate>)delegate
                                   error:(NSError **)error;
```

**示例：**
```objc
NSURL *fileURL = [[NSBundle mainBundle] URLForResource:@"watchface"
                                          withExtension:@"bin"];
NSError *error = nil;

BOOL success = [manager uploadMarketWatchFaceWithFileURL:fileURL
                                                delegate:self
                                                   error:&error];
if (!success) {
    NSLog(@"上传失败: %@", error.localizedDescription);
}
```

---

### 上传自定义表盘

```objc
/// @param image 原始图片
/// @param timePosition 时间位置
/// @param color 颜色
/// @param delegate 传输进度代理
/// @param error 错误信息
/// @return 是否成功开始传输
- (BOOL)uploadCustomWatchFaceWithImage:(UIImage *)image
                          timePosition:(WFTimePosition)timePosition
                                 color:(WFDialColor)color
                              delegate:(nullable id<WFTransferDelegate>)delegate
                                 error:(NSError **)error;
```

**参数说明：**

| 参数 | 类型 | 说明 |
|-----|------|------|
| image | UIImage | 原始背景图片（SDK 会自动处理） |
| timePosition | WFTimePosition | 时间显示位置（左上、右上、左下、右下、居中） |
| color | WFDialColor | 时间颜色（白、黑、黄、橙、粉、紫、蓝、青、绿） |
| delegate | id\<WFTransferDelegate\> | 传输进度回调代理 |
| error | NSError ** | 错误信息输出 |

**示例：**
```objc
UIImage *backgroundImage = [UIImage imageNamed:@"my_background"];
NSError *error = nil;

BOOL success = [manager uploadCustomWatchFaceWithImage:backgroundImage
                                          timePosition:WFTimePositionTopLeft
                                                 color:WFDialColorWhite
                                              delegate:self
                                                 error:&error];
if (!success) {
    NSLog(@"创建失败: %@", error.localizedDescription);
}
```

---

### 图片验证

```objc
/// 验证图片是否符合要求
/// @param image 图片
/// @param message 错误消息（输出参数）
/// @return 是否有效
- (BOOL)validateImage:(UIImage *)image message:(NSString **)message;
```

**示例：**
```objc
UIImage *image = [UIImage imageNamed:@"test"];
NSString *message = nil;

if (![manager validateImage:image message:&message]) {
    NSLog(@"图片验证失败: %@", message);
    // 显示错误提示给用户
} else {
    NSLog(@"图片验证通过");
    // 继续上传流程
}
```

---

### 传输控制

#### 暂停传输

```objc
/// 暂停当前传输
- (void)pauseTransfer;
```

**示例：**
```objc
[manager pauseTransfer];
```

#### 取消传输

```objc
/// 取消当前传输
- (void)cancelTransfer;
```

**示例：**
```objc
[manager cancelTransfer];
```

#### 重试传输

```objc
/// 重试失败的传输
- (void)retryTransfer;
```

**示例：**
```objc
// 在传输失败后重试
- (void)watchFaceTransferDidFailWithError:(NSError *)error {
    if (error.code == WFErrorCodeTransferTimeout) {
        // 超时错误，自动重试
        [[WFManager sharedInstance] retryTransfer];
    }
}
```

---

### WFTransferDelegate - 传输回调协议

```objc
@protocol WFTransferDelegate <NSObject>

@optional

/// 传输开始
- (void)watchFaceTransferDidStart;

/// 进度更新
- (void)watchFaceTransferDidUpdateProgress:(WFTransferProgress *)progress;

/// 传输完成
- (void)watchFaceTransferDidComplete;

/// 传输失败
- (void)watchFaceTransferDidFailWithError:(NSError *)error;

/// 传输暂停
- (void)watchFaceTransferDidPause;

/// 传输取消
- (void)watchFaceTransferDidCancel;

@end
```

**实现示例：**

```objc
#pragma mark - WFTransferDelegate

- (void)watchFaceTransferDidStart {
    NSLog(@"开始传输");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.hidden = NO;
        self.progressView.progress = 0.0;
    });
}

- (void)watchFaceTransferDidUpdateProgress:(WFTransferProgress *)progress {
    NSLog(@"传输进度: %.1f%% (%ld/%ld)",
          progress.percentage * 100,
          progress.currentPacket,
          progress.totalPackets);

    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.progress = progress.percentage;
    });
}

- (void)watchFaceTransferDidComplete {
    NSLog(@"传输完成");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.hidden = YES;
        [self showSuccessAlert];
    });
}

- (void)watchFaceTransferDidFailWithError:(NSError *)error {
    NSLog(@"传输失败: %@", error.localizedDescription);
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.hidden = YES;
        [self showErrorAlert:error.localizedDescription];
    });
}
```

---

### WFTransferProgress - 进度模型

```objc
@interface WFTransferProgress : NSObject

/// 当前包序号
@property (nonatomic, assign) NSInteger currentPacket;

/// 总包数
@property (nonatomic, assign) NSInteger totalPackets;

/// 已传输字节数
@property (nonatomic, assign) NSInteger bytesTransferred;

/// 总字节数
@property (nonatomic, assign) NSInteger totalBytes;

/// 百分比 (0.0-1.0)
@property (nonatomic, assign, readonly) float percentage;

/// 进度消息
@property (nonatomic, copy) NSString *message;

@end
```

---

### 枚举类型

#### WFTimePosition - 时间位置

```objc
typedef NS_ENUM(NSInteger, WFTimePosition) {
    WFTimePositionNone = 0,         // 无
    WFTimePositionTopLeft = 1,      // 左上
    WFTimePositionBottomLeft = 2,   // 左下
    WFTimePositionTopRight = 3,     // 右上
    WFTimePositionBottomRight = 4,  // 右下
    WFTimePositionCenter = 5        // 居中
};
```

#### WFDialColor - 表盘颜色

```objc
typedef NS_ENUM(NSInteger, WFDialColor) {
    WFDialColorWhite = 0,   // 白色
    WFDialColorBlack = 1,   // 黑色
    WFDialColorYellow = 2,  // 黄色
    WFDialColorOrange = 3,  // 橙色
    WFDialColorPink = 4,    // 粉色
    WFDialColorPurple = 5,  // 紫色
    WFDialColorBlue = 6,    // 蓝色
    WFDialColorCyan = 7,    // 青色
    WFDialColorGreen = 8    // 绿色
};
```

#### WFScreenShape - 屏幕形状

```objc
typedef NS_ENUM(NSInteger, WFScreenShape) {
    WFScreenShapeRound = 0,   // 圆形
    WFScreenShapeSquare = 1   // 方形
};
```

#### WFErrorCode - 错误代码

```objc
typedef NS_ENUM(NSInteger, WFErrorCode) {
    WFErrorCodeDeviceNotConnected = 1000,       // 设备未连接
    WFErrorCodeDeviceNotSupported = 1001,       // 设备不支持
    WFErrorCodeInvalidParameters = 1002,        // 参数无效
    WFErrorCodeImageProcessingFailed = 1003,    // 图片处理失败
    WFErrorCodeTransferFailed = 1004,           // 传输失败
    WFErrorCodeTransferCancelled = 1005,        // 传输取消
    WFErrorCodeTransferTimeout = 1006,          // 传输超时
    WFErrorCodeFileNotFound = 1007,             // 文件不存在
    WFErrorCodeFileReadFailed = 1008,           // 文件读取失败
    WFErrorCodeInsufficientStorage = 1009,      // 设备存储不足
    WFErrorCodePARConversionFailed = 1010,      // PAR 转换失败
    WFErrorCodeFileTooLarge = 1011,             // 文件过大
    WFErrorCodeInvalidData = 1012,              // 数据无效
    WFErrorCodeInvalidImage = 1013              // 图片无效
};
```

---

## 代码示例

### 示例 1：完整的自定义表盘上传流程

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>

@interface WatchFaceViewController () <WFTransferDelegate>

@property (weak, nonatomic) IBOutlet UIImageView *previewImageView;
@property (weak, nonatomic) IBOutlet UIProgressView *progressView;
@property (weak, nonatomic) IBOutlet UIButton *uploadButton;
@property (weak, nonatomic) IBOutlet UISegmentedControl *positionControl;
@property (weak, nonatomic) IBOutlet UISegmentedControl *colorControl;

@end

@implementation WatchFaceViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self checkDeviceConnection];
}

- (void)checkDeviceConnection {
    WFManager *manager = [WFManager sharedInstance];

    if ([manager isDeviceConnected]) {
        WFDeviceScreenInfo *info = [manager getCurrentDeviceScreenInfo];
        self.title = [NSString stringWithFormat:@"表盘制作 (%ldx%ld)",
                      info.width, info.height];
        self.uploadButton.enabled = YES;
    } else {
        self.title = @"表盘制作 (设备未连接)";
        self.uploadButton.enabled = NO;

        UIAlertController *alert = [UIAlertController
            alertControllerWithTitle:@"提示"
                             message:@"请先连接智能手表设备"
                      preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"确定"
                                                 style:UIAlertActionStyleDefault
                                               handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

- (IBAction)uploadCustomWatchFace:(id)sender {
    UIImage *image = self.previewImageView.image;

    if (!image) {
        [self showAlert:@"请先选择背景图片"];
        return;
    }

    // 验证图片
    WFManager *manager = [WFManager sharedInstance];
    NSString *validationMessage = nil;

    if (![manager validateImage:image message:&validationMessage]) {
        [self showAlert:validationMessage];
        return;
    }

    // 获取用户选择的时间位置和颜色
    WFTimePosition position = (WFTimePosition)(self.positionControl.selectedSegmentIndex + 1);
    WFDialColor color = (WFDialColor)self.colorControl.selectedSegmentIndex;

    // 开始上传
    NSError *error = nil;
    BOOL success = [manager uploadCustomWatchFaceWithImage:image
                                              timePosition:position
                                                     color:color
                                                  delegate:self
                                                     error:&error];

    if (!success) {
        [self showAlert:error.localizedDescription];
    } else {
        self.uploadButton.enabled = NO;
        self.progressView.hidden = NO;
    }
}

#pragma mark - WFTransferDelegate

- (void)watchFaceTransferDidStart {
    NSLog(@"✅ 开始上传表盘");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.progress = 0.0;
    });
}

- (void)watchFaceTransferDidUpdateProgress:(WFTransferProgress *)progress {
    NSLog(@"📊 进度: %.1f%% (%ld/%ld包)",
          progress.percentage * 100,
          progress.currentPacket,
          progress.totalPackets);

    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.progress = progress.percentage;
    });
}

- (void)watchFaceTransferDidComplete {
    NSLog(@"🎉 上传完成");
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.hidden = YES;
        self.uploadButton.enabled = YES;
        [self showAlert:@"表盘上传成功！"];
    });
}

- (void)watchFaceTransferDidFailWithError:(NSError *)error {
    NSLog(@"❌ 上传失败: %@", error.localizedDescription);
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.hidden = YES;
        self.uploadButton.enabled = YES;
        [self showAlert:[NSString stringWithFormat:@"上传失败: %@",
                        error.localizedDescription]];
    });
}

- (void)showAlert:(NSString *)message {
    UIAlertController *alert = [UIAlertController
        alertControllerWithTitle:@"提示"
                         message:message
                  preferredStyle:UIAlertControllerStyleAlert];
    [alert addAction:[UIAlertAction actionWithTitle:@"确定"
                                             style:UIAlertActionStyleDefault
                                           handler:nil]];
    [self presentViewController:alert animated:YES completion:nil];
}

@end
```

### 示例 2：上传市场表盘

```objc
- (IBAction)uploadMarketWatchFace:(id)sender {
    // 从 Bundle 中读取表盘文件
    NSURL *fileURL = [[NSBundle mainBundle] URLForResource:@"market_watchface"
                                              withExtension:@"bin"];

    if (!fileURL) {
        NSLog(@"❌ 找不到表盘文件");
        return;
    }

    WFManager *manager = [WFManager sharedInstance];

    // 检查设备连接
    if (![manager isDeviceConnected]) {
        [self showAlert:@"设备未连接，请先连接设备"];
        return;
    }

    // 开始上传
    NSError *error = nil;
    BOOL success = [manager uploadMarketWatchFaceWithFileURL:fileURL
                                                    delegate:self
                                                       error:&error];

    if (!success) {
        NSLog(@"❌ 上传失败: %@", error.localizedDescription);
        [self showAlert:error.localizedDescription];
    } else {
        NSLog(@"✅ 开始上传市场表盘");
        self.progressView.hidden = NO;
    }
}
```

### 示例 3：Swift 中使用

```swift
import UIKit

class WatchFaceViewController: UIViewController, WFTransferDelegate {

    @IBOutlet weak var progressView: UIProgressView!
    @IBOutlet weak var uploadButton: UIButton!

    override func viewDidLoad() {
        super.viewDidLoad()
        checkDeviceConnection()
    }

    func checkDeviceConnection() {
        let manager = WFManager.sharedInstance()

        if manager.isDeviceConnected() {
            if let screenInfo = manager.getCurrentDeviceScreenInfo() {
                print("✅ 设备已连接")
                print("📱 屏幕尺寸: \(screenInfo.width)x\(screenInfo.height)")
                print("🔵 屏幕形状: \(screenInfo.shape == .round ? "圆形" : "方形")")
                uploadButton.isEnabled = true
            }
        } else {
            print("❌ 设备未连接")
            uploadButton.isEnabled = false
            showAlert(message: "请先连接智能手表设备")
        }
    }

    @IBAction func uploadCustomWatchFace() {
        guard let image = UIImage(named: "background") else {
            showAlert(message: "找不到背景图片")
            return
        }

        let manager = WFManager.sharedInstance()

        // 验证图片
        var validationMessage: NSString?
        if !manager.validateImage(image, message: &validationMessage) {
            showAlert(message: validationMessage as String? ?? "图片验证失败")
            return
        }

        // 上传自定义表盘
        var error: NSError?
        let success = manager.uploadCustomWatchFace(
            with: image,
            timePosition: .topLeft,
            color: .white,
            delegate: self,
            error: &error
        )

        if !success {
            showAlert(message: error?.localizedDescription ?? "上传失败")
        } else {
            uploadButton.isEnabled = false
            progressView.isHidden = false
        }
    }

    // MARK: - WFTransferDelegate

    func watchFaceTransferDidStart() {
        print("✅ 开始上传")
        DispatchQueue.main.async {
            self.progressView.progress = 0.0
        }
    }

    func watchFaceTransferDidUpdateProgress(_ progress: WFTransferProgress) {
        print("📊 进度: \(progress.percentage * 100)%")
        DispatchQueue.main.async {
            self.progressView.progress = progress.percentage
        }
    }

    func watchFaceTransferDidComplete() {
        print("🎉 上传完成")
        DispatchQueue.main.async {
            self.progressView.isHidden = true
            self.uploadButton.isEnabled = true
            self.showAlert(message: "表盘上传成功！")
        }
    }

    func watchFaceTransferDidFail(withError error: Error) {
        print("❌ 上传失败: \(error.localizedDescription)")
        DispatchQueue.main.async {
            self.progressView.isHidden = true
            self.uploadButton.isEnabled = true
            self.showAlert(message: "上传失败: \(error.localizedDescription)")
        }
    }

    func showAlert(message: String) {
        let alert = UIAlertController(
            title: "提示",
            message: message,
            preferredStyle: .alert
        )
        alert.addAction(UIAlertAction(title: "确定", style: .default))
        present(alert, animated: true)
    }
}
```

---

## 动态库依赖说明

### 🔗 依赖关系图

```
YourApp.app
├── YourApp (可执行文件)
└── Frameworks/
    ├── WatchFaceSDK_ObjC.framework        (主 SDK)
    │   └── 依赖 → WatchProtocolSDK.framework
    │   └── 依赖 → ABParTool.framework
    ├── WatchProtocolSDK.framework         (必须嵌入)
    └── ABParTool.framework                (必须嵌入)
```

### ⚠️ 动态库加载机制

WatchFaceSDK_ObjC 在运行时会尝试加载 WatchProtocolSDK 和 ABParTool：

```objc
// 动态库链接符号
@rpath/WatchProtocolSDK.framework/WatchProtocolSDK
@rpath/ABParTool.framework/ABParTool
```

**@rpath 的解析路径：**
1. `@executable_path/Frameworks` (App 的 Frameworks 目录)
2. `@loader_path/Frameworks` (Framework 自己的 Frameworks 目录)

### ✅ 正确的嵌入方式

**在 Xcode 中：**

Target → General → Frameworks, Libraries, and Embedded Content

```
WatchFaceSDK_ObjC.xcframework      → Embed & Sign ✅
WatchProtocolSDK.xcframework       → Embed & Sign ✅
ABParTool.xcframework              → Embed & Sign ✅
```

### ❌ 错误的配置会导致：

**错误 1：未嵌入依赖库**
```
dyld: Library not loaded: @rpath/WatchProtocolSDK.framework/WatchProtocolSDK
  Referenced from: /var/containers/Bundle/Application/.../YourApp.app/Frameworks/WatchFaceSDK_ObjC.framework/WatchFaceSDK_ObjC
  Reason: image not found
```

**解决方案：** 将 WatchProtocolSDK.xcframework 设置为 **Embed & Sign**

**错误 2：使用了静态库版本**
```
Undefined symbols for architecture arm64:
  "_OBJC_CLASS_$_WPDeviceManager", referenced from:
      objc-class-ref in WatchFaceSDK_ObjC
```

**解决方案：** 确保使用 **Output-ObjC-Dynamic** 中的 WatchProtocolSDK.xcframework

### 📦 验证嵌入是否正确

编译后，在产品目录中检查：

```bash
# 在 Xcode 中: Product → Show Build Folder in Finder
cd YourApp.app/Frameworks

# 应该看到：
ls -la
WatchFaceSDK_ObjC.framework/
WatchProtocolSDK.framework/
ABParTool.framework/
```

使用 otool 验证链接关系：

```bash
otool -L WatchFaceSDK_ObjC.framework/WatchFaceSDK_ObjC

# 应该显示：
@rpath/WatchProtocolSDK.framework/WatchProtocolSDK
@rpath/ABParTool.framework/ABParTool
```

---

## 常见问题

### Q1: 为什么必须使用 Output-ObjC-Dynamic 中的 WatchProtocolSDK？

**A:** WatchFaceSDK_ObjC v1.0.1 采用纯动态库架构，需要动态链接到 WatchProtocolSDK。Output-ObjC 中的是静态库版本，会导致链接错误。

```
✅ 使用: Output-ObjC-Dynamic/WatchProtocolSDK.xcframework (动态库)
❌ 不要使用: Output-ObjC/WatchProtocolSDK.xcframework (静态库)
```

### Q2: 运行时崩溃提示 "image not found"？

**A:** 这是因为依赖的动态库没有正确嵌入。

**检查清单：**
- [ ] WatchProtocolSDK.xcframework 是否设置为 **Embed & Sign**
- [ ] ABParTool.xcframework 是否设置为 **Embed & Sign**
- [ ] 是否使用了正确的动态库版本
- [ ] Build Settings 中的 Framework Search Paths 是否正确

### Q3: 支持哪些图片格式？

**A:** SDK 支持所有 UIImage 支持的格式：

- ✅ PNG（推荐，无损）
- ✅ JPEG/JPG
- ✅ HEIC
- ✅ BMP
- ✅ GIF（静态）

**推荐使用 PNG 格式以获得最佳质量。**

### Q4: 自定义表盘图片有什么要求？

**A:** 图片要求：

| 项目 | 要求 |
|-----|------|
| **推荐尺寸** | 与设备屏幕尺寸一致（通过 `getRecommendedImageSize` 获取） |
| **最小尺寸** | 不小于 240x240 |
| **最大尺寸** | 不限制（SDK 会自动缩放） |
| **长宽比** | 建议 1:1 |
| **文件大小** | SDK 会自动压缩到设备支持的大小 |

### Q5: 传输速度慢怎么办？

**A:** 传输速度受以下因素影响：

- 蓝牙信号强度（建议设备距离 < 1米）
- 设备 MTU 大小（SDK 自动适配）
- 图片文件大小（SDK 会自动压缩）

**优化建议：**
- ✅ 确保设备距离近
- ✅ 避免其他蓝牙设备干扰
- ✅ 使用较小的图片
- ✅ 关闭其他蓝牙应用

### Q6: Swift 项目如何集成？

**A:** Swift 项目集成步骤：

1. 添加 Framework 到项目
2. 创建 Bridging Header
   - File → New → Header File
   - 命名为 `YourApp-Bridging-Header.h`
3. 在 Bridging Header 中导入：
   ```objc
   #import <WatchFaceSDK_ObjC/WFManager.h>
   ```
4. 在 Build Settings → Objective-C Bridging Header 中设置 Header 文件路径

### Q7: 如何取消正在进行的传输？

**A:** 调用取消方法：

```objc
[[WFManager sharedInstance] cancelTransfer];
```

会触发 `watchFaceTransferDidCancel` 回调。

### Q8: 是否支持后台传输？

**A:** SDK 依赖蓝牙连接，需要：

1. 在 Info.plist 添加蓝牙后台模式：
   ```xml
   <key>UIBackgroundModes</key>
   <array>
       <string>bluetooth-central</string>
   </array>
   ```

2. ⚠️ **注意：** iOS 后台蓝牙有限制，长时间传输可能被系统暂停

### Q9: 上传的表盘在手表上显示异常？

**A:** 检查：

- 时间位置选择是否正确
- 颜色选择是否与背景对比度足够
- 图片是否过暗或过亮
- 设备屏幕形状是否匹配（圆形/方形）

### Q10: 如何获取设备屏幕信息？

**A:** 使用 `getCurrentDeviceScreenInfo` 方法：

```objc
WFDeviceScreenInfo *info = [[WFManager sharedInstance] getCurrentDeviceScreenInfo];

if (info) {
    NSLog(@"宽度: %ld", info.width);
    NSLog(@"高度: %ld", info.height);
    NSLog(@"形状: %@", info.shape == WFScreenShapeRound ? @"圆形" : @"方形");
    NSLog(@"MTU: %ld", info.mtu);
}
```

---

## 故障排查

### 问题 1: 编译错误 "Framework not found"

**症状：**
```
error: Framework not found WatchFaceSDK_ObjC
```

**解决方案：**

1. 检查 Framework 是否已添加到项目
2. 检查 Build Settings → Framework Search Paths
3. 确保 Framework 路径正确

```
Framework Search Paths: $(PROJECT_DIR)/Frameworks
```

### 问题 2: 运行时崩溃 "dyld: Library not loaded"

**症状：**
```
dyld: Library not loaded: @rpath/WatchProtocolSDK.framework/WatchProtocolSDK
Reason: image not found
```

**解决方案：**

检查 Target → General → Frameworks, Libraries, and Embedded Content：

```
✅ WatchProtocolSDK.xcframework → Embed & Sign
```

### 问题 3: 链接错误 "Undefined symbols"

**症状：**
```
Undefined symbols for architecture arm64:
  "_OBJC_CLASS_$_WPDeviceManager"
```

**解决方案：**

确保使用的是 **Output-ObjC-Dynamic** 中的动态库版本，而不是静态库版本。

### 问题 4: Swift 中找不到头文件

**症状：**
```
'WatchFaceSDK_ObjC/WFManager.h' file not found
```

**解决方案：**

1. 确保在 Bridging Header 中导入
2. 检查 Build Settings → Objective-C Bridging Header 路径
3. 确保 Framework 已添加到项目

### 问题 5: 设备始终显示未连接

**症状：**
```objc
[manager isDeviceConnected] 返回 NO
```

**解决方案：**

1. 确保先使用 WatchProtocolSDK 连接设备
2. 检查蓝牙权限是否已授予
3. 检查设备是否已配对

```objc
// 使用 WatchProtocolSDK 连接设备
WPBluetoothManager *btManager = [WPBluetoothManager sharedInstance];
[btManager startScanning:YES];
// ... 连接设备
```

### 问题 6: 图片上传失败

**常见错误码及解决方案：**

| 错误码 | 说明 | 解决方案 |
|-------|------|---------|
| 1000 | 设备未连接 | 先连接设备 |
| 1003 | 图片处理失败 | 检查图片格式和大小 |
| 1006 | 传输超时 | 重试或检查蓝牙连接 |
| 1009 | 设备存储不足 | 清理设备存储空间 |
| 1013 | 图片无效 | 使用有效的图片文件 |

---

## 📞 技术支持

如有问题，请联系：

- **Email**: 315082431@qq.com
- **GitHub Issues**: [提交问题](https://github.com/BruceZhang2017/SmartBracelet/issues)

---

## 📄 许可证

Copyright © 2026 bruce  . All rights reserved.

---

## 📝 版本历史

### v1.0.1 (2026-01-14)

- ✅ 更新为纯动态库架构
- ✅ 使用最新 WatchProtocolSDK 动态库
- ✅ 支持最新的扫描超时功能（通过 WatchProtocolSDK）
- ✅ 保持 API 完全兼容
- ✅ 优化动态库链接和加载机制

### v1.0.0 (2026-01-13)

- ✅ 首次发布
- ✅ 纯 Objective-C 实现
- ✅ 市场表盘上传功能
- ✅ 自定义表盘制作功能
- ✅ 智能图片处理（RGB565、PAR 转换）
- ✅ 实时传输进度监控
- ✅ 传输控制（暂停、取消、重试）

---

**祝您使用愉快！** 🎉
