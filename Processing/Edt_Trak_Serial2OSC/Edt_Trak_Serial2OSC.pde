import netP5.*;
import oscP5.*;

import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() 
{
  size(200, 200);
  // Set your target IP adress (127.0.0.1 to send to your own PC) + port
  myRemoteLocation = new NetAddress("127.0.0.1", 8000);
  // Listening port is 12000, but we don't use it.
  oscP5 = new OscP5(this, 12000);
  
  printArray(Serial.list());
  // Change this to your own Serial port identifier, this is on a Mac
  // The serial BAUD rate should be the same as in the Arduino sketch
  myPort = new Serial(this, "/dev/cu.usbmodem14131", 1000000);
  // This is our line end, set in the Arduino sketch
  myPort.bufferUntil(':');
}

void draw()
{
  rect(50, 50, 100, 100);
}

void serialEvent (Serial myPort) {
  // Read until our separator (defined in Arduino sketch)
  String input  = myPort.readStringUntil(':');
  // Check if Trak (T) or Pedal (P)
  if(input.charAt(0) == 'P') {
    int button;
    try {
        button = Integer.parseInt(input.substring(2, 3));
      } catch (NumberFormatException e) {
        button = 0;
      }
    OscMessage myMessage = new OscMessage("/Pedal");
    myMessage.add(button);
    oscP5.send(myMessage, myRemoteLocation); 
  } else if (input.charAt(0) == 'T') {
    // Remove T- from start and : from the end and split
    String[] inputs = input.substring(2, input.length() - 1).split("-");
    // Create an int holder
    int[] values = new int[inputs.length];
    
    // Parse to ints, or set to 0 if garbage data (Arduino sends a lot of rubbish when turned on)
    for(int i = 0; i < inputs.length; i++) {
      try {
        values[i] = Integer.parseInt(inputs[i]);
      } catch (NumberFormatException e) {
        values[i] = 0;
      }
    }   
    // Send over OSC
    OscMessage myMessage = new OscMessage("/Trak");
    myMessage.add(values);
    oscP5.send(myMessage, myRemoteLocation);
  } else {
    println("rubbish");
  }
}