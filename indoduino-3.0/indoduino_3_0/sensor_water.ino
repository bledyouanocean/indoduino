void waterPump() {

  // available pins 4,5,8,13
  // read the state of the moisture sensor value:
  moistState1 = analogRead(moistPin1);
  moistState2 = analogRead(moistPin2);
  // check if the sensors are high.

  if (moistState1 >= 500 )  {   
    digitalWrite(masterPump, LOW);
    digitalWrite(pumpPin1, LOW);
    pumpState1 = LOW;
  }
  else {
    digitalWrite(masterPump, HIGH);
    digitalWrite(pumpPin1, HIGH);
    pumpState1 = HIGH;

  }

  // repeat process above with second sensor.
  if (moistState2 >= 500) {
    digitalWrite(masterPump, LOW);

    digitalWrite(pumpPin2, LOW);
    pumpState2 = LOW;
  }

  else {
    digitalWrite(masterPump, HIGH);
    digitalWrite(pumpPin2, HIGH);
    pumpState2 = HIGH;
  }  

}






