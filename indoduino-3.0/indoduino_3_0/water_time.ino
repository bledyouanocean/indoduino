void waterTime() {
  
    if (Minute < 15) 
    digitalWrite(relayPin2, LOW);
    else 
    digitalWrite(relayPin2, HIGH);

}
