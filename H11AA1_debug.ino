const int ZERO_CROSS_PIN = 2;  // Pin connected to H11AA1

void setup() {
  pinMode(ZERO_CROSS_PIN, INPUT_PULLUP);  // Zero-cross input pin
  
  Serial.begin(115200);
  
  // Attach interrupt for zero-cross detection
  attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), zeroCrossISR, FALLING);
  Serial.println("Zero-cross detection test started...");
}

void loop() {
  // Empty loop, everything is handled by the interrupt for zero-cross detection
}

// Zero-crossing detection ISR
void zeroCrossISR() {
  Serial.println("Zero-cross detected!");
}
