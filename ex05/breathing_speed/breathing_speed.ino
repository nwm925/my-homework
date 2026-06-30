// 作业5 (ex05): 多档位触摸调速呼吸灯
//
// 功能说明:
//   LED持续呈呼吸灯效果。
//   用户每触摸一次引脚, LED"呼吸"的节奏就会发生改变,
//   共有三个明显的速度级别, 循环切换 (1→2→3→1...)
//
// 关键技术:
//   - PWM呼吸灯 (ledc)
//   - 触摸传感器 (touchRead) + 边缘检测 + 防抖
//   - 速度档位变量 (speedLevel) 循环切换
//   - 通过改变 delay() 来控制呼吸速度
//
// 硬件连接:
//   - LED: GPIO 2 (板载LED, PWM输出)
//   - 触摸引脚: T0 (GPIO 4)

const int ledPin = 2;       // LED引脚 (PWM)
const int touchPin = T0;     // 触摸引脚

// ========== PWM参数 ==========
const int freq = 5000;           // PWM频率 5000Hz
const int resolution = 8;        // 8位分辨率 (0-255)
// =============================

// ========== 触摸检测参数 ==========
const int TOUCH_THRESHOLD = 20;
const unsigned long DEBOUNCE_MS = 150;
// ==================================

// ========== 速度档位定义 ==========
// 档位1: 慢速呼吸 (delay 20ms, 约5秒一个周期)
// 档位2: 中速呼吸 (delay 10ms, 约2.5秒一个周期)
// 档位3: 快速呼吸 (delay 3ms, 约0.8秒一个周期)
const int SPEED_DELAYS[] = {20, 10, 3};
const char* SPEED_NAMES[] = {"慢速", "中速", "快速"};
const int NUM_SPEEDS = 3;
// ===================================

// ========== 状态变量 ==========
int speedLevel = 0;               // 当前速度档位 (0=慢, 1=中, 2=快)
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;
// ==============================

void setup() {
  Serial.begin(115200);

  // 初始化PWM (简化API, 自动分配通道)
  ledcAttach(ledPin, freq, resolution);

  Serial.println("==========================================");
  Serial.println("ex05: 多档位触摸调速呼吸灯");
  Serial.println("触摸切换速度: 慢速 → 中速 → 快速 → 慢速...");
  Serial.print("当前档位: ");
  Serial.print(speedLevel + 1);
  Serial.print(" - ");
  Serial.println(SPEED_NAMES[speedLevel]);
  Serial.println("==========================================");
}

void loop() {
  // ===== 1. 触摸检测与档位切换 =====
  int touchValue = touchRead(touchPin);
  bool currentTouchState = (touchValue < TOUCH_THRESHOLD);

  // 防抖处理
  if (currentTouchState != lastTouchState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    static bool stableTouchState = false;
    if (currentTouchState != stableTouchState) {
      stableTouchState = currentTouchState;

      // 检测到触摸按下 → 切换档位
      if (currentTouchState == true) {
        speedLevel = (speedLevel + 1) % NUM_SPEEDS;  // 循环切换: 0→1→2→0...
        Serial.print("[切换] 档位 → ");
        Serial.print(speedLevel + 1);
        Serial.print "/");
        Serial.print(NUM_SPEEDS);
        Serial.print(" (");
        Serial.print(SPEED_NAMES[speedLevel]);
        Serial.print(", delay=");
        Serial.print(SPEED_DELAYS[speedLevel]);
        Serial.println("ms)");
      }
    }
  }
  lastTouchState = currentTouchState;

  // ===== 2. PWM呼吸灯 (根据当前档位改变速度) =====
  int breatheDelay = SPEED_DELAYS[speedLevel];

  // 逐渐变亮 (占空比从0增加到255)
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledPin, dutyCycle);
    delay(breatheDelay);

    // 在呼吸过程中也检测触摸 (非阻塞)
    // 注: 此处使用delay, 触摸响应会有轻微延迟, 但可接受
  }

  // 逐渐变暗 (占空比从255减少到0)
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPin, dutyCycle);
    delay(breatheDelay);
  }

  // 注: 每完成一个呼吸周期, 串口输出一次
  // 如需减少串口输出, 可注释下面这行
  // Serial.print(".");
}
