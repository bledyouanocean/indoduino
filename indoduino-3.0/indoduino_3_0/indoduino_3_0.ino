#include "DHT.h"
#include <Wire.h>
#include "RTClib.h"


#define DHTPIN1 3
#define DHTTYPE DHT11

DHT dht1(DHTPIN1, DHTTYPE);


RTC_DS1307 RTC;


const int moistPin1 = A0;     // moisture sensor pin
const int moistPin2 = A1;     // sencond moisture sensor pin
const int relayPin1 = 12;     // light relay pin
const int relayPin2 = 11;     //watering spike pumps
const int masterPump = 2; //pin for soil pumps
const int fanPin = 10;   //fan.
const int heaterRelay = 9;  //heater.
const int pumpPin1 = 6; //soil sensor solenoid valve
const int pumpPin2 = 7; //solenoid valve 2

int lightState = 0;
int moistState1 = 0;
int moistState2 = 0;
int pumpState1 = 0;
int pumpState2 = 0;
int Hour = 0;
int Minute = 0;
int Second = 0;
int Temp = 0;
int humid = 0;
int heatState = HIGH;
int fanState = HIGH;
long timechanged = 0;
long interval = 120000;   



void setup() {
  
  
  
  Serial.begin(9600);

  // initialize the relay pins as outputs:
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(heaterRelay, OUTPUT);
  pinMode(fanPin, OUTPUT); 
  pinMode(pumpPin1, OUTPUT);
  pinMode(pumpPin2, OUTPUT);
  pinMode(masterPump, OUTPUT);

  // initialize the moisture sensors pins as inputs:
  pinMode(moistPin1, INPUT);
  pinMode(moistPin2, INPUT);

  digitalWrite(relayPin1, HIGH);
  digitalWrite(relayPin2, HIGH);
  digitalWrite(fanPin, HIGH);
  digitalWrite(pumpPin1, HIGH);
  digitalWrite(pumpPin2, HIGH);
  digitalWrite(masterPump, HIGH);

  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    delay(500);

    adjustTemp();

    // following line sets the RTC to the date & time this sketch was compiled

    // RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void loop(){

  
  Temp = dht1.readTemperature();
  humid = dht1.readHumidity();

  // declare declare declare!
  unsigned long currentMillis = millis();

  DateTime now = RTC.now();

  Hour = now.hour();
  Minute = now.minute();
  Second = now.second();

  delay(1000);
  // i like you... simple. simplest, yet most important function.  
  lightTime();



  // two minutes before working magic again.
  if (currentMillis > (timechanged+interval)) {

    adjustTemp();

    timechanged=currentMillis;
  }



  //watering spikes
  waterPump();

  //timed water pump
  waterTime();

  //the serial output
  serialOut();

}


// 'CHA BRAH!







