# WatchFaceSDK-ObjC 快速开始指南

**5 分钟快速集成** ⚡

---

## 📦 本目录包含的内容

```
Output-ObjC-Dynamic/
├── WatchProtocolSDK.xcframework       ← 蓝牙通信协议 SDK（动态库）
├── WatchFaceSDK_ObjC.xcframework      ← 表盘管理 SDK（动态库）
├── WATCHFACE_SDK_INTEGRATION_GUIDE.md ← 详细集成文档
├── QUICK_START.md                     ← 本文件（快速开始）
└── README.md                          ← WatchProtocolSDK 文档
```

⚠️ **注意**: 还需要 `ABParTool.xcframework`（位于项目根目录）

---

## 🚀 5 步快速集成

### 步骤 1️⃣ 添加 Framework（1 分钟）

将以下 **3 个** XCFramework 拖入 Xcode 项目：

```
✅ WatchProtocolSDK.xcframework    (来自本目录)
✅ WatchFaceSDK_ObjC.xcframework   (来自本目录)
✅ ABParTool.xcframework           (来自项目根目录)
```

### 步骤 2️⃣ 配置嵌入方式（1 分钟）

**极其重要！** 否则运行时会崩溃。

打开 Xcode: **Target** → **General** → **Frameworks, Libraries, and Embedded Content**

将所有 Framework 设置为 **Embed & Sign**：

```
WatchProtocolSDK.xcframework    → Embed & Sign ✅
WatchFaceSDK_ObjC.xcframework   → Embed & Sign ✅
ABParTool.xcframework           → Embed & Sign ✅
```

### 步骤 3️⃣ 添加蓝牙权限（30 秒）

在 `Info.plist` 中添加：

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>
```

### 步骤 4️⃣ 导入头文件（10 秒）

**Objective-C:**
```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
```

**Swift:**
在 Bridging Header 中添加：
```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
```

### 步骤 5️⃣ 开始使用（2 分钟）

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>

@interface YourViewController () <WFTransferDelegate>
@end

@implementation YourViewController

- (void)uploadCustomWatchFace {
    // 1. 获取管理器单例
    WFManager *manager = [WFManager sharedInstance];

    // 2. 检查设备连接
    if (![manager isDeviceConnected]) {
        NSLog(@"设备未连接");
        return;
    }

    // 3. 准备图片
    UIImage *image = [UIImage imageNamed:@"background"];

    // 4. 上传自定义表盘
    NSError *error = nil;
    BOOL success = [manager uploadCustomWatchFaceWithImage:image
                                              timePosition:WFTimePositionTopLeft
                                                     color:WFDialColorWhite
                                                  delegate:self
                                                     error:&error];

    if (!success) {
        NSLog(@"上传失败: %@", error.localizedDescription);
    }
}

#pragma mark - WFTransferDelegate

- (void)watchFaceTransferDidStart {
    NSLog(@"开始上传");
}

- (void)watchFaceTransferDidUpdateProgress:(WFTransferProgress *)progress {
    NSLog(@"进度: %.1f%%", progress.percentage * 100);
}

- (void)watchFaceTransferDidComplete {
    NSLog(@"上传完成");
}

- (void)watchFaceTransferDidFailWithError:(NSError *)error {
    NSLog(@"上传失败: %@", error.localizedDescription);
}

@end
```

---

## ✅ 完成！

现在你可以：
- ✅ 上传市场表盘
- ✅ 创建自定义表盘
- ✅ 监控传输进度
- ✅ 控制传输流程（暂停、取消、重试）

---

## 📚 下一步

查看完整文档了解更多功能：

- **详细集成文档**: [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)
- **WatchProtocolSDK 文档**: [README.md](README.md)

---

## ⚠️ 常见错误

### 错误 1: 运行时崩溃 "image not found"

**原因**: 未设置 **Embed & Sign**

**解决**: 参考步骤 2️⃣，确保所有 Framework 都是 **Embed & Sign**

### 错误 2: 设备未连接

**原因**: 需要先使用 WatchProtocolSDK 连接设备

**解决**:
```objc
// 先连接设备
WPBluetoothManager *btManager = [WPBluetoothManager sharedInstance];
[btManager startScanning:YES];
// ... 连接设备后再使用 WatchFaceSDK
```

### 错误 3: 编译错误 "Framework not found"

**原因**: Framework 路径不正确

**解决**: 检查 Build Settings → Framework Search Paths
```
$(PROJECT_DIR)/Frameworks
```

---

## 📞 技术支持

- **Email**: 315082431@qq.com
- **详细文档**: [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)

---

**快速开始就是这么简单！** 🎉
