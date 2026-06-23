// 作业2 扩展: 演示 millis() 非阻塞多任务处理
// 同时运行两个独立任务:
//   任务1: LED以1Hz频率闪烁 (每500ms切换)
//   任务2: 串口每秒输出一次运行时间戳

const int ledPin = 2;

// 任务1: LED闪烁
const unsigned long blinkInterval = 500;
unsigned long previousBlinkMillis = 0;
bool ledState = LOW;

// 任务2: 串口输出时间戳
const unsigned long printInterval = 1000;
unsigned long previousPrintMillis = 0;
unsigned long startMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  startMillis = millis();
  Serial.println("millis() 多任务演示启动...");
  Serial.println("任务1: LED 1Hz闪烁 | 任务2: 每秒输出时间戳");
  Serial.println("================================================");
}

void loop() {
  unsigned long currentMillis = millis();

  // ===== 任务1: LED闪烁 (1Hz) =====
  if (currentMillis - previousBlinkMillis >= blinkInterval) {
    previousBlinkMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  // ===== 任务2: 每秒输出运行时间 =====
  if (currentMillis - previousPrintMillis >= printInterval) {
    previousPrintMillis = currentMillis;
    unsigned long elapsed = (currentMillis - startMillis) / 1000;
    Serial.print("系统已运行: ");
    Serial.print(elapsed);
    Serial.print(" 秒 | LED状态: ");
    Serial.println(ledState ? "亮" : "灭");
  }

  // 两个任务互不阻塞!
  // 如果用 delay()，只能串行执行，两个任务无法同时进行
}
