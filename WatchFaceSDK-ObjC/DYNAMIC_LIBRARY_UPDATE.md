# WatchFaceSDK_ObjC 动态库更新说明

## 📅 更新日期
2026-01-14

## 🎯 更新概述

WatchFaceSDK_ObjC 已成功更新为**纯动态库**版本，并使用最新的 **WatchProtocolSDK 动态库**。

---

## ✅ 更新内容

### 1. 库类型确认
```
✅ WatchFaceSDK_ObjC.xcframework - 动态库 (Dynamically Linked Shared Library)
✅ 依赖 WatchProtocolSDK 动态库 (Output-ObjC-Dynamic)
✅ 依赖 ABParTool 动态库
```

### 2. 架构支持
- **iOS Device**: arm64
- **iOS Simulator**: arm64 + x86_64 (支持 M1/M2 Mac 和 Intel Mac)

### 3. 动态库依赖关系
```bash
WatchFaceSDK_ObjC.framework
├── @rpath/WatchProtocolSDK.framework/WatchProtocolSDK
└── @rpath/ABParTool.framework/ABParTool
```

### 4. Framework 大小
```
312KB - 合理的动态库大小
```

---

## 🔄 与之前版本的区别

### 旧版本 (静态链接)
```
- 使用 Output-ObjC/WatchProtocolSDK.xcframework (静态库)
- 链接 libWatchProtocolSDK-device.a 和 libWatchProtocolSDK-simulator.a
- WatchProtocolSDK 代码被静态链接到 WatchFaceSDK_ObjC 中
```

### 新版本 (动态链接) ✅
```
- 使用 Output-ObjC-Dynamic/WatchProtocolSDK.xcframework (动态库)
- 动态链接 WatchProtocolSDK.framework
- WatchProtocolSDK 作为独立的动态库运行时加载
```

---

## 📊 WatchProtocolSDK Header 更新分析

### Header 文件对比结果
| Header 文件 | 状态 | 说明 |
|------------|------|------|
| WatchProtocolSDK.h | ✅ 无变化 | 主头文件 |
| **WPBluetoothManager.h** | ⚠️ **26行差异** | 新增扫描超时功能 |
| WPDeviceManager.h | ✅ 无变化 | 设备管理 |
| WPDeviceModel.h | ✅ 无变化 | 设备模型 |
| WPHealthDataModels.h | ✅ 无变化 | 健康数据模型 |
| WPHealthDataStorage.h | ✅ 无变化 | 数据存储协议 |
| WPLogger.h | ✅ 无变化 | 日志系统 |

### WPBluetoothManager.h 新增功能
```objc
// 新增属性
@property (nonatomic, assign) NSTimeInterval scanTimeout;

// 新增方法
- (void)startScanning:(BOOL)deleteCache timeout:(NSTimeInterval)timeout;
- (void)connectAndScanWithMac:(NSString *)macAddress
                   deviceName:(NSString *)deviceName
                      timeout:(NSTimeInterval)timeout;
```

### 影响评估
✅ **无影响** - WatchFaceSDK-Pure-ObjC 源代码中**没有使用** WPBluetoothManager 相关类，因此 header 更新不影响 WatchFaceSDK 的功能。

---

## 📦 集成方式

### 方式一：手动集成 XCFramework（推荐）

#### 1. 添加所需 Framework
将以下 Framework 拖入 Xcode 项目：

```
WatchFaceSDK_ObjC.xcframework      (主 SDK)
WatchProtocolSDK.xcframework       (依赖 - 来自 Output-ObjC-Dynamic)
ABParTool.xcframework              (依赖)
```

#### 2. 配置 Xcode 项目
在 **Target** → **General** → **Frameworks, Libraries, and Embedded Content** 中：

- ✅ 将**所有** Framework 设置为 **Embed & Sign**（动态库必须嵌入）

#### 3. 配置 Build Settings
在 **Build Settings** 中添加：

```
Framework Search Paths: $(PROJECT_DIR)/Frameworks
```

#### 4. 运行时依赖
确保 app bundle 中包含以下动态库：
```
YourApp.app/
└── Frameworks/
    ├── WatchFaceSDK_ObjC.framework
    ├── WatchProtocolSDK.framework  ← 必须包含
    └── ABParTool.framework         ← 必须包含
```

---

## ⚠️ 重要注意事项

### 1. 动态库嵌入
**必须**将所有依赖的动态库设置为 **Embed & Sign**，否则运行时会报错：
```
dyld: Library not loaded: @rpath/WatchProtocolSDK.framework/WatchProtocolSDK
Reason: image not found
```

### 2. 与静态库版本的兼容性
- 新版本 WatchFaceSDK_ObjC 是动态库，与旧版本不兼容
- 如果项目中已集成旧版本，需要：
  1. 删除旧的 WatchFaceSDK_ObjC.xcframework
  2. 删除旧的 WatchProtocolSDK.xcframework (来自 Output-ObjC)
  3. 重新添加新版本的所有 Framework

### 3. WatchProtocolSDK 版本
确保使用的是 **Output-ObjC-Dynamic** 目录下的 WatchProtocolSDK.xcframework，而不是 Output-ObjC 目录下的静态库版本。

### 4. 代码兼容性
✅ API 接口**完全兼容**，无需修改任何代码。

---

## 🔨 重新构建

如果需要重新构建 WatchFaceSDK_ObjC 动态库，运行：

```bash
./build_watchface_dynamic.sh
```

**构建要求：**
- Xcode 12.0+
- macOS 10.15+
- 预先构建 Output-ObjC-Dynamic/WatchProtocolSDK.xcframework

---

## 📞 技术支持

如有问题，请联系：
- **Email**: 315082431@qq.com
- **GitHub Issues**: [提交问题](https://github.com/BruceZhang2017/SmartBracelet/issues)

---

## 📝 版本历史

### v1.0.1 (2026-01-14)
- ✅ 更新为纯动态库架构
- ✅ 使用最新 WatchProtocolSDK 动态库
- ✅ 支持最新的扫描超时功能（通过 WatchProtocolSDK）
- ✅ 保持 API 完全兼容

### v1.0.0 (2026-01-13)
- ✅ 首次发布（静态链接版本）

---

**构建成功！** 🎉
