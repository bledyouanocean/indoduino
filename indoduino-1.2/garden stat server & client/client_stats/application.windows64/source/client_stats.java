import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.net.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class client_stats extends PApplet {



int port = 9998;

int xPos = 51;         // horizontal position of the graph
int ypos = 8;

Client thisClient;

public void setup () {
  // set the window size:
  size(500, 300); 

  textFont(createFont("SanSerif", 8));

  thisClient = new Client(this, "24.27.6.17", port);

  background(0);
  frameRate(30); // Slow it down a little
}

public void draw () {

  stroke(100, 255, 50);
  line(50, 250, 50, 200);
  line(50, 200, 450, 200);
  line(50, 250, 450, 250);
  line(450, 250, 450, 200);

  // get the ASCII string:
 // if (thisClient != null) {
   
   if (thisClient.available() > 0) {
      String inString = thisClient.readStringUntil('\n');
      noFill();
      stroke(100, 255, 50);
      rect(51, 51, 200, 124);
      fill(255);
      text(inString, 53, ypos * 7);
      ypos++;
    
  
      // trim off any whitespace:
      inString = trim(inString);
      // convert to an int and map to the screen height:
      float inByte = PApplet.parseFloat(inString); 
      inByte = map(inByte, 0, 50, 50, 0);

      // draw the line:
      if (inByte >= 24) {
        stroke(127, 34, 255);
      }
      else { 
        stroke(255, 0, 0);
      }
      line(xPos, 250, xPos, 200 + inByte);
      // at the edge of the screen, go back to the beginning:
      if (xPos >= 400) {
        xPos = 51;
        background(0);
      } 
      else if (inByte > 0) {
      // increment the horizontal position:
        xPos++;
        //delay(500);
        ypos = 9;

        fill(0);
        stroke(100, 255, 50);
        rect(51, 51, 200, 124);
        
     // }
    }
  }
}


  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "client_stats" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
