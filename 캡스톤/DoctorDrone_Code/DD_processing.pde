import processing.serial.*;

Serial myPort;        // The serial port

int[] val = new int[128];

void setup () {
  // set the window size:
  size(400, 600);

  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 115200);
  
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');

  // set inital background:
  background(255);
  rect(0, 0, 1024, 1024);
  stroke(255,0,0);
  noLoop();
  delay(2000);
}

void draw () {
    background(255);

    for (int i =4; i<128; i++){
      line(i*3 +1,height,i*3 +1,height-val[i]*4);
      
    }
}


void serialEvent (Serial myPort) {
  try{
      byte[] inByte = new byte[200];
      
      myPort.readBytesUntil('\n',inByte);
      
        // convert to an int and map to the screen height:
        for(int i = 0; i<128; i++){
         val[i] = int(inByte[i]);      
        }
        redraw();

  }catch(Exception e){
    println("Err");
  }
}
