int mydelay = 0;
int myvalue=0;
int last_CH1_state = 0;
int potValue = 0;  // To store potentiometer reading

void setup() {
  // Same as original code
  PCICR |= (1 << PCIE0);    // enable PCMSK0 scan                                                 
  PCMSK0 |= (1 << PCINT0);  // Set pin D8 trigger an interrupt on state change. Input from optocoupler
  pinMode(3,OUTPUT);        // Define D3 as output for the TRIAC pulse
  Serial.begin(9600);       // Start serial communication (Bluetooth)
}

void loop() {
   // Read the potentiometer value (0-1023) and map it to 10-10,000us
   potValue = analogRead(A0);  
   myvalue = map(potValue, 0, 1023, 10000, 10);  // Map potentiometer to control delay for TRIAC firing

   if (Serial.available() > 0) { 
      myvalue = map(Serial.read(), 0, 255, 10000, 10);  // Bluetooth control as an alternative
   }
    
   if (mydelay) {
      delayMicroseconds(myvalue);  // This delay controls the power (speed)
      digitalWrite(3, HIGH);
      delayMicroseconds(100);
      digitalWrite(3, LOW);
      mydelay = 0;
   } 
}

// Interrupt service routine for zero-cross detection
ISR(PCINT0_vect) {
  if (PINB & B00000001) {  // Pin 8 HIGH? Detecting zero-cross
    if (last_CH1_state == 0) {  // If previous state was LOW
      mydelay = 1;  // State change detected
    }
  } else if (last_CH1_state == 1) {  // Pin 8 LOW? State change from HIGH to LOW
    mydelay = 1;  // State change detected
    last_CH1_state = 0;  // Store current state
  }
}
