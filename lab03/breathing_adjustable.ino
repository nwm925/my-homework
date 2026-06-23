// 实验3 扩展: 可调节呼吸灯
// 通过修改参数体验不同呼吸效果:
//   - SPEED: 控制呼吸速度（越小越快）
//   - RESOLUTION: 控制亮度细腻度（越大越平滑）
//   - 高分辨率(12位=0-4095) vs 低分辨率(8位=0-255)

const int ledPin = 2;

// ========== 可调节参数 ==========
const int SPEED = 5;              // 呼吸速度 (delay毫秒数, 越小越快)
const int freq = 5000;            // PWM频率
const int resolution = 12;        // 分辨率 12位 (0-4095, 更细腻)
// ================================

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);

  Serial.print("呼吸灯 - 速度:");
  Serial.print(SPEED);
  Serial.print("ms, 分辨率:");
  Serial.print(resolution);
  Serial.println("位");
}

void loop() {
  int maxDuty = (1 << resolution) - 1;  // 2^resolution - 1

  // 逐渐变亮
  for (int dutyCycle = 0; dutyCycle <= maxDuty; dutyCycle++) {
    ledcWrite(ledPin, dutyCycle);
    delay(SPEED);
  }

  // 逐渐变暗
  for (int dutyCycle = maxDuty; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPin, dutyCycle);
    delay(SPEED);
  }

  Serial.print("Breathing cycle completed (max=");
  Serial.print(maxDuty);
  Serial.println(")");
}
