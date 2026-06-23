// 作业3 扩展: 可交互SOS信号
// 使用 millis() 非阻塞 + 串口命令控制
// 命令:
//   's' - 开始发送SOS
//   'p' - 暂停SOS
//   'f' - 加速 (时间减半)
//   'n' - 正常速度
//   发送 'status' - 查看当前状态
//
// 展示 millis() 的优势: 在发送SOS的同时可以接收串口命令

const int ledPin = 2;

// SOS参数 (可动态调整)
unsigned long dotTime = 200;    // 短闪时间
unsigned long dashTime = 600;   // 长闪时间
unsigned long offTime = 200;    // 灭时间
unsigned long letterGap = 500;  // 字母间隔
unsigned long wordGap = 2000;   // 单词间隔

// 状态变量
bool sosActive = true;
unsigned long previousMillis = 0;
int stepIndex = 0;
unsigned long currentDuration = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("====================================");
  Serial.println("ex03: 交互式SOS信号 (millis非阻塞)");
  Serial.println("命令: s=开始 p=暂停 f=加速 n=正常");
  Serial.println("      status=查看状态");
  Serial.println("====================================");

  currentDuration = dotTime;  // 第一步: 短闪亮
  digitalWrite(ledPin, HIGH);
  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  // ===== 串口命令处理 (非阻塞) =====
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    handleCommand(cmd);
  }

  // ===== SOS信号发送 =====
  if (sosActive && currentMillis - previousMillis >= currentDuration) {
    previousMillis = currentMillis;
    advanceSOS();
  }
}

// 推进SOS信号序列
void advanceSOS() {
  stepIndex++;
  if (stepIndex >= 18) stepIndex = 0;  // 18步完成一个SOS周期

  bool ledOn;
  // 根据步骤设置LED状态和持续时间
  if (stepIndex < 6) {
    // S: 短闪×3 (ON/OFF交替)
    ledOn = (stepIndex % 2 == 0);
    currentDuration = ledOn ? dotTime : offTime;
  } else if (stepIndex == 6) {
    // 字母间隔
    ledOn = false;
    currentDuration = letterGap;
  } else if (stepIndex < 13) {
    // O: 长闪×3
    ledOn = (stepIndex % 2 == 1);
    currentDuration = ledOn ? dashTime : offTime;
  } else if (stepIndex == 13) {
    // 字母间隔
    ledOn = false;
    currentDuration = letterGap;
  } else if (stepIndex < 17) {
    // S: 短闪×3 (第二组)
    int s2 = stepIndex - 14;
    ledOn = (s2 % 2 == 0);
    currentDuration = ledOn ? dotTime : offTime;
  } else {
    // 单词间隔 (长停顿)
    ledOn = false;
    currentDuration = wordGap;
  }

  digitalWrite(ledPin, ledOn ? HIGH : LOW);
}

void handleCommand(String cmd) {
  if (cmd == "s") {
    sosActive = true;
    Serial.println("[命令] SOS 开始发送");
  } else if (cmd == "p") {
    sosActive = false;
    digitalWrite(ledPin, LOW);
    Serial.println("[命令] SOS 已暂停");
  } else if (cmd == "f") {
    dotTime = 100; dashTime = 300;
    offTime = 100; letterGap = 250; wordGap = 1000;
    Serial.println("[命令] 速度: 快速 (2x)");
  } else if (cmd == "n") {
    dotTime = 200; dashTime = 600;
    offTime = 200; letterGap = 500; wordGap = 2000;
    Serial.println("[命令] 速度: 正常 (1x)");
  } else if (cmd == "status") {
    Serial.print("[状态] SOS="); Serial.print(sosActive ? "运行中" : "已暂停");
    Serial.print(" 步骤="); Serial.print(stepIndex);
    Serial.print(" 速度="); Serial.print(dotTime == 100 ? "快速" : "正常");
    Serial.println();
  } else {
    Serial.println("[错误] 未知命令");
  }
}
