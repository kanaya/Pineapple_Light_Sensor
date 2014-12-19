const int sw1 = 2;
const int sw2 = 3;
const int sw4 = 4;
const int sw8 = 5;

void setup() {
  Serial.begin(9600);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);
  pinMode(sw8, INPUT_PULLUP);
}

void loop() {
  int b1 = digitalRead(sw1) & 0x01;
  int b2 = digitalRead(sw2) & 0x01;
  int b4 = digitalRead(sw4) & 0x01;
  int b8 = digitalRead(sw8) & 0x01;
  int b = (b8 << 3) | (b4 << 2) | (b2 << 1) | b1;
  Serial.println(b);
  delay(10);
}

