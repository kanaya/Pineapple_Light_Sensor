const int STATUS_INACTIVE = 0;
const int STATUS_ACTIVE   = 1;

int th = 400;

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
}

void loop() {
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
