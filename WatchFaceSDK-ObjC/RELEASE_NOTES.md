# WatchFaceSDK-ObjC 版本说明

---

## 📦 版本 1.0.0 (2026-01-28)

### 🎉 首次发布

WatchFaceSDK-ObjC 是一个纯 Objective-C 实现的智能手表表盘管理 SDK。

---

## ✨ 核心功能

### 表盘管理
- ✅ **市场表盘上传** - 支持从文件或 NSData 上传预制表盘
- ✅ **自定义表盘上传** - 从用户照片创建个性化表盘
- ✅ **实时进度监控** - 完整的传输进度回调
- ✅ **传输控制** - 支持暂停、取消、重试

### 设备适配
- ✅ **自动屏幕检测** - 自动查询设备屏幕尺寸（方形/圆形）
- ✅ **动态 MTU 协商** - 根据设备 MTU 自动优化传输
- ✅ **连接状态检测** - 实时检查设备连接状态
- ✅ **智能分包传输** - 自动计算最优包大小

### 图片处理
- ✅ **自动格式转换** - 支持 PNG、JPG 等常见格式
- ✅ **智能裁剪压缩** - 自动适配目标尺寸
- ✅ **PAR 格式转换** - 转换为手表专用格式
- ✅ **图片验证** - 自动检查图片有效性

---

## 🏗 技术特性

### 架构设计
- ✅ **纯 Objective-C** - 无 Swift 运行时依赖
- ✅ **动态库实现** - 标准 Framework 集成方式
- ✅ **模块化设计** - 清晰的职责分离
- ✅ **单例模式** - 简化 API 调用

### 集成依赖
- ✅ **WatchProtocolSDK** - 依赖动态库版本
- ✅ **ABParTool** - 图片格式转换（可选）
- ✅ **系统框架** - Foundation, UIKit, CoreGraphics

### 平台支持
- ✅ **iOS 13.0+** - 支持 iOS 13 及以上版本
- ✅ **多架构** - arm64 (设备) + arm64/x86_64 (模拟器)
- ✅ **Xcode 12.0+** - 兼容最新开发工具

---

## 📋 API 列表

### WFManager (主管理器)

#### 单例访问
```objc
+ (instancetype)sharedInstance;
```

#### 设备信息
```objc
- (BOOL)isDeviceConnected;
- (nullable WFDeviceScreenInfo *)getCurrentDeviceScreenInfo;
- (CGSize)getRecommendedImageSize;
```

#### 市场表盘
```objc
- (BOOL)uploadMarketWatchFaceWithData:(NSData *)data
                             delegate:(nullable id<WFTransferDelegate>)delegate
                                error:(NSError **)error;

- (BOOL)uploadMarketWatchFaceWithFileURL:(NSURL *)fileURL
                                delegate:(nullable id<WFTransferDelegate>)delegate
                                   error:(NSError **)error;
```

#### 自定义表盘
```objc
- (BOOL)uploadCustomWatchFaceWithImage:(UIImage *)image
                          timePosition:(WFTimePosition)timePosition
                                 color:(WFDialColor)color
                              delegate:(nullable id<WFTransferDelegate>)delegate
                                 error:(NSError **)error;
```

#### 图片验证
```objc
- (BOOL)validateImage:(UIImage *)image message:(NSString **)message;
```

#### 传输控制
```objc
- (void)pauseTransfer;
- (void)cancelTransfer;
- (void)retryTransfer;
```

---

### WFTransferDelegate (传输代理)

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

### 数据模型

#### WFDeviceScreenInfo
- `width` - 屏幕宽度
- `height` - 屏幕高度
- `shape` - 屏幕形状（方形/圆形）
- `mtu` - 蓝牙 MTU 值

#### WFTransferProgress
- `currentPacket` - 当前包序号
- `totalPackets` - 总包数
- `bytesTransferred` - 已传输字节
- `totalBytes` - 总字节数
- `percentComplete` - 完成百分比 (0-100)

---

### 枚举类型

#### WFTimePosition (时间位置)
```objc
WFTimePositionNone           // 无时间
WFTimePositionTopLeft        // 左上
WFTimePositionTopCenter      // 上中
WFTimePositionTopRight       // 右上
WFTimePositionMiddleLeft     // 中左
WFTimePositionCenter         // 居中
WFTimePositionMiddleRight    // 中右
WFTimePositionBottomLeft     // 左下
WFTimePositionBottomCenter   // 下中
WFTimePositionBottomRight    // 右下
```

#### WFDialColor (表盘颜色)
```objc
WFDialColorWhite   // 白色
WFDialColorBlack   // 黑色
WFDialColorRed     // 红色
WFDialColorGreen   // 绿色
WFDialColorBlue    // 蓝色
WFDialColorYellow  // 黄色
```

#### WFScreenShape (屏幕形状)
```objc
WFScreenShapeSquare = 1  // 方形
WFScreenShapeRound = 2   // 圆形
```

#### WFDialType (表盘类型)
```objc
WFDialTypeMarket = 0   // 市场表盘
WFDialTypeCustom = 1   // 自定义表盘
```

---

## 🔄 内部实现

### 实现细节

#### 设备查询
- 通过 `WPBluetoothManager` 获取当前连接设备
- 从 `WPBluetoothWatchDevice` 读取屏幕参数和 MTU
- 自动识别屏幕形状（方形/圆形）
- 提供默认值处理未连接状态

#### 数据传输
- 查询设备真实 MTU（而非硬编码）
- 发送传输配置（包数、文件大小、MTU 等）
- 分包传输，每包携带进度信息
- 通过 `WPCommands` 发送蓝牙数据包
- 监听传输完成通知，自动发送下一包

#### 自定义表盘
- 设置时间位置和颜色（通过 `WPCommands.setTimePositionAndColor`）
- 将图片转换为 PAR 格式（通过 `ABParTool`）
- 自动裁剪和压缩到目标尺寸
- 限制文件大小（默认 120KB）

---

## 📊 性能指标

| 指标 | 值 |
|------|---|
| **框架大小** | 316 KB |
| **启动开销** | 极低（单例模式） |
| **内存占用** | < 5 MB（传输时） |
| **传输速度** | 取决于 MTU（典型 20-30 KB/s） |
| **支持图片** | PNG, JPG, 最大 10 MB |
| **输出大小** | PAR 格式，约 100-120 KB |

---

## 🐛 已知限制

### 图片处理
- 仅支持 RGB 颜色空间
- 动图（GIF）不支持
- 建议图片尺寸 >= 240x240

### 传输限制
- 同时只能上传一个表盘
- 传输中断需要重新开始（不支持断点续传）
- 依赖设备蓝牙连接稳定性

### 平台限制
- 仅支持 iOS（不支持 macOS、watchOS）
- 需要真机测试（模拟器无蓝牙）

---

## 🔒 安全与隐私

### 数据安全
- ✅ 所有数据通过蓝牙加密传输
- ✅ 不上传用户数据到云端
- ✅ 图片仅在设备本地处理

### 权限要求
- ✅ 蓝牙权限（必需）
- ✅ 相册访问权限（上传自定义表盘时）

---

## 📝 代码示例

### 最小可行代码

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>

@interface MyViewController () <WFTransferDelegate>
@end

@implementation MyViewController

- (void)uploadPhoto {
    UIImage *photo = [UIImage imageNamed:@"my_photo.jpg"];

    WFManager *manager = [WFManager sharedInstance];
    NSError *error = nil;

    BOOL success = [manager uploadCustomWatchFaceWithImage:photo
                                              timePosition:WFTimePositionTopCenter
                                                     color:WFDialColorWhite
                                                  delegate:self
                                                     error:&error];

    if (!success) {
        NSLog(@"上传失败: %@", error.localizedDescription);
    }
}

#pragma mark - WFTransferDelegate

- (void)transferDidUpdateProgress:(WFTransferProgress *)progress {
    NSLog(@"进度: %.1f%%", progress.percentComplete);
}

- (void)transferDidComplete {
    NSLog(@"上传成功！");
}

@end
```

---

## 🆚 与其他版本对比

### WatchFaceSDK-ObjC vs WatchFaceSDK (Swift)

| 特性 | WatchFaceSDK-ObjC | WatchFaceSDK (Swift) |
|------|-------------------|----------------------|
| **语言** | Objective-C | Swift |
| **库类型** | 动态库 | 静态库/动态库 |
| **依赖** | WatchProtocolSDK-ObjC | WatchProtocolSDK-Swift |
| **包大小** | 316 KB | ~800 KB |
| **Swift 运行时** | ❌ 不需要 | ✅ 需要 |
| **向后兼容** | ✅ 优秀 | ⚠️ Swift 版本依赖 |
| **集成难度** | ⭐⭐⭐ 简单 | ⭐⭐⭐⭐ 中等 |

**推荐使用场景**:
- **纯 Objective-C 项目** → WatchFaceSDK-ObjC ✅
- **Swift 项目** → 两者皆可（ObjC 版更稳定）
- **体积敏感** → WatchFaceSDK-ObjC ✅
- **需要最新 Swift 特性** → WatchFaceSDK (Swift)

---

## 🔧 故障排除

### dyld: Library not loaded
**原因**: 动态库未嵌入
**解决**: 设置为 "Embed & Sign"

### Undefined symbols
**原因**: 框架未正确链接
**解决**: 检查框架是否在项目中

### 设备未连接
**原因**: WatchProtocolSDK 未初始化
**解决**: 调用 `[WPBluetoothManager initCentral]`

### 图片验证失败
**原因**: 图片尺寸或格式不符
**解决**: 检查图片尺寸 >= 240x240，格式为 PNG/JPG

更多问题请参考 `README.md` 和 `INTEGRATION_CHECKLIST.md`。

---

## 📚 文档索引

| 文档 | 说明 |
|------|------|
| `README.md` | 完整集成指南和 API 参考 |
| `INTEGRATION_CHECKLIST.md` | 集成检查清单 |
| `RELEASE_NOTES.md` | 本文档 - 版本说明 |

---

## 🚀 快速链接

- **集成指南**: 查看 `README.md`
- **快速开始**: 查看 `README.md` → "🚀 快速开始"
- **API 参考**: 查看 `README.md` → "📖 API 参考"
- **常见问题**: 查看 `README.md` → "❓ 常见问题"
- **集成检查**: 查看 `INTEGRATION_CHECKLIST.md`

---

## 📞 技术支持

**邮箱**: 315082431@qq.com

**提供信息**:
1. Xcode 版本
2. iOS 版本
3. 完整错误日志
4. Framework 配置截图

---

## 📄 许可证

Copyright © 2026 Huaxin. All rights reserved.

---

## 🎉 致谢

感谢 WatchProtocolSDK 团队提供底层蓝牙通信支持。

---

**WatchFaceSDK-ObjC v1.0.0** - 让表盘上传变得简单 🚀
