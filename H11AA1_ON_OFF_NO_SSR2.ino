const int inputPin = 2;  // Pin connected to H11AA1 output
int value = 0;

void setup() {
  Serial.begin(115200);
  pinMode(inputPin, INPUT); 
}

void loop(){
  value = digitalRead(inputPin); 
  
  if (value == HIGH) {
      Serial.println("OFF (No zero-cross detected)");
  } else {
      Serial.println("ON (Zero-cross detected)");
  }
  
  delay(1000); 
}
