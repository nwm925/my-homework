// 作业4 (ex04): 基于触摸传感器的"自锁"开关
//
// 功能说明:
//   摸一下触摸引脚, LED亮起并保持长亮;
//   松开手再摸一下, LED熄灭。
//   实现类似自锁开关的Toggle翻转效果。
//
// 关键技术:
//   - 触摸传感器 (touchRead) 检测手指触摸
//   - 布尔型状态变量 (ledState) 记录LED当前状态
//   - 边缘检测: 检测"未触摸→触摸"的上升沿瞬间
//   - 软件防抖: 使用 millis() 防止手抖误触发
//
// 硬件连接:
//   - LED: GPIO 2 (板载LED)
//   - 触摸引脚: T0 (GPIO 4), 需连接一根导线作为触摸感应端

const int ledPin = 2;       // LED引脚
const int touchPin = T0;     // 触摸引脚 (T0 = GPIO 4)

// ========== 触摸检测参数 ==========
const int TOUCH_THRESHOLD = 20;     // 触摸阈值: touchRead值低于此值视为"被触摸"
const unsigned long DEBOUNCE_MS = 150;  // 防抖时间(毫秒): 忽略短于该时间的状态变化
// ===================================

// ========== 状态变量 ==========
bool ledState = false;              // LED当前状态 (false=灭, true=亮)
bool lastTouchState = false;        // 上一次触摸状态 (false=未触摸, true=被触摸)
unsigned long lastDebounceTime = 0; // 上次状态变化的时间戳
// ==============================

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // 初始熄灭LED

  Serial.println("==========================================");
  Serial.println("ex04: 触摸传感器\"自锁\"开关");
  Serial.println("摸一下→亮, 再摸一下→灭 (Toggle翻转)");
  Serial.print("防抖时间: "); Serial.print(DEBOUNCE_MS);
  Serial.println("ms");
  Serial.println("==========================================");
}

void loop() {
  // 1. 读取触摸传感器原始值
  int touchValue = touchRead(touchPin);

  // 2. 判断当前是否被触摸 (值越低, 触摸越明显)
  bool currentTouchState = (touchValue < TOUCH_THRESHOLD);

  // 3. 软件防抖: 仅在状态稳定超过防抖时间后才处理
  if (currentTouchState != lastTouchState) {
    // 状态发生了变化, 记录时间戳
    lastDebounceTime = millis();
  }

  // 如果状态稳定时间超过防抖阈值, 确认为有效状态变化
  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {
    // 4. 边缘检测: 检测"从未触摸到触摸"的上升沿
    //    lastTouchState 已被更新(见下方), 这里用"之前记录的稳定状态"
    //    实际逻辑: currentTouchState 是稳定后的新状态
    //    如果当前是"触摸"且之前记录的是"未触摸" → 检测到按下瞬间

    // 使用静态变量记录"已确认的稳定触摸状态"
    static bool stableTouchState = false;

    if (currentTouchState != stableTouchState) {
      stableTouchState = currentTouchState;

      // 检测到触摸按下瞬间 (上升沿)
      if (currentTouchState == true) {
        // 翻转LED状态
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);

        Serial.print("[触发] 检测到触摸! LED → ");
        Serial.println(ledState ? "亮 (ON)" : "灭 (OFF)");
        Serial.print("        触摸值: ");
        Serial.println(touchValue);
      }
      // 检测到松手瞬间 (下降沿) — 不做任何操作
      else {
        Serial.print("[释放] 手指已离开, 触摸值恢复: ");
        Serial.println(touchValue);
      }
    }
  }

  // 5. 更新上一次触摸状态 (用于下一轮循环的状态变化检测)
  lastTouchState = currentTouchState;

  // 6. 串口输出实时触摸值 (用于调试, 可注释掉以减少输出)
  // Serial.print("Touch: ");
  // Serial.println(touchValue);

  delay(10);  // 小延迟, 避免过于频繁的检测
}
