// Arduino pin assignment
#define PIN_LED  9
#define PIN_TRIG 12   // sonar sensor TRIGGER
#define PIN_ECHO 13   // sonar sensor ECHO

// configurable parameters
#define SND_VEL 346.0     // sound velocity at 24 celsius degree (unit: m/sec)
#define INTERVAL 25       // sampling interval (unit: msec)
#define PULSE_DURATION 10 // ultra-sound Pulse Duration (unit: usec)
#define _DIST_MIN 100.0   // minimum distance (unit: mm)
#define _DIST_MAX 300.0   // maximum distance (unit: mm)

#define TIMEOUT ((INTERVAL / 2) * 1000.0)     // max echo wait time (usec)
#define SCALE (0.001 * 0.5 * SND_VEL)         // convert duration to distance (mm)

unsigned long last_sampling_time = 0;

// 함수 선언
float USS_measure(int TRIG, int ECHO);
int calculateBrightness(float distance);

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIG, LOW);

  Serial.begin(57600);
}

void loop() {
  // 샘플링 주기 확인
  if (millis() < (last_sampling_time + INTERVAL))
    return;

  // 거리 측정
  float distance = USS_measure(PIN_TRIG, PIN_ECHO);
  int brightness = 255;  // default: LED off (active low 기준)

  // 거리 유효성 판단 및 밝기 계산
  if ((distance > _DIST_MIN) && (distance < _DIST_MAX)) {
    brightness = calculateBrightness(distance);
  }

  // LED 밝기 조절 (active low)
  analogWrite(PIN_LED, brightness);

  // 디버깅용 출력
  Serial.print("Distance: "); Serial.print(distance);
  Serial.print(" mm, Brightness: "); Serial.println(brightness);

  // 다음 샘플링 시간 설정
  last_sampling_time += INTERVAL;
}

// 거리 측정 함수 (단위: mm)
float USS_measure(int TRIG, int ECHO) {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);

  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE;
}

// 거리 기반 밝기 계산 함수 (active low → 값이 작을수록 밝음)
int calculateBrightness(float distance) {
  // 200mm에서 가장 밝고, 100mm와 300mm에서 가장 어두움 (삼각형 형태)
  float brightness;

  if (distance <= _DIST_MIN || distance >= _DIST_MAX) {
    brightness = 255;  // LED off
  } else if (distance == 200.0) {
    brightness = 0;  // 가장 밝게
  } else if (distance < 200.0) {
    brightness = 255.0 * (200.0 - distance) / 100.0;
  } else {  // distance > 200.0
    brightness = 255.0 * (distance - 200.0) / 100.0;
  }

  // 값 보정
  if (brightness < 0) brightness = 0;
  if (brightness > 255) brightness = 255;

  return (int)brightness;
}
