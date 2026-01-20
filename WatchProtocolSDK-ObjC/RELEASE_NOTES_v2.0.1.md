# WatchProtocolSDK-ObjC v2.0.1 发布说明

## 📅 发布信息

- **版本号**: v2.0.1
- **发布日期**: 2026-01-20
- **编译时间**: 2026-01-20 16:10
- **Framework 大小**: 832K
- **支持平台**: iOS 13.0+

---

## 🎉 重大更新

### ✅ 完整的命令系统实现 (WPCommands)

基于 Swift 版本 `XGZTCommands.swift` 的完整移植，新增核心命令系统：

#### 1. 新增文件
- `WPCommands.h` (231 行) - 命令类型定义和方法声明
- `WPCommands.m` (548 行) - 完整的命令实现和协议解析

#### 2. 核心功能
- **33 种命令类型**: 涵盖设备控制、健康监测、系统设置等
- **自动协议解析**: `handleResponse:` 方法自动解析所有响应数据
- **自动设备更新**: 自动更新 `currentDevice` 的属性
- **自动回调**: 自动调用 delegate 方法通知上层

---

## 🔧 API 新增功能

### P0 核心命令（已实现）

| 命令方法 | 功能 | 命令码 |
|---------|------|--------|
| `syncTime:utc:` | 同步时间 | 0x50 |
| `getBatteryLevel` | 获取电量 | 0x51 |
| `getDeviceInfo` | 获取设备信息 | 0x5C |
| `findDevice` | 查找设备 | 0x8B |

### P1 健康数据命令（已实现）

| 命令方法 | 功能 | 命令码 |
|---------|------|--------|
| `startTest:control:` | 开始/停止健康测量 | 0xC5 |
| `getNewestHeartData:` | 获取最新心率数据 | 0xCA |
| `getStepData:type:` | 获取步数数据 | 0xC9 |
| `getSleepData:type:` | 获取睡眠数据 | - |

### P2 设备控制命令（已实现）

| 命令方法 | 功能 | 命令码 |
|---------|------|--------|
| `setScreenBrightness:` | 设置屏幕亮度 | 0x5A |
| `setDoNotDisturb:` | 设置勿扰模式 | 0x5F |
| `setAlarm:` | 设置闹钟 | 0x60 |
| `setReminder:` | 设置久坐提醒 | 0x61 |

---

## 🐛 问题修复

### 问题4：电量获取不到 ✅ 已彻底解决

**之前状态**:
- ❌ `queryBatteryLevel` 方法为 TODO 占位符
- ❌ 无协议实现，第三方开发者需要自己解析数据

**现在状态**:
- ✅ `WPCommands.getBatteryLevel` 完整实现
- ✅ 自动解析响应数据（电量百分比 + 充电状态）
- ✅ 自动更新 `currentDevice.batteryLevel` 和 `currentDevice.isCharging`
- ✅ 自动回调 `didReceiveBatteryLevel:isCharging:` 代理方法

**使用示例**:
```objc
// 1. 查询电量
[[WPBluetoothManager sharedInstance] queryBatteryLevel];

// 2. 实现代理方法接收结果
- (void)didReceiveBatteryLevel:(NSInteger)level isCharging:(BOOL)charging {
    NSLog(@"电量: %ld%%, 充电中: %@", level, charging ? @"是" : @"否");
}
```

### 问题5：心率检测方法找不到 ✅ 已彻底解决

**之前状态**:
- ❌ `startHeartRateMonitoring` 方法为 TODO 占位符
- ❌ 无协议实现，第三方开发者无法获取心率数据

**现在状态**:
- ✅ `WPCommands.startTest:control:` 完整实现（支持心率/血氧/血压）
- ✅ `WPCommands.getNewestHeartData:` 完整实现（查询历史数据）
- ✅ 自动解析实时测量数据和历史数据
- ✅ 自动更新 `currentDevice.currentHeartrate`
- ✅ 自动回调 `didReceiveHeartRate:` 代理方法

**使用示例**:
```objc
// 1. 开始连续心率测量
[[WPBluetoothManager sharedInstance] startHeartRateMonitoring];

// 2. 停止心率测量
[[WPBluetoothManager sharedInstance] stopHeartRateMonitoring];

// 3. 查询最新心率数据
[WPCommands getNewestHeartData:0];  // 0=心率, 1=血氧, 2=血压

// 4. 实现代理方法接收结果
- (void)didReceiveHeartRate:(NSInteger)heartRate {
    NSLog(@"心率: %ld bpm", heartRate);
}
```

---

## 🏗️ 技术细节

### 自动协议解析机制

在 `WPBluetoothManager.m` 的 BLE 数据回调中集成了自动解析：

```objc
- (void)peripheral:(CBPeripheral *)peripheral
didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    NSData *data = characteristic.value;
    if (data) {
        // 🆕 v2.0.1: 自动解析协议数据
        [WPCommands handleResponse:data];

        // 保持向后兼容：仍然回调原始数据
        if ([self.delegate respondsToSelector:@selector(receiveData:)]) {
            [self.delegate receiveData:data];
        }
    }
}
```

### 协议解析流程

1. **接收数据** → BLE characteristic 更新回调
2. **自动识别** → `handleResponse:` 根据命令码（byte[1]）识别响应类型
3. **专用解析** → 调用对应的 `handleXXXResponse:` 方法
4. **自动更新** → 更新 `currentDevice` 属性
5. **自动通知** → 回调 delegate 方法

### 命令码映射表（部分）

| 命令码 | 响应类型 | 专用处理方法 |
|--------|---------|-------------|
| 0x50 | 时间同步响应 | `handleSyncTimeResponse:` |
| 0x51 | 电量响应 | `handleBatteryLevelResponse:` |
| 0x5C | 设备信息响应 | `handleDeviceInfoResponse:` |
| 0xC5 | 测量响应（心率/血氧/血压） | `handleStartTestResponse:` |
| 0xCA | 历史数据响应 | `handleNewestHeartDataResponse:` |
| 0xC9 | 步数数据响应 | `handleStepDataResponse:` |

---

## 📊 代码统计

| 指标 | 数值 |
|------|------|
| 新增文件 | 2 个 |
| 新增代码 | 779 行 |
| 修改文件 | 1 个 (WPBluetoothManager.m) |
| 修改代码 | 68 行 |
| 命令类型 | 33 种 |
| 命令方法 | 57+ 个 |
| 响应解析方法 | 9 个 |
| 消除 TODO | 全部（4个占位符 → 实际实现） |

---

## ✅ 符号验证

Framework 包含以下关键符号：

```bash
$ nm -g WatchProtocolSDK.framework/WatchProtocolSDK | grep "OBJC_CLASS"

_OBJC_CLASS_$_WPBluetoothManager       ✅
_OBJC_CLASS_$_WPDeviceManager          ✅
_OBJC_CLASS_$_WPEmptyHealthDataStorage ✅
_OBJC_CLASS_$_WPCommands               ✅ 新增
```

---

## 🎯 向后兼容性

完全兼容 v2.0.0 API：

- ✅ 所有现有方法签名不变
- ✅ 所有现有代理方法不变
- ✅ 现有集成代码无需修改
- ✅ 新增功能为增量更新，不破坏现有功能

---

## 📦 集成方式

### 方式1：替换现有 Framework（推荐）

```bash
# 删除旧版本
rm -rf YourProject/Frameworks/WatchProtocolSDK.xcframework

# 复制新版本
cp -R Output-ObjC-Dynamic/WatchProtocolSDK.xcframework YourProject/Frameworks/

# 清理并重新编译
rm -rf ~/Library/Developer/Xcode/DerivedData/*
```

### 方式2：Xcode 重新添加

1. 删除项目中的旧 Framework
2. 拖入新的 `WatchProtocolSDK.xcframework`
3. 确保 Embed 设置为 **"Embed & Sign"**

---

## 🚀 升级后可以做什么

### 1. 电量监控 ⚡

```objc
// 定时查询电量
[NSTimer scheduledTimerWithTimeInterval:60 repeats:YES block:^(NSTimer *timer) {
    [[WPBluetoothManager sharedInstance] queryBatteryLevel];
}];

// 接收电量更新
- (void)didReceiveBatteryLevel:(NSInteger)level isCharging:(BOOL)charging {
    // 更新 UI，显示电量和充电状态
    self.batteryLabel.text = [NSString stringWithFormat:@"%ld%%", level];
    self.chargingIcon.hidden = !charging;
}
```

### 2. 心率监测 ❤️

```objc
// 开始连续心率监测
[[WPBluetoothManager sharedInstance] startHeartRateMonitoring];

// 接收实时心率
- (void)didReceiveHeartRate:(NSInteger)heartRate {
    // 更新心率图表
    [self.heartRateChart addDataPoint:heartRate];

    // 异常检测
    if (heartRate > 100) {
        [self showHeartRateWarning];
    }
}

// 停止监测（节省设备电量）
[[WPBluetoothManager sharedInstance] stopHeartRateMonitoring];
```

### 3. 设备查找 🔍

```objc
// 让手表震动/响铃
[WPCommands findDevice];
```

### 4. 屏幕亮度调节 💡

```objc
// 设置屏幕亮度 (1-5)
[WPCommands setScreenBrightness:3];
```

---

## 📖 完整文档

详细集成指南和 API 文档：

- **DYNAMIC_FRAMEWORK_INTEGRATION.md** - Framework 集成完整指南
- **LINKER_ERROR_FIX.md** - 链接错误快速修复
- **README.md** - API 使用文档
- **WPCOMMANDS_IMPLEMENTATION_SUMMARY.md** - WPCommands 实现详解

---

## 🔗 相关文档

- [SDK 对比报告](../WatchProtocolSDK-ObjC/SDK_COMPARISON_REPORT.md)
- [第三方问题解决方案](../WatchProtocolSDK-ObjC/THIRD_PARTY_ISSUES_RESOLUTION.md)
- [WPCommands 实现总结](../WatchProtocolSDK-ObjC/WPCOMMANDS_IMPLEMENTATION_SUMMARY.md)

---

## 📞 技术支持

如有问题，请联系：315082431@qq.com

提供问题时，请附上：
1. Xcode 版本
2. 完整错误信息
3. 集成方式（动态/静态）
4. 最小可复现代码

---

## 🎉 总结

v2.0.1 是一个重要的功能性更新版本：

- ✅ **问题4（电量）**和**问题5（心率）**彻底解决
- ✅ 新增 779 行经过验证的协议实现代码
- ✅ 第三方开发者可直接使用，无需自行解析协议
- ✅ 完全向后兼容 v2.0.0
- ✅ 纯 Objective-C 实现，无 Swift 依赖

**建议所有 v2.0.0 用户升级到 v2.0.1！**
