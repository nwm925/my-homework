// 实验2 扩展: 可变频率LED闪烁
// 演示不同delay值对闪烁频率的影响
// delay越小 → 闪烁越快；delay越大 → 闪烁越慢
// 当delay很小时（如10ms），由于视觉暂留效应，人眼无法分辨闪烁

const int ledPin = 2;

// 闪烁间隔数组（毫秒），从小到大体验不同频率
const int delays[] = {1000, 500, 200, 100, 50, 20, 10};
const int numDelays = sizeof(delays) / sizeof(delays[0]);
int currentDelayIndex = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  Serial.println("可变频率LED闪烁测试开始...");
}

void loop() {
  int currentDelay = delays[currentDelayIndex];

  Serial.print("当前闪烁间隔: ");
  Serial.print(currentDelay);
  Serial.print("ms, 频率: ");
  Serial.print(1000.0 / (2 * currentDelay));  // 频率 = 1/周期(秒)
  Serial.println("Hz");

  // 使用当前频率闪烁10次
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(currentDelay);
    digitalWrite(ledPin, LOW);
    delay(currentDelay);
  }

  // 切换到下一个频率
  currentDelayIndex = (currentDelayIndex + 1) % numDelays;
  delay(2000); // 频率切换间隔
}
