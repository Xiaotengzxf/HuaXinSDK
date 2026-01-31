//
//  WPCommands+SwitchTableExtension.h
//  WatchProtocolSDK-ObjC
//
//  Created by Claude on 2026/01/31.
//  Copyright © 2026 Huaxin. All rights reserved.
//
//  🎯 功能：开关表扩展功能增强（应用通知开关管理）
//  ✨ 新增内容：
//    - 带完成回调的查询方法
//    - 带完成回调的设置方法
//    - 连接状态检查
//    - 错误处理机制
//

#import "WPCommands.h"

@class WPBluetoothWatchDevice;

NS_ASSUME_NONNULL_BEGIN

// MARK: - 完成回调

/**
 * 开关表扩展完成回调（查询场景）
 * @param success 是否成功（YES: 查询成功，NO: 查询失败）
 * @param p0 P0 字节（包含第一组通知开关）
 * @param p1 P1 字节（包含第二组通知开关）
 * @param p2 P2 字节（包含第三组通知开关）
 * @param p3 P3 字节（包含第四组通知开关）
 * @param error 错误信息（success=NO 时有值）
 *
 * @note 各字节位定义详见 handleSwitchTableExtensionResponse 方法注释
 */
typedef void(^WPSwitchTableExtensionQueryCompletion)(BOOL success, uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, NSError * _Nullable error);

/**
 * 开关表扩展完成回调（设置场景）
 * @param success 是否成功（YES: 设置成功，NO: 设置失败）
 * @param error 错误信息（success=NO 时有值）
 */
typedef void(^WPSwitchTableExtensionSetCompletion)(BOOL success, NSError * _Nullable error);

// MARK: - WPCommands 开关表扩展

@interface WPCommands (SwitchTableExtension)

// MARK: - 🔥 推荐使用的方法

/**
 * 查询开关表扩展（带完成回调）
 * @param completion 完成回调
 *
 * @discussion
 * 查询设备的所有应用通知开关状态（如微信、QQ、Facebook 等）。
 * 此方法会自动检查蓝牙连接状态，避免在未连接时发送无效指令。
 *
 * @note 使用示例:
 * ```objc
 * [WPCommands getSwitchTableExtensionWithCompletion:^(BOOL success, uint8_t p0, uint8_t p1, uint8_t p2, uint8_t p3, NSError *error) {
 *     if (success) {
 *         // 解析微信开关状态（P1 的 bit 1）
 *         BOOL wechatEnabled = ((p1 >> 1) & 1) > 0;
 *         NSLog(@"微信通知: %@", wechatEnabled ? @"开启" : @"关闭");
 *
 *         // 解析来电提醒（P0 的 bit 1）
 *         BOOL callEnabled = ((p0 >> 1) & 1) > 0;
 *         NSLog(@"来电提醒: %@", callEnabled ? @"开启" : @"关闭");
 *     } else {
 *         NSLog(@"查询失败: %@", error.localizedDescription);
 *     }
 * }];
 * ```
 *
 * @warning 如果设备未连接，completion 会返回 success=NO 和相应错误
 * @note 查询结果也会自动更新到 currentDevice 的相关属性（如 isWechat、isFacebook 等）
 * @note 查询结果也会触发代理回调 didReceiveSwitchTableExtension:p1:p2:p3:
 */
+ (void)getSwitchTableExtensionWithCompletion:(nullable WPSwitchTableExtensionQueryCompletion)completion;

/**
 * 设置开关表扩展（带完成回调）
 * @param p0 P0 字节（包含第一组通知开关：空消息、来电、未接来电、短信、邮件、日程、FaceTime、QQ）
 * @param p1 P1 字节（包含第二组通知开关：Skype、微信、WhatsApp、Gmail、Hangout、Inbox、Line、Twitter）
 * @param p2 P2 字节（包含第三组通知开关：Facebook、Facebook Messenger、Instagram、微博、KakaoTalk、Facebook Page Manager、Viber、VK Client）
 * @param p3 P3 字节（包含第四组通知开关：Telegram、Snapchat、钉钉、支付宝、TikTok、LinkedIn）
 * @param completion 完成回调
 *
 * @discussion
 * 设置设备的应用通知开关状态。每个字节包含 8 个开关位（P3 只使用 6 个）。
 * 此方法会自动检查蓝牙连接状态，避免在未连接时发送无效指令。
 *
 * @note 使用示例:
 * ```objc
 * // 从当前设备读取开关状态
 * WPBluetoothWatchDevice *device = [WPBluetoothManager sharedInstance].currentDevice;
 *
 * // 修改微信通知开关（P1 的 bit 1）
 * device.isWechat = YES;
 *
 * // 重新计算 P1 字节
 * uint8_t p1 = 0;
 * p1 |= device.isSkype ? (1 << 0) : 0;
 * p1 |= device.isWechat ? (1 << 1) : 0;  // 微信
 * p1 |= device.isWhatsapp ? (1 << 2) : 0;
 * // ... 其他位
 *
 * // 调用设置方法（其他字节保持不变）
 * [WPCommands setSwitchTableExtensionWithP0:p0 p1:p1 p2:p2 p3:p3 completion:^(BOOL success, NSError *error) {
 *     if (success) {
 *         NSLog(@"✅ 设置成功");
 *     } else {
 *         NSLog(@"❌ 设置失败: %@", error.localizedDescription);
 *     }
 * }];
 * ```
 *
 * @warning 如果设备未连接，completion 会返回 success=NO 和相应错误
 * @note 设置成功后，建议重新查询以确认设置生效
 */
+ (void)setSwitchTableExtensionWithP0:(uint8_t)p0
                                   p1:(uint8_t)p1
                                   p2:(uint8_t)p2
                                   p3:(uint8_t)p3
                           completion:(nullable WPSwitchTableExtensionSetCompletion)completion;

// MARK: - 辅助方法

/**
 * 从设备对象计算 P0 字节
 * @param device 设备对象
 * @return P0 字节值
 *
 * @discussion
 * 根据设备对象的通知开关属性，计算出 P0 字节的值。
 * 方便在设置开关时使用。
 */
+ (uint8_t)calculateP0FromDevice:(WPBluetoothWatchDevice *)device;

/**
 * 从设备对象计算 P1 字节
 * @param device 设备对象
 * @return P1 字节值
 */
+ (uint8_t)calculateP1FromDevice:(WPBluetoothWatchDevice *)device;

/**
 * 从设备对象计算 P2 字节
 * @param device 设备对象
 * @return P2 字节值
 */
+ (uint8_t)calculateP2FromDevice:(WPBluetoothWatchDevice *)device;

/**
 * 从设备对象计算 P3 字节
 * @param device 设备对象
 * @return P3 字节值
 */
+ (uint8_t)calculateP3FromDevice:(WPBluetoothWatchDevice *)device;

/**
 * 便捷方法：直接从设备对象设置开关表扩展
 * @param device 设备对象（从中读取所有通知开关属性）
 * @param completion 完成回调
 *
 * @discussion
 * 这是一个便捷方法，会自动从设备对象中读取所有通知开关属性，
 * 计算出 P0-P3 字节，然后调用设置方法。
 *
 * @note 使用示例:
 * ```objc
 * WPBluetoothWatchDevice *device = [WPBluetoothManager sharedInstance].currentDevice;
 * device.isWechat = YES;
 * device.isFacebook = NO;
 *
 * [WPCommands setSwitchTableExtensionFromDevice:device completion:^(BOOL success, NSError *error) {
 *     if (success) {
 *         NSLog(@"✅ 设置成功");
 *     }
 * }];
 * ```
 */
+ (void)setSwitchTableExtensionFromDevice:(WPBluetoothWatchDevice *)device
                               completion:(nullable WPSwitchTableExtensionSetCompletion)completion;

// MARK: - 内部方法（供 WPCommands.m 调用）

/**
 * 处理查询响应（内部方法）
 * @note 此方法由 WPCommands.m 的 handleSwitchTableExtensionResponse 调用
 */
+ (void)handleQueryResponse:(BOOL)success p0:(uint8_t)p0 p1:(uint8_t)p1 p2:(uint8_t)p2 p3:(uint8_t)p3;

/**
 * 处理设置响应（内部方法）
 * @note 此方法由 WPCommands.m 的 handleSwitchTableExtensionResponse 调用
 */
+ (void)handleSetResponse:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
