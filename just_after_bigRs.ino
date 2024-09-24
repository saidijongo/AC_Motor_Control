// Pin definitions
const int TRIAC_PIN = 9;  // Pin to trigger MOC3021
const int ZERO_CROSS_PIN = 2;  // Zero-cross detection from H11AA1
const int POT_PIN = A0;  // Potentiometer for speed control

volatile boolean zeroCrossDetected = false;  // Flag for zero-cross detection
int delayTime = 0;  // Delay time for phase angle control

void setup() {
  // Set up pin modes
  pinMode(TRIAC_PIN, OUTPUT);  // Output to MOC3021 to trigger TRIAC
  digitalWrite(TRIAC_PIN, LOW);  // Ensure TRIAC is off initially
  pinMode(ZERO_CROSS_PIN, INPUT_PULLUP);  // Zero-cross input pin

  // Attach interrupt for zero-cross detection
  attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), zeroCrossISR, FALLING);

  // Set up serial communication for debugging (optional)
  Serial.begin(115200);
}

void loop() {
  // Read potentiometer value (0 to 1023)
  int potValue = analogRead(POT_PIN);
  
  // Map potentiometer value to phase angle delay (0 to 8333 microseconds)
  delayTime = map(potValue, 0, 1023, 500, 8333);  // Increase minimum delay for testing
  
  // Wait for zero-cross detection
  if (zeroCrossDetected) {
    zeroCrossDetected = false;  // Reset zero-cross flag
    
    // Delay the firing of TRIAC according to the phase angle
    delayMicroseconds(delayTime);
    
    // Fire the TRIAC to control motor speed
    fireTriac();
  }

  // Optional: Print values to Serial Monitor for debugging
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("   Delay Time (microseconds): ");
  Serial.println(delayTime);
  
  delay(10);  // Small delay for stability
}

// Zero-crossing detection ISR
void zeroCrossISR() {
  zeroCrossDetected = true;  // Set flag when zero-cross is detected
  Serial.println("Zero-cross detected!");  // Debugging: Print zero-cross detection
}

// Fire the TRIAC by sending a pulse to MOC3021
void fireTriac() {
  digitalWrite(TRIAC_PIN, HIGH);  // Trigger the TRIAC
  delayMicroseconds(50);  // Longer pulse for TRIAC triggering
  digitalWrite(TRIAC_PIN, LOW);  // Turn off after the pulse
}
