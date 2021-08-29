/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include "EmonLib.h"
// Include Emon Library
EnergyMonitor emon1;
// Create an instance
#define fadePin 9


unsigned long myMilli, mySec, myMin, myHour = 0;
String fileName, extName, stringThree;
int EEsize = 1024; // size in bytes of your board's EEPROM

//fileName = String("log-"); 

void setup() {

  Serial.begin(9600);    

  emon1.current(1, 111.1);             // Current: input pin, calibration.
  pinMode(fadePin, OUTPUT);
  

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }  

}

void loop() {

  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  double appPower = Irms*230.0;

  /*

  Serial.println("255"); 

  analogWrite(fadePin, 255);

  delay(5000); 

  Serial.println("200"); 

  analogWrite(fadePin, 200);
  
  delay(5000); 

  Serial.println("150"); 

  analogWrite(fadePin, 150);

  delay(5000); 

  Serial.println("0"); 

  analogWrite(fadePin, 0);

*/

  if (Serial.available() > 0) {

    // read incoming serial data:

    char inChar = Serial.read();

    // Type the next ASCII value from what you received:

    Serial.print(inChar); 

    if (inChar == '1')
    {
      
      Serial.println("option 1 chosen - 255");
      analogWrite(fadePin, 255); 

    }
    else if(inChar == '2')
    {
      Serial.println("option 2 chosen - 200");
      analogWrite(fadePin, 200); 
      
    }

    else if(inChar == '3')
    {
      Serial.println("option 2 chosen - 175");
      analogWrite(fadePin, 175); 
      
    }

    
    else if(inChar == '4')
    {
      Serial.println("option 2 chosen - 150");
      analogWrite(fadePin, 150); 
      
    }

    else if(inChar == '5')
    {
      Serial.println("option 2 chosen - 100");
      analogWrite(fadePin, 100); 
      
    }

    else if(inChar == '6')
    {
      Serial.println("option 2 chosen - 50");
      analogWrite(fadePin, 50); 
      
    }


    else if(inChar == '0')
    {
      Serial.println("option 2 chosen - 0");
      analogWrite(fadePin, 0);       
    }


    else
    {
      Serial.println("option other chosen"); 
      
    }

  }

  if (mySec == 60)
  {
    mySec = 0;
    myMin = myMin + 1;
  }
  else if(myMin == 60)
  {
    myMin = 0;
    myHour = myHour + 1;
  }

  Serial.print(myHour);           // Apparent power
  Serial.print(":");
  Serial.print(myMin);
  Serial.print(":");
  Serial.print(mySec);
  Serial.print(" ");
  Serial.print(appPower);           // Apparent power
  Serial.print(" ");
  Serial.println(Irms);             // Irms
  delay(1000); 

  mySec = mySec + 1;  

  
  // nothing happens after setup
}
