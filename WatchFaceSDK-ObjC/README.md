# WatchFaceSDK-ObjC 集成指南

**版本**: 1.0.0
**发布日期**: 2026-01-28
**类型**: 纯 Objective-C 动态库

---

## 📱 简介

WatchFaceSDK-ObjC 是一个纯 Objective-C 实现的智能手表表盘管理 SDK，提供完整的表盘上传、管理和自定义功能。

### 核心功能

- ✅ **市场表盘上传** - 支持上传预制表盘文件
- ✅ **自定义表盘** - 从照片创建个性化表盘
- ✅ **设备信息查询** - 自动适配不同屏幕尺寸
- ✅ **传输进度监控** - 实时追踪上传进度
- ✅ **智能图片处理** - 自动裁剪、压缩、格式转换
- ✅ **蓝牙优化** - 自动 MTU 协商，分包传输

---

## 🔧 系统要求

| 项目 | 要求 |
|------|------|
| **iOS** | 13.0+ |
| **Xcode** | 12.0+ |
| **语言** | Objective-C / Swift |
| **依赖框架** | WatchProtocolSDK (动态库), ABParTool |

---

## 📦 集成步骤

### 步骤 1: 添加框架到项目

将以下框架拖入 Xcode 项目：

```
✅ WatchFaceSDK_ObjC.xcframework
✅ WatchProtocolSDK.xcframework (来自 Output-ObjC-Dynamic 目录)
✅ ABParTool.xcframework (可选，用于图片转换)
```

### 步骤 2: 配置框架嵌入设置 ⭐ 重要

1. 选择项目 Target
2. 进入 **General** 标签页
3. 找到 **Frameworks, Libraries, and Embedded Content** 部分
4. 确保设置如下：

| 框架 | Embed 设置 |
|------|-----------|
| WatchFaceSDK_ObjC.xcframework | **Embed & Sign** ⭐ |
| WatchProtocolSDK.xcframework | **Embed & Sign** ⭐ |
| ABParTool.xcframework | **Embed & Sign** ⭐ |

**⚠️ 关键说明**：
- 这些都是**动态库**，必须设置为 "Embed & Sign"
- 如果设置为 "Do Not Embed"，运行时会报错：`dyld: Library not loaded`

### 步骤 3: 导入头文件

#### Objective-C 项目

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
#import <WatchFaceSDK_ObjC/WFTransferDelegate.h>
#import <WatchFaceSDK_ObjC/WFEnums.h>
```

#### Swift 项目

创建 Bridging Header：

```objc
// YourProject-Bridging-Header.h
#import <WatchFaceSDK_ObjC/WFManager.h>
#import <WatchFaceSDK_ObjC/WFTransferDelegate.h>
#import <WatchFaceSDK_ObjC/WFEnums.h>
```

然后在 Swift 中直接使用：

```swift
let manager = WFManager.sharedInstance()
```

---

## 🚀 快速开始

### 1. 检查设备连接

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>

WFManager *manager = [WFManager sharedInstance];

// 检查设备是否连接
if ([manager isDeviceConnected]) {
    NSLog(@"✅ 设备已连接");

    // 获取设备屏幕信息
    WFDeviceScreenInfo *screenInfo = [manager getCurrentDeviceScreenInfo];
    NSLog(@"📱 屏幕尺寸: %ldx%ld",
          (long)screenInfo.width,
          (long)screenInfo.height);
    NSLog(@"📡 MTU: %ld", (long)screenInfo.mtu);
} else {
    NSLog(@"❌ 设备未连接");
}
```

### 2. 上传市场表盘

```objc
// 从文件上传
NSURL *fileURL = [[NSBundle mainBundle] URLForResource:@"watchface"
                                          withExtension:@"bin"];
NSError *error = nil;

BOOL success = [manager uploadMarketWatchFaceWithFileURL:fileURL
                                                delegate:self
                                                   error:&error];

if (!success) {
    NSLog(@"❌ 上传失败: %@", error.localizedDescription);
}
```

### 3. 上传自定义表盘

```objc
#import <WatchFaceSDK_ObjC/WFEnums.h>

UIImage *image = [UIImage imageNamed:@"my_photo.jpg"];

BOOL success = [manager uploadCustomWatchFaceWithImage:image
                                          timePosition:WFTimePositionTopCenter
                                                 color:WFDialColorWhite
                                              delegate:self
                                                 error:&error];
```

### 4. 监听传输进度

实现 `WFTransferDelegate` 协议：

```objc
@interface MyViewController () <WFTransferDelegate>
@end

@implementation MyViewController

#pragma mark - WFTransferDelegate

- (void)transferDidStart {
    NSLog(@"✅ 传输开始");
    // 更新 UI：显示进度条
}

- (void)transferDidUpdateProgress:(WFTransferProgress *)progress {
    CGFloat percent = progress.percentComplete;
    NSLog(@"📤 传输进度: %.1f%% (%ld/%ld)",
          percent,
          (long)progress.currentPacket,
          (long)progress.totalPackets);

    // 更新 UI：更新进度条
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.progress = percent / 100.0;
    });
}

- (void)transferDidComplete {
    NSLog(@"✅ 传输完成");
    // 更新 UI：显示成功提示
}

- (void)transferDidFailWithError:(NSError *)error {
    NSLog(@"❌ 传输失败: %@", error.localizedDescription);
    // 更新 UI：显示错误提示
}

- (void)transferDidCancel {
    NSLog(@"⚠️ 传输取消");
    // 更新 UI：恢复初始状态
}

@end
```

---

## 📖 API 参考

### WFManager - 主管理器

#### 单例

```objc
+ (instancetype)sharedInstance;
```

#### 设备信息

```objc
// 检查设备是否连接
- (BOOL)isDeviceConnected;

// 获取设备屏幕信息
- (nullable WFDeviceScreenInfo *)getCurrentDeviceScreenInfo;

// 获取推荐的图片尺寸
- (CGSize)getRecommendedImageSize;
```

#### 市场表盘上传

```objc
// 从 NSData 上传
- (BOOL)uploadMarketWatchFaceWithData:(NSData *)data
                             delegate:(nullable id<WFTransferDelegate>)delegate
                                error:(NSError **)error;

// 从文件 URL 上传
- (BOOL)uploadMarketWatchFaceWithFileURL:(NSURL *)fileURL
                                delegate:(nullable id<WFTransferDelegate>)delegate
                                   error:(NSError **)error;
```

#### 自定义表盘上传

```objc
- (BOOL)uploadCustomWatchFaceWithImage:(UIImage *)image
                          timePosition:(WFTimePosition)timePosition
                                 color:(WFDialColor)color
                              delegate:(nullable id<WFTransferDelegate>)delegate
                                 error:(NSError **)error;
```

**参数说明**:

- `timePosition`: 时间显示位置
  ```objc
  typedef NS_ENUM(NSInteger, WFTimePosition) {
      WFTimePositionNone = 0,
      WFTimePositionTopLeft,
      WFTimePositionTopCenter,
      WFTimePositionTopRight,
      WFTimePositionMiddleLeft,
      WFTimePositionCenter,
      WFTimePositionMiddleRight,
      WFTimePositionBottomLeft,
      WFTimePositionBottomCenter,
      WFTimePositionBottomRight
  };
  ```

- `color`: 时间文字颜色
  ```objc
  typedef NS_ENUM(NSInteger, WFDialColor) {
      WFDialColorWhite = 0,
      WFDialColorBlack,
      WFDialColorRed,
      WFDialColorGreen,
      WFDialColorBlue,
      WFDialColorYellow
  };
  ```

#### 图片验证

```objc
- (BOOL)validateImage:(UIImage *)image message:(NSString **)message;
```

#### 传输控制

```objc
- (void)pauseTransfer;   // 暂停传输
- (void)cancelTransfer;  // 取消传输
- (void)retryTransfer;   // 重试传输
```

---

### WFTransferDelegate - 传输代理

```objc
@protocol WFTransferDelegate <NSObject>

@optional
- (void)transferDidStart;
- (void)transferDidUpdateProgress:(WFTransferProgress *)progress;
- (void)transferDidComplete;
- (void)transferDidFailWithError:(NSError *)error;
- (void)transferDidCancel;

@end
```

---

### WFTransferProgress - 传输进度

```objc
@interface WFTransferProgress : NSObject

@property (nonatomic, assign) NSInteger currentPacket;     // 当前包序号
@property (nonatomic, assign) NSInteger totalPackets;      // 总包数
@property (nonatomic, assign) NSInteger bytesTransferred;  // 已传输字节
@property (nonatomic, assign) NSInteger totalBytes;        // 总字节数
@property (nonatomic, assign, readonly) CGFloat percentComplete;  // 百分比 (0-100)

@end
```

---

### WFDeviceScreenInfo - 设备屏幕信息

```objc
@interface WFDeviceScreenInfo : NSObject

@property (nonatomic, assign) NSInteger width;   // 屏幕宽度
@property (nonatomic, assign) NSInteger height;  // 屏幕高度
@property (nonatomic, assign) WFScreenShape shape;  // 屏幕形状
@property (nonatomic, assign) NSInteger mtu;     // 蓝牙 MTU

- (CGSize)cgSize;  // 转换为 CGSize

@end
```

**屏幕形状枚举**:
```objc
typedef NS_ENUM(NSInteger, WFScreenShape) {
    WFScreenShapeSquare = 1,  // 方形
    WFScreenShapeRound = 2    // 圆形
};
```

---

## 💡 完整使用示例

### 示例 1: 完整的自定义表盘上传流程

```objc
@interface WatchFaceViewController () <WFTransferDelegate>

@property (nonatomic, strong) WFManager *manager;
@property (nonatomic, weak) IBOutlet UIProgressView *progressView;
@property (nonatomic, weak) IBOutlet UILabel *statusLabel;
@property (nonatomic, weak) IBOutlet UIButton *uploadButton;

@end

@implementation WatchFaceViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.manager = [WFManager sharedInstance];
}

- (IBAction)uploadCustomWatchFace:(id)sender {
    // 1. 检查设备连接
    if (![self.manager isDeviceConnected]) {
        [self showAlert:@"请先连接设备"];
        return;
    }

    // 2. 选择图片
    UIImagePickerController *picker = [[UIImagePickerController alloc] init];
    picker.delegate = self;
    picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    [self presentViewController:picker animated:YES completion:nil];
}

#pragma mark - UIImagePickerControllerDelegate

- (void)imagePickerController:(UIImagePickerController *)picker
        didFinishPickingMediaWithInfo:(NSDictionary<UIImagePickerControllerInfoKey,id> *)info {

    [picker dismissViewControllerAnimated:YES completion:nil];

    UIImage *image = info[UIImagePickerControllerOriginalImage];

    // 3. 验证图片
    NSString *validationMessage = nil;
    if (![self.manager validateImage:image message:&validationMessage]) {
        [self showAlert:validationMessage];
        return;
    }

    // 4. 开始上传
    self.uploadButton.enabled = NO;
    self.statusLabel.text = @"准备上传...";

    NSError *error = nil;
    BOOL success = [self.manager uploadCustomWatchFaceWithImage:image
                                                   timePosition:WFTimePositionTopCenter
                                                          color:WFDialColorWhite
                                                       delegate:self
                                                          error:&error];

    if (!success) {
        self.uploadButton.enabled = YES;
        [self showAlert:[NSString stringWithFormat:@"上传失败: %@",
                        error.localizedDescription]];
    }
}

#pragma mark - WFTransferDelegate

- (void)transferDidStart {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = @"正在上传...";
        self.progressView.progress = 0.0;
    });
}

- (void)transferDidUpdateProgress:(WFTransferProgress *)progress {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.progressView.progress = progress.percentComplete / 100.0;
        self.statusLabel.text = [NSString stringWithFormat:@"上传中... %.1f%%",
                                progress.percentComplete];
    });
}

- (void)transferDidComplete {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = @"上传成功！";
        self.uploadButton.enabled = YES;
        [self showAlert:@"表盘上传成功！"];
    });
}

- (void)transferDidFailWithError:(NSError *)error {
    dispatch_async(dispatch_get_main_queue(), ^{
        self.statusLabel.text = @"上传失败";
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

### 示例 2: Swift 使用

```swift
import UIKit

class WatchFaceViewController: UIViewController {

    let manager = WFManager.sharedInstance()

    @IBOutlet weak var progressView: UIProgressView!
    @IBOutlet weak var statusLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
    }

    @IBAction func uploadWatchFace(_ sender: Any) {
        guard manager.isDeviceConnected() else {
            showAlert("请先连接设备")
            return
        }

        let picker = UIImagePickerController()
        picker.delegate = self
        picker.sourceType = .photoLibrary
        present(picker, animated: true)
    }
}

extension WatchFaceViewController: UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    func imagePickerController(_ picker: UIImagePickerController,
                              didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        picker.dismiss(animated: true)

        guard let image = info[.originalImage] as? UIImage else { return }

        var validationMessage: NSString?
        guard manager.validate(image, message: &validationMessage) else {
            showAlert(validationMessage as String? ?? "图片无效")
            return
        }

        statusLabel.text = "准备上传..."

        do {
            try ObjCExceptionCatcher.catchException {
                self.manager.uploadCustomWatchFace(
                    with: image,
                    timePosition: .topCenter,
                    color: .white,
                    delegate: self
                )
            }
        } catch {
            showAlert("上传失败: \(error.localizedDescription)")
        }
    }
}

extension WatchFaceViewController: WFTransferDelegate {

    func transferDidStart() {
        DispatchQueue.main.async {
            self.statusLabel.text = "正在上传..."
            self.progressView.progress = 0
        }
    }

    func transferDidUpdate(_ progress: WFTransferProgress) {
        DispatchQueue.main.async {
            self.progressView.progress = Float(progress.percentComplete / 100.0)
            self.statusLabel.text = String(format: "上传中... %.1f%%", progress.percentComplete)
        }
    }

    func transferDidComplete() {
        DispatchQueue.main.async {
            self.statusLabel.text = "上传成功！"
            self.showAlert("表盘上传成功！")
        }
    }

    func transferDidFail(withError error: Error) {
        DispatchQueue.main.async {
            self.statusLabel.text = "上传失败"
            self.showAlert("上传失败: \(error.localizedDescription)")
        }
    }

    func showAlert(_ message: String) {
        let alert = UIAlertController(title: "提示", message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "确定", style: .default))
        present(alert, animated: true)
    }
}
```

---

## ❓ 常见问题

### Q1: dyld: Library not loaded 错误？

**原因**: 动态库未正确嵌入。

**解决方案**:
1. 选择 Target → **General** → **Frameworks, Libraries, and Embedded Content**
2. 确认所有框架的 Embed 设置为 **"Embed & Sign"**
3. Clean Build Folder (⇧⌘K)
4. 重新编译

---

### Q2: 链接错误：Undefined symbols for architecture arm64？

**原因**: 框架未正确添加或路径错误。

**解决方案**:
1. 检查框架是否在 **Frameworks, Libraries, and Embedded Content** 列表中
2. 清理 DerivedData：`rm -rf ~/Library/Developer/Xcode/DerivedData/*`
3. 重新编译

---

### Q3: 上传失败，提示设备未连接？

**原因**: 设备未通过 WatchProtocolSDK 连接。

**解决方案**:
```objc
// 1. 确保已初始化 WatchProtocolSDK
#import <WatchProtocolSDK/WPBluetoothManager.h>

WPBluetoothManager *btManager = [WPBluetoothManager sharedInstance];
[btManager initCentral];

// 2. 扫描并连接设备
[btManager startScanning:YES];

// 3. 在连接成功回调中使用 WatchFaceSDK
```

---

### Q4: 图片验证失败？

**常见原因**:
- 图片尺寸过小（建议 >= 240x240）
- 图片格式不支持（仅支持 PNG、JPG）
- 图片损坏或无法读取

**解决方案**:
```objc
NSString *message = nil;
if (![manager validateImage:image message:&message]) {
    NSLog(@"验证失败: %@", message);
    // 根据错误提示修正图片
}
```

---

### Q5: Swift 项目如何使用？

需要创建 Bridging Header：

1. **File** → **New** → **File** → **Header File**
2. 命名为 `YourProject-Bridging-Header.h`
3. 在 **Build Settings** → **Objective-C Bridging Header** 中设置路径
4. 在 Bridging Header 中导入：
   ```objc
   #import <WatchFaceSDK_ObjC/WFManager.h>
   #import <WatchFaceSDK_ObjC/WFTransferDelegate.h>
   ```

---

## 🔗 依赖关系

```
WatchFaceSDK_ObjC.xcframework
    ↓ 依赖
WatchProtocolSDK.xcframework (动态库)
    ↓ 依赖
    • CoreBluetooth.framework (系统)
    • Foundation.framework (系统)
    ↓ 可选
ABParTool.xcframework
    ↓ 用于
    • PAR 格式图片转换
```

---

## 📝 错误码参考

```objc
typedef NS_ENUM(NSInteger, WFErrorCode) {
    WFErrorCodeDeviceNotConnected = 1001,  // 设备未连接
    WFErrorCodeInvalidData = 1002,         // 数据无效
    WFErrorCodeInvalidImage = 1003,        // 图片无效
    WFErrorCodeImageProcessFailed = 1004,  // 图片处理失败
    WFErrorCodeTransferFailed = 1005       // 传输失败
};
```

---

## 🛠 调试技巧

### 启用详细日志

SDK 会自动输出调试日志，使用 Xcode Console 查看：

```
📱 设备屏幕信息: 240x240, 形状: 2, MTU: 240
🔗 设备连接状态: 已连接
🖼 处理自定义表盘 - 目标尺寸: 240x240
📤 开始上传自定义表盘 - PAR 大小: 98765 bytes
📡 设备 MTU: 240, 包大小: 220
📦 总包数: 449, 文件大小: 98765 bytes
📤 发送包 1/449 (大小: 220 bytes, 进度: 0%)
...
✅ 传输完成
```

### 检查框架版本

```objc
NSBundle *bundle = [NSBundle bundleForClass:[WFManager class]];
NSString *version = bundle.infoDictionary[@"CFBundleShortVersionString"];
NSLog(@"WatchFaceSDK 版本: %@", version);
```

---

## 📞 技术支持

如有问题，请提供：

1. **Xcode 版本**
2. **iOS 版本**
3. **设备型号**
4. **完整错误日志**
5. **Framework Search Paths 配置**
6. **Embed 设置截图**

联系方式：315082431@qq.com

---

## 📄 许可证

Copyright © 2026 Huaxin. All rights reserved.

---

## 🎉 总结

WatchFaceSDK-ObjC 提供了简单易用的 API，让表盘上传功能集成变得轻而易举：

✅ **3 步集成** - 添加框架 → 设置 Embed & Sign → 导入头文件
✅ **5 行代码** - 即可实现表盘上传
✅ **纯 Objective-C** - 无 Swift 运行时依赖
✅ **完整文档** - 详细的 API 参考和示例代码

开始使用 WatchFaceSDK-ObjC，为您的用户带来个性化的表盘体验！🚀
