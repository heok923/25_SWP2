int ledPin = 7;  // GPIO 7번 핀 사용

void setup() {
  pinMode(ledPin, OUTPUT);  // 핀을 출력 모드로 설정
}

void loop() {
  // 1. 처음 1초 동안 LED 켜기
  digitalWrite(ledPin, HIGH);
  delay(1000);   // 1초 대기

  // 2. 다음 1초 동안 LED가 5회 깜빡이도록
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPin, HIGH);
    delay(100);  // 0.1초 켜짐
    digitalWrite(ledPin, LOW);
    delay(100);  // 0.1초 꺼짐
  }

  // 3. LED 끄고 무한루프 상태에서 종료
  digitalWrite(ledPin, LOW);
  while (1) {
    // 무한루프
  }
}
