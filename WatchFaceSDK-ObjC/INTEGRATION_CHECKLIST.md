# WatchFaceSDK-ObjC 集成清单

快速检查您的集成是否正确。

---

## ✅ 集成检查清单

### 步骤 1: 添加框架 ✓

- [ ] 已将 `WatchFaceSDK_ObjC.xcframework` 拖入项目
- [ ] 已将 `WatchProtocolSDK.xcframework` 拖入项目
- [ ] 已将 `ABParTool.xcframework` 拖入项目（可选）

### 步骤 2: 配置 Embed 设置 ✓ **最重要**

进入 **Target → General → Frameworks, Libraries, and Embedded Content**，确认：

- [ ] `WatchFaceSDK_ObjC.xcframework` 设置为 **"Embed & Sign"**
- [ ] `WatchProtocolSDK.xcframework` 设置为 **"Embed & Sign"**
- [ ] `ABParTool.xcframework` 设置为 **"Embed & Sign"**（如果添加）

**⚠️ 常见错误**：设置成 "Do Not Embed" 会导致运行时崩溃！

### 步骤 3: 导入头文件 ✓

#### Objective-C

在需要使用的文件中：

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
#import <WatchFaceSDK_ObjC/WFTransferDelegate.h>
#import <WatchFaceSDK_ObjC/WFEnums.h>
```

- [ ] 已在代码中导入必要头文件
- [ ] 编译无报错

#### Swift

创建 Bridging Header：

```objc
// YourProject-Bridging-Header.h
#import <WatchFaceSDK_ObjC/WFManager.h>
#import <WatchFaceSDK_ObjC/WFTransferDelegate.h>
#import <WatchFaceSDK_ObjC/WFEnums.h>
```

- [ ] 已创建 Bridging Header
- [ ] 已在 Build Settings 中配置 Bridging Header 路径
- [ ] Swift 代码可以访问 `WFManager`

### 步骤 4: 初始化依赖 ✓

在 AppDelegate 或首次使用前：

```objc
#import <WatchProtocolSDK/WPBluetoothManager.h>

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // 初始化 WatchProtocolSDK
    [[WPBluetoothManager sharedInstance] initCentral];

    return YES;
}
```

- [ ] 已初始化 WatchProtocolSDK
- [ ] 蓝牙权限已在 Info.plist 中配置

### 步骤 5: 配置蓝牙权限 ✓

在 `Info.plist` 中添加：

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表</string>
<key>NSBluetoothPeripheralUsageDescription</key>
<string>需要使用蓝牙连接智能手表</string>
```

- [ ] 已添加蓝牙权限描述
- [ ] 权限描述文字已本地化

### 步骤 6: 测试基础功能 ✓

```objc
WFManager *manager = [WFManager sharedInstance];

// 测试 1: SDK 初始化
NSLog(@"✅ SDK 初始化成功");

// 测试 2: 检查设备连接
BOOL connected = [manager isDeviceConnected];
NSLog(@"设备连接状态: %@", connected ? @"已连接" : @"未连接");

// 测试 3: 获取屏幕信息
WFDeviceScreenInfo *info = [manager getCurrentDeviceScreenInfo];
NSLog(@"屏幕尺寸: %ldx%ld", (long)info.width, (long)info.height);
```

- [ ] SDK 初始化无报错
- [ ] 可以查询设备连接状态
- [ ] 可以获取设备屏幕信息

---

## 🐛 常见问题快速排查

### 问题 1: dyld: Library not loaded

**症状**：
```
dyld: Library not loaded: @rpath/WatchFaceSDK_ObjC.framework/WatchFaceSDK_ObjC
```

**检查**：
- [ ] Embed 设置是否为 "Embed & Sign"？
- [ ] 是否使用了正确的 xcframework 文件？

**解决**：
1. Target → General → Frameworks, Libraries, and Embedded Content
2. 将所有框架改为 **"Embed & Sign"**
3. Clean Build Folder (⇧⌘K)
4. 重新编译

---

### 问题 2: Undefined symbols for architecture arm64

**症状**：
```
Undefined symbols for architecture arm64:
  "_OBJC_CLASS_$_WFManager", referenced from:
```

**检查**：
- [ ] 框架是否在项目中？
- [ ] Framework Search Paths 是否正确？

**解决**：
1. 删除框架重新添加
2. 清理 DerivedData
3. 重启 Xcode

---

### 问题 3: Module 'WatchFaceSDK_ObjC' not found

**症状**：
```objc
#import <WatchFaceSDK_ObjC/WFManager.h>
// Error: Module 'WatchFaceSDK_ObjC' not found
```

**检查**：
- [ ] 框架是否正确添加？
- [ ] 导入语法是否正确（使用尖括号 `<>`）？

**解决**：
```objc
// ✅ 正确
#import <WatchFaceSDK_ObjC/WFManager.h>

// ❌ 错误
#import "WFManager.h"
```

---

### 问题 4: 设备未连接

**症状**：
```objc
[manager isDeviceConnected];  // 返回 NO
```

**检查**：
- [ ] WatchProtocolSDK 是否已初始化？
- [ ] 蓝牙是否已开启扫描？
- [ ] 设备是否已成功连接？

**解决**：
```objc
// 1. 初始化
[[WPBluetoothManager sharedInstance] initCentral];

// 2. 扫描设备
[[WPBluetoothManager sharedInstance] startScanning:YES];

// 3. 连接设备（在发现设备回调中）
[[WPBluetoothManager sharedInstance] connectToPeripheral:peripheralInfo];

// 4. 连接成功后使用 WatchFaceSDK
```

---

## 📋 验证清单

完成以下所有项目，确保集成正确：

### 编译验证
- [ ] 项目可以成功编译
- [ ] 没有链接错误
- [ ] 没有导入错误

### 运行时验证
- [ ] 应用可以正常启动
- [ ] 没有 dyld 错误
- [ ] 可以创建 WFManager 实例

### 功能验证
- [ ] 可以检查设备连接状态
- [ ] 可以获取设备屏幕信息
- [ ] 可以上传表盘（如果设备已连接）

---

## 🎯 最小可行代码

复制以下代码到您的项目中测试：

```objc
// ViewController.m
#import "ViewController.h"
#import <WatchFaceSDK_ObjC/WFManager.h>

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    WFManager *manager = [WFManager sharedInstance];

    NSLog(@"========================================");
    NSLog(@"WatchFaceSDK 集成测试");
    NSLog(@"========================================");

    // 测试 1: 设备连接
    BOOL connected = [manager isDeviceConnected];
    NSLog(@"1️⃣ 设备连接: %@", connected ? @"✅ 已连接" : @"❌ 未连接");

    // 测试 2: 屏幕信息
    WFDeviceScreenInfo *info = [manager getCurrentDeviceScreenInfo];
    NSLog(@"2️⃣ 屏幕信息: %ldx%ld (MTU: %ld)",
          (long)info.width, (long)info.height, (long)info.mtu);

    // 测试 3: 推荐尺寸
    CGSize size = [manager getRecommendedImageSize];
    NSLog(@"3️⃣ 推荐尺寸: %.0fx%.0f", size.width, size.height);

    NSLog(@"========================================");
    NSLog(@"✅ 所有测试通过！集成成功！");
    NSLog(@"========================================");
}

@end
```

**期望输出**：
```
========================================
WatchFaceSDK 集成测试
========================================
1️⃣ 设备连接: ✅ 已连接
2️⃣ 屏幕信息: 240x240 (MTU: 240)
3️⃣ 推荐尺寸: 240x240
========================================
✅ 所有测试通过！集成成功！
========================================
```

如果看到以上输出，说明集成成功！🎉

---

## 📞 需要帮助？

如果按照清单检查后仍有问题，请提供：

1. ✅ Xcode 版本
2. ✅ iOS 版本
3. ✅ 完整错误日志
4. ✅ Embed 设置截图
5. ✅ Framework Search Paths 配置

联系：315082431@qq.com
