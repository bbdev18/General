#include "EmonLib.h"
#include <SoftwareSerial.h>
SoftwareSerial hc06(2,3);
// Include Emon Library
EnergyMonitor emon1;
EnergyMonitor emon2;
EnergyMonitor emon3;
// Create an instance
// int led = 8;   
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(led, OUTPUT);
  Serial.begin(9600);
  hc06.begin(9600);

  emon1.current(1, 111.1);             // Current: input pin, calibration.
  emon2.current(2, 111.1);             // Current: input pin, calibration.
  emon3.current(3, 111.1);             // Current: input pin, calibration.
  Serial.println("Starting recording, ");
}

void loop()
{

digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(500);                       // wait for a second
digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
delay(500);                       // wait for a second
double Irms = emon1.calcIrms(1480);  // Calculate Irms only
double Irms2 = emon2.calcIrms(1480);  // Calculate Irms only
double Irms3 = emon3.calcIrms(1480);  // Calculate Irms only
Irms = Irms / 2.0;
Irms2 = Irms2 / 2.0;
Irms3 = Irms3 / 2.0;

if ( (Irms > 1.9) || (Irms2 > 1.9) || (Irms3 > 1.9))
{
  Serial.print("P1(A), ");
  Serial.print(Irms);             // Irms
  
  Serial.print(",P2(A), ");
  Serial.print(Irms2);             // Irms
  
  Serial.print(",P3(A), ");
  Serial.println(Irms3);             // Irms
  
  hc06.print("P1(A), ");
  hc06.print(Irms);             // Irms
  
  hc06.print(",P2(A), ");
  hc06.print(Irms2);             // Irms
  
  hc06.print(",P3(A), ");
  hc06.println(Irms3);             // Irms
} 

}
