# HuaXinSDK

华歆智能手表 iOS SDK 套件 - 提供完整的智能手表设备通信和表盘管理解决方案

## 📦 SDK 概述

HuaXinSDK 是一套完整的 iOS SDK 套件，用于智能手表设备的蓝牙通信、健康数据同步和表盘管理。本仓库包含以下 SDK：

### 1. WatchProtocolSDK
智能手表协议通信 SDK，提供设备连接、命令处理和健康数据同步功能。

**核心功能：**
- ✅ 蓝牙设备连接与管理
- ✅ 设备命令处理
- ✅ 健康数据同步（步数、睡眠、心率、血氧、血压）
- ✅ 基于协议的数据存储接口
- ✅ 模块化架构设计

**最新版本：** v1.0.2
**文档：** [查看详细文档](WatchProtocolSDK/README.md)

---

### 2. WatchFaceSDK
智能手表表盘管理 SDK，提供表盘上传、自定义和图片处理功能。

**核心功能：**
- ✅ 市场表盘上传
- ✅ 自定义表盘创建与上传
- ✅ 智能图片处理（PAR 转换）
- ✅ 圆形/方形屏幕适配
- ✅ 实时传输进度回调
- ✅ 自动图片压缩优化
- ✅ 线程安全设计

**最新版本：** v1.0.2
**文档：** [查看详细文档](WatchFaceSDK/README.md)

---

## 🚀 快速开始

### 系统要求

- iOS 12.0+
- Xcode 12.0+
- Swift 5.0+
- CocoaPods 1.10.0+

### 安装

#### 使用 CocoaPods（推荐）

在 `Podfile` 中添加：

```ruby
# WatchProtocolSDK - 智能手表协议通信
pod 'WatchProtocolSDK', '~> 1.0.2'

# WatchFaceSDK - 智能手表表盘管理（依赖 WatchProtocolSDK）
pod 'WatchFaceSDK', '~> 1.0.2'

# 依赖库
pod 'SwiftyJSON'
pod 'CryptoSwift'
```

然后运行：
```bash
pod install
```

#### 手动集成

1. 从 [Releases](https://github.com/Xiaotengzxf/HuaXinSDK/releases) 下载最新版本
2. 将对应的 `.xcframework` 文件拖入项目
3. 在 Target -> General -> Frameworks, Libraries, and Embedded Content 中设置为 "Embed & Sign"

---

## 📖 使用示例

### WatchProtocolSDK - 设备连接与数据同步

```swift
import WatchProtocolSDK

// 初始化协议管理器
let protocolManager = WatchProtocolManager.shared

// 连接设备
protocolManager.connect(to: peripheral) { result in
    switch result {
    case .success:
        print("✅ 设备连接成功")

        // 同步健康数据
        protocolManager.syncHealthData { data in
            print("📊 步数: \(data.steps)")
            print("💤 睡眠: \(data.sleepMinutes) 分钟")
            print("❤️ 心率: \(data.heartRate) bpm")
        }

    case .failure(let error):
        print("❌ 连接失败: \(error)")
    }
}
```

### WatchFaceSDK - 上传自定义表盘

```swift
import WatchFaceSDK
import WatchProtocolSDK

class WatchFaceViewController: UIViewController, TransferDelegate {

    func uploadCustomWatchFace() {
        guard let image = UIImage(named: "my_watchface") else { return }

        do {
            try WatchFaceManager.shared.uploadCustomWatchFace(
                image: image,
                timePosition: .center,
                color: .white,
                delegate: self
            )
        } catch {
            print("❌ 上传失败: \(error)")
        }
    }

    // MARK: - TransferDelegate

    func transferDidStart() {
        print("🚀 开始传输表盘")
    }

    func transferDidUpdateProgress(_ progress: TransferProgress) {
        let percentage = Int(progress.percentage * 100)
        print("📊 传输进度: \(percentage)%")
    }

    func transferDidComplete() {
        print("✅ 表盘传输成功")
    }

    func transferDidFail(error: Error) {
        print("❌ 传输失败: \(error.localizedDescription)")
    }
}
```

---

## 📚 详细文档

### WatchProtocolSDK 文档
- [中文接入文档](WatchProtocolSDK/v1.0.2/WatchProtocolSDK-接入文档-中文.md)
- [English Integration Guide](WatchProtocolSDK/v1.0.2/WatchProtocolSDK-Integration-Guide-EN.md)
- [版本历史](WatchProtocolSDK/v1.0.2/VERSION.txt)
- [README](WatchProtocolSDK/README.md)

### WatchFaceSDK 文档
- [中文接入文档](WatchFaceSDK/v1.0.2/WatchFaceSDK-接入文档-中文.md)
- [English Integration Guide](WatchFaceSDK/v1.0.2/WatchFaceSDK-Integration-Guide-EN.md)
- [版本历史](WatchFaceSDK/v1.0.2/VERSION.txt)
- [README](WatchFaceSDK/README.md)

---

## 🔄 版本信息

| SDK | 当前版本 | 发布日期 | 状态 |
|-----|---------|---------|------|
| WatchProtocolSDK | v1.0.2 | 2026-01-10 | ✅ 稳定 |
| WatchFaceSDK | v1.0.2 | 2026-01-11 | ✅ 稳定 |

### 最近更新

#### WatchProtocolSDK v1.0.2 (2026-01-10)
- 🔧 优化蓝牙连接稳定性
- 📊 改进健康数据同步性能
- 🐛 修复已知问题
- 📖 更新文档和示例

#### WatchFaceSDK v1.0.2 (2026-01-11)
- 🔄 与 WatchProtocolSDK v1.0.2 版本同步
- 🚀 增强传输稳定性
- ⚡ 优化图片处理性能
- 📖 更新文档和示例代码

---

## 🏗 架构说明

```
HuaXinSDK
│
├── WatchProtocolSDK         # 协议通信层
│   ├── 蓝牙连接管理
│   ├── 设备命令处理
│   ├── 健康数据同步
│   └── 数据存储接口
│
└── WatchFaceSDK            # 表盘管理层（依赖 WatchProtocolSDK）
    ├── 市场表盘上传
    ├── 自定义表盘创建
    ├── 图片处理与转换
    └── 传输进度管理
```

### SDK 依赖关系

```
WatchFaceSDK
    └── 依赖 WatchProtocolSDK
            ├── SwiftyJSON
            └── CryptoSwift
```

---

## ⚙️ 配置要求

### Info.plist 权限配置

使用 SDK 需要在 `Info.plist` 中添加以下权限：

```xml
<!-- 蓝牙权限 -->
<key>NSBluetoothAlwaysUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>

<key>NSBluetoothPeripheralUsageDescription</key>
<string>需要使用蓝牙连接智能手表设备</string>

<!-- 照片访问权限（仅 WatchFaceSDK 需要）-->
<key>NSPhotoLibraryUsageDescription</key>
<string>需要访问相册选择表盘图片</string>
```

---

## 🔧 故障排除

### 常见问题

#### 1. CocoaPods 安装失败
```bash
# 清理 CocoaPods 缓存
pod cache clean --all
pod deintegrate
pod install
```

#### 2. 蓝牙连接失败
- 确保已在 Info.plist 中添加蓝牙权限
- 检查设备蓝牙是否开启
- 确认设备在可连接范围内

#### 3. 表盘上传失败
- 确保设备已通过 WatchProtocolSDK 连接成功
- 检查图片格式（支持 PNG、JPG）
- 确认图片尺寸满足要求

---

## 📄 许可证

本项目采用 MIT 许可证。详见 [LICENSE](LICENSE) 文件。

---

## 👥 技术支持

如有问题或建议，请通过以下方式联系：

- **Email**: 315082431@qq.com
- **GitHub Issues**: [提交问题](https://github.com/Xiaotengzxf/HuaXinSDK/issues)
- **GitHub**: [https://github.com/Xiaotengzxf/HuaXinSDK](https://github.com/Xiaotengzxf/HuaXinSDK)

---

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request 来帮助改进 SDK。

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

---

## 📊 更新日志

完整的更新日志请查看各 SDK 的 VERSION.txt 文件：
- [WatchProtocolSDK 更新日志](WatchProtocolSDK/v1.0.2/VERSION.txt)
- [WatchFaceSDK 更新日志](WatchFaceSDK/v1.0.2/VERSION.txt)

---

**© 2025-2026. All Rights Reserved.**
