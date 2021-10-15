#include <Arduino.h>
#include "EmonLib.h"
#include <driver/adc.h>

// The GPIO pin were the CT sensor is connected to (should be an ADC input)
#define ADC_INPUT 34

// The voltage in our apartment. Usually this is 230V for Europe, 110V for US.
// Ours is higher because the building has its own high voltage cabin.
#define HOME_VOLTAGE 247.0


// Force EmonLib to use 10bit ADC resolution
#define ADC_BITS    10
#define ADC_COUNTS  (1<<ADC_BITS)

EnergyMonitor emon1;

void setup()
{
  adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
  analogReadResolution(10);
  Serial.begin(115200);

  // Initialize emon library (30 = calibration number)
  emon1.current(ADC_INPUT, 111.1);

}

void loop(){

  double amps = emon1.calcIrms(1480); // Calculate Irms only
  double watt = amps * HOME_VOLTAGE;  

  Serial.print("Current(A), ");
  Serial.println(amps);             // Irms

  Serial.print("Watt(W), ");
  Serial.println(watt);             // Irms

  delay(1000);
  


}
