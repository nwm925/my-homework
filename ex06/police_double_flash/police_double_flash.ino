// 作业6 (ex06): 警车双闪灯效 (双通道PWM)
//
// 两个LED呈现反相呼吸效果:
//   LED A变亮时LED B变暗, LED A变暗时LED B变亮
//   类似警车双闪灯
//
// 使用 ledcAttach() 简化API (兼容各版本ESP32板包)

const int ledPinA = 2;   // LED A (板载)
const int ledPinB = 5;   // LED B (面包板外接)

const int freq = 5000;
const int resolution = 8;
const int maxDuty = 255;

void setup() {
  Serial.begin(115200);

  // 简化API: ledcAttach自动分配通道, 返回通道号
  int chA = ledcAttach(ledPinA, freq, resolution);
  int chB = ledcAttach(ledPinB, freq, resolution);

  Serial.println("==========================================");
  Serial.println("ex06: 警车双闪灯效");
  Serial.print("LED A: GPIO"); Serial.print(ledPinA);
  Serial.print(" (通道"); Serial.print(chA); Serial.println(")");
  Serial.print("LED B: GPIO"); Serial.print(ledPinB);
  Serial.print(" (通道"); Serial.print(chB); Serial.println(")");
  Serial.println("反相: A亮→B暗, A暗→B亮");
  Serial.println("==========================================");
}

void loop() {
  // 阶段1: A 0→255, B 255→0
  for (int dutyA = 0; dutyA <= maxDuty; dutyA++) {
    int dutyB = maxDuty - dutyA;
    ledcWrite(ledPinA, dutyA);
    ledcWrite(ledPinB, dutyB);
    delay(10);
  }

  // 阶段2: A 255→0, B 0→255
  for (int dutyA = maxDuty; dutyA >= 0; dutyA--) {
    int dutyB = maxDuty - dutyA;
    ledcWrite(ledPinA, dutyA);
    ledcWrite(ledPinB, dutyB);
    delay(10);
  }

  Serial.println("Cycle completed");
}
