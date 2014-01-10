import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import processing.net.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class server_stats_headless_test extends PApplet {




int port = 9997;
Serial myPort;        // The serial port

Server myServer;

public void setup () {
  // set the window size:
  
 
  myServer = new Server(this, port);
  // List all the available serial ports
 // println(Serial.list());
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 57600);
  // set inital background:
 
}

public void draw () {

}        



public void serialEvent (Serial myPort) {
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    myServer.write(inString);
 
   
    }
 
  }



  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "server_stats_headless_test" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
