# Output-ObjC-Dynamic 包内容说明

**纯 Objective-C 动态库完整包**

---

## 📦 包含的 Framework

### 1. WatchProtocolSDK.xcframework ⭐

**功能**: 智能手表蓝牙通信协议 SDK

**类型**: 动态库 (Dynamic Framework)

**大小**: ~600KB

**架构支持**:
- `ios-arm64` (真机)
- `ios-arm64_x86_64-simulator` (模拟器)

**主要功能**:
- ✅ 蓝牙设备扫描和连接
- ✅ 设备管理（配对、断开、重连）
- ✅ 健康数据同步（步数、睡眠、心率等）
- ✅ 协议指令处理
- ✅ 数据存储协议化

**文档**: [README.md](README.md)

---

### 2. WatchFaceSDK_ObjC.xcframework ⭐

**功能**: 智能手表表盘管理 SDK

**类型**: 动态库 (Dynamic Framework)

**大小**: 312KB

**架构支持**:
- `ios-arm64` (真机)
- `ios-arm64_x86_64-simulator` (模拟器)

**主要功能**:
- ✅ 市场表盘上传
- ✅ 自定义表盘制作
- ✅ 图片智能处理（裁剪、压缩、格式转换）
- ✅ 实时传输进度监控
- ✅ 传输控制（暂停、取消、重试）

**依赖**: WatchProtocolSDK, ABParTool

**文档**: [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)

---

## 📄 文档清单

### 核心文档

| 文档 | 说明 | 适用对象 |
|-----|------|---------|
| **QUICK_START.md** | 5 分钟快速开始 | 所有开发者（推荐首先阅读） |
| **WATCHFACE_SDK_INTEGRATION_GUIDE.md** | WatchFaceSDK 详细集成指南 | 使用表盘功能的开发者 |
| **README.md** | WatchProtocolSDK 详细文档 | 使用蓝牙通信功能的开发者 |
| **PACKAGE_CONTENTS.md** | 本文件（包内容说明） | 了解整体架构 |

### 技术文档

| 文档 | 说明 |
|-----|------|
| **DYNAMIC_FRAMEWORK_INTEGRATION.md** | 动态库集成说明 |
| **LINKER_ERROR_FIX.md** | 链接错误修复指南 |

---

## 🔗 依赖关系

```
WatchFaceSDK_ObjC.framework
├── 依赖 → WatchProtocolSDK.framework (本包包含)
└── 依赖 → ABParTool.framework (需要单独获取)

WatchProtocolSDK.framework
└── 依赖 → 系统框架 (CoreBluetooth, Foundation 等)
```

---

## 📐 架构概览

### 动态库加载链

```
YourApp
  │
  ├── WatchFaceSDK_ObjC.framework (动态加载)
  │     │
  │     ├── WatchProtocolSDK.framework (运行时依赖)
  │     └── ABParTool.framework (运行时依赖)
  │
  └── WatchProtocolSDK.framework (也可以直接使用)
```

### 使用场景

**场景 1: 只需要蓝牙通信功能**
```
仅集成: WatchProtocolSDK.xcframework
```

**场景 2: 需要表盘管理功能**
```
必须集成:
  - WatchFaceSDK_ObjC.xcframework
  - WatchProtocolSDK.xcframework (依赖)
  - ABParTool.xcframework (依赖)
```

**场景 3: 完整功能**
```
集成全部:
  - WatchProtocolSDK.xcframework (蓝牙通信)
  - WatchFaceSDK_ObjC.xcframework (表盘管理)
  - ABParTool.xcframework (工具库)
```

---

## ⚙️ 集成检查清单

### ✅ Framework 添加

- [ ] WatchProtocolSDK.xcframework 已添加到项目
- [ ] WatchFaceSDK_ObjC.xcframework 已添加到项目（如需表盘功能）
- [ ] ABParTool.xcframework 已添加到项目（如需表盘功能）

### ✅ Embed 配置

- [ ] 所有 Framework 设置为 **Embed & Sign**
- [ ] 验证 Build Phases → Embed Frameworks 中包含所有 Framework

### ✅ Build Settings

- [ ] Framework Search Paths 已配置
- [ ] Enable Bitcode 设置为 NO（如果使用了不支持 Bitcode 的库）

### ✅ 权限配置

- [ ] Info.plist 已添加蓝牙权限描述
- [ ] 如需后台传输，已添加 Background Modes

### ✅ 导入头文件

- [ ] Objective-C: 已导入 `<WatchProtocolSDK/WatchProtocolSDK.h>`
- [ ] Objective-C: 已导入 `<WatchFaceSDK_ObjC/WFManager.h>`（如需）
- [ ] Swift: Bridging Header 已配置

---

## 🎯 快速决策

### 你需要什么功能？

**只需要连接设备、读取健康数据？**
→ 只集成 **WatchProtocolSDK**
→ 阅读 [README.md](README.md)

**需要上传表盘、制作表盘？**
→ 集成 **WatchFaceSDK_ObjC + 依赖**
→ 阅读 [QUICK_START.md](QUICK_START.md)

**需要完整功能？**
→ 集成**所有 Framework**
→ 先阅读 [QUICK_START.md](QUICK_START.md)，再查看详细文档

---

## 📊 版本信息

| Framework | 版本 | 发布日期 | 类型 |
|-----------|------|---------|------|
| WatchProtocolSDK | v1.0.0 | 2026-01-14 | 动态库 |
| WatchFaceSDK_ObjC | v1.0.1 | 2026-01-14 | 动态库 |

---

## 🔄 更新日志

### 2026-01-14

**WatchProtocolSDK v1.0.0**
- ✅ 发布动态库版本
- ✅ 新增扫描超时功能
- ✅ 优化蓝牙连接稳定性

**WatchFaceSDK_ObjC v1.0.1**
- ✅ 更新为纯动态库架构
- ✅ 使用最新 WatchProtocolSDK 动态库
- ✅ 保持 API 完全兼容

---

## ⚠️ 重要提示

### 1. 必须使用动态库版本

本包中的 Framework 都是**动态库**，必须设置为 **Embed & Sign**。

### 2. 不要混用静态库和动态库

如果你之前使用了静态库版本（Output-ObjC），请完全移除后再使用本包。

### 3. ABParTool 位置

ABParTool.xcframework 不在本包中，位于项目根目录：
```
SmartBracelet/ABParTool.xcframework
```

### 4. 运行时依赖

所有依赖的动态库必须在运行时可用，否则会崩溃：
```
dyld: Library not loaded: @rpath/WatchProtocolSDK.framework/WatchProtocolSDK
```

---

## 📞 技术支持

- **Email**: 315082431@qq.com
- **GitHub Issues**: [提交问题](https://github.com/BruceZhang2017/SmartBracelet/issues)

---

## 📝 许可证

Copyright © 2026 Anker Innovations. All rights reserved.

---

**完整的纯 Objective-C 动态库解决方案！** 🎉
