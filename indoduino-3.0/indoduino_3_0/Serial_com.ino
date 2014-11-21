void serialOut() {
  
DateTime now = RTC.now();
   
Hour = now.hour();
Minute = now.minute();
Second = now.second();
    
unsigned long currentMillis = millis();
  
  
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
    else if (currentMillis >= 3600000 && ((((currentMillis)/1000)/60)/60)/60 <= 24) {
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
    Serial.println();
    Serial.print("\n");
    Serial.print("\t Soil 1 state:");
    Serial.println(moistState1);
    Serial.print("\t Soil 2 state:");
    Serial.println(moistState2);
    Serial.println();
    Serial.print("\t humidity 1: ");
    Serial.print(humid);
    Serial.print("%\t");
    Serial.print("\n");
    Serial.print("\t temp 1: ");
    Serial.print((Temp * 1.8) + 32);
    Serial.print("\n");
    Serial.print("\n");
    if(heatState == HIGH) 
    Serial.print("\t Heater status: OFF");
    else 
    Serial.print("\t Heater status: ON");
    Serial.print("\n");
    if(fanState == LOW) {
    Serial.print("\t Fan status: ON");
    Serial.print("\n");
    }
    else if(fanState == HIGH)
    {
     Serial.print("\t Fan status: OFF");
     Serial.print("\n");
    }
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
    if(lightState == 0) 
    Serial.print("\t light status: ON");
    else 
    Serial.print("\t light status: OFF");
    Serial.print("\n");
    Serial.print(Temp);

}
