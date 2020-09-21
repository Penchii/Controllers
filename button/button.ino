const int buttonPin = 2;
// variables will change:
int buttonState = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("BEEP BOOP-INITIALIZED");
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = analogRead(buttonPin);
  Serial.println(buttonState);
  /*
  if (buttonState == HIGH) {
    
  Serial.println("H");
  } else {
    
  Serial.println("L");
  }   
  */
}
