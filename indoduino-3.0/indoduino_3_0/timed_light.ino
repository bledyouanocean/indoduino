void lightTime() {
  
if (Hour > 6 && Hour < 19) {
  digitalWrite(relayPin1, LOW);
  lightState = LOW;
     }
else {
  digitalWrite(relayPin1, HIGH);
  lightState = HIGH;
     }
}
