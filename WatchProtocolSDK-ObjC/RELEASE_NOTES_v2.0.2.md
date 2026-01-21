# WatchProtocolSDK-ObjC v2.0.2 发布说明

📅 **发布日期**: 2026-01-21
🎯 **版本**: v2.0.2
🏷 **类型**: Bug Fix Release

---

## 🐛 修复的问题

### 问题 1: 自动重连失败 (Critical)

**症状**:
- 用户按使用指南执行自动重连
- 打开 app 后开始扫描
- 没有任何连接结果或错误提示

**根因**:
1. UUID 大小写不匹配导致设备无法识别
2. 扫描超时后没有回调通知用户

**修复**:
- ✅ 统一 UUID 为大写,避免大小写匹配问题
- ✅ 新增 `didScanTimeout:` 代理方法,扫描超时时通知用户
- ✅ 改进日志输出,便于排查问题

---

## 🆕 新增功能

### 1. 扫描超时回调 (New Delegate Method)

```objc
@protocol WPBluetoothManagerDelegate <NSObject>

@optional

// 🆕 v2.0.2: 扫描超时回调
- (void)didScanTimeout:(NSString *)macAddress;

@end
```

**使用示例**:
```objc
- (void)didScanTimeout:(NSString *)macAddress {
    NSLog(@"⏰ 扫描超时，未找到设备: %@", macAddress);

    // 提示用户
    UIAlertController *alert = [UIAlertController
        alertControllerWithTitle:@"连接失败"
        message:@"未找到目标设备。请确保设备已开启且在蓝牙范围内。"
        preferredStyle:UIAlertControllerStyleAlert];
    [alert addAction:[UIAlertAction actionWithTitle:@"确定"
                                              style:UIAlertActionStyleDefault
                                            handler:nil]];
    [self presentViewController:alert animated:YES completion:nil];
}
```

### 2. 改进的设备匹配逻辑

- 所有 UUID 统一转换为大写进行匹配
- 兼容旧版本保存的小写 UUID
- 更健壮的设备识别机制

---

## 📝 升级指南

### 方式 1: 替换 Framework (推荐)

1. **删除旧版本**
   - 在 Xcode 中移除旧的 `WatchProtocolSDK.xcframework`
   - 选中后按 Delete 键，选择 "Move to Trash"

2. **添加新版本**
   - 将新的 `WatchProtocolSDK.xcframework` 拖入项目
   - 确保 Embed 设置为 **"Embed & Sign"**

3. **清理并重新编译**
   ```bash
   # 清理 DerivedData
   rm -rf ~/Library/Developer/Xcode/DerivedData/*
   ```
   - Product → Clean Build Folder (⇧⌘K)
   - Product → Build (⌘B)

### 方式 2: 使用 Git 更新

```bash
# 如果你的项目使用 Git 管理 Framework
git pull origin main
```

---

## ⚠️ 破坏性变更

**无破坏性变更** ✅

- 新增的 `didScanTimeout:` 方法为 `@optional`,不实现也不影响现有功能
- UUID 大小写修复向后兼容
- 所有现有 API 保持不变

---

## 🎯 推荐操作

### 1. 实现超时回调 (强烈推荐)

虽然 `didScanTimeout:` 是可选的,但**强烈建议**实现该方法,以提升用户体验:

```objc
- (void)didScanTimeout:(NSString *)macAddress {
    // 选项 A: 自动重试
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 3 * NSEC_PER_SEC),
                   dispatch_get_main_queue(), ^{
        [[WPBluetoothManager sharedInstance] connectAndScanWithMac:macAddress
                                                         deviceName:@""
                                                            timeout:10.0];
    });

    // 选项 B: 提示用户手动重试
    // [显示提示对话框]
}
```

### 2. 调整扫描超时时间 (可选)

如果设备较远或蓝牙信号弱,可以增加扫描超时时间:

```objc
// 默认 10 秒
[[WPBluetoothManager sharedInstance] connectAndScanWithMac:mac
                                                 deviceName:name
                                                    timeout:10.0];

// 增加到 20 秒
[[WPBluetoothManager sharedInstance] connectAndScanWithMac:mac
                                                 deviceName:name
                                                    timeout:20.0];
```

---

## 📊 改进的日志输出

现在你会看到更详细的日志:

**成功连接**:
```
✅ 蓝牙已开启
🔍 开始扫描目标设备: e watch (457E5B71-DB8B-B7A9-9B0B-B33329B39AD9)
🔍 发现设备: e watch [457E5B71-DB8B-B7A9-9B0B-B33329B39AD9]
✅ 找到目标设备 e watch，准备连接
⏹ 停止扫描
📱 连接指定的蓝牙设备: e watch
✅ 设备连接成功: e watch
```

**扫描超时**:
```
✅ 蓝牙已开启
🔍 开始扫描目标设备: e watch (457E5B71-DB8B-B7A9-9B0B-B33329B39AD9)
🔍 发现设备: Other Device [123ABC...]
⏰ 扫描超时，停止扫描
⚠️ 未找到目标设备: 457E5B71-DB8B-B7A9-9B0B-B33329B39AD9
```

---

## 🧪 测试建议

### 测试场景 1: 正常连接
1. 确保设备在蓝牙范围内
2. 打开 app 执行自动重连
3. 应该能看到完整的连接日志
4. 连接成功

### 测试场景 2: 扫描超时
1. 关闭设备或将设备移出蓝牙范围
2. 打开 app 执行自动重连
3. 应该在 10 秒后收到 `didScanTimeout:` 回调
4. 日志显示 "未找到目标设备"

### 测试场景 3: UUID 兼容性
1. 使用旧版本保存的设备 UUID
2. 升级到 v2.0.2
3. 应该能正常识别和连接设备

---

## 📦 Framework 信息

- **大小**: 832 KB
- **架构**: arm64 (iOS 设备), arm64 + x86_64 (模拟器)
- **最低系统要求**: iOS 13.0+
- **依赖**: CoreBluetooth, Foundation (无第三方依赖)
- **语言**: 纯 Objective-C (无 Swift 运行时依赖)

---

## 🔗 相关文档

- **完整修复说明**: [BUGFIX_v2.0.2.md](../../WatchProtocolSDK-ObjC/BUGFIX_v2.0.2.md)
- **集成指南**: [DYNAMIC_FRAMEWORK_INTEGRATION.md](./DYNAMIC_FRAMEWORK_INTEGRATION.md)
- **链接错误修复**: [LINKER_ERROR_FIX.md](./LINKER_ERROR_FIX.md)
- **API 文档**: [README.md](./README.md)

---

## 📞 技术支持

如有问题,请联系: **315082431@qq.com**

提供问题时,请附上:
1. Xcode 版本: `xcodebuild -version`
2. 完整错误信息或日志
3. 使用的 Framework 版本

---

## 🎉 致谢

感谢所有提供反馈的用户！你们的反馈帮助我们持续改进 SDK。

---

**版本历史**:
- v2.0.2 (2026-01-21) - 🐛 修复自动重连问题,新增超时回调
- v2.0.1 (2026-01-19) - ✨ 新增健康数据查询功能
- v2.0.0 (2026-01-12) - 🎉 初始版本发布
