
void setup() {
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D7,HIGH);//red ligth(default LOW)
  digitalWrite(D6,HIGH);//red ligth(default LOW)
}

void loop(){
  digitalWrite(D6,LOW);//green ligth
  delay(1000);
  digitalWrite(D6,HIGH);
  delay(1000);
}
