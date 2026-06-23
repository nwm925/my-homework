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