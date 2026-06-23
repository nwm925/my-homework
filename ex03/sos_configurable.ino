// 作业3 扩展: 可配置参数的SOS信号
// 使用 millis() 非阻塞方式，所有时序参数可调节

const int ledPin = 2;

// ========== SOS时序参数 (毫秒) ==========
const unsigned long DOT_ON    = 200;   // 短闪(S) 亮的时间
const unsigned long DOT_OFF   = 200;   // 短闪(S) 灭的时间
const unsigned long DASH_ON   = 600;   // 长闪(O) 亮的时间
const unsigned long DASH_OFF  = 200;   // 长闪(O) 灭的时间
const unsigned long GAP_LETTER = 500;  // 字母之间间隔
const unsigned long GAP_WORD   = 2000; // 单词之间间隔 (SOS结束长停顿)
// ========================================

// SOS序列
enum Phase {
  S_DOT1_ON, S_DOT1_OFF,
  S_DOT2_ON, S_DOT2_OFF,
  S_DOT3_ON, S_GAP1,
  O_DASH1_ON, O_DASH1_OFF,
  O_DASH2_ON, O_DASH2_OFF,
  O_DASH3_ON, O_GAP2,
  S2_DOT1_ON, S2_DOT1_OFF,
  S2_DOT2_ON, S2_DOT2_OFF,
  S2_DOT3_ON, WORD_GAP,
  NUM_PHASES
};

unsigned long previousMillis = 0;
Phase currentPhase = S_DOT1_ON;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  Serial.println("SOS可配置信号启动 (millis非阻塞)");
  Serial.print("短闪:"); Serial.print(DOT_ON);
  Serial.print("ms 长闪:"); Serial.print(DASH_ON);
  Serial.println("ms");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= getPhaseDuration(currentPhase)) {
    previousMillis = currentMillis;
    currentPhase = (Phase)((currentPhase + 1) % NUM_PHASES);

    bool ledOn = isLedOnPhase(currentPhase);
    digitalWrite(ledPin, ledOn ? HIGH : LOW);

    Serial.print("Phase "); Serial.print(currentPhase);
    Serial.print(": LED="); Serial.print(ledOn ? "ON" : "OFF");
    Serial.print(" ("); Serial.print(getPhaseDuration(currentPhase));
    Serial.println("ms)");
  }
}

// 获取当前阶段的持续时间
unsigned long getPhaseDuration(Phase p) {
  switch (p) {
    case S_DOT1_ON:  case S_DOT2_ON:  case S_DOT3_ON:
    case S2_DOT1_ON: case S2_DOT2_ON: case S2_DOT3_ON:
      return DOT_ON;
    case S_DOT1_OFF: case S_DOT2_OFF: case S_DOT3_OFF:
    case S2_DOT1_OFF:case S2_DOT2_OFF:case S2_DOT3_OFF:
      return DOT_OFF;
    case O_DASH1_ON: case O_DASH2_ON: case O_DASH3_ON:
      return DASH_ON;
    case O_DASH1_OFF:case O_DASH2_OFF:case O_DASH3_OFF:
      return DASH_OFF;
    case S_GAP1: case O_GAP2:
      return GAP_LETTER;
    case WORD_GAP:
      return GAP_WORD;
    default: return 200;
  }
}

// 判断当前阶段LED是否亮
bool isLedOnPhase(Phase p) {
  switch (p) {
    case S_DOT1_ON: case S_DOT2_ON: case S_DOT3_ON:
    case O_DASH1_ON: case O_DASH2_ON: case O_DASH3_ON:
    case S2_DOT1_ON: case S2_DOT2_ON: case S2_DOT3_ON:
      return true;
    default: return false;
  }
}
