# WatchProtocolSDK-ObjC Framework 版本信息

## 📦 版本详情

**版本号**: v1.0.0
**构建日期**: 2026-01-13
**开发语言**: Objective-C
**最低支持**: iOS 13.0+

---

## 🏗 架构支持

### iOS 设备版本 (ios-arm64)
- ✅ **arm64** - iPhone 6s 及更新设备

### iOS 模拟器版本 (ios-arm64_x86_64-simulator)
- ✅ **arm64** - Apple Silicon Mac 模拟器
- ✅ **x86_64** - Intel Mac 模拟器

---

## 📊 Framework 信息

| 项目 | 值 |
|------|-----|
| Framework 名称 | WatchProtocolSDK.xcframework |
| 包大小 | ~952 KB |
| 静态库类型 | Static Library (.a) |
| 模块支持 | ✅ 支持模块化导入 |
| Bitcode | ⚠️ 不包含（iOS 14+ 已废弃） |

---

## 📋 包含的模块

### Core (核心管理类)
- `WPDeviceManager` - 设备管理器
- `WPBluetoothManager` - 蓝牙管理器

### Models (数据模型)
- `WPHealthDataModels` - 健康数据模型
- `WPDeviceModel` - 设备信息模型

### Protocols (协议定义)
- `WPHealthDataStorage` - 数据存储协议

### Utils (工具类)
- `WPLogger` - 日志系统

---

## 🔍 验证信息

### 设备版本静态库
```bash
$ lipo -info ios-arm64/libWatchProtocolSDK-device.a
Non-fat file: ios-arm64/libWatchProtocolSDK-device.a is architecture: arm64
```

### 模拟器版本静态库
```bash
$ lipo -info ios-arm64_x86_64-simulator/libWatchProtocolSDK-simulator.a
Architectures in the fat file: ios-arm64_x86_64-simulator/libWatchProtocolSDK-simulator.a are: arm64 x86_64
```

---

## 📝 更新日志

### v1.0.0 (2026-01-13)
- ✅ 首次发布
- ✅ 完整的设备管理功能
- ✅ 蓝牙连接管理
- ✅ 健康数据存储协议
- ✅ 线程安全的日志系统
- ✅ 支持 iOS 设备和模拟器（多架构）

---

## 🎯 下一步

1. **集成到项目**
   - 查看 `INTEGRATION_GUIDE.md` 获取详细集成步骤

2. **学习使用**
   - 查看 `README.md` 获取完整 API 文档
   - 参考示例代码快速上手

3. **反馈问题**
   - 邮箱：315082431@qq.com

---

## 📄 相关文件

- `WatchProtocolSDK.xcframework` - Framework 主文件
- `README.md` - API 文档
- `INTEGRATION_GUIDE.md` - 集成指南
- `WatchProtocolSDK-ObjC.podspec` - CocoaPods 配置
- `VERSION_INFO.md` - 本文件

---

## ⚖️ 许可证

MIT License

Copyright (c) 2026 Huaxin Technology

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
