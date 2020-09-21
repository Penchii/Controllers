/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/
/*
 * This program is to be run on an Arduino Duemilanove.
 * It handles input for 
 *    1 Joystick(Analog)
 *    1 RotaryEncoder with button(Digital)
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

//Iterrupt service routing is executed when a HIGH or LOW transition is detected on CLK
void isr() {  
  if (digitalRead(PinCLK))
    up = digitalRead(PinDT);
  else
    up = !digitalRead(PinDT);

 turnDetected = true;
}
//---------------------------------------------------------------------------------------
// pressOn = is the button considered on? pressDown = is the button currently pressed down(comes from digital read) 
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
  attachInterrupt(0, isr, FALLING); //Interrupt 0 is always connected to pin 2

  pressOn = false;
  pressDown = false;
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  String outputString = "";
  
  /*---------------------JOYSTICK---------------------*/
  //-----READING INPUT------
  // When the button is pressed analogRead(__)== 0, otherwise it oscillated with high numbers.
  
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

  // JOYSTICK ONE
  outputString = outputString + "JOne";
  // x direction
  if(greenDown)
  {
    outputString = outputString + "2";
  } else if (yellowDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  
  // z direction
  if(orangeDown)
  {
    outputString = outputString + "2";
  } else if (redDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  
  // JOYSTICK TWO
  outputString = outputString + "JTwo";
  // x direction
  if(greenDown)
  {
    outputString = outputString + "2";
  } else if (yellowDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }
  
  // z direction
  if(orangeDown)
  {
    outputString = outputString + "2";
  } else if (redDown)
  {  
    outputString = outputString + "0";
  } else
  {
    outputString = outputString + "1";
  }

  /*---------------------DIAL---------------------*/  
  static long virtualPosition = 0; //Does not count properly without static
  
  //Is pushbutton pressed?
  pressDown = !digitalRead(PinSW);
  
  outputString = outputString + "RedOne";
  if(pressDown)
  {
    outputString = outputString + "1";
  } else
  {
    outputString = outputString + "0";
  }
  
  outputString = outputString + "RedTwo";
  if(pressDown)
  {
    outputString = outputString + "1";
  } else
  {
    outputString = outputString + "0";
  }

  // ROTARY-ENCODER-ONE
  outputString = outputString + "RotaryOne";

  if (turnDetected) { //Is rotation detected
    if (up)
      outputString = outputString + "2";
      //virtualPosition++;
     else
      outputString = outputString + "0";
      //virtualPosition--;

     turnDetected = false; //Do not repeat if (turnDetected) in loop until another rotation is detected
     
     //turnString = "C " + virtualPosition;
     //Serial.println(virtualPosition);
  }else
  {
    
      outputString = outputString + "1";
  }
  /*---------------------COMMON---------------------*/ 
  Serial.println(outputString);
  delay(100);        // delay in between reads for stability
}
