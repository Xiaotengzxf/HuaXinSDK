# 智能手表 SDK 动态库完整包

**纯 Objective-C 动态库解决方案** | **版本 v1.0** | **发布日期: 2026-01-14**

---

## 🎯 快速导航

### 🚀 我要快速开始
**5 分钟集成** → [QUICK_START.md](QUICK_START.md)

### 📚 我要详细文档
**完整集成指南** → [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)

### 📦 我要了解包内容
**包内容说明** → [PACKAGE_CONTENTS.md](PACKAGE_CONTENTS.md)

### 🔧 我遇到了问题
**故障排查** → [WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查](WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查)

---

## 📦 本包包含

```
Output-ObjC-Dynamic/
│
├── 📱 Framework (动态库)
│   ├── WatchProtocolSDK.xcframework (692KB)     - 蓝牙通信协议 SDK
│   └── WatchFaceSDK_ObjC.xcframework (312KB)    - 表盘管理 SDK
│
└── 📄 文档
    ├── INDEX.md (本文件)                        - 目录导航
    ├── QUICK_START.md                           - 5分钟快速开始
    ├── WATCHFACE_SDK_INTEGRATION_GUIDE.md       - WatchFaceSDK 详细文档
    ├── PACKAGE_CONTENTS.md                      - 包内容说明
    ├── DYNAMIC_LIBRARY_UPDATE.md                - 动态库更新说明
    ├── README.md                                - WatchProtocolSDK 文档
    ├── DYNAMIC_FRAMEWORK_INTEGRATION.md         - 动态库集成说明
    └── LINKER_ERROR_FIX.md                      - 链接错误修复
```

---

## 🎯 根据需求选择文档

### 场景 1: 首次集成

**我是新手，想快速开始**
1. 阅读 [QUICK_START.md](QUICK_START.md)（5 分钟）
2. 按步骤操作
3. 运行示例代码

**我想了解详细信息**
1. 阅读 [PACKAGE_CONTENTS.md](PACKAGE_CONTENTS.md) 了解包内容
2. 阅读 [DYNAMIC_LIBRARY_UPDATE.md](DYNAMIC_LIBRARY_UPDATE.md) 了解更新内容
3. 阅读 [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md) 详细集成

### 场景 2: 只需要蓝牙功能

**我只需要连接设备、读取数据**
→ 阅读 [README.md](README.md)（WatchProtocolSDK 文档）

### 场景 3: 需要表盘功能

**我需要上传/制作表盘**
→ 阅读 [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)

### 场景 4: 遇到问题

**运行时崩溃**
→ [WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查](WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查)

**链接错误**
→ [LINKER_ERROR_FIX.md](LINKER_ERROR_FIX.md)

**动态库加载问题**
→ [DYNAMIC_FRAMEWORK_INTEGRATION.md](DYNAMIC_FRAMEWORK_INTEGRATION.md)

---

## ⚡ 3 分钟快速集成

### 1. 添加 Framework

拖入 Xcode 项目：
```
✅ WatchProtocolSDK.xcframework (本目录)
✅ WatchFaceSDK_ObjC.xcframework (本目录)
✅ ABParTool.xcframework (项目根目录)
```

### 2. 配置嵌入

**Target → General → Frameworks, Libraries, and Embedded Content**

全部设置为 **Embed & Sign**

### 3. 添加权限

Info.plist:
```xml
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>
```

### 4. 使用

```objc
#import <WatchFaceSDK_ObjC/WFManager.h>

WFManager *manager = [WFManager sharedInstance];
[manager uploadCustomWatchFaceWithImage:image
                          timePosition:WFTimePositionTopLeft
                                 color:WFDialColorWhite
                              delegate:self
                                 error:&error];
```

详细步骤请查看 [QUICK_START.md](QUICK_START.md)

---

## 📊 技术规格

### WatchProtocolSDK

| 项目 | 说明 |
|-----|------|
| **功能** | 蓝牙通信协议 |
| **类型** | 动态库 |
| **大小** | 692KB |
| **架构** | arm64, x86_64 (simulator) |
| **iOS** | 13.0+ |
| **语言** | Objective-C |

### WatchFaceSDK_ObjC

| 项目 | 说明 |
|-----|------|
| **功能** | 表盘管理 |
| **类型** | 动态库 |
| **大小** | 312KB |
| **架构** | arm64, x86_64 (simulator) |
| **iOS** | 13.0+ |
| **语言** | Objective-C |
| **依赖** | WatchProtocolSDK, ABParTool |

---

## 🔗 依赖关系

```
App
 ├── WatchFaceSDK_ObjC
 │   ├── → WatchProtocolSDK ✅
 │   └── → ABParTool ✅
 │
 └── WatchProtocolSDK
     └── → 系统框架
```

⚠️ **重要**: 所有依赖的动态库都必须设置为 **Embed & Sign**

---

## ✨ 主要功能

### WatchProtocolSDK 功能

- ✅ 蓝牙设备扫描（支持超时）
- ✅ 设备连接管理
- ✅ 健康数据同步
- ✅ 协议指令处理
- ✅ 数据存储协议化

### WatchFaceSDK_ObjC 功能

- ✅ 市场表盘上传
- ✅ 自定义表盘制作
- ✅ 智能图片处理（裁剪、压缩、RGB565、PAR）
- ✅ 实时传输进度
- ✅ 传输控制（暂停、取消、重试）

---

## 🎓 学习路径

### 初级（快速上手）

1. **快速开始** - [QUICK_START.md](QUICK_START.md) (5 分钟)
2. **运行示例代码** - 见快速开始文档
3. **测试基本功能** - 上传一个表盘

### 中级（深入理解）

1. **更新说明** - [DYNAMIC_LIBRARY_UPDATE.md](DYNAMIC_LIBRARY_UPDATE.md)
2. **详细 API 文档** - [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)
3. **代码示例** - 见集成指南中的示例
4. **错误处理** - 了解各种错误码和处理方法

### 高级（优化和定制）

1. **动态库机制** - [DYNAMIC_FRAMEWORK_INTEGRATION.md](DYNAMIC_FRAMEWORK_INTEGRATION.md)
2. **性能优化** - 了解 MTU、传输速度优化
3. **自定义扩展** - 基于协议扩展功能

---

## ⚠️ 注意事项

### ✅ 正确做法

```objc
// 1. 设置为 Embed & Sign
Target → General → Frameworks → Embed & Sign

// 2. 先连接设备
WPBluetoothManager *btManager = [WPBluetoothManager sharedInstance];
[btManager startScanning:YES];

// 3. 然后使用表盘功能
WFManager *manager = [WFManager sharedInstance];
[manager uploadCustomWatchFace...];
```

### ❌ 错误做法

```objc
// ❌ 不要设置为 Do Not Embed（会崩溃）
// ❌ 不要混用静态库和动态库
// ❌ 不要在设备未连接时使用表盘功能
```

---

## 📞 获取帮助

### 优先级 1: 查看文档

大多数问题可以通过文档解决：
- [QUICK_START.md](QUICK_START.md) - 快速开始
- [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md) - 详细文档
- [故障排查章节](WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查) - 常见问题

### 优先级 2: 检查配置

- [ ] Framework 是否都设置为 Embed & Sign？
- [ ] 是否使用了正确的动态库版本？
- [ ] Info.plist 是否添加了蓝牙权限？
- [ ] 设备是否已连接？

### 优先级 3: 联系技术支持

- **Email**: 315082431@qq.com
- **GitHub Issues**: [提交问题](https://github.com/BruceZhang2017/SmartBracelet/issues)

---

## 📝 版本历史

### v1.0.1 (2026-01-14) - WatchFaceSDK_ObjC

- ✅ 更新为纯动态库架构
- ✅ 使用最新 WatchProtocolSDK
- ✅ API 完全兼容

### v1.0.0 (2026-01-14) - WatchProtocolSDK

- ✅ 发布动态库版本
- ✅ 新增扫描超时功能
- ✅ 优化连接稳定性

---

## 📄 许可证

Copyright © 2026 Anker Innovations. All rights reserved.

---

## 🎉 开始使用

**选择你的起点：**

→ **快速开始**: [QUICK_START.md](QUICK_START.md)

→ **详细文档**: [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)

→ **了解内容**: [PACKAGE_CONTENTS.md](PACKAGE_CONTENTS.md)

**祝您集成顺利！** 🚀
