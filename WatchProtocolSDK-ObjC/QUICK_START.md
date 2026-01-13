# WatchProtocolSDK-ObjC 快速开始

## 🚀 5 分钟快速集成

### 步骤 1: 添加 Framework

将 `WatchProtocolSDK.xcframework` 拖入你的 Xcode 项目。

**在 Target -> General -> Frameworks, Libraries, and Embedded Content:**
- 确认 `WatchProtocolSDK.xcframework` 已添加
- 设置 Embed 为 **Embed & Sign** ⚠️ 重要！

### 步骤 2: 添加系统框架

**在 Target -> Build Phases -> Link Binary With Libraries 添加:**
- `CoreBluetooth.framework`
- `Foundation.framework`

### 步骤 3: 配置蓝牙权限

在 `Info.plist` 中添加：

```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>
<key>NSBluetoothPeripheralUsageDescription</key>
<string>需要使用蓝牙与智能手表进行数据交互</string>
```

### 步骤 4: 创建数据存储实现

创建一个新文件 `MyHealthDataStorage.h`:

```objc
#import <Foundation/Foundation.h>
#import <WatchProtocolSDK/WatchProtocolSDK.h>

@interface MyHealthDataStorage : NSObject <WPHealthDataStorageProtocol>
@end
```

创建 `MyHealthDataStorage.m`:

```objc
#import "MyHealthDataStorage.h"

@implementation MyHealthDataStorage

- (void)saveStepData:(WPStepData *)data {
    NSLog(@"💾 保存步数: %ld", (long)data.step);
    // TODO: 保存到你的数据库
}

- (void)saveSleepData:(WPSleepData *)data {
    NSLog(@"💾 保存睡眠数据");
    // TODO: 保存到你的数据库
}

- (void)saveHeartData:(WPHeartData *)data {
    NSLog(@"💾 保存心率: %ld", (long)data.heart);
    // TODO: 保存到你的数据库
}

- (void)saveOxygenData:(WPOxygenData *)data {
    NSLog(@"💾 保存血氧: %ld", (long)data.oxygen);
    // TODO: 保存到你的数据库
}

- (void)saveBloodPressureData:(WPBloodPressureData *)data {
    NSLog(@"💾 保存血压: %ld/%ld", (long)data.max, (long)data.min);
    // TODO: 保存到你的数据库
}

@end
```

### 步骤 5: 初始化 SDK

在 `AppDelegate.m` 中：

```objc
#import "AppDelegate.h"
#import "MyHealthDataStorage.h"
#import <WatchProtocolSDK/WatchProtocolSDK.h>

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // 1. 创建数据存储
    MyHealthDataStorage *storage = [[MyHealthDataStorage alloc] init];

    // 2. 初始化设备管理器
    [[WPDeviceManager sharedInstance] initializeWithStorage:storage];

    // 3. 初始化蓝牙管理器
    [[WPBluetoothManager sharedInstance] initCentral];

    NSLog(@"✅ WatchProtocolSDK 初始化完成");

    return YES;
}

@end
```

### 步骤 6: 扫描和连接设备

在你的 `ViewController.m` 中：

```objc
#import "ViewController.h"
#import <WatchProtocolSDK/WatchProtocolSDK.h>

@interface ViewController () <WPBluetoothManagerDelegate>
@property (nonatomic, strong) NSMutableArray<WPPeripheralInfo *> *devices;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // 设置蓝牙代理
    [WPBluetoothManager sharedInstance].delegate = self;

    // 初始化设备列表
    self.devices = [NSMutableArray array];
}

// 开始扫描
- (IBAction)scanButtonTapped:(id)sender {
    [[WPBluetoothManager sharedInstance] startScanning:YES];
}

// 停止扫描
- (IBAction)stopButtonTapped:(id)sender {
    [[WPBluetoothManager sharedInstance] stopScanning];
}

// MARK: - WPBluetoothManagerDelegate

- (void)onBleReady {
    NSLog(@"✅ 蓝牙已准备就绪");
}

- (void)didDiscoverPeripheral:(WPPeripheralInfo *)peripheralInfo {
    NSLog(@"🔍 发现设备: %@", peripheralInfo.peripheral.name ?: @"未知");
    [self.devices addObject:peripheralInfo];
    // TODO: 更新 UI
}

- (void)didConnectPeripheral:(CBPeripheral *)peripheral {
    NSLog(@"✅ 连接成功: %@", peripheral.name);
    // TODO: 获取设备信息
}

- (void)didDisconnectPeripheral:(CBPeripheral *)peripheral error:(NSError *)error {
    NSLog(@"🔌 设备断开");
}

- (void)receiveData:(NSData *)data {
    NSLog(@"📩 接收数据: %@", data);
    // TODO: 解析数据
}

@end
```

---

## ✅ 验证安装

运行项目，在控制台应该看到：

```
✅ WatchProtocolSDK 初始化完成
✅ 蓝牙已准备就绪
```

---

## 🎯 下一步

### 1. 连接设备

```objc
// 连接指定外设
[[WPBluetoothManager sharedInstance] connectToPeripheral:peripheral];

// 或通过 MAC 地址连接
[[WPBluetoothManager sharedInstance] connectToDeviceWithMac:@"XX:XX:XX:XX:XX:XX"];
```

### 2. 发送数据

```objc
NSData *data = [@"Hello" dataUsingEncoding:NSUTF8StringEncoding];
BOOL success = [[WPBluetoothManager sharedInstance] sendData:data];
```

### 3. 管理设备

```objc
// 获取设备管理器
WPDeviceManager *manager = [WPDeviceManager sharedInstance];

// 获取缓存的设备列表
NSArray *devices = manager.cacheDevices;

// 查找设备
WPBluetoothWatchDevice *device = [manager findDeviceWithMac:@"XX:XX:XX:XX:XX:XX"];
```

---

## 📚 完整文档

- **API 文档**: `README.md`
- **集成指南**: `INTEGRATION_GUIDE.md`
- **版本信息**: `VERSION_INFO.md`

---

## ❓ 常见问题

### Q: 编译时提示找不到头文件？

**A**: 确保：
1. Framework 的 Embed 设置为 "Embed & Sign"
2. 导入语句正确：`#import <WatchProtocolSDK/WatchProtocolSDK.h>`

### Q: 运行时崩溃？

**A**: 检查：
1. 是否添加了 CoreBluetooth.framework
2. 是否在 Info.plist 中添加了蓝牙权限
3. 是否正确初始化了 SDK

### Q: 如何调试？

**A**:
```objc
// 查看日志文件路径
NSString *logPath = [[WPLogger sharedInstance] logFilePath];
NSLog(@"日志文件: %@", logPath);
```

---

## 🎉 恭喜！

你已经成功集成 WatchProtocolSDK-ObjC！

现在可以开始：
- 扫描蓝牙设备
- 连接智能手表
- 同步健康数据

有问题？联系：315082431@qq.com
