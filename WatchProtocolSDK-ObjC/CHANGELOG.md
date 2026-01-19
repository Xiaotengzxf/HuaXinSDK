# WatchProtocolSDK-ObjC 版本更新日志

所有重要的版本变更都将记录在本文件中。

格式遵循 [Keep a Changelog](https://keepachangelog.com/zh-CN/1.0.0/)，版本号遵循 [语义化版本](https://semver.org/lang/zh-CN/)。

---

## [1.1.0] - 2026-01-19

### 新增（Added）

#### 扫描设备保存便捷方法

**问题背景**：
在之前的版本中，扫描设备返回 `WPPeripheralInfo *` 类型，而保存设备需要 `WPBluetoothWatchDevice *` 类型，第三方开发者需要手动创建和转换对象，增加了使用复杂度。

**解决方案**：
新增三种便捷方法，简化从扫描设备到保存设备的流程：

1. **工厂方法**（推荐，架构清晰）
   ```objective-c
   + (instancetype)deviceFromPeripheralInfo:(WPPeripheralInfo *)peripheralInfo;
   ```

2. **一步保存**（推荐，最简洁）
   ```objective-c
   + (void)savePeripheralInfoToSandbox:(WPPeripheralInfo *)peripheralInfo;
   ```

3. **Category 扩展**（可选，链式调用风格）
   ```objective-c
   - (WPBluetoothWatchDevice *)toWatchDevice;
   - (void)saveToSandbox;
   ```

**使用示例**：
```objective-c
// 方法 1：工厂方法
WPBluetoothWatchDevice *device = [WPBluetoothWatchDevice deviceFromPeripheralInfo:info];
[WPBluetoothWatchDevice saveToSandbox:device];

// 方法 2：一步保存
[WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];

// 方法 3：Category 扩展（需导入头文件）
#import "WPPeripheralInfo+WatchDevice.h"
[info saveToSandbox];
```

**相关文件**：
- `Models/WPDeviceModel.h` - 添加工厂方法声明
- `Models/WPDeviceModel.m` - 实现工厂方法
- `Extensions/WPPeripheralInfo+WatchDevice.h` - Category 扩展头文件
- `Extensions/WPPeripheralInfo+WatchDevice.m` - Category 扩展实现
- `PERIPHERAL_TO_DEVICE_GUIDE.md` - 详细使用指南

**相关 Issue**：
- 修复第三方开发者反馈的类型不兼容问题

### 改进（Improved）

- 更新 `ExampleViewController.m` 示例代码，展示新方法的使用
- 更新 `README.md`，添加新功能说明
- 新增 `PERIPHERAL_TO_DEVICE_GUIDE.md` 详细使用指南

### 架构设计

**设计原则**：
- 符合依赖倒置原则（DIP）：业务层依赖基础层
- 符合单一职责原则（SRP）：业务逻辑集中在业务模型中
- 提供多种使用方式，满足不同开发者的习惯

**依赖关系**：
```
WPDeviceModel.m → 导入 → WPBluetoothManager.h（使用前向声明）
WPPeripheralInfo+WatchDevice.m → 导入 → WPDeviceModel.h
```

---

## [1.0.0] - 2026-01-12

### 新增（Added）

- 🎉 首次发布 WatchProtocolSDK-ObjC
- ✅ 纯 Objective-C 实现的蓝牙通信协议 SDK
- ✅ 蓝牙设备管理（扫描、连接、断开、重连）
- ✅ 健康数据同步（步数、睡眠、心率、血氧、血压）
- ✅ 协议化存储设计
- ✅ 线程安全设计
- ✅ 完善的日志系统
- ✅ 模块化架构

### 核心模块

#### 蓝牙管理（Core/WPBluetoothManager）
- 设备扫描和发现
- 设备连接管理
- 数据收发
- 连接状态监控

#### 设备管理（Core/WPDeviceManager）
- 设备缓存管理
- 设备持久化存储
- 连接失败诊断

#### 数据模型（Models）
- `WPDeviceModel` - 设备信息模型
- `WPHealthDataModels` - 健康数据模型

#### 协议定义（Protocols）
- `WPBluetoothManagerDelegate` - 蓝牙管理代理
- `WPHealthDataStorageProtocol` - 健康数据存储协议

#### 工具类（Utils）
- `WPLogger` - 日志系统
- `WPDataTransform` - 数据转换工具

### 支持平台

- iOS 13.0+
- Xcode 12.0+
- Objective-C

### 依赖框架

- `CoreBluetooth.framework`
- `Foundation.framework`

---

## 版本说明

### 版本号规则

采用语义化版本号 `MAJOR.MINOR.PATCH`：

- **MAJOR**：重大架构变更或不兼容的 API 修改
- **MINOR**：向下兼容的功能性新增
- **PATCH**：向下兼容的问题修正

### 版本类型

- **[新增]（Added）**：新功能
- **[改进]（Changed）**：对现有功能的变更
- **[弃用]（Deprecated）**：即将移除的功能
- **[移除]（Removed）**：已移除的功能
- **[修复]（Fixed）**：Bug 修复
- **[安全]（Security）**：安全相关的修复

---

## 升级指南

### 从 v1.0.0 升级到 v1.1.0

**向下兼容**：完全兼容，无需修改现有代码。

**可选升级**：
如果你的代码中有手动创建 `WPBluetoothWatchDevice` 对象的逻辑，可以考虑使用新的工厂方法简化代码。

**旧代码（仍然有效）**：
```objective-c
WPPeripheralInfo *info = ...;

WPBluetoothWatchDevice *device = [[WPBluetoothWatchDevice alloc] init];
device.deviceName = info.peripheral.name;
device.mac = info.macAddress;
[WPBluetoothWatchDevice saveToSandbox:device];
```

**新代码（推荐）**：
```objective-c
WPPeripheralInfo *info = ...;

// 方式 1：工厂方法
WPBluetoothWatchDevice *device = [WPBluetoothWatchDevice deviceFromPeripheralInfo:info];
[WPBluetoothWatchDevice saveToSandbox:device];

// 方式 2：一步保存
[WPBluetoothWatchDevice savePeripheralInfoToSandbox:info];
```

**详细指南**：参考 [PERIPHERAL_TO_DEVICE_GUIDE.md](PERIPHERAL_TO_DEVICE_GUIDE.md)

---

## 反馈与贡献

如果你在使用过程中遇到问题或有改进建议，欢迎：

- 提交 Issue
- 发送邮件给技术支持团队
- 参与代码贡献

---

## 许可证

Copyright © 2026 Huaxin. All rights reserved.
