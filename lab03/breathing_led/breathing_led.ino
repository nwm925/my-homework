// 实验3: LED呼吸灯 - PWM技术实现
// 使用 ESP32 PWM (ledc) 控制LED亮度渐变，产生呼吸效果

// 定义LED引脚
const int ledPin = 2;

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);

  // 直接将引脚、频率和分辨率绑定
  ledcAttach(ledPin, freq, resolution);

  Serial.println("呼吸灯实验开始...");
}

void loop() {
  // 逐渐变亮 (占空比从0增加到255)
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledPin, dutyCycle);
    delay(10);
  }

  // 逐渐变暗 (占空比从255减少到0)
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPin, dutyCycle);
    delay(10);
  }

  Serial.println("Breathing cycle completed");
}
