import processing.sound.*;
import processing.serial.*;
import static javax.swing.JOptionPane.*;

Amplitude amp;
AudioIn in;
Serial esp32;

final boolean debug = true;
int baudRate = 115200;

void setup() {
  String COMx, COMlist = "";
  try {
    if(debug) printArray(Serial.list());
    int i = Serial.list().length;
    if (i != 0) {
      if (i >= 2) {
        for (int j = 0; j < i;) {
          COMlist += char(j+'a') + " = " + Serial.list()[j];
          if (++j < i) COMlist += "\n\r";
        }
        COMx = showInputDialog(COMlist);
        if (COMx == null) exit();
        if (COMx.isEmpty()) exit();
        i = int(COMx.toLowerCase().charAt(0) - 'a') + 1;
      }
      String portName = Serial.list()[i-1];
      if(debug) println(portName);
      esp32 = new Serial(this, portName, baudRate);
      esp32.bufferUntil('\n');
    }
    else {
      showMessageDialog(frame,"Device is not connected to the PC");
      exit();
    }
  }
  catch (Exception e)
  { //Print the type of error
    showMessageDialog(frame,"COM port is not available (may\nbe in use by another program)");
    println("Error:", e);
    exit();
  }
  
  size(640, 360);
  background(255);
    
  // Create an Input stream which is routed into the Amplitude analyzer
  amp = new Amplitude(this);
  in = new AudioIn(this, 0);
  in.start();
  amp.input(in);
}      

void draw() {
  clear();
  float vol = amp.analyze() * 200;
  String output = Float.toString(vol);
  esp32.write(output + "\n");
  fill(127);
  stroke(0);
  ellipse(width/2, height/2, 10 + vol, 10 + vol);
}
