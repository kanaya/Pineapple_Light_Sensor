const int sw1 = 2;
const int sw2 = 3;
const int sw4 = 4;
const int sw8 = 5;

const int STATUS_INACTIVE = 0;
const int STATUS_ACTIVE   = 1;

const int th_min = 300;
const int th_step = 40;
int th = th_min + th_step * 8;

int current_status = STATUS_INACTIVE;

int sensorPins[3] = { A0, A1, A2 };
int sensorValues[3] = { 0, 0, 0 };
int ledPin = 13;

void send_midi_note_on() {
  Serial.write(0x90);
  Serial.write(10);
  Serial.write(127);
}

void send_midi_note_off() {
  Serial.write(0x80);
  Serial.write(10);
  Serial.write(0);
}
  
void setup() {
  Serial.begin(31250);
  pinMode(ledPin, OUTPUT);
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
  th = th_min + b * th_step;
  for (int i = 0; i < 3; ++i) {
    sensorValues[i] = analogRead(sensorPins[i]);
  } 
  if (sensorValues[0] >= th || sensorValues[1] >= th || sensorValues[2] >= th) {
    if (current_status == STATUS_INACTIVE) {
      current_status = STATUS_ACTIVE;
      digitalWrite(ledPin, 1);
      send_midi_note_on();
    }
  }
  if (sensorValues[0] < th && sensorValues[1] < th && sensorValues[2] < th) {
    if (current_status == STATUS_ACTIVE) {
      current_status = STATUS_INACTIVE;
      digitalWrite(ledPin, 0);
      send_midi_note_off();
    }
  }
}

