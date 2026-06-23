// 作业2 参考: millis() 函数使用指南
//
// millis() 返回自程序启动以来的毫秒数 (unsigned long, 约50天后溢出归零)
//
// 基本用法模式:
//   1. 定义间隔常量和"上次执行时间"变量
//   2. 在 loop() 中获取当前 millis()
//   3. 检查是否到达间隔时间 (current - previous >= interval)
//   4. 执行操作并更新 previous
//
// 对比:
//   delay():   阻塞式, 暂停所有程序, 简单但不灵活
//   millis():  非阻塞式, 程序继续运行, 稍复杂但功能强大

const int ledPin = 2;

// ===== millis() 标准模式 (1Hz闪烁) =====
unsigned long previousMillis = 0;
const unsigned long interval = 500;  // 500ms半周期 = 1Hz
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // millis() 使用注意事项:
  // - 返回值是 unsigned long (0 到 4,294,967,295)
  // - 约50天后会溢出归零 (4,294,967,295ms ≈ 49.7天)
  // - 使用减法比较 (current - previous) 可以正确处理溢出
  Serial.println("millis() 指南 - 1Hz LED闪烁");
}

void loop() {
  unsigned long currentMillis = millis();

  // 关键: 用 currentMillis - previousMillis >= interval
  // 不要用 currentMillis >= previousMillis + interval (可能溢出问题)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // 更新上次执行时间

    // 切换LED
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
  }

  // millis() 的好处: loop() 不会被阻塞
  // 可以在这里添加更多任务!
}
