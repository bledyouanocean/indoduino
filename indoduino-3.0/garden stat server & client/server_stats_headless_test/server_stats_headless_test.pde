import processing.serial.*;
import processing.net.*;

int port = 9997;
Serial myPort;        // The serial port

Server myServer;

void setup () {
  // set the window size:
  
 
  myServer = new Server(this, port);
  // List all the available serial ports
 // println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 57600);
  // set inital background:
 
}

void draw () {

}        



void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    myServer.write(inString);
 
   
    }
 
  }



