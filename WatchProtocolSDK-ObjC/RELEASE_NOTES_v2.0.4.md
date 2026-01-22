# WatchProtocolSDK v2.0.4 发布说明

## 发布日期
2026-01-22

## 版本号
v2.0.4

## 更新内容

### 🆕 新功能

#### 指令数据日志打印
- **发送指令日志**：在发送数据到设备时自动打印十六进制格式的指令数据
- **接收指令日志**：在接收设备返回的数据时自动打印十六进制格式的响应数据
- **详细信息**：日志包含数据长度和完整的十六进制字符串

### 📝 日志格式示例

```objc
// 发送指令示例
📤 发送指令 [20 bytes]: AB0101020304050607080910111213141516171819

// 接收指令示例
📥 接收指令 [15 bytes]: AB02640100010203040506070809
```

### 💡 使用场景

1. **调试和开发**
   - 方便开发者查看和分析蓝牙通信的原始数据
   - 快速定位协议解析问题

2. **第三方集成**
   - 第三方 App 集成 SDK 时，可以通过日志了解设备通信细节
   - 便于排查设备连接和数据传输问题

3. **技术支持**
   - 用户遇到问题时，可以提供日志帮助技术支持团队分析问题

### 🔧 实现细节

#### 修改的文件
- `WatchProtocolSDK-ObjC/Core/WPBluetoothManager.m`

#### 关键修改点

**发送数据 (WPBluetoothManager.m:312-336)**
```objc
- (BOOL)sendData:(NSData *)data {
    // ... 连接检查 ...

    // 打印发送给设备的指令数据
    NSString *hexString = [data hexEncodedString];
    [[WPLogger sharedInstance] log:[NSString stringWithFormat:@"📤 发送指令 [%ld bytes]: %@",
                                   (long)data.length, hexString]];

    // ... 数据发送 ...
}
```

**接收数据 (WPBluetoothManager.m:699-721)**
```objc
- (void)peripheral:(CBPeripheral *)peripheral
didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic
             error:(NSError *)error {
    // ... 错误检查 ...

    NSData *data = characteristic.value;
    if (data) {
        // 打印设备返回的指令数据
        NSString *hexString = [data hexEncodedString];
        [[WPLogger sharedInstance] log:[NSString stringWithFormat:@"📥 接收指令 [%ld bytes]: %@",
                                       (long)data.length, hexString]];

        // ... 数据处理 ...
    }
}
```

### 📱 如何查看日志

日志通过 `WPLogger` 输出，第三方 App 可以通过以下方式查看：

1. **Xcode 控制台**
   - 运行 App 时，日志会自动输出到 Xcode 的控制台
   - 搜索 "📤" 或 "📥" 可以快速定位指令日志

2. **WPLogger 代理**
   - 如果需要在 App 中自定义日志处理，可以实现 WPLogger 的代理方法
   - 详见 `WPLogger.h` 文档

### ⚠️ 注意事项

1. **性能影响**
   - 日志输出对性能影响极小，可以放心在生产环境使用
   - 如需关闭日志，可以通过 WPLogger 的配置进行控制

2. **数据隐私**
   - 日志包含设备通信的原始数据
   - 发布 App 时请注意数据隐私保护
   - 建议在生产环境中根据需要调整日志级别

### 🔄 向后兼容性

- ✅ 完全向后兼容 v2.0.0 - v2.0.3
- ✅ 不影响现有 API 和功能
- ✅ 纯新增功能，不破坏现有代码

### 📦 集成方式

无需任何代码修改，直接替换 XCFramework 即可使用新功能：

```bash
# 删除旧版本
rm -rf YourApp/Frameworks/WatchProtocolSDK.xcframework

# 复制新版本
cp -r Output-ObjC-Dynamic/WatchProtocolSDK.xcframework YourApp/Frameworks/

# 清理构建缓存
xcodebuild clean -project YourApp.xcodeproj
```

### 🎯 完整示例

```objc
// 1. 初始化蓝牙管理器
WPBluetoothManager *manager = [WPBluetoothManager sharedInstance];
[manager initCentral];

// 2. 连接设备
[manager connectAndScanWithMac:@"AA:BB:CC:DD:EE:FF"
                    deviceName:@"MyWatch"
                       timeout:10.0];

// 3. 发送指令（会自动打印日志）
NSData *commandData = [NSData dataWithBytes:(uint8_t[]){0xAB, 0x01, 0x00} length:3];
[manager sendData:commandData];
// 控制台输出: 📤 发送指令 [3 bytes]: AB0100

// 4. 接收数据（会自动打印日志）
// 当设备返回数据时，控制台自动输出:
// 📥 接收指令 [5 bytes]: AB02640101
```

## 升级建议

推荐所有用户升级到 v2.0.4，特别是：
- 正在开发和调试蓝牙通信功能的开发者
- 需要技术支持和问题诊断的用户
- 第三方集成商和 SDK 使用者

---

**上一版本**: [v2.0.3](./RELEASE_NOTES_v2.0.3.md)

**问题反馈**: 如有任何问题，请联系技术支持
