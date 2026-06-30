# my-homework

这是我的 GitHub 使用作业仓库。

## 作业内容

### ex01 - HelloWorld 程序
- 使用 print 输出 Hello World
- 使用 input 函数实现键盘输入并显示输出

### lab01 - 实验1: Arduino IDE 安装与 ESP32 环境配置
- ESP32 环境搭建测试
- 板载 LED 闪烁测试 (使用 delay)

### lab02 - 实验2: 基础IO实验 - LED闪烁控制
- `led_blink.ino`: 使用 `delay()` 实现基础 LED 闪烁 (1秒间隔)
- `sos_signal.ino`: 使用 `delay()` 实现 SOS 求救信号 (三短三长三短)
- `blink_variable.ino`: 可变频率闪烁测试 (验证不同 delay 值对频率影响)

### lab03 - 实验3: LED呼吸灯 (PWM)
- `breathing_led.ino`: PWM 基础呼吸灯 (8位分辨率, 0-255)
- `breathing_adjustable.ino`: 可调节参数呼吸灯 (12位高分辨率, 0-4095)
- `breathing_sine.ino`: 正弦波非线性呼吸灯 (使用 sin() 实现更自然效果)

### ex02 - 作业2: millis() 控制 1Hz LED 闪烁
- `millis_blink.ino`: 使用 `millis()` 替代 `delay()` 实现 1Hz 非阻塞闪烁
- `millis_multitask.ino`: 多任务演示 (同时运行 LED 闪烁和串口时间戳)
- `millis_guide.ino`: `millis()` 函数使用指南

### ex03 - 作业3: millis() 控制 SOS 信号
- `sos_millis.ino`: 使用 `millis()` + 状态机实现 SOS 摩尔斯电码
- `sos_configurable.ino`: 可配置参数版本 (枚举状态机)
- `sos_interactive.ino`: 交互式版本 (串口命令控制启停/速度)

### ex04 - 作业4: 触摸传感器"自锁"开关
- `touch_toggle.ino`: 基于触摸传感器的自锁开关
- 使用布尔状态变量 `ledState` + 边缘检测逻辑
- 检测触摸按下瞬间翻转LED状态 (摸一下亮, 再摸一下灭)
- 软件防抖 (millis) 防止手抖误触发

### ex05 - 作业5: 多档位触摸调速呼吸灯
- `breathing_speed.ino`: 触摸切换速度档位的呼吸灯
- 3个速度级别 (慢/中/快), 每次触摸循环切换 (1→2→3→1)
- PWM呼吸灯根据档位改变 `delay()` 时长
- 结合触摸自锁开关逻辑和PWM呼吸灯代码

### ex06 - 作业6: 警车双闪灯效 (双通道PWM)
- `police_double_flash.ino`: 双LED反相呼吸闪烁
- 两个独立PWM通道 (LED A: GPIO 2, LED B: GPIO 5)
- 反相关系: dutyA + dutyB = 255 (A变亮时B变暗)
- 平滑交替渐变, 类似警车灯效

### ex07 - 作业7: Web网页端无极调光器
- `web_dimmer.ino`: WiFi + Web服务器 + HTML滑动条
- HTML `<input type="range">` 滑动条 (0-255)
- JavaScript `fetch()` 发送GET请求实时调节PWM
- WiFi AP模式 (热点: ESP32-Dimmer), 手机/电脑浏览器访问

### ex08 - 作业8: 物联网安防报警器
- `iot_alarm.ino`: Web远程布防/撤防 + 触摸触发报警
- 状态机: DISARMED → ARMED → ALARM
- 网页端"布防"/"撤防"按钮控制
- 布防状态下触摸引脚触发LED高频闪烁报警
- 仅网页端撤防可解除报警

### ex09 - 作业9: 实时传感器Web仪表盘
- `sensor_dashboard.ino`: 触摸传感器数据实时Web监控
- RESTful API: `GET /api/touch` 返回触摸模拟量JSON
- Web页面AJAX定时拉取 (300ms间隔)
- 实时数值显示 + 进度条 + 历史趋势柱状图
- 手指靠近时数值实时变化、颜色渐变提示