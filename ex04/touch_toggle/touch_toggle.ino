// 作业4 (ex04): 触摸传感器"自锁"开关 [调试版]
//
// 先运行此版本来观察触摸值的范围，
// 根据串口输出的值调整 TOUCH_THRESHOLD

const int ledPin = 2;
const int touchPin = T0;      // GPIO 4

// ========== 可调参数 ==========
const int TOUCH_THRESHOLD = 35;    // ← 先改成35试试! 如果还不亮继续改大
const unsigned long DEBOUNCE_MS = 150;
// =============================

bool ledState = false;
bool lastTouchState = false;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // 启动时先读一次看看初始值
  int initVal = touchRead(touchPin);
  Serial.println("==========================================");
  Serial.println("ex04: 触摸传感器自锁开关 (调试版)");
  Serial.print("未触摸时的基准值: ");
  Serial.println(initVal);
  Serial.print("当前阈值: ");
  Serial.println(TOUCH_THRESHOLD);
  Serial.println("如果无法触发，修改 TOUCH_THRESHOLD");
  Serial.println("规则: 阈值应该 > 触摸时的值 且 < 未触摸时的值");
  Serial.println("==========================================");
}

void loop() {
  int touchValue = touchRead(touchPin);

  // ★ 始终打印触摸值，观察范围 (找到合适的阈值后可以注释掉)
  Serial.print("Touch值: ");
  Serial.print(touchValue);
  Serial.print("  状态: ");
  Serial.println(touchValue < TOUCH_THRESHOLD ? "● 触摸中" : "○ 未触摸");

  bool currentTouchState = (touchValue < TOUCH_THRESHOLD);

  // 防抖
  if (currentTouchState != lastTouchState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    static bool stableTouchState = false;
    if (currentTouchState != stableTouchState) {
      stableTouchState = currentTouchState;

      if (currentTouchState == true) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);
        Serial.print(">>> [触发!] LED → ");
        Serial.println(ledState ? "亮" : "灭");
      }
    }
  }

  lastTouchState = currentTouchState;
  delay(80);  // 调试时放慢一点方便观察
}
