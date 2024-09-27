// Pin Definitions
const int TRIAC_PIN = 9;      
const int ZERO_CROSS_PIN = 2;   
const int POT_PIN = A0;           

const int lookupTable[] = {
  0, 46, 93, 139, 185, 231, 277, 324, 370, 416, 462, 509, 555, 601, 647, 694, 740, 
  786, 832, 879, 925, 971, 1017, 1064, 1110, 1156, 1202, 1249, 1295, 1341, 1387, 
  1434, 1480, 1526, 1572, 1619, 1665, 1711, 1757, 1804, 1850, 1896, 1942, 1989, 
  2035, 2081, 2127, 2174, 2220, 2266, 2312, 2359, 2405, 2451, 2497, 2544, 2590, 
  2636, 2682, 2729, 2775, 2821, 2867, 2914, 2960, 3006, 3052, 3099, 3145, 3191, 
  3237, 3284, 3330, 3376, 3422, 3469, 3515, 3561, 3607, 3654, 3700, 3746, 3792, 
  3839, 3885, 3931, 3977, 4024, 4070, 4116, 4162, 4209, 4255, 4301, 4347, 4394, 
  4440, 4486, 4532, 4579, 4625, 4671, 4717, 4764, 4810, 4856, 4902, 4949, 4995, 
  5041, 5087, 5134, 5180, 5226, 5272, 5319, 5365, 5411, 5457, 5504, 5550, 5596, 
  5642, 5689, 5735, 5781, 5827, 5874, 5920, 5966, 6012, 6059, 6105, 6151, 6197, 
  6244, 6290, 6336, 6382, 6429, 6475, 6521, 6567, 6614, 6660, 6706, 6752, 6799, 
  6845, 6891, 6937, 6984, 7030, 7076, 7122, 7169, 7215, 7261, 7307, 7354, 7400, 
  7446, 7492, 7539, 7585, 7631, 7677, 7724, 7770, 7816, 7862, 7909, 7955, 8001, 
  8047, 8094, 8140, 8186, 8232, 8279, 8333
};

volatile boolean zeroCrossDetected = false;  
int potValue = 0;                            
int delayTime = 0;                           
int angle = 0;                              

void setup() {
  pinMode(TRIAC_PIN, OUTPUT);               
  digitalWrite(TRIAC_PIN, LOW);             
  pinMode(ZERO_CROSS_PIN, INPUT_PULLUP);    
  
  attachInterrupt(digitalPinToInterrupt(ZERO_CROSS_PIN), zeroCrossISR, FALLING);

  Serial.begin(115200);
}

void loop() {
  // Read potentiometer value (0 to 1023)
  potValue = analogRead(POT_PIN);

  angle = map(potValue, 0, 1023, 0, 180);

  delayTime = lookupTable[angle];

  if (zeroCrossDetected) {
    zeroCrossDetected = false;  // Reset zero-cross flag

    // Print the calculated delay time and angle
    Serial.print("Potentiometer Value: ");
    Serial.print(potValue);
    Serial.print("   Angle: ");
    Serial.print(angle);
    Serial.print("°   Delay Time (µs): ");
    Serial.println(delayTime);

    // Fire the TRIAC after the calculated delay
    delayMicroseconds(delayTime);
    
    // Trigger the TRIAC via MOC3021
    digitalWrite(TRIAC_PIN, HIGH);  
    delayMicroseconds(delayTime);
    //digitalWrite(TRIAC_PIN, LOW);  
  }

  delay(10); 
}

void zeroCrossISR() {
  zeroCrossDetected = true; 
}
