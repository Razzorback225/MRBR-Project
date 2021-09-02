#define ZCD_PIN 19
#define GC_PIN 18

int delta

void setup() {
  // put your setup code here, to run once:
  pinMode(ZCD_PIN, INPUT);
  pinMode(GC_PIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ZCD_PIN), setTrackVoltage, FALLING);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(GC_PIN, LOW);  
  if(Serial.available() > 0){
    String spdPerc = Serial.readStringUntil('#');
    delta = map(spdPerc, 0, 100, 8500, 0);
  }
  digitalWrite(GC_PIN, LOW);
}

void setTrackVoltage(){
  delayMicroseconds(volt);
  digitalWrite(GC_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(GC_PIN, LOW);
}
