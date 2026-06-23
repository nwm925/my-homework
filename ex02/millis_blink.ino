// 作业2 (ex02): 使用 millis() 函数控制LED以1Hz频率稳定闪烁
// 与 delay() 不同，millis() 是非阻塞方式，不会暂停程序执行
//
// 1Hz = 每秒1个完整周期 (亮→灭→亮)
// 周期 = 1000ms, 半周期 = 500ms
// LED亮500ms, 灭500ms

const int ledPin = 2;                  // ESP32板载LED引脚
const unsigned long interval = 500;    // 500ms半周期

unsigned long previousMillis = 0;      // 上次切换LED的时间
bool ledState = LOW;                   // 当前LED状态

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("ex02: millis() 1Hz LED闪烁启动");
}

void loop() {
  // 获取当前运行毫秒数
  unsigned long currentMillis = millis();

  // 检查是否到达切换时间
  if (currentMillis - previousMillis >= interval) {
    // 保存当前时间作为下次参考
    previousMillis = currentMillis;

    // 切换LED状态
    ledState = !ledState;
    digitalWrite(ledPin, ledState);

    // 串口输出当前状态
    if (ledState == HIGH) {
      Serial.println("LED ON");
    } else {
      Serial.println("LED OFF");
    }
  }

  // 这里可以放其他代码，不会被阻塞！
  // 这就是 millis() 相比 delay() 的优势
}
