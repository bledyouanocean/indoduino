#include "DHT.h"

#define DHTPIN1 2
#define DHTPIN2 3

#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);

DHT dht2(DHTPIN2, DHTTYPE);

#include <Wire.h>
#include "RTClib.h"

RTC_Millis RTC;


const int moistPin1 = A0;     // moisture sensor pin
const int moistPin2 = A1;     // sencond moisture sensor pin
const int relayPin1 = 11;     // light relay pin
const int relayPin2 = 12;     // watering spike pump relay pin
const int relayPin3 =  9;      // second watering pump relay pin
const int timerPin = 7;       // Timer LED.
const int fanPin = 6;
const int heaterRelay = 10;
const int deHum = 4;
int inByte = 0;
int lightState = HIGH;
int moistState1 = 0;
int moistState2 = 0;
int lightState3 = 0;      // variables for reading the moisture sensor, light, and pump statuses
int pumpState1 = 0;
int pumpState2 = 0;
int heatState = 0;

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
  digitalWrite(relayPin1, HIGH);
  digitalWrite(heaterRelay, LOW);

  establishContact();


 // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
}
void loop(){

  
  
   DateTime now = RTC.now();
    
    
  
  
  float h1 = dht1.readHumidity();
  float t1 = dht1.readTemperature();
  float h2 = dht2.readHumidity();
  float t2 = dht2.readTemperature();
  



  if (h1 >= 57) {
    digitalWrite(fanPin, HIGH);
    digitalWrite(deHum, HIGH);
  } 
  else {
    digitalWrite(deHum, LOW);
  }
  

  

   if (t1 <= 21.00) {
    digitalWrite(heaterRelay, HIGH);
    digitalWrite(fanPin, LOW);
    
    
  }
 else if (t1 >= 21.00) {
    digitalWrite(fanPin, HIGH);
    digitalWrite(heaterRelay, LOW);
  }
  




  // read the state of the moisture sensor value:
  moistState1 = analogRead(moistPin1);
  moistState2 = analogRead(moistPin2);
  // check if the sensors are high.
  // if it is, the buttonState is HIGH:
  if (moistState1 >= 500 )     

    digitalWrite(relayPin3, HIGH);
  else
    digitalWrite(relayPin3, LOW);



  //repeat process above with second sensor.
  if (moistState2 >= 500)

    digitalWrite(relayPin2, HIGH);

  else
    digitalWrite(relayPin2, LOW);
  // from here on is the timer for the lights.
  // as you can see above i have a VERY high number
  // as my time interval. that is because arduino 
  // counts time in milliseconds. 
  // that number is 12 hours worth of milliseconds and, of corse, light.
    unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    if (lightState == LOW)
      lightState = HIGH;
    else
      lightState = LOW;

    // set the light relay with the ledState of the variable:
    digitalWrite(relayPin1, lightState);
  }

  // i call this the oven timer. when the lights have gone through
  // an 8 week cycle it will turn on an LED to let you know to start
  // looking for signs of a good harvest.
  if(currentMillis > interval * 112) {
    digitalWrite(timerPin, HIGH);
    Serial.print(" DING! Fries are done!     ");
    Serial.print("\n");    //should occurr on the 56th day.
    delay(10);
  }
  else
    digitalWrite(timerPin, LOW);


  if (Serial.available() > 0) {
    

    inByte = Serial.read();

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
    Serial.print("\t Soil 1 state:");
    Serial.print(moistState1);
    Serial.print("\n");

    Serial.print("\t Soil 2 state:");


    Serial.print(moistState2);
    Serial.print("\n");



    Serial.print("\t humidity 1: ");
    Serial.print(h1);
    Serial.print("%\t");
    Serial.print("\n");
    Serial.print("\t humidity 2: ");
    Serial.print(h2);
    Serial.print("%\t");
    Serial.print("\n");
    Serial.print("\t temp 1: ");
    Serial.print(t1);
    Serial.print("\n");
    Serial.print("\t temp 2: ");
    Serial.print(t2);
    
    





   Serial.print("\n");
    heatState = (digitalRead(10));
    if(heatState == HIGH) {
      Serial.print("\t heater status: ON");
      Serial.print("\n");
    }
    else if(heatState == LOW)
    {
      Serial.print("\t heater status: OFF");
      Serial.print("\n");
    }
    pumpState1 = map(digitalRead(9), 0, 1, 0, 1);
    pumpState2 = map(digitalRead(12), 0, 1, 0, 1);
    lightState3 = map(digitalRead(11), 0, 1,0, 1);
    if(pumpState1 == 1){
      Serial.print("\t pump 1 status: ON");
    }
    else 
    {
      Serial.print("\t pump 1 status: OFF");
    }
    Serial.print("\n");

    if(pumpState2 == 1){
      Serial.print("\t pump 2 status: ON");
    }
    else if(pumpState2 == 0)
      Serial.print("\t pump 2 status: OFF");

    Serial.print("\n");

    if(lightState3 == 1) {

      Serial.print("\t light status: ON");
    }
    else {
      Serial.print("\t light status: OFF");
      
    }
    
    Serial.print("\n");
    Serial.println(analogRead(A0));
    
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(analogRead(A1));
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    
    
    Serial.print("\n");
    


  }
}



void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println('A');   // send a capital A
    delay(300);
  }
}


