# WatchProtocolSDK-ObjC v2.0.11 发布说明

## 🎉 发布信息

- **版本号**: v2.0.11
- **发布日期**: 2026-01-30
- **类型**: 功能更新 (Feature Release)
- **Framework 大小**: 1.2M
- **兼容性**: iOS 13.0+

---

## 🆕 新增功能

### 1. ⏰ 闹钟管理功能

完整的闹钟管理功能，支持查询、设置、修改和删除闹钟。

**主要特性**:
- 查询闹钟总数和可用数量
- 查询闹钟详细信息（时间、开关状态、重复周期）
- 设置新闹钟或修改现有闹钟
- 支持灵活的重复周期设置（每天、工作日、周末、自定义）
- 启用/禁用闹钟
- 自动同步到设备模型
- 代理回调和通知支持

**使用示例**:
```objc
// 设置每天早上 7:30 的闹钟
WPAlarmData *alarm = [[WPAlarmData alloc] init];
alarm.alarmId = 0;
alarm.enabled = YES;
alarm.hour = 7;
alarm.minute = 30;
alarm.repeatDays = 0x7F;  // 每天
[WPCommands setAlarmInfo:0x01 alarm:alarm];
```

### 2. 💺 久坐提醒功能

帮助用户养成健康习惯的久坐提醒功能。

**主要特性**:
- 设置提醒时间段（开始-结束时间）
- 自定义提醒间隔（分钟）
- 支持工作日/周末/每天等周期设置
- 启用/禁用提醒
- 实时同步设置

**使用示例**:
```objc
// 工作日 9:00-18:00，每60分钟提醒
WPReminderInfoResponse *reminder = [[WPReminderInfoResponse alloc] init];
reminder.eventType = 0;        // 久坐提醒
reminder.cycle = 0x1F;         // 工作日
reminder.startHour = 9;
reminder.endHour = 18;
reminder.period = 60;
[WPCommands setReminderInfo:reminder];
```

### 3. 💧 喝水提醒功能

帮助用户保持水分摄入的喝水提醒功能。

**主要特性**:
- 与久坐提醒类似的功能特性
- 独立的开关控制
- 灵活的时间段和间隔设置

**使用示例**:
```objc
// 每天 8:00-22:00，每2小时提醒
WPReminderInfoResponse *reminder = [[WPReminderInfoResponse alloc] init];
reminder.eventType = 1;        // 喝水提醒
reminder.cycle = 0x7F;         // 每天
reminder.startHour = 8;
reminder.endHour = 22;
reminder.period = 120;         // 120分钟
[WPCommands setReminderInfo:reminder];
```

---

## 🔧 API 更新

### 新增方法 (WPCommands)

```objc
// 闹钟管理
+ (void)getAlarmInfo:(NSInteger)type;
+ (void)setAlarmInfo:(NSInteger)setCmd alarm:(WPAlarmData *)alarm;

// 提醒管理
+ (void)getReminderInfo:(NSInteger)eventType;
+ (void)setReminderInfo:(WPReminderInfoResponse *)response;
```

### 新增代理方法 (WPBluetoothManagerDelegate)

```objc
// 闹钟回调
- (void)didUpdateAlarmCount:(NSInteger)count canUse:(NSInteger)canUse;
- (void)didUpdateAlarmInfo:(WPAlarmData *)alarm;

// 提醒回调
- (void)didUpdateLongSitReminder:(WPReminderInfo *)reminder;
- (void)didUpdateDrinkWaterReminder:(WPReminderInfo *)reminder;
```

### 新增通知

```objc
// 闹钟
NSNotificationName const WPAlarmUpdatedNotification = @"WPAlarmUpdated";

// 提醒
NSNotificationName const WPLongSitReminderUpdatedNotification = @"WPLongSitReminderUpdated";
NSNotificationName const WPDrinkWaterReminderUpdatedNotification = @"WPDrinkWaterReminderUpdated";
```

---

## 📊 数据模型

### WPAlarmData

```objc
@interface WPAlarmData : NSObject
@property (nonatomic, assign) NSInteger alarmId;      // 闹钟索引 (0-7)
@property (nonatomic, assign) BOOL enabled;            // 是否启用
@property (nonatomic, assign) NSInteger hour;          // 小时 (0-23)
@property (nonatomic, assign) NSInteger minute;        // 分钟 (0-59)
@property (nonatomic, assign) NSInteger repeatDays;    // 重复周期位图
@end
```

### WPReminderInfo

```objc
@interface WPReminderInfo : NSObject
@property (nonatomic, assign) BOOL enabled;            // 是否启用
@property (nonatomic, assign) NSInteger startHour;     // 开始小时
@property (nonatomic, assign) NSInteger startMinute;   // 开始分钟
@property (nonatomic, assign) NSInteger endHour;       // 结束小时
@property (nonatomic, assign) NSInteger endMinute;     // 结束分钟
@property (nonatomic, assign) NSInteger interval;      // 间隔（分钟）
@end
```

### WPReminderInfoResponse

```objc
@interface WPReminderInfoResponse : NSObject
@property (nonatomic, assign) NSInteger eventType;     // 事件类型 (0=久坐 1=喝水)
@property (nonatomic, assign) NSInteger cycle;         // 重复周期位图
@property (nonatomic, assign) NSInteger startHour;
@property (nonatomic, assign) NSInteger startMinute;
@property (nonatomic, assign) NSInteger endHour;
@property (nonatomic, assign) NSInteger endMinute;
@property (nonatomic, assign) NSInteger period;        // 间隔（分钟）
@end
```

---

## 📚 文档

本次发布包含以下新文档：

1. **ALARM_REMINDER_SOLUTION.md** - 完整技术方案和实现细节
2. **ALARM_REMINDER_QUICK_GUIDE.md** - 快速实现指南
3. **ALARM_REMINDER_USAGE_EXAMPLE.md** - 详细使用示例
4. **ALARM_REMINDER_IMPLEMENTATION_SUMMARY.md** - 实现总结
5. **BUILD_REPORT_v2.0.11.md** - 构建报告
6. **RELEASE_NOTES_v2.0.11.md** - 本文件

---

## 🔄 升级指南

### 从 v2.0.10 升级

1. **替换 Framework**
   - 删除旧的 `WatchProtocolSDK.xcframework`
   - 添加新的 `WatchProtocolSDK.xcframework` (v2.0.11)
   - 确保 Embed 设置为 "Embed & Sign"

2. **可选：实现新的代理方法**
   ```objc
   - (void)didUpdateAlarmInfo:(WPAlarmData *)alarm {
       // 处理闹钟更新
   }

   - (void)didUpdateLongSitReminder:(WPReminderInfo *)reminder {
       // 处理久坐提醒更新
   }
   ```

3. **清理并重新编译**
   - Product → Clean Build Folder (⇧⌘K)
   - Product → Build (⌘B)

### 兼容性说明

✅ **向后兼容**: 完全兼容 v2.0.10，无破坏性变更
✅ **代理方法**: 新增的代理方法都是 `@optional`，不影响现有实现
✅ **数据模型**: 扩展了设备模型，不影响现有字段

---

## 🎯 使用场景

### 场景 1: 智能闹钟应用

```objc
// 设置工作日早晨闹钟
WPAlarmData *workdayAlarm = [[WPAlarmData alloc] init];
workdayAlarm.alarmId = 0;
workdayAlarm.enabled = YES;
workdayAlarm.hour = 6;
workdayAlarm.minute = 30;
workdayAlarm.repeatDays = 0x1F;  // 周一到周五
[WPCommands setAlarmInfo:0x01 alarm:workdayAlarm];

// 设置周末闹钟
WPAlarmData *weekendAlarm = [[WPAlarmData alloc] init];
weekendAlarm.alarmId = 1;
weekendAlarm.enabled = YES;
weekendAlarm.hour = 9;
weekendAlarm.minute = 0;
weekendAlarm.repeatDays = 0x60;  // 周六周日
[WPCommands setAlarmInfo:0x01 alarm:weekendAlarm];
```

### 场景 2: 健康管理应用

```objc
// 久坐提醒：办公时间每小时提醒
WPReminderInfoResponse *longSitReminder = [[WPReminderInfoResponse alloc] init];
longSitReminder.eventType = 0;
longSitReminder.cycle = 0x1F;     // 工作日
longSitReminder.startHour = 9;
longSitReminder.endHour = 18;
longSitReminder.period = 60;      // 60分钟
[WPCommands setReminderInfo:longSitReminder];

// 喝水提醒：全天每2小时提醒
WPReminderInfoResponse *drinkWaterReminder = [[WPReminderInfoResponse alloc] init];
drinkWaterReminder.eventType = 1;
drinkWaterReminder.cycle = 0x7F;  // 每天
drinkWaterReminder.startHour = 8;
drinkWaterReminder.endHour = 22;
drinkWaterReminder.period = 120;  // 120分钟
[WPCommands setReminderInfo:drinkWaterReminder];
```

### 场景 3: 综合健康监测

结合现有的心率、步数等功能，打造完整的健康监测体系：

```objc
@interface HealthMonitorViewController () <WPBluetoothManagerDelegate>
@end

@implementation HealthMonitorViewController

- (void)setupHealthMonitoring {
    // 设置闹钟
    [self setupDailyAlarms];

    // 设置提醒
    [self setupHealthReminders];

    // 开始心率监测
    [[WPBluetoothManager sharedInstance] startHeartRateMonitoring];
}

- (void)didUpdateAlarmInfo:(WPAlarmData *)alarm {
    // 更新 UI 显示闹钟状态
    [self.tableView reloadData];
}

- (void)didUpdateLongSitReminder:(WPReminderInfo *)reminder {
    // 更新久坐提醒 UI
    self.longSitSwitch.on = reminder.enabled;
}

- (void)didReceiveHeartRate:(NSInteger)heartRate {
    // 显示心率数据
    self.heartRateLabel.text = [NSString stringWithFormat:@"%ld bpm", heartRate];
}

@end
```

---

## 🔍 重复周期位图说明

### 位图格式

```
bit0 = 周一
bit1 = 周二
bit2 = 周三
bit3 = 周四
bit4 = 周五
bit5 = 周六
bit6 = 周日
```

### 常用值

| 值 | 二进制 | 说明 |
|----|--------|------|
| 0x7F | 0b01111111 | 每天（周一到周日） |
| 0x1F | 0b00011111 | 工作日（周一到周五） |
| 0x60 | 0b01100000 | 周末（周六周日） |
| 0x01 | 0b00000001 | 仅周一 |
| 0x02 | 0b00000010 | 仅周二 |
| 0x15 | 0b00010101 | 周一、周三、周五 |
| 0x2A | 0b00101010 | 周二、周四、周六 |

### 代码示例

```objc
// 自定义周期：周一、周三、周五
NSInteger customDays = (1 << 0) | (1 << 2) | (1 << 4);  // 0x15

WPAlarmData *alarm = [[WPAlarmData alloc] init];
alarm.repeatDays = customDays;
```

---

## ⚠️ 注意事项

1. **闹钟数量限制**
   - 大多数设备支持 8 个闹钟（索引 0-7）
   - 使用前先查询 `alarmCanUse` 确认可用数量

2. **提醒类型**
   - eventType = 0：久坐提醒
   - eventType = 1：喝水提醒
   - 两种提醒互不影响，可同时启用

3. **时间格式**
   - 使用 24 小时制
   - 小时范围：0-23
   - 分钟范围：0-59

4. **代理方法**
   - 所有新增代理方法都是 `@optional`
   - 可选择性实现需要的回调

5. **通知机制**
   - 支持 NSNotification 和代理两种回调方式
   - 根据需要选择合适的方式

---

## 🐛 已知问题

目前无已知问题。如发现问题，请联系技术支持。

---

## 📞 技术支持

### 联系方式

- **邮箱**: 315082431@qq.com
- **文档**: 查看 `ALARM_REMINDER_SOLUTION.md`

### 问题反馈

提交问题时请包含：
1. SDK 版本：v2.0.11
2. Xcode 版本
3. iOS 版本
4. 完整错误日志
5. 重现步骤

---

## 🎊 致谢

感谢所有使用 WatchProtocolSDK-ObjC 的开发者！

本次更新完全基于 Swift 版本实现，保证了功能的一致性和稳定性。

---

## 📈 统计数据

- **新增代码**: 275 行
- **新增文档**: 14,000+ 字
- **新增 API**: 8 个方法
- **新增数据模型**: 3 个类
- **Framework 大小**: 1.2M
- **编译时间**: ~30 秒

---

**发布日期**: 2026-01-30
**版本**: v2.0.11
**状态**: ✅ Production Ready
**下载**: Output-ObjC-Dynamic/WatchProtocolSDK.xcframework
