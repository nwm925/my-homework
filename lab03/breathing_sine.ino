// 实验3 扩展: 正弦波非线性呼吸灯
// 人眼对亮度的感知是对数关系，线性渐变看起来不自然
// 使用 sin() 函数让亮度变化更柔和、更接近自然呼吸

const int ledPin = 2;
const int freq = 5000;
const int resolution = 12;        // 12位分辨率 (0-4095)
const int maxDuty = 4095;

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
  Serial.println("正弦波呼吸灯启动 (非线性, 更自然)...");
}

void loop() {
  // 使用正弦波产生柔和的呼吸效果
  // sin() 返回值范围 [-1, 1]，映射到 [0, maxDuty]
  for (float angle = 0; angle < 2 * PI; angle += 0.01) {
    // sin(angle) ∈ [-1, 1] → 映射到 [0, 1]
    float brightness = (sin(angle) + 1.0) / 2.0;

    // 写入PWM占空比
    int dutyCycle = (int)(brightness * maxDuty);
    ledcWrite(ledPin, dutyCycle);
    delay(5);
  }

  Serial.println("Breathing cycle (sine) completed");
}
