/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

/*---------------------JOYSTICK---------------------*/
const byte ledPin = 13; //Saves memory

// The integer input from the joystick, between 0 & 255(?)
int greenInput, yellowInput, orangeInput, redInput;

// Is the corresponding button currently pressed?
bool greenOn, yellowOn, orangeOn, redOn;

// Conversion from integer input to a bool 
bool greenDown, yellowDown, orangeDown, redDown;


/*---------------------DIAL---------------------*/
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
String resetString;
String turnString;

bool pressOn, pressDown;


// -----------------------------------------------SETUP------------------------------------------------------------------//
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("BEEP BOOP. I'M ALIVE!");
  
  /*---------------------JOYSTICK---------------------*/
  greenOn = false;
  greenDown = false;
  
  yellowOn = false;
  yellowDown = false;  
  
  orangeOn = false;
  orangeDown= false;
  
  redOn = false;
  redDown = false;
  
  /*---------------------DIAL---------------------*/
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);
  resetString = "";
  turnString = "";
  attachInterrupt(0, isr, FALLING); //Interrupt 0 is always connected to pin 2

  pressOn = false;
  pressDown = false;
  
}

// the loop routine runs over and over again forever:
void loop() {
  /*---------------------JOYSTICK---------------------*/
  //-----READING INPUT------
  // GREEN: read the input on analog pin 0:
  greenInput = analogRead(A0);
  greenDown = (greenInput == 0);
   
  // YELLOW: read the input on analog pin 1:
  yellowInput = analogRead(A1);
  yellowDown = (yellowInput == 0);
  
  // ORANGE: read the input on analog pin 0:
  orangeInput = analogRead(A2);
  orangeDown = (orangeInput == 0);
  
  // RED: read the input on analog pin 1:
  redInput = analogRead(A3);
  redDown = (redInput == 0);

  //-----SEND INPUT TO UNITY -----
  // println is sent to Unity
  // /*
  
  // GREEN: print out the value you read:
  if(greenDown != greenOn) // Has the state changed?
  {
    greenOn = greenDown;
    
    // Serial.println(greenInput);
    if(greenOn){
      Serial.println("greenJ1On");
    }else{
      Serial.println("greenJ1Off");
    }
  }

  // YELLOW: print out the value you read:
  if(yellowDown != yellowOn)
  {
    yellowOn = yellowDown;
    
    // Serial.println(yellowInput);
    if(yellowOn){
      Serial.println("yellowJ1On");
    }else{
      Serial.println("yellowJ1Off");
    }
  }
  
  // ORANGE: print out the value you read:
  if(orangeDown != orangeOn)
  {
    orangeOn = orangeDown;
    
    // Serial.println(orangeInput);
    if(orangeOn){
      Serial.println("orangeJ1On");
    }else{
      Serial.println("orangeJ1Off");
    }
  }
  
  // RED: print out the value you read:
  if(redDown != redOn)
  {
    redOn = redDown;
    
    // Serial.println(redInput);
    if(redOn){
      Serial.println("redJ1On");
    }else{
      Serial.println("redJ1Off");
    }
  }
// */

  /*---------------------DIAL---------------------*/  
  static long virtualPosition = 0; //Does not count properly without static
  
  //Is pushbutton pressed?
  pressDown = !digitalRead(PinSW);

  if(pressDown != pressOn)
  {
    pressOn = pressDown;
    
    // Serial.println(redInput);
    if(pressOn){
      Serial.println("J1pressOn");
    }else{
      Serial.println("J1pressOff");
    }
  }

  if (turnDetected) { //Is rotation detected
    if (up)
      Serial.println("R1+");
      //virtualPosition++;
     else
      Serial.println("R1-");
      //virtualPosition--;

     turnDetected = false; //Do not repeat if (turnDetected) in loop until another rotation is detected
     
     turnString = "C " + virtualPosition;
     //Serial.println(virtualPosition);
  }
  /*---------------------COMMON---------------------*/ 
  delay(100);        // delay in between reads for stability
}
