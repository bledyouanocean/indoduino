

void adjustTemp() {

  Temp = dht1.readTemperature();
  humid = dht1.readHumidity();

  if (Temp < 20) {
    digitalWrite(heaterRelay, LOW);

    digitalWrite(fanPin, HIGH);
    heatState = LOW;
    fanState = HIGH;
  }
  else if (Temp > 26 || humid > 54 && Temp > 21) {
    digitalWrite(fanPin, LOW);
    digitalWrite(heaterRelay, HIGH);
    heatState = HIGH;
    fanState = LOW;
  }
  else {
    digitalWrite(fanPin, HIGH);
    digitalWrite(heaterRelay, HIGH);
    heatState = HIGH;
    fanState = HIGH;
  }


}



