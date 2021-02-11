//Based on: https://how2electronics.com/uv-sensor-ml8511-arduino-uv-ray-intensity-meter/

#define UVOUT 32 //Output from the sensor
#define REF_3V3 34 //3.3V power on the Arduino board


////####################################################################################################
////---------------------------------------------------------------------------------------------------
////-------------------------------------------Setup---------------------------------------------------
////---------------------------------------------------------------------------------------------------
////####################################################################################################

void setup()
{

  //#######################################################
  //Serial
  Serial.begin(9600); //Init serial port

  //#######################################################
  //ML8511
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);

}


////####################################################################################################
////---------------------------------------------------------------------------------------------------
////-------------------------------------------Loop---------------------------------------------------
////---------------------------------------------------------------------------------------------------
////####################################################################################################
void loop()
{
  
  int uvLevel = averageAnalogRead(UVOUT);
  int refLevel = averageAnalogRead(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float outputVoltage = 3.3 / refLevel * uvLevel;

  float uvIntensity = mapfloat(outputVoltage, 0.80, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level

  Serial.print("output: ");Serial.println(refLevel);
  Serial.print("ML8511 output: ");Serial.println(uvLevel);
  Serial.print("ML8511 voltage: ");Serial.println(outputVoltage);
  Serial.print("UV Intensity (mW/cm^2): ");Serial.println(uvIntensity);

  Serial.println("#######################");
  delay(2000);
}


////####################################################################################################
////---------------------------------------------------------------------------------------------------
////-------------------------------------------Functions-----------------------------------------------
////---------------------------------------------------------------------------------------------------
////####################################################################################################

//Takes an average of readings on a given pin and returns the average
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8;
  unsigned int runningValue = 0; 

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);  
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
