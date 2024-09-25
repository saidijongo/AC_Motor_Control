// Pin Definitions
const int PWM_PIN_HIN1 = 9;  // High-side MOSFET A (H-Bridge leg 1) - Timer1
const int PWM_PIN_LIN1 = 10; // Low-side MOSFET A (H-Bridge leg 1) - Timer1
const int PWM_PIN_HIN2 = 11; // High-side MOSFET B (H-Bridge leg 2) - Timer2
const int PWM_PIN_LIN2 = 12; // Low-side MOSFET B (H-Bridge leg 2) - Timer2
const int POT_PIN = A0;      // Potentiometer for speed control

void setup() {
  // Set up pins as outputs
  pinMode(PWM_PIN_HIN1, OUTPUT);
  pinMode(PWM_PIN_LIN1, OUTPUT);
  pinMode(PWM_PIN_HIN2, OUTPUT);
  pinMode(PWM_PIN_LIN2, OUTPUT);
  
  // Set Timer1 for 20kHz PWM on pins 9 and 10
  setupTimer1For20kHzPWM();
  
  // Set Timer2 for 20kHz PWM on pins 11 and 12
  setupTimer2For20kHzPWM();
}

void loop() {
  int potValue = analogRead(POT_PIN);  // Read the potentiometer
  int pwmValue = map(potValue, 0, 1023, 0, 800);  // Map to PWM duty cycle
  
  // Set PWM signals for both high-side and low-side MOSFETs
  OCR1A = pwmValue;        // Control pin 9 (HIN1)
  OCR1B = 800 - pwmValue;  // Control pin 10 (LIN1) - inverted signal
  
  OCR2A = pwmValue;        // Control pin 11 (HIN2)
  OCR2B = 800 - pwmValue;  // Control pin 12 (LIN2) - inverted signal
}

// Set Timer1 (pins 9 and 10) for 20kHz PWM
void setupTimer1For20kHzPWM() {
  // Set Fast PWM mode with ICR1 as top
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);  // No prescaler

  // Set the top value for 20kHz PWM
  ICR1 = 800;  // Top value (16MHz / (20kHz * 2)) = 800
}

// Set Timer2 (pins 11 and 12) for 20kHz PWM
void setupTimer2For20kHzPWM() {
  // Set Fast PWM mode with top value set by OCR2A
  TCCR2A = _BV(WGM21) | _BV(WGM20) | _BV(COM2A1) | _BV(COM2B1);
  TCCR2B = _BV(CS20);  // No prescaler

  // Set the top value for 20kHz PWM
  OCR2A = 800;  // Top value (approximately 20kHz)
}
