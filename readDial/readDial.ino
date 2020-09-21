//https://forum.arduino.cc/index.php?topic=242356.0 

volatile boolean turnDetected;
volatile boolean up;

const int PinCLK = 2; //Generates interrupts using CLK signal
const int PinDT = 3; //Reads DT signals
const int PinSW = 4; //Used for the push button switch(?)

void isr() {  //Iterrupt service routing is executed when a HIGH or LOW transition is detected on CLK
  if (digitalRead(PinCLK))
    up = digitalRead(PinDT);
  else
    up = !digitalRead(PinDT);

 turnDetected = true;
}


void setup() {
  // put your setup code here, to run once:
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);

  attachInterrupt(0, isr, FALLING); //Interrupt 0 is always connected to pin 2
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  static long virtualPosition = 0; //Does not count properly without static

  if (!digitalRead(PinSW)) { //Is pushbutton pressed?
    virtualPosition = 0; //If yes, reset counter to zero
    Serial.print("Reset = ");
    Serial.println(virtualPosition);
  }

  if (turnDetected) { //Is rotation detected
    if (up)
      virtualPosition++;
     else
      virtualPosition--;

     turnDetected = false; //Do not repeat if (turnDetected) in loop until another rotation is detected

     Serial.println("Count= " + virtualPosition);
     
  }

  
}
