// 作业3 (ex03): 使用 millis() 函数控制LED产生SOS闪烁信号
//
// SOS 摩尔斯电码: ... --- ...
//   短闪(S/dot): LED亮200ms, 灭200ms
//   长闪(O/dash): LED亮600ms, 灭200ms
//   字母间隔: 灭500ms
//   单词间隔: 灭2000ms (每次SOS播放完毕后较长的熄灭停顿)
//
// 使用 millis() 非阻塞方式 + 状态机实现

const int ledPin = 2;

// SOS信号序列定义: 每个步骤 {LED状态, 持续时间(ms)}
// S: 短闪×3  → O: 长闪×3  → S: 短闪×3  → 长停顿
struct Step {
  bool ledOn;           // true=LED亮, false=LED灭
  unsigned long duration; // 持续时间(毫秒)
  const char* desc;     // 步骤描述
};

const Step sosSequence[] = {
  // S: 第一个短闪周期
  {true,  200, "S-短闪1 亮"},
  {false, 200, "S-短闪1 灭"},
  {true,  200, "S-短闪2 亮"},
  {false, 200, "S-短闪2 灭"},
  {true,  200, "S-短闪3 亮"},
  {false, 500, "字母间隔"},       // S到O之间

  // O: 长闪周期
  {true,  600, "O-长闪1 亮"},
  {false, 200, "O-长闪1 灭"},
  {true,  600, "O-长闪2 亮"},
  {false, 200, "O-长闪2 灭"},
  {true,  600, "O-长闪3 亮"},
  {false, 500, "字母间隔"},       // O到S之间

  // S: 第二个短闪周期
  {true,  200, "S-短闪1 亮"},
  {false, 200, "S-短闪1 灭"},
  {true,  200, "S-短闪2 亮"},
  {false, 200, "S-短闪2 灭"},
  {true,  200, "S-短闪3 亮"},
  {false, 2000, "SOS结束-长停顿"}, // 每次SOS播放完毕后较长的熄灭停顿
};

const int totalSteps = sizeof(sosSequence) / sizeof(sosSequence[0]);

int currentStep = 0;                 // 当前步骤索引
unsigned long previousMillis = 0;    // 上次切换步骤的时间

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  Serial.println("========================================");
  Serial.println("ex03: millis() SOS 求救信号");
  Serial.println("摩尔斯电码: ... --- ...");
  Serial.println("========================================");
  Serial.print("总步骤数: ");
  Serial.println(totalSteps);

  // 初始化第一步
  digitalWrite(ledPin, sosSequence[0].ledOn);
  Serial.print("步骤 1: ");
  Serial.println(sosSequence[0].desc);
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // 检查是否到达切换下一步的时间
  if (currentMillis - previousMillis >= sosSequence[currentStep].duration) {
    previousMillis = currentMillis;

    // 切换到下一步 (循环)
    currentStep = (currentStep + 1) % totalSteps;

    // 执行当前步骤
    digitalWrite(ledPin, sosSequence[currentStep].ledOn ? HIGH : LOW);

    Serial.print("步骤 ");
    Serial.print(currentStep + 1);
    Serial.print("/");
    Serial.print(totalSteps);
    Serial.print(": ");
    Serial.print(sosSequence[currentStep].desc);
    Serial.print(" (");
    Serial.print(sosSequence[currentStep].duration);
    Serial.println("ms)");
  }

  // millis() 非阻塞，程序可以同时处理其他任务
}
