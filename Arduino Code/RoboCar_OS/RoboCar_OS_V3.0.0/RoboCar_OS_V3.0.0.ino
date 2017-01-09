#include <SPI.h>
#include <Arduino.h>
#include <AFMotor.h>
#include <EthernetUdp.h>
#include <Ethernet.h>

/*
  Turns on an LED on for one second, then off for one second, repeatedly.
*/
//Driving State Variables
char car[4];

//Camera Variables
char camera[4];

//Network Variables
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);

unsigned int localPort = 8888;      //Local Port to listen to

//Instance of Ethernet UDP to send and received packets through
EthernetUDP Udp;

//Buffers for sending and receiving variables
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
char ReplyBuffer[] = "acknowledged";

//Driving Variables
AF_DCMotor DriveMotor(4);
AF_DCMotor TurnMotor(2);

AF_DCMotor testMotor(1);

//Light Variables
int lights[] = {6, 8, 9, 10};        //6 = Front 8 = Brake 9 = Right Turning 10 = Left Turning
int lightCount = 4;

//Other Variables
int horn = 11;
int timer = 800;
char input[UDP_TX_PACKET_MAX_SIZE];

void setup()
{
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
    //Initalize output values
    //Lights
  for (int thisPin = 0; thisPin < lightCount; thisPin++)  {
    pinMode(lights[thisPin], OUTPUT);
  }
	// Initialize Other Pinouts
  Serial.begin(9600);
    //Horn
  pinMode(horn, OUTPUT);

  //Initalize Drive Motors off
  DriveMotor.setSpeed(0);
  TurnMotor.setSpeed(0);

  //Turn Running Lights On
  analogWrite(lights[0], 5);      //Set to 5 to dim and 255 to make bright
}

//Horn
void hornControll(){
    if (input[5] = 'h')
    {
        digitalWrite(horn, HIGH);
    }
    else if(input[5] = 'l')
    {
        digitalWrite(horn, LOW);
    }
}

//Turn Signal Controll
void turnSignal(){
  if (input[0] == 'a')
  {
    digitalWrite(lights[0], HIGH);
    delay(timer);
    digitalWrite(lights[0], LOW);
    delay(timer);
  }
   else if(input[8] == 'l')
  {
    digitalWrite(lights[0], LOW);
  }
  if (input[8] == 't')
  {
    digitalWrite(lights[1], HIGH);
    delay(timer);
    digitalWrite(lights[1], LOW);
    delay(timer);
  }
  else if(input[8] == 'x')
  {
    digitalWrite(lights[1], LOW);
  }
}

void loop()
{
    //Data available, read packet
    int packetSize = Udp.parsePacket();
    if(packetSize)
    {
        //Packet Information
        Serial.print("Received packet size: ");
        Serial.println(packetSize);
        Serial.print("From: ");
        //Remote Ip Information
        IPAddress remote = Udp.remoteIP();
// TODO (Stanley#1#): Understand how to do this code
        for (int i =0; i < 4; i++)
            {
                Serial.print(remote[i], DEC);
        if (i < 3)
            {
                Serial.print(".");
        }
        }
        //Port Information
        Serial.print(", port: ");
        Serial.println(Udp.remotePort());

        //Read the packet into the PacketBuffer
        Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
        for (int i =0; i < 14; i++)
        {
            input[i] = packetBuffer[i];
        }
    //Print out the buffer information
    Serial.println("Contents:");
    Serial.println(packetBuffer);

     // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();

  }
      //Handle The information
    turnSignal();
  delay(10);
}
