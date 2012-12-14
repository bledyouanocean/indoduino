const int moistPin1 = A0;     // moisture sensor pin
const int moistPin2 = A1;     // sencond moisture sensor pin
const int relayPin1 = 11;     // light relay pin
const int relayPin2 = 12;     // watering spike pump relay pin
const int relayPin3 =  13;      // second watering pump relay pin
const int relayPin4 = 7;       // Timer LED.
int inByte = 0;
int lightState = HIGH;
int moistState1 = 0;
int moistState2 = 0;
int lightState3 = 0;      // variables for reading the moisture sensor, light, and pump statuses
int pumpState1 = 0;
int pumpState2 = 0;


long previousMillis = 0;



long interval = 43200000;   // 12 hours
void setup() {
  Serial.begin(9600);
  // initialize the relay pins as outputs:
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  // initialize the moisture sensors pins as inputs:
  pinMode(moistPin1, INPUT);
  pinMode(moistPin2, INPUT); 
  digitalWrite(relayPin1, HIGH);

  establishContact();

}
void loop(){


  // read the state of the moisture sensor value:
  moistState1 = analogRead(moistPin1);
  moistState2 = analogRead(moistPin2);
  // check if the sensors are high.
  // if it is, the buttonState is HIGH:
  if (moistState1 >= 500 )     

    digitalWrite(relayPin3, LOW);
  else
    digitalWrite(relayPin3, HIGH);



  //repeat process above with second sensor.
  if (moistState2 >= 500)

    digitalWrite(relayPin2, LOW);

  else
    digitalWrite(relayPin2, HIGH);
  // from here on is the timer for the lights.
  // as you can see above i have a VERY high number
  // as my time interval. that is because arduino counts time in milliseconds. that number is 12 hours worth of milliseconds and, of course, light.
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
  // looking for signs of a good harvest
  if(currentMillis > interval * 112) {
    digitalWrite(relayPin4, HIGH);
    Serial.print(" DING! Fries are done!     ");
    Serial.print("\n");
    delay(1000);
  }
  else
    digitalWrite(relayPin4, LOW);


  if (Serial.available() > 0) {

    inByte = Serial.read();

   
    
    Serial.print("\n");
    
    if (currentMillis <= 3600000){
      Serial.print("\t Elapsed minutes: ");
    Serial.print(((currentMillis)/1000)/60)/60;}
    else {
      Serial.print("\t Elapsed Hour:");
      Serial.print((((currentMillis)/1000)/60)/60)/60;}
    Serial.print("\n");
    Serial.print("\t Soil 1 state:");
    Serial.print(moistState1);
    Serial.print("\n");

    Serial.print("\t Soil 2 state:");


    Serial.print(moistState2);
    Serial.print("\n");









    pumpState1 = map(digitalRead(13), 0, 1, 0, 1);
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
    delay(432);



  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

