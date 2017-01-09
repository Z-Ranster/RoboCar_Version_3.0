//Variable Declarations
//**** H ****
//Horn                    //** Horn Does Not Appear to Be working
int pn_Horn = 42;
//**** L ****
//Light - Indicator
int LED_Status = 26;
//**** M ****
//Motor Definitions
int Speed = 200; // Motor Speeds Duty Cycle Range: 0 - 255
// Motor A Definition (Output 1, 2)
int ASpeedPin = 9; 
int AInput1 = 8;   // Define Motor A I1 Interface
int AInput2 = 11;   // Define Motor A I2 Interface
// Motor B Definition (Output 3, 4)
int BSpeedPin = 10;
int BInput1 = 12;   // Define Motor B I1 Interface
int BInput2 = 13;    // Define Motor B I2 Interface
//**** S ****
//Serial Communication Definitions
int Serial_Speed = 9600;
//**** T ****
//TMP Variables

//Classes
//**** M ****
//Motor Clockwise Configureation    **Need to add in varriables to determine which motor to turn A or B
void Motor_Clockwise(){

}

//Program Startup
void setup() {
  //Serial Begin
  Serial.begin(Serial_Speed);
  Serial.println("!! - S - System Starting! - !!");
  
  //Initial Test Code
  //Enable TMP Items

  //Enable and Set Motor Speeds
  analogWrite(ASpeedPin,Speed); //Analog Write to Generate PWW to Control Motor Speed
  analogWrite(BSpeedPin,10); //Analog Write to Generate PWW to Control Motor Speed

  //Turn Motors
  //Stop = 1-->LOW + 2-->LOW or 1-->HIGH + 2-->HIGH or 1-->No Input + 2-->No Input
  //Clockwise =  !-->Low + 2-->HIGH
  //Anticlockwise = 1-->HIGH + 2-->LOW
  digitalWrite(AInput1, LOW);
  digitalWrite(AInput2, HIGH);
  
  digitalWrite(BInput1, LOW);
  digitalWrite(BInput2, HIGH);
  
  //Final Comments
  Serial.println("!! - S - System Ready! - !!");
  digitalWrite(pn_Horn, HIGH);
  delay(50);
  digitalWrite(pn_Horn, LOW);
}

//Continuous Loop
void loop() {
  //Initial Test Code
  digitalWrite(LED_Status, HIGH);
  Serial.println("!! - U - LED_Status: HIGH - !!");
  delay(1500);
  digitalWrite(LED_Status, LOW);
  Serial.println("!! - U - LED_Status: LOW - !!");
  delay(1500);
}
