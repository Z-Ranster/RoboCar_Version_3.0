//Imports
#include <SPI.h>              // needed for Arduino versions later than 0018
#include <AFMotor.h>          //Adafruit Motor Sheild
#include <SoftwareSerial.h>   //Replicates the Bluetooth port for the Bluetooth Module

//--Variables--
//Drive Motors
AF_DCMotor motorR(1);   
AF_DCMotor motorL(3);  

//MSC Drive
float fltPowerOne = 0;
float fltPowerTwo = 0;
boolean negR = false;
boolean negL = false;


//--Communication--
char charIncoming;
int intCurrentByte = 0;

//Bluetooth Communication
//Bluetooth Definition
int rx = 14;
int tx = 15;
SoftwareSerial Bluetooth(rx, tx); //Position 1: RX, Position 2: TX
int noSignal = 0;

//Driverstation Variables
int intInputNum = 4;        //Make sure that this value matches those that are below
float DSInput[4];           //Controller input is put here
String DSInputName[]={"Zero Axis", "First Axis", "Second Axis", "Third Axis", "Fourth Axis"};      //Names of the input channels are put here
int DSRefInput[] {97, 98, 99, 100, 101};  //ASCII to Byte letter conversions (lowecase 'a' starts at 97 and goes up by one each time.

//Special Function Variables
AF_DCMotor motor3(3);   //Make sure to come back and make names better later
AF_DCMotor motor4(4);   //Make sure to come back and make names better later

//--Functions and Methods--
//Communication Methods
//Method that handles checking all of the incoming messages and setting the correct varriables from it
void CheckMessage() {
  charIncoming = Bluetooth.read();
  
  if(charIncoming == 'a') {
    DSInput[0] = Bluetooth.parseFloat();
   }
  else if (charIncoming == 'b') {
    DSInput[1] = Bluetooth.parseFloat();
   }

}

//Drive Methods
void Drive(){
 /* if(DSInput[0]>=0){
  negL = false;
  fltPowerOne = (-1*DSInput[0]*255);
  }else if(DSInput[0]<0){
  negL = true;
  fltPowerOne = (-1*DSInput[0]*255); 
  }
  if(DSInput[1]>=0){
  negR = false;
  fltPowerTwo = (-1*DSInput[1]*255);
  }else if(DSInput[1]<0){
    negR = true;
    fltPowerTwo = (-1*DSInput[1]*255);  
  }
  if(negL == true){
        motorL.run(BACKWARD);
        motorL.setSpeed(fltPowerOne);
        //Serial.print("Motor FL Backward Speed: ");
        //Serial.println(-fltPowerOne);
      }
    if (negL == false){
        motorL.run(FORWARD);
        motorL.setSpeed(fltPowerOne);
        //Serial.print("Motor FL Forward Speed: ");
        //Serial.println(fltPowerOne);
      } 
    if(negR == true){
        motorR.run(BACKWARD);
        motorR.setSpeed(fltPowerTwo);
        //Serial.print("Motor FR Backward Speed: ");
        //Serial.println(-fltPowerTwo);
      }
    if (negR == false){
        motorR.run(FORWARD);
        motorR.setSpeed(fltPowerTwo);
        //Serial.print("Motor FR Forward Speed: ");
        //Serial.println(fltPowerTwo);
     }*/
     //--------------------------------------------------------------------------The section directly above this and the section directly below this is what may or may not work (it is the logic for driving the tank treds)
     //negL and negR are booleans used to set the direction of the motors (forwards or backwards)
     //fltPowerTwo is used for motorR speed, fltPowerOne is used for motorL speed
     //DSInput[0] is used to store the float from the controller for motorR speed calulation
     //DSInput[1] is used to store the float from the controller for motorL speed calulation
     //--------------Also the only change that is between V1 and the V2 of this file is that the below section is commented out in V1 and the top is not commented out. The opposite is true for V2 of this file. It is proved with the logic the way Michael originally provided it.
  fltPowerOne = (-1*DSInput[0]*255);//+(DSInput[1]*255);
  fltPowerTwo = (-1*DSInput[1]*255);//+(-1*DSInput[1]*255);
  if(fltPowerOne >255){
      fltPowerOne = 255;
     }
    else if (fltPowerOne < -255){
      fltPowerOne = -255;
     }
    if(fltPowerTwo >255){
      fltPowerTwo = 255;
     }
    else if (fltPowerTwo <-255){
      fltPowerTwo = -255;
     }
    
    if(fltPowerOne <= 0){
        motorL.run(BACKWARD);
        motorL.setSpeed(-fltPowerOne);
        //Serial.print("Motor FL Backward Speed: ");
        //Serial.println(-fltPowerOne);
      }
    if (fltPowerOne>0){
        motorL.run(FORWARD);
        motorL.setSpeed(fltPowerOne);
        //Serial.print("Motor FL Forward Speed: ");
        //Serial.println(fltPowerOne);
      } 
    if(fltPowerTwo <= 0){
        motorR.run(BACKWARD);
        motorR.setSpeed(-fltPowerTwo);
        //Serial.print("Motor FR Backward Speed: ");
        //Serial.println(-fltPowerTwo);
      }
    if (fltPowerTwo>0){
        motorR.run(FORWARD);
        motorR.setSpeed(fltPowerTwo);
        //Serial.print("Motor FR Forward Speed: ");
        //Serial.println(fltPowerTwo);
     }
}

void NoBluetoothCommunication() {
  Bluetooth.println("!--NO Bluetooth--!");
  noSignal += 1;
  if (noSignal > 40){
    noSignal = 0;    //if you have over 3 seconds of packet loss, the robot will stop moving.
    //DriveMotorR(0, true);  //Not sure if this actually can work
    //DriveMotorL(0, true);  //Note sure if this actually can work
      motorL.setSpeed(0);
      motorL.run(FORWARD);
      motorR.setSpeed(0);//even if you don't need all of these motors, other people do.
      motorR.run(FORWARD);  
      //Serial.println("!--No Bluetooth for 60ms so robot has stopped moving--!");
  }
  delay(40); // delay for 60ms for rough timing on the packet loss shutdown
}

//--Initial Setup Code--
void setup()  {
  //--Start Communications--
  Bluetooth.begin(9600);
  //Serial.begin(9600);
  //Serial.println("!--Communication Started--!");
  
  //--Initialize Car Default State--
  //Drive Motors
  motorL.setSpeed(0);
  motorL.run(FORWARD);
  motorR.setSpeed(0);//even if you don't need all of these motors, other people do.
  motorR.run(FORWARD);
  //Serial.println("!--Robot Initalized and Ready to Go--!");
}

//--Primary Loop--
void loop()  {
  //Bluetooth connection determines path of main loop
  while(Bluetooth.available()>0){
    CheckMessage();
    //Finish code to actually drive the robot and do the math for tank drive
    Drive();
   }

  //The following runs if there is no Bluetooth connection
  NoBluetoothCommunication();
}
 
