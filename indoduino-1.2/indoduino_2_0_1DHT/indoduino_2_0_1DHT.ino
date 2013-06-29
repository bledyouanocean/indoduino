#include "DHT.h"

#define DHTPIN1 2
//#define DHTPIN2 3

#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);

//DHT dht2(DHTPIN2, DHTTYPE);

#include <Wire.h>
#include "RTClib.h"

#include <NewPing.h>

#define TRIGGER_PIN  5  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

RTC_DS1307 RTC;

const int moistPin1 = A0;     // moisture sensor pin
const int moistPin2 = A1;     // sencond moisture sensor pin
const int relayPin1 = 12;     // light relay pin
const int relayPin2 = 11;     //watering spike pumps
const int relayPin3 =  8;     
const int timerPin = 13;       // Timer LED.
const int fanPin = 10;
const int heaterRelay = 9;
const int pumpPin1 = 6; //aquaponics pumps
const int pumpPin2 = 7; //aquaponics pumps
int inByte = 0;
int lightState = 0;
int moistState1 = 0;
int moistState2 = 0;
int waterLevel =0;
      // variables for reading the moisture sensor, light, and pump statuses
int pumpState1 = 0;
int pumpState2 = 0;
int heatState = 0;
int pumpTimer = LOW;
int Hour = 0;
int Minute = 0;
int Second = 0;
int fanState = 0;
int Temp = 0;
int humid = 0;
int Readt = 0;
int Readh = 0;



long previousMillis = 0;



long interval = 43200000;   // 12 hours

void setup() {
  Serial.begin(57600);
  // initialize the relay pins as outputs:
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(timerPin, OUTPUT);
  pinMode(heaterRelay, OUTPUT);
  // initialize the moisture sensors pins as inputs:
  pinMode(moistPin1, INPUT);
  pinMode(moistPin2, INPUT);
 pinMode(fanPin, OUTPUT); 
 pinMode(pumpPin1, OUTPUT);
  pinMode(pumpPin2, OUTPUT);
  
  // digitalWrite(relayPin2, HIGH);
  // digitalWrite(relayPin3, HIGH);
  
  
  
  //digitalWrite(heaterRelay, HIGH);
 float t1 = dht1.readTemperature();
    float h1 = dht1.readHumidity();
    


    Wire.begin();
    RTC.begin();
    if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  

   
 // following line sets the RTC to the date & time this sketch was compiled
    
 // RTC.adjust(DateTime(__DATE__, __TIME__));
}
void loop(){
  
 

 
  
  
   
  
   DateTime now = RTC.now();
   
      Hour = now.hour();
    Minute = now.minute();
    Second = now.second();
    
    
   // float t1 = dht1.readTemperature();
   // float h1 = dht1.readHumidity();
    
    if (Hour == 0 && Minute == 0 && now.second() == 0) 
   checkWater();
   
   
   if (Hour > 6 && Hour < 19)
  digitalWrite(relayPin1, LOW);
else
digitalWrite(relayPin1, HIGH);
    
  
 if (now.second() == 0 || now.second() == 30) { 
 // float h1 = dht1.readHumidity();
 // float t1 = dht1.readTemperature();
 // float h2 = dht2.readHumidity();
 // float t2 = dht2.readTemperature();
  
Readt = dht1.readTemperature();
Readh = dht1.readHumidity();

Temp = Readt;
humid = Readh;
   if (Temp < 20) {
    digitalWrite(heaterRelay, LOW);
    
    digitalWrite(fanPin, HIGH);
    
  }
 else if (Temp > 26 || humid > 54 && Temp > 21) {
    digitalWrite(fanPin, LOW);
    digitalWrite(heaterRelay, HIGH);
  }
  else {
  digitalWrite(fanPin, HIGH);
    digitalWrite(heaterRelay, HIGH);
    }
  


 }

delay(2000);
  // read the state of the moisture sensor value:
  moistState1 = analogRead(moistPin1);
  moistState2 = analogRead(moistPin2);
  // check if the sensors are high.
  
  if (moistState1 >= 500 )     

    digitalWrite(pumpPin1, LOW);
  else
    digitalWrite(pumpPin1, HIGH);



  // repeat process above with second sensor.
  if (moistState2 >= 500)

    digitalWrite(pumpPin2, LOW);

  else
    digitalWrite(pumpPin2, HIGH);
    
    
    
    
     
    
    if (Minute < 15) 
    {
    
    digitalWrite(relayPin2, LOW);
   // digitalWrite(pumpPin2, LOW);
    }
    
    else 
    {
    
    digitalWrite(relayPin2, HIGH);
    //digitalWrite(pumpPin2, HIGH);
    }
    

   
  // from here on is the timer for the lights.
  // as you can see above i have a VERY high number
  // as my time interval. that is because arduino 
  // counts time in milliseconds. 
  // that number is 12 hours worth of milliseconds and, of corse, light.
    unsigned long currentMillis = millis();
    /*

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (lightState == LOW)
      lightState = HIGH;
    else
      lightState = LOW;

    // set the light relay with the ledState of the variable:
    digitalWrite(relayPin1, lightState);
  }
 
  
  */
 

  // i call this the oven timer. when the lights have gone through
  // an 8 week cycle it will turn on an LED to let you know to start
  // looking for signs of a good harvest.
  if(currentMillis > interval * 112) {
    digitalWrite(timerPin, HIGH);
    delay(100);
    digitalWrite(timerPin, LOW);
    Serial.print(" DING! Fries are done!     ");
    Serial.print("\n");    //should occurr on the 56th day.
    
  }
  else
    digitalWrite(timerPin, LOW);


  //if (Serial.available() > 0) {
    

   // inByte = Serial.read();
    
    Serial.println();

Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
  


    if (currentMillis <= 3600000){
      Serial.print("minutes: ");
      Serial.print(((currentMillis)/1000)/60)/60;
    }
    else if (currentMillis >= 3600000){
      Serial.print("Hour: ");
      Serial.print((((currentMillis)/1000)/60)/60)/60;
    }
    else 
    {
      Serial.print("day: ");
      Serial.print(((((currentMillis)/1000)/60)/60)/60)/24;
    }
    
    
    
    
    
    Serial.print("\n");
    if (digitalRead(relayPin2) == 0)
    
    Serial.print("\t Aquaponics pumps: ON");
    else
    Serial.print("\t Aquaponics pumps: OFF");
    Serial.print("\n");
    
    
  /*  if (moistState2 > 950) {
    Serial.println("\t Grow bed empty!");
    }
    else if (moistState2 < 950 && moistState2 > 350) {
      Serial.println("\t Grow bed filling!");
    }
    else {
      Serial.println("\t Grow bed full!");
    }
    
  
    */
    
    if (waterLevel > 50)
    Serial.print("water is low!");
    else
    Serial.println();


    Serial.print("\n");
    Serial.print("\t Soil 1 state:");
    Serial.println(moistState1);
   // Serial.print("\n");
    Serial.print("\t Soil 2 state:");
    Serial.println(moistState2);
    Serial.println();
   

    Serial.print("\t humidity 1: ");
    Serial.print(humid);
    Serial.print("%\t");
    Serial.print("\n");
   // Serial.print("\t humidity 2: ");
  //  Serial.print(h2);
  //  Serial.print("%\t");
  //  Serial.print("\n");
    Serial.print("\t temp 1: ");
    Serial.print((Temp * 1.8) + 32);
    Serial.print("\n");
    //Serial.print("\t temp 2: ");
   // Serial.print((t2* 1.8) + 32);
    
     Serial.print("\n");

int heatstate = digitalRead(heaterRelay);

if(heatstate == HIGH) 
Serial.print("\t Heater status: OFF");

else 
 Serial.print("\t Heater status: ON");




   Serial.print("\n");
    fanState = (digitalRead(10));
    if(fanState == LOW) {
      Serial.print("\t Fan status: ON");
     
      Serial.print("\n");
    }
    else if(fanState == HIGH)
    {
      Serial.print("\t Fan status: OFF");
     
      Serial.print("\n");
    }
    pumpState1 = digitalRead(6);
    pumpState2 = digitalRead(7);
    lightState = (digitalRead(relayPin1));
    if(pumpState1 == 0)
      Serial.print("\t Soil pump 1 status: ON");
    
    else 
    
      Serial.print("\t Soil pump 1 status: OFF");
    
    Serial.print("\n");

    if(pumpState2 == 0)
      Serial.print("\t Soil pump 2 status: ON");
    
    else if(pumpState2 == 1)
      Serial.print("\t Soil pump 2 status: OFF");
      
      Serial.println();

     
      
   lightState = (digitalRead(relayPin1));

    if(lightState == 0) 
    Serial.print("\t light status: ON");
    else 
    Serial.print("\t light status: OFF");
    
    
   Serial.print("\n");
   // Serial.println(analogRead(A0));
Serial.print(Temp);
  
  }

  



void checkWater() {
  
 
 unsigned int uS = sonar.ping();
 
 waterLevel = (uS / US_ROUNDTRIP_CM);
  }










