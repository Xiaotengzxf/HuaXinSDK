# WatchFaceSDK

A comprehensive iOS SDK for smart watch face management and transfer.

## Overview

WatchFaceSDK provides functionality for uploading and managing custom watch faces for smart watches. It works seamlessly with WatchProtocolSDK to handle watch face image processing, transfer, and installation.

## Features

- ✅ Market watch face upload
- ✅ Custom watch face creation and upload
- ✅ Intelligent image processing (PAR conversion)
- ✅ Circle/Square screen adaptation
- ✅ Real-time transfer progress callbacks
- ✅ Automatic image compression
- ✅ Thread-safe design
- ✅ Comprehensive error handling

## Requirements

- iOS 12.0+
- Xcode 12.0+
- Swift 5.0+
- WatchProtocolSDK v1.0.2+

## Installation

### CocoaPods

Add to your `Podfile`:

```ruby
pod 'WatchFaceSDK', '~> 1.0.2'
```

Then run:
```bash
pod install
```

### Manual Integration

1. Download the latest release from the releases page
2. Drag `WatchFaceSDK.xcframework` into your Xcode project
3. In Target -> General -> Frameworks, Libraries, and Embedded Content, set to "Embed & Sign"

## Quick Start

### Import the SDK

```swift
import WatchFaceSDK
import WatchProtocolSDK
```

### Upload Custom Watch Face

```swift
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
            print("❌ Upload failed: \(error)")
        }
    }

    // MARK: - TransferDelegate

    func transferDidStart() {
        print("🚀 Transfer started")
    }

    func transferDidUpdateProgress(_ progress: TransferProgress) {
        print("📊 Progress: \(Int(progress.percentage * 100))%")
    }

    func transferDidComplete() {
        print("✅ Transfer completed")
    }

    func transferDidFail(error: Error) {
        print("❌ Transfer failed: \(error)")
    }
}
```

## Documentation

- [中文接入文档](v1.0.2/WatchFaceSDK-接入文档-中文.md)
- [English Integration Guide](v1.0.2/WatchFaceSDK-Integration-Guide-EN.md)
- [Version History](v1.0.2/VERSION.txt)

## Version History

### v1.0.2 (2026-01-11)
- Synchronized version with WatchProtocolSDK v1.0.2
- Enhanced transfer stability
- Improved image processing performance
- Updated documentation and examples

See [VERSION.txt](v1.0.2/VERSION.txt) for complete release notes.

## Dependencies

- WatchProtocolSDK v1.0.2+
- SwiftyJSON
- CryptoSwift

## License

WatchFaceSDK is available under the MIT license. See the [LICENSE](LICENSE) file for more info.

## Support

For issues and questions:
- Email: 315082431@qq.com
- GitHub: [https://github.com/Xiaotengzxf/HuaXinSDK](https://github.com/Xiaotengzxf/HuaXinSDK)

---

**© 2025-2026. All Rights Reserved.**
