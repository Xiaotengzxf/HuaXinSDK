# WatchFaceSDK_ObjC 动态库完整包

**欢迎使用 WatchFaceSDK_ObjC 纯动态库解决方案！** 🎉

---

## 📦 本包内容

### Framework (动态库)
```
✅ WatchProtocolSDK.xcframework (692KB)     - 蓝牙通信协议 SDK
✅ WatchFaceSDK_ObjC.xcframework (312KB)    - 表盘管理 SDK
```

### 完整文档集合
```
📖 INDEX.md                                - 📍 从这里开始！主导航文档
📖 QUICK_START.md                          - ⚡ 5分钟快速集成
📖 WATCHFACE_SDK_INTEGRATION_GUIDE.md      - 📚 完整API文档和示例
📖 PACKAGE_CONTENTS.md                     - 📦 包内容详细说明
📖 DYNAMIC_LIBRARY_UPDATE.md               - 🔄 动态库更新和迁移指南
📖 README.md                               - 📘 WatchProtocolSDK文档
📖 DYNAMIC_FRAMEWORK_INTEGRATION.md        - 🔧 动态库集成技术细节
📖 LINKER_ERROR_FIX.md                     - 🔨 链接错误修复指南
```

---

## 🚀 快速开始（3 步）

### 第 1 步：选择你的起点

**新手用户** → 打开 [QUICK_START.md](QUICK_START.md)
- 5 分钟快速集成
- 包含完整示例代码
- 常见错误解决方案

**有经验的开发者** → 打开 [INDEX.md](INDEX.md)
- 快速导航到所需章节
- 场景化文档索引
- 完整学习路径

**需要详细 API 文档** → 打开 [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)
- 完整 API 参考
- Swift 和 Objective-C 示例
- 高级功能详解

### 第 2 步：了解关键信息

⚠️ **极其重要**：动态库必须设置为 **Embed & Sign**
```
Target → General → Frameworks, Libraries, and Embedded Content
→ 所有 Framework 设置为 "Embed & Sign" ✅
```

### 第 3 步：开始集成

参考 [QUICK_START.md](QUICK_START.md) 的 5 步集成流程即可！

---

## 📚 文档使用指南

### 按使用场景选择

| 你的需求 | 推荐文档 |
|---------|---------|
| 🆕 首次使用，快速上手 | [QUICK_START.md](QUICK_START.md) |
| 📖 了解完整功能和 API | [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md) |
| 🔄 从旧版本迁移 | [DYNAMIC_LIBRARY_UPDATE.md](DYNAMIC_LIBRARY_UPDATE.md) |
| 📦 了解包结构和依赖 | [PACKAGE_CONTENTS.md](PACKAGE_CONTENTS.md) |
| 🔧 深入了解动态库机制 | [DYNAMIC_FRAMEWORK_INTEGRATION.md](DYNAMIC_FRAMEWORK_INTEGRATION.md) |
| 🔨 遇到链接错误 | [LINKER_ERROR_FIX.md](LINKER_ERROR_FIX.md) |
| 📘 使用蓝牙通信功能 | [README.md](README.md) |
| 🗺️ 整体导航和学习路径 | [INDEX.md](INDEX.md) |

### 按学习阶段选择

**初级（快速上手）**
1. [QUICK_START.md](QUICK_START.md) - 5 分钟快速集成
2. 运行示例代码
3. 测试基本功能

**中级（深入理解）**
1. [DYNAMIC_LIBRARY_UPDATE.md](DYNAMIC_LIBRARY_UPDATE.md) - 了解更新内容
2. [WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md) - 完整 API
3. [PACKAGE_CONTENTS.md](PACKAGE_CONTENTS.md) - 理解架构

**高级（优化和定制）**
1. [DYNAMIC_FRAMEWORK_INTEGRATION.md](DYNAMIC_FRAMEWORK_INTEGRATION.md) - 动态库原理
2. 性能优化技巧
3. 自定义扩展

---

## ⚡ 最快上手方式

### 5 分钟快速集成

1. **添加 Framework** (1 分钟)
   ```
   拖入项目:
   ✅ WatchProtocolSDK.xcframework
   ✅ WatchFaceSDK_ObjC.xcframework
   ✅ ABParTool.xcframework (项目根目录)
   ```

2. **设置 Embed & Sign** (1 分钟)
   ```
   Target → General → Frameworks
   → 全部设置为 "Embed & Sign"
   ```

3. **添加蓝牙权限** (30 秒)
   ```xml
   Info.plist:
   <key>NSBluetoothAlwaysUsageDescription</key>
   <string>需要使用蓝牙连接智能手表设备</string>
   ```

4. **导入头文件** (10 秒)
   ```objc
   #import <WatchFaceSDK_ObjC/WFManager.h>
   ```

5. **开始使用** (2 分钟)
   ```objc
   WFManager *manager = [WFManager sharedInstance];
   [manager uploadCustomWatchFaceWithImage:image
                              timePosition:WFTimePositionTopLeft
                                     color:WFDialColorWhite
                                  delegate:self
                                     error:&error];
   ```

详细步骤请查看 [QUICK_START.md](QUICK_START.md)

---

## ⚠️ 重要提示

### ✅ 正确做法
- 所有 Framework 设置为 **Embed & Sign**
- 使用 Output-ObjC-Dynamic 目录下的动态库
- 先连接蓝牙设备，再使用表盘功能

### ❌ 错误做法
- ❌ 设置为 Do Not Embed（会崩溃）
- ❌ 混用静态库和动态库
- ❌ 在设备未连接时上传表盘

---

## 🎯 关键功能

### WatchProtocolSDK 功能
- ✅ 蓝牙设备扫描（支持超时）
- ✅ 设备连接管理
- ✅ 健康数据同步
- ✅ 协议指令处理

### WatchFaceSDK_ObjC 功能
- ✅ 市场表盘上传
- ✅ 自定义表盘制作
- ✅ 智能图片处理（裁剪、压缩、RGB565、PAR）
- ✅ 实时传输进度
- ✅ 传输控制（暂停、取消、重试）

---

## 📊 技术规格

| 项目 | WatchProtocolSDK | WatchFaceSDK_ObjC |
|-----|------------------|-------------------|
| **类型** | 动态库 | 动态库 |
| **大小** | 692KB | 312KB |
| **架构** | arm64, x86_64 | arm64, x86_64 |
| **iOS** | 13.0+ | 13.0+ |
| **语言** | Objective-C | Objective-C |

---

## 📞 技术支持

**遇到问题？**
1. 查看 [故障排查章节](WATCHFACE_SDK_INTEGRATION_GUIDE.md#故障排查)
2. 检查 [常见错误](QUICK_START.md#⚠️-常见错误)
3. 阅读 [链接错误修复](LINKER_ERROR_FIX.md)

**需要帮助？**
- Email: 315082431@qq.com
- GitHub: [提交 Issue](https://github.com/BruceZhang2017/SmartBracelet/issues)

---

## 📝 版本信息

| Framework | 版本 | 发布日期 | 类型 |
|-----------|------|---------|------|
| WatchProtocolSDK | v1.0.0 | 2026-01-14 | 动态库 |
| WatchFaceSDK_ObjC | v1.0.1 | 2026-01-14 | 动态库 |

---

## 🎉 开始使用

**推荐阅读顺序：**

1. **本文件** (00-README-FIRST.md) - ✅ 你在这里
2. **[QUICK_START.md](QUICK_START.md)** - 快速上手
3. **[WATCHFACE_SDK_INTEGRATION_GUIDE.md](WATCHFACE_SDK_INTEGRATION_GUIDE.md)** - 深入学习

**或者使用导航文档：**
→ [INDEX.md](INDEX.md) - 完整导航和学习路径

---

**一切准备就绪，开始你的智能手表开发之旅吧！** 🚀
