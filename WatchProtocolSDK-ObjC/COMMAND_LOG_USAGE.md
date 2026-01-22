# 指令日志使用指南

## 📖 概述

WatchProtocolSDK v2.0.4 新增了自动打印蓝牙指令数据的功能，帮助开发者更好地调试和了解设备通信过程。

## 🎯 功能特性

### 自动日志输出
- ✅ **发送日志**：每次发送数据到设备时自动打印
- ✅ **接收日志**：每次接收设备数据时自动打印
- ✅ **十六进制格式**：清晰显示原始数据
- ✅ **数据长度**：显示字节数便于快速判断
- ✅ **零配置**：无需任何额外设置

### 日志格式

```
📤 发送指令 [字节数]: 十六进制数据
📥 接收指令 [字节数]: 十六进制数据
```

## 📱 使用示例

### 示例 1：查询电量

```objc
// 发送查询电量指令
[[WPBluetoothManager sharedInstance] queryBatteryLevel];

// Xcode 控制台输出：
// 📤 发送指令 [3 bytes]: AB0100
// 📥 接收指令 [5 bytes]: AB02640101
```

**日志解读**：
- `AB0100`: 查询电量指令
  - `AB`: 协议头
  - `01`: 命令类型（查询电量）
  - `00`: 参数
- `AB02640101`: 电量响应
  - `AB02`: 响应头
  - `64`: 电量值 100%
  - `01`: 充电状态（正在充电）
  - `01`: 校验位

### 示例 2：心率测量

```objc
// 开始心率测量
[[WPBluetoothManager sharedInstance] startHeartRateMonitoring];

// Xcode 控制台输出：
// 📤 发送指令 [4 bytes]: AB030001
// 📥 接收指令 [6 bytes]: AB04004B0001
```

**日志解读**：
- `AB030001`: 开始心率测量指令
  - `AB`: 协议头
  - `03`: 命令类型（健康数据测试）
  - `00`: 测试类型（心率）
  - `01`: 控制字（开始）
- `AB04004B0001`: 心率数据响应
  - `AB04`: 响应头
  - `00`: 数据类型（心率）
  - `4B`: 心率值 75 bpm
  - `00`: 附加状态
  - `01`: 校验位

### 示例 3：自定义指令

```objc
// 发送自定义指令
NSData *customCommand = [NSData dataWithBytes:(uint8_t[]){0xAB, 0x05, 0x01, 0x02, 0x03} length:5];
[[WPBluetoothManager sharedInstance] sendData:customCommand];

// Xcode 控制台输出：
// 📤 发送指令 [5 bytes]: AB05010203
```

## 🔍 如何查看日志

### 方法 1：Xcode 控制台（推荐）

1. 在 Xcode 中运行 App（Cmd + R）
2. 打开 Debug Area（View → Debug Area → Show Debug Area）
3. 切换到 Console 标签
4. 搜索关键词：
   - 搜索 `📤` 查看所有发送的指令
   - 搜索 `📥` 查看所有接收的指令
   - 搜索 `发送指令` 或 `接收指令`

### 方法 2：设备控制台（iOS 设备）

1. 将设备连接到 Mac
2. 打开 Xcode → Window → Devices and Simulators
3. 选择你的设备
4. 点击 "Open Console" 按钮
5. 过滤日志（输入关键词）

### 方法 3：保存日志文件

```objc
// 在 AppDelegate.m 中重定向日志到文件
- (BOOL)application:(UIApplication *)application
didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // 获取文档目录
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths firstObject];
    NSString *logPath = [documentsDirectory stringByAppendingPathComponent:@"bluetooth_log.txt"];

    // 重定向标准输出到文件
    freopen([logPath cStringUsingEncoding:NSASCIIStringEncoding], "a+", stdout);

    return YES;
}
```

然后可以通过 iTunes File Sharing 或其他方式导出日志文件。

## 📊 完整通信示例

### 连接设备并查询数据

```objc
// 1. 初始化蓝牙管理器
WPBluetoothManager *manager = [WPBluetoothManager sharedInstance];
manager.delegate = self;
[manager initCentral];

// 2. 扫描并连接设备
[manager connectAndScanWithMac:@"AA:BB:CC:DD:EE:FF"
                    deviceName:@"MyWatch"
                       timeout:10.0];

// 3. 连接成功后查询电量
- (void)didConnectPeripheral:(WPPeripheralInfo *)peripheralInfo {
    NSLog(@"设备已连接");
    [[WPBluetoothManager sharedInstance] queryBatteryLevel];
}

// 4. 接收电量数据
- (void)didReceiveBatteryLevel:(NSInteger)batteryLevel isCharging:(BOOL)isCharging {
    NSLog(@"电量: %ld%%, 充电中: %@", (long)batteryLevel, isCharging ? @"是" : @"否");
}
```

### 完整控制台日志输出

```
✅ 蓝牙已开启
🔍 开始扫描设备
🔍 发现设备: MyWatch [AA:BB:CC:DD:EE:FF] RSSI: -45
✅ 找到目标设备 MyWatch，准备连接
⏹ 停止扫描
✅ 设备连接成功: MyWatch
✅ 已自动设置 currentDevice: MyWatch
🔍 发现服务: 0000FF12-0000-1000-8000-00805F9B34FB
🔍 发现特征: 0000FF01-0000-1000-8000-00805F9B34FB
🔍 发现特征: 0000FF02-0000-1000-8000-00805F9B34FB
🔋 开始查询设备电量
📤 发送指令 [3 bytes]: AB0100
📥 接收指令 [5 bytes]: AB02640101
电量: 100%, 充电中: 是
```

## 🛠 调试技巧

### 技巧 1：过滤日志

使用 Xcode 控制台的过滤功能：
```
搜索: 📤|📥
```
这样只会显示指令相关的日志。

### 技巧 2：对比发送和接收

发送和接收日志会成对出现，便于对比：
```
📤 发送指令 [3 bytes]: AB0100
📥 接收指令 [5 bytes]: AB02640101
```

### 技巧 3：验证协议实现

检查数据格式是否符合协议规范：
- 第 1 个字节：协议头（通常是 `AB`）
- 第 2 个字节：命令类型
- 后续字节：参数和数据
- 最后一个字节：校验位

### 技巧 4：定位问题

1. **设备无响应**
   - 检查是否有 `📤 发送指令` 日志
   - 如果没有，说明数据未发送成功
   - 检查设备连接状态

2. **数据解析错误**
   - 查看 `📥 接收指令` 的原始数据
   - 对照协议文档验证数据格式
   - 检查字节序和数据类型

3. **通信异常**
   - 对比正常情况和异常情况的日志
   - 检查数据长度是否一致
   - 验证校验位是否正确

## 🎨 自定义日志处理

如果需要自定义日志输出格式，可以实现 WPLogger 的代理：

```objc
// 1. 实现 WPLoggerDelegate 协议
@interface MyViewController : UIViewController <WPLoggerDelegate>
@end

// 2. 设置代理
[[WPLogger sharedInstance] setDelegate:self];

// 3. 实现代理方法
- (void)wpLogger:(WPLogger *)logger didLogMessage:(NSString *)message {
    // 自定义处理日志
    if ([message containsString:@"📤"] || [message containsString:@"📥"]) {
        // 保存到数据库、上传到服务器等
        [self saveLogToDatabase:message];
    }
}
```

## ⚠️ 注意事项

### 性能
- 日志输出对性能影响极小（< 1%）
- 在高频数据传输场景下也可以正常使用
- 不会影响蓝牙通信的实时性

### 数据隐私
- 日志包含设备通信的原始数据
- 在生产环境中请注意保护用户隐私
- 建议：
  - 开发环境：保留完整日志
  - 测试环境：保留关键日志
  - 生产环境：根据需要调整级别

### 日志级别控制

```objc
// 如需关闭指令日志，可以设置 WPLogger 的日志级别
// （注：当前版本尚未实现级别控制，计划在后续版本中添加）
```

## 📚 协议参考

### 常见指令码

| 指令 | 十六进制 | 说明 |
|------|---------|------|
| 查询电量 | AB0100 | 查询设备电量和充电状态 |
| 开始心率测量 | AB030001 | 开始连续心率测量 |
| 停止心率测量 | AB030000 | 停止心率测量 |
| 查询最新心率 | AB040000 | 获取最新的心率数据 |
| 开始血氧测量 | AB030101 | 开始血氧测量 |
| 开始血压测量 | AB030201 | 开始血压测量 |

### 响应格式

| 响应类型 | 格式 | 示例 |
|---------|------|------|
| 电量响应 | AB02[电量][充电][校验] | AB02640101 |
| 心率响应 | AB0400[心率][状态][校验] | AB04004B0001 |
| 血氧响应 | AB0401[血氧][状态][校验] | AB04015F0001 |

## 🎯 快速排查清单

遇到问题时，按以下顺序检查：

1. ✅ **检查蓝牙状态**
   - 查看是否有 `✅ 蓝牙已开启` 日志

2. ✅ **检查设备连接**
   - 查看是否有 `✅ 设备连接成功` 日志

3. ✅ **检查指令发送**
   - 查看是否有 `📤 发送指令` 日志
   - 验证发送的数据是否正确

4. ✅ **检查设备响应**
   - 查看是否有 `📥 接收指令` 日志
   - 验证接收的数据格式是否正确

5. ✅ **检查数据解析**
   - 查看是否有对应的回调（如 `didReceiveBatteryLevel:`）
   - 验证解析结果是否符合预期

---

**提示**: 如果遇到问题，请将完整的日志输出发送给技术支持团队，我们会帮助您快速定位问题！
