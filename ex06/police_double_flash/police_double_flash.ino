// 作业6 (ex06): 警车双闪灯效 (双通道PWM)
//
// 功能说明:
//   两个LED灯呈现平滑交替的渐变闪烁效果 —
//   当灯A的亮度逐渐增加时, 灯B的亮度同步逐渐减小,
//   形成一个变亮、另一个变暗的"反相"呼吸效果,
//   类似警车双闪灯。
//
// 关键技术:
//   - 双通道独立PWM
//   - 反相占空比: dutyA + dutyB = 255 (互补)
//   - 使用 ledcSetup + ledcAttachPin 建立两个独立PWM通道
//
// 硬件连接:
//   - LED A: GPIO 2 (板载LED, PWM通道0)
//   - LED B: GPIO 5 (面包板外接LED, 串联220Ω限流电阻, PWM通道1)
//
// 面包板接线:
//   GPIO 5 → 220Ω电阻 → LED正极(长脚) → LED负极(短脚) → GND

const int ledPinA = 2;   // LED A (PWM通道0)
const int ledPinB = 5;   // LED B (PWM通道1)

// ========== PWM参数 ==========
const int freq = 5000;           // PWM频率 5000Hz
const int resolution = 8;        // 8位分辨率 (0-255)
const int maxDuty = 255;         // 最大占空比

// PWM通道号
const int pwmChannelA = 0;
const int pwmChannelB = 1;
// =============================

void setup() {
  Serial.begin(115200);

  // 配置两个独立的PWM通道
  ledcSetup(pwmChannelA, freq, resolution);
  ledcAttachPin(ledPinA, pwmChannelA);

  ledcSetup(pwmChannelB, freq, resolution);
  ledcAttachPin(ledPinB, pwmChannelB);

  Serial.println("==========================================");
  Serial.println("ex06: 警车双闪灯效 (双通道反相PWM)");
  Serial.print("LED A: GPIO "); Serial.print(ledPinA);
  Serial.print(" (通道"); Serial.print(pwmChannelA); Serial.println(")");
  Serial.print("LED B: GPIO "); Serial.print(ledPinB);
  Serial.print(" (通道"); Serial.print(pwmChannelB); Serial.println(")");
  Serial.println("A变亮时B变暗, A变暗时B变亮 (反相)");
  Serial.println("==========================================");
}

void loop() {
  // ===== 警车双闪: 两个LED反相呼吸 =====
  //
  // 阶段1: A从暗→亮, B从亮→暗 (互补关系)
  //   dutyA: 0 → 255
  //   dutyB: 255 → 0
  //   dutyA + dutyB = 255 (始终互补)

  // A逐渐变亮, B逐渐变暗
  for (int dutyA = 0; dutyA <= maxDuty; dutyA++) {
    int dutyB = maxDuty - dutyA;  // 反相: A+B=255

    ledcWrite(pwmChannelA, dutyA);
    ledcWrite(pwmChannelB, dutyB);
    delay(10);
  }

  // 阶段2: A从亮→暗, B从暗→亮
  //   dutyA: 255 → 0
  //   dutyB: 0 → 255

  // A逐渐变暗, B逐渐变亮
  for (int dutyA = maxDuty; dutyA >= 0; dutyA--) {
    int dutyB = maxDuty - dutyA;  // 反相: A+B=255

    ledcWrite(pwmChannelA, dutyA);
    ledcWrite(pwmChannelB, dutyB);
    delay(10);
  }

  Serial.println("Police double-flash cycle completed");
}
