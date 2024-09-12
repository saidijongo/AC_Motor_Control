
#include "DHT.h"
#define DHTPIN 2          //DHT22 digital pin to Arduino pin connection

// Uncomment the sensor you are using i am using DHT22
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22     // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 test!");
  pinMode(7, OUTPUT);     //SSR switching on/off pin
  dht.begin();            //Begin sensor operation
}

void loop() {
  delay(2000);    //2 seconds delay 

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature(); 

  Serial.print("Temperature: ");
  Serial.print(t);           //Print temperature on serial monitor
  Serial.print(" *C ");

  if(t<=22){    //Temperature less than 22 *C switch off AC(Air Conditioner)
    digitalWrite(7, LOW); 
    }

  if(t>=23){    //Temperature greater than 22 *C switch on AC(Air Conditioner)
    digitalWrite(7, HIGH); 
    }

}
