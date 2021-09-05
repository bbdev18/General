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

#include <SPI.h>
#include <SD.h>
#include "EEPROM.h"

#include "EmonLib.h"
// Include Emon Library
EnergyMonitor emon1;
// Create an instance

File myFile;

unsigned long myMilli, mySec, myMin, myHour = 0;
String fileName, extName, stringThree;
int EEsize = 1024; // size in bytes of your board's EEPROM

//fileName = String("log-"); 

void setup() {

  Serial.begin(9600);    

  emon1.current(1, 111.1);             // Current: input pin, calibration.
  

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("Loop - initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");


//EEPROM.write(position,date);
//EEPROM.write(0, 0);
int initialVal;

initialVal = EEPROM.read(0);

Serial.println("Eeprom read/write...");
Serial.println(initialVal);
initialVal = initialVal + 1;
EEPROM.write(0, initialVal);
Serial.println("Eeprom Write Done...");

extName = String(".txt");
fileName = String("Log_");

fileName = fileName + initialVal;
fileName = fileName + extName;
Serial.println(fileName);

  // open the file for reading:
  /*
  myFile = SD.open("test.txt");

  if (myFile) {
  Serial.println("test.txt:");
  // read from the file until there's nothing else in it:
  while (myFile.available()) {
  Serial.write(myFile.read());
  }
  // close the file:
  myFile.close();
  } else {
  // if the file didn't open, print an error:
  Serial.println("error opening test.txt");
  }
*/

}

void loop() {

  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  double appPower = Irms*230.0;
  
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

  EEPROM.write(1, mySec);

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
  myFile = SD.open(fileName, FILE_WRITE);
  myFile.print(myHour);           // Apparent power
  myFile.print(":");
  myFile.print(myMin);
  myFile.print(":");
  myFile.print(mySec);
  myFile.print(" ");
  myFile.println(appPower);           // Apparent power
  myFile.close();

  mySec = mySec + 1;  

  
  // nothing happens after setup
}
