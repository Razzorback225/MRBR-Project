#define ZCD_PIN 19
#define GC_PIN 18

int delta;

void setup() {
  //Define pin mode
  pinMode(ZCD_PIN, INPUT);
  pinMode(GC_PIN, OUTPUT);
  //Define interrupt on input pin
  attachInterrupt(digitalPinToInterrupt(ZCD_PIN), setTrackVoltage, FALLING);
  //Init serial 
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(GC_PIN, LOW);  
  if(Serial.available() > 0){
    String spdPerc = Serial.readStringUntil('#');
    delta = map(spdPerc.toInt(), 0, 100, 8500, 0);
    Serial.print("Speed percentage : ");Serial.println(spdPerc);
    Serial.print("Delay value : ");Serial.println(delta);
  }
  digitalWrite(GC_PIN, LOW);
}

//Set track voltage according to the set microDelay
void setTrackVoltage(){
  delayMicroseconds(delta);
  digitalWrite(GC_PIN, HIGH);
  delayMicroseconds(500);
  digitalWrite(GC_PIN, LOW);
}
