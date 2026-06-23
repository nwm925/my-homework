// 实验2 进阶: SOS求救信号
// 基于摩尔斯电码实现SOS信号: 三短闪、三长闪、三短闪
// S: ... (短闪3次)
// O: --- (长闪3次)
// S: ... (短闪3次)

const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 发送 SOS 信号
  Serial.println("Sending SOS...");

  // S: 短闪3次 (每闪200ms亮 + 200ms灭)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // 字母间隔

  // O: 长闪3次 (每闪600ms亮 + 200ms灭)
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(600);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
  delay(500); // 字母间隔

  // S: 短闪3次
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }

  delay(2000); // 单词间隔（较长停顿）
}
