# WatchProtocolSDK-ObjC v1.1.0 快速入门

## 🚀 新功能速览

v1.1.0 版本解决了扫描设备和保存设备的类型转换问题，提供**三种超简单的方法**！

---

## ⚡️ 最快 5 分钟上手

### 问题回顾

**之前版本**（需要手动转换，麻烦）：
```objective-c
WPPeripheralInfo *info = ...; // 扫描到的设备

// ❌ 需要手动创建对象
WPBluetoothWatchDevice *device = [[WPBluetoothWatchDevice alloc] init];
device.deviceName = info.peripheral.name;
device.mac = info.macAddress;
[WPBluetoothWatchDevice saveToSandbox:device];
```

**v1.1.0 版本**（一行代码搞定）：
```objective-c
WPPeripheralInfo *info = ...; // 扫描到的设备

// ✅ 一行代码搞定！
[WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];
```

---

## 📝 三种使用方式

### 方式 1️⃣：一步保存（推荐，最简单）

```objective-c
#import <WatchProtocolSDK/WatchProtocolSDK.h>

// 扫描设备
[[WPBluetoothManager sharedInstance] startScanning:YES];

// 获取扫描结果
NSArray<WPPeripheralInfo *> *devices = [WPBluetoothManager sharedInstance].discoveredPeripherals;

// 一行代码保存所有设备
for (WPPeripheralInfo *info in devices) {
    [WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];
}
```

**适用场景**：只需要保存设备，不需要额外处理

---

### 方式 2️⃣：工厂方法（推荐，灵活）

```objective-c
#import <WatchProtocolSDK/WatchProtocolSDK.h>

// 扫描设备
NSArray<WPPeripheralInfo *> *devices = [WPBluetoothManager sharedInstance].discoveredPeripherals;
WPPeripheralInfo *info = devices.firstObject;

// 创建设备对象
WPBluetoothWatchDevice *device = [WPBluetoothWatchDevice deviceFromPeripheralInfo:info];

// 可以设置更多信息（可选）
device.batteryLevel = 80;
device.mtu = 512;

// 保存
[WPBluetoothWatchDevice saveToSandbox:device];
```

**适用场景**：需要在保存前设置额外信息

---

### 方式 3️⃣：Category 扩展（可选，链式调用风格）

```objective-c
#import <WatchProtocolSDK/WatchProtocolSDK.h>
#import <WatchProtocolSDK/WPPeripheralInfo+WatchDevice.h>  // ← 需要导入这个头文件

// 扫描设备
NSArray<WPPeripheralInfo *> *devices = [WPBluetoothManager sharedInstance].discoveredPeripherals;
WPPeripheralInfo *info = devices.firstObject;

// 方式 A：转换为设备对象
WPBluetoothWatchDevice *device = [info toWatchDevice];
[WPBluetoothWatchDevice saveToSandbox:device];

// 方式 B：直接保存（一行代码）
[info saveToSandbox];
```

**适用场景**：喜欢链式调用风格的开发者

---

## 🎯 完整示例：扫描并保存设备

```objective-c
#import <WatchProtocolSDK/WatchProtocolSDK.h>

@interface MyViewController () <WPBluetoothManagerDelegate>
@property (nonatomic, strong) NSMutableArray<WPPeripheralInfo *> *discoveredDevices;
@end

@implementation MyViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // 1. 设置代理
    [WPBluetoothManager sharedInstance].delegate = self;

    // 2. 初始化蓝牙
    [[WPBluetoothManager sharedInstance] initCentral];

    // 3. 初始化设备列表
    self.discoveredDevices = [NSMutableArray array];
}

- (IBAction)startScanButtonTapped:(id)sender {
    // 清空列表
    [self.discoveredDevices removeAllObjects];

    // 开始扫描
    [[WPBluetoothManager sharedInstance] startScanning:YES];
}

#pragma mark - WPBluetoothManagerDelegate

// 发现新设备时调用
- (void)didDiscoverPeripheral:(WPPeripheralInfo *)peripheralInfo {
    dispatch_async(dispatch_get_main_queue(), ^{
        // 添加到列表
        [self.discoveredDevices addObject:peripheralInfo];

        // 🎉 新功能：自动保存设备（一行代码）
        [WPBluetoothWatchDevice savePeripheralInfoToSandbox:peripheralInfo];

        // 更新 UI
        [self.tableView reloadData];

        NSLog(@"✅ 发现并保存设备: %@", peripheralInfo.peripheral.name);
    });
}

// 连接成功时调用
- (void)didConnectPeripheral:(CBPeripheral *)peripheral {
    dispatch_async(dispatch_get_main_queue(), ^{
        // 找到对应的 peripheralInfo
        WPPeripheralInfo *peripheralInfo = nil;
        for (WPPeripheralInfo *info in self.discoveredDevices) {
            if ([info.peripheral.identifier isEqual:peripheral.identifier]) {
                peripheralInfo = info;
                break;
            }
        }

        if (peripheralInfo) {
            // 🎉 新功能：使用工厂方法创建设备对象
            WPBluetoothWatchDevice *device = [WPBluetoothWatchDevice deviceFromPeripheralInfo:peripheralInfo];

            // 连接成功后，可以更新更多信息
            // device.batteryLevel = [self readBatteryLevel];
            // device.mtu = [self readMTU];

            // 保存更新后的信息
            [WPBluetoothWatchDevice saveToSandbox:device];

            NSLog(@"✅ 设备连接并保存: %@", peripheral.name);
        }
    });
}

@end
```

---

## 🔄 从旧版本迁移

### 无需修改现有代码！

**旧代码（v1.0.0）**：
```objective-c
WPBluetoothWatchDevice *device = [[WPBluetoothWatchDevice alloc] init];
device.deviceName = info.peripheral.name;
device.mac = info.macAddress;
[WPBluetoothWatchDevice saveToSandbox:device];
```

**依然有效！** ✅ 完全向下兼容

**但建议升级到新方法**：
```objective-c
// 推荐方式：一行代码搞定
[WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];
```

---

## ❓ 常见问题

### Q1: 三种方法有什么区别？

**A**: 功能完全相同，只是风格不同：
- **方式 1**（一步保存）：最简洁，适合只需要保存的场景
- **方式 2**（工厂方法）：最灵活，适合需要额外处理的场景
- **方式 3**（Category 扩展）：链式调用风格，需要导入额外头文件

**推荐**：根据个人习惯选择，大多数情况用方式 1 或 2

---

### Q2: 是否必须升级代码？

**A**: 不需要！旧代码依然有效。但新方法更简洁，建议在新代码中使用。

---

### Q3: Category 扩展需要额外导入吗？

**A**: 是的，使用方式 3 需要导入：
```objective-c
#import <WatchProtocolSDK/WPPeripheralInfo+WatchDevice.h>
```

但方式 1 和方式 2 不需要额外导入。

---

### Q4: 创建的设备对象包含哪些信息？

**A**: 从扫描信息创建的设备对象仅包含：
- `deviceName`（设备名称）
- `mac`（MAC 地址）

其他信息（电量、MTU、固件版本等）需要连接设备后获取。

---

## 📚 更多资源

- **详细使用指南**: [PERIPHERAL_TO_DEVICE_GUIDE.md](PERIPHERAL_TO_DEVICE_GUIDE.md)
- **版本更新日志**: [CHANGELOG.md](CHANGELOG.md)
- **技术总结**: [v1.1.0-UPDATE-SUMMARY.md](v1.1.0-UPDATE-SUMMARY.md)
- **API 文档**: [README.md](README.md)

---

## 🎉 开始使用

1. 下载 `WatchProtocolSDK.xcframework`
2. 拖入项目
3. 导入头文件：`#import <WatchProtocolSDK/WatchProtocolSDK.h>`
4. 使用新方法：`[WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];`

**就这么简单！** 🚀

---

**版本**: v1.1.0
**发布日期**: 2026-01-19
**向下兼容**: ✅ 完全兼容 v1.0.0
