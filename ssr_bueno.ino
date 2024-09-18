// Pin definitions
const int SSR_PIN = 9;         // Pin connected to SSR control input (via resistor)
const int POT_PIN = A0;        // Pin connected to the potentiometer

void setup() {
  // Setup pin modes
  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);   // Ensure SSR is off initially
  
  // Set up serial communication for debugging (optional)
  Serial.begin(115200);
}

void loop() {
  // Read the potentiometer value (0 to 1023) and map to PWM range (0 to 255)
  int potValue = analogRead(POT_PIN);
  int pwmValue = map(potValue, 0, 1023, 0, 255);  // Map to PWM range
  
  analogWrite(SSR_PIN, pwmValue);
  
  delay(10);  // Small delay for stability
}
