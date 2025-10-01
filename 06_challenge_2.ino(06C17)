int ledPin = 7;
int period = 1000; // 기본값 1000us (1ms) / 10000us (10ms) / 100us (0.1ms)
int duty = 50;     // 기본 duty 50%

void setup() {
  pinMode(ledPin, OUTPUT);
}

// period 설정 함수
void set_period(int p) {
  if (p < 100) p = 100;
  if (p > 10000) p = 10000;
  period = p;
}

// duty 설정 함수
void set_duty(int d) {
  if (d < 0) d = 0;
  if (d > 100) d = 100;
  duty = d;
}

// PWM 출력 함수
void pwm_cycle() {
  int on_time = period * duty / 100;          // us
  int off_time = period - on_time;            // us
  
  if (on_time > 0) {
    digitalWrite(ledPin, HIGH);
    delayMicroseconds(on_time);
  }
  if (off_time > 0) {
    digitalWrite(ledPin, LOW);
    delayMicroseconds(off_time);
  }
}

void loop() {
  // 삼각파 패턴으로 duty 변화
  for (int d = 0; d <= 100; d++) {   // 0 → 100
    set_duty(d);
    for (int i = 0; i < 10; i++) {   // 약 10ms 동안 유지
      pwm_cycle();
    }
  }
  for (int d = 100; d >= 0; d--) {   // 100 → 0
    set_duty(d);
    for (int i = 0; i < 10; i++) {
      pwm_cycle();
    }
  }
}
