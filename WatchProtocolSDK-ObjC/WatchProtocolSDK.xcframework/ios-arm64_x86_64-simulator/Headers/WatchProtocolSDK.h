//
//  WatchProtocolSDK.h
//  WatchProtocolSDK-ObjC
//
//  Created by Claude on 2026/01/12.
//  Copyright © 2026 Huaxin. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for WatchProtocolSDK.
FOUNDATION_EXPORT double WatchProtocolSDKVersionNumber;

//! Project version string for WatchProtocolSDK.
FOUNDATION_EXPORT const unsigned char WatchProtocolSDKVersionString[];

// MARK: - 数据模型
#import <WatchProtocolSDK/WPHealthDataModels.h>
#import <WatchProtocolSDK/WPDeviceModel.h>

// MARK: - 协议
#import <WatchProtocolSDK/WPHealthDataStorage.h>

// MARK: - 核心管理类
#import <WatchProtocolSDK/WPDeviceManager.h>
#import <WatchProtocolSDK/WPBluetoothManager.h>

// MARK: - 工具类
#import <WatchProtocolSDK/WPLogger.h>
