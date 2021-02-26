//Based on: https://github.com/adafruit/Adafruit_SGP30

#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

/* return absolute humidity [mg/m^3] with approximation formula
* @param temperature [°C]
* @param humidity [%RH]
*/

uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}


//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Setup---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void setup() {
  Serial.begin(9600);

  if (! sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }else{
    Serial.print("Found SGP30 serial #");
    Serial.print(sgp.serialnumber[0], HEX);
    Serial.print(sgp.serialnumber[1], HEX);
    Serial.println(sgp.serialnumber[2], HEX);
  }
  // If you have a baseline measurement from before you can assign it to start, to 'self-calibrate'
  //sgp.setIAQBaseline(0x8E68, 0x8F41);  // Will vary for each sensor!
  //sgp.setIAQBaseline(0x8F0C, 0x89D4);  // Will vary for each sensor! You will get it after 30 iterations, see below
}

int counter = 0;


//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Loop---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void loop() {
  // If you have a temperature / humidity sensor, you can set the absolute humidity to enable the humditiy compensation for the air quality signals
  float temperature = 30.1; // [°C]
  float humidity = 60.2; // [%RH]
  sgp.setHumidity(getAbsoluteHumidity(temperature, humidity));

  //TVOC & eCO2
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }else{
    Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.println(" ppb\t");
    Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");
  }

  //Raw H2 & Ethanol
  if (! sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return;
  }else{
    Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.println(" \t");
    Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");
  }
  delay(1000);

  //Used to get the calibration values
  counter++;
  if (counter == 30) {
    counter = 0;

    uint16_t TVOC_base, eCO2_base;
    if (! sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {
      Serial.println("Failed to get baseline readings");
      return;
    }else{
      Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
      Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
    }
    
  }
  Serial.println("#################################");
}
