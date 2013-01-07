import processing.serial.*;
 
 Serial myPort;        // The serial port
 int xPos = 1;         // horizontal position of the graph
 int yPos = 1;




 void setup () {
 // set the window size:
 size(1250, 250);        
 
 // List all the available serial ports
 println(Serial.list());
 // I know that the first port in the serial list on my mac
 // is always my  Arduino, so I open Serial.list()[0].
 // Open whatever port is the one you're using.
 myPort = new Serial(this, Serial.list()[1], 9600);
 


 // don't generate a serialEvent() unless you get a newline character:
 
 myPort.bufferUntil('\n');
 // set inital background:
 background(0);
 textFont(createFont("Georgia", 14));
   
 }
 void draw () {
  


 }
  


 
 // everything happens in the serialEvent()

 
 void serialEvent (Serial myPort) {
  
   
 // get the ASCII string:
 
 String inString = myPort.readStringUntil('\n');
 
 
 if (inString != null) {
   myPort.write("'");
 // trim off any whitespace:
 inString = trim(inString);
 
 // convert to an int and map to the screen height:
 float inByte = float(inString); 
 inByte = map(inByte, 0, 1023, height, 0);
 
 
 

   stroke(255,0,0);
   line(xPos, height, xPos, height - inByte);
   
   
   
 }
 
 
 
 // at the edge of the screen, go back to the beginning:
 if (xPos >= width) {
 xPos = 0;
 yPos = 0;
 background(0); 
 } 
 else {
 // increment the horizontal position:
 xPos++;
 }
 }


 
 
 


