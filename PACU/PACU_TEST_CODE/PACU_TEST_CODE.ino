#ifdef __AVR__
//Define pins for AVR chip family
#define ZCD_PIN 2
#define GC_PIN 8

#elif __XTENSA__
//Define pins for ESP chip family 
#define ZCD_PIN 18
#define GC_PIN 19

#endif

int delta = 10000;

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
  //Serial.println(0);
}

//Set track voltage according to the set microDelay
void setTrackVoltage(){
  //Serial.println(1);
  delayMicroseconds(delta);
  digitalWrite(GC_PIN, HIGH);
  delayMicroseconds(100);
  digitalWrite(GC_PIN, LOW);
}
