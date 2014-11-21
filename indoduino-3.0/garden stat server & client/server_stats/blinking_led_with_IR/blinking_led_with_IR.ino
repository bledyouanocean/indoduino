

#include <IRremote.h>

int RECV_PIN = 11;
int pinOne = 9;
IRrecv irrecv(RECV_PIN);

decode_results results;

boolean led = false;

void setup() {
    
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(pinOne, OUTPUT);
  digitalWrite(pinOne, HIGH);
}



void loop() {
  
  
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    
    switch (results.value) {
  
  
case 0xFF58A7:
   {
     if (led == false) {
     digitalWrite(pinOne, LOW);
     Serial.println("LED is ON");
     led = true;
     }
     else {
     digitalWrite(pinOne, HIGH);
     led = false;
     Serial.println("LED is OFF");
     }
   }
   
break;


case 0xFF50AF:
   {
     
   }
   break;


case 0xFF00FF:
   {
   }
   break;


case 0xFF20DF:
   {
   }
   break;


case 0xFF12ED:
   {
   }
   break;


case 0xFF02FD:
   {
   }
   break;
   
   
case 0xFFA857:
   {
   }
   break;
   
  
case 0xFF8877:
   {
   }
   break;  

case 0xFFD827:
   {
   }
   break;
   

case 0xFF9867:
   {
   }
   break;
   

case 0xFF08F7:
   {
   }
   break;
   
    }
   
   

   irrecv.resume();
    
   }
}
   
   

