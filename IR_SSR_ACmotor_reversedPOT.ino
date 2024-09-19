// Pin definitions
const int SSR_PIN = 9;  
const int POT_PIN = A0; 
const int IR_PIN = 8; 
 
void setup() {
  // Setup pin modes
  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);  // Ensure SSR is off initially
  
  pinMode(IR_PIN, INPUT);      // Set IR sensor pin as input
  
  // Set up serial communication for debugging (optional)
  Serial.begin(115200);
}

void loop() {
  // Read the IR sensor state (HIGH = interrupted, LOW = not interrupted)
  int irState = digitalRead(IR_PIN);
  
  // Read the potentiometer value (0 to 1023)
  int potValue = analogRead(POT_PIN);
  int pwmValue;

  if (irState == HIGH) {
    // If the IR sensor is interrupted, set motor speed to 100%
    pwmValue = 255;
  } else {
    // If the IR sensor is not interrupted, set motor speed to 10% or based on potentiometer
    pwmValue = map(potValue, 0, 1023, 25, 255);  // Map the pot value to 10% to 100% range
  }

  // Write the calculated PWM value to the SSR
  analogWrite(SSR_PIN, pwmValue);
  
  // Optional: Print values to Serial Monitor for debugging
  Serial.print("IR State: ");
  Serial.print(irState == HIGH ? "Interrupted" : "Not Interrupted");
  Serial.print("   Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print("   PWM Value: ");
  Serial.println(pwmValue);
  
  delay(10);  // Small delay for stability
}
