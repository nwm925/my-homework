// 作业5 (ex05): 多档位触摸调速呼吸灯 [改进版]
//
// LED持续呈呼吸灯效果。
// 每触摸一次引脚, 呼吸节奏循环切换:
//   慢速 (约8秒/周期) → 中速 (约1.5秒/周期) → 快速 (约0.3秒/周期)
//
// 改进: 同时改变 delay() 时长 和 占空比步长(Step),
//       让三档之间的呼吸速度差异非常明显

const int ledPin = 2;
const int touchPin = T0;

// ========== PWM参数 ==========
const int freq = 5000;
const int resolution = 8;        // 8位 (0-255)
const int maxDuty = 255;
// =============================

// ========== 触摸参数 ==========
const int TOUCH_THRESHOLD = 500;
const unsigned long DEBOUNCE_MS = 150;
// ==============================

// ========== 三档速度定义 ==========
//                       档位1(慢)  档位2(中)  档位3(快)
const int SPEED_DELAYS[] = { 15,       6,        2  };  // delay毫秒数
const int SPEED_STEPS[]  = { 1,        3,        6  };  // 每次递增的步长
const char* SPEED_NAMES[] = {"慢速", "中速", "快速"};
const int NUM_SPEEDS = 3;
// ===================================

int speedLevel = 0;
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);

  Serial.println("==========================================");
  Serial.println("ex05: 多档位触摸调速呼吸灯 (改进版)");
  Serial.println("触摸切换: 慢速(~8s) → 中速(~1.5s) → 快速(~0.3s)");
  Serial.print("当前档位: ");
  Serial.print(speedLevel + 1);
  Serial.print(" - ");
  Serial.print(SPEED_NAMES[speedLevel]);
  Serial.print(" (delay=");
  Serial.print(SPEED_DELAYS[speedLevel]);
  Serial.print("ms, step=");
  Serial.print(SPEED_STEPS[speedLevel]);
  Serial.println(")");
  Serial.println("==========================================");
}

void loop() {
  // ===== 触摸检测 =====
  int touchValue = touchRead(touchPin);
  bool currentTouchState = (touchValue < TOUCH_THRESHOLD);

  if (currentTouchState != lastTouchState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    static bool stableTouchState = false;
    if (currentTouchState != stableTouchState) {
      stableTouchState = currentTouchState;

      if (currentTouchState == true) {
        speedLevel = (speedLevel + 1) % NUM_SPEEDS;
        Serial.print("[切换] 档位 → ");
        Serial.print(speedLevel + 1);
        Serial.print("/");
        Serial.print(NUM_SPEEDS);
        Serial.print(" (");
        Serial.print(SPEED_NAMES[speedLevel]);
        Serial.print(", delay=");
        Serial.print(SPEED_DELAYS[speedLevel]);
        Serial.print("ms, step=");
        Serial.print(SPEED_STEPS[speedLevel]);
        Serial.println(")");
      }
    }
  }
  lastTouchState = currentTouchState;

  // ===== PWM呼吸灯 =====
  int delayMs = SPEED_DELAYS[speedLevel];
  int step = SPEED_STEPS[speedLevel];

  // 逐渐变亮
  for (int duty = 0; duty <= maxDuty; duty += step) {
    ledcWrite(ledPin, duty);
    delay(delayMs);
  }

  // 逐渐变暗
  for (int duty = maxDuty; duty >= 0; duty -= step) {
    ledcWrite(ledPin, duty);
    delay(delayMs);
  }
}
