Pod::Spec.new do |s|
  s.name             = 'WatchFaceSDK'
  s.version          = '1.0.2'
  s.summary          = 'A Swift SDK for smart watch face management and transfer.'
  s.description      = <<-DESC
                       WatchFaceSDK provides comprehensive functionality for uploading and managing custom watch faces.
                       It includes:
                       - Market watch face upload
                       - Custom watch face creation and upload
                       - Intelligent image processing (PAR conversion)
                       - Circle/Square screen adaptation
                       - Real-time transfer progress callbacks
                       - Automatic image compression
                       - Thread-safe design
                       - Works seamlessly with WatchProtocolSDK
                       DESC

  s.homepage         = 'https://github.com/Xiaotengzxf/HuaXinSDK'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'Xiaotengzxf' => '315082431@qq.com' }
  s.source           = { :git => 'https://github.com/Xiaotengzxf/HuaXinSDK.git', :tag => "watchface-v#{s.version}" }

  s.ios.deployment_target = '12.0'
  s.swift_version = '5.0'

  # Use the XCFramework from the versioned directory
  s.vendored_frameworks = 'WatchFaceSDK/v1.0.2/WatchFaceSDK.xcframework'

  s.frameworks = 'Foundation', 'UIKit', 'CoreGraphics'

  # Dependencies
  s.dependency 'WatchProtocolSDK', '~> 1.0.2'
  s.dependency 'SwiftyJSON'
  s.dependency 'CryptoSwift'

end
