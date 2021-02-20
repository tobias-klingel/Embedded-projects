//One wire
#define MAX_SENSORS 15

// Data wire which is connected to the middle pin of the DS18B20 sensor
#define ONE_WIRE_BUS 15

//##############################################

//One wire
#include <OneWire.h>
#include <DallasTemperature.h>

//##############################################
int num_sensors;
DeviceAddress addresses [MAX_SENSORS];


// Setup a one-wire instance to communicate with any One-wire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass one-wire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
//##############################################



//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Setup---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void setup(void) {
  Serial.begin(9600);

  //--------------------------------------------
  //DS18B20
  sensors.begin();

  //Get the number of sensors
  num_sensors = sensors.getDeviceCount();
  Serial.print("Found ");Serial.print(num_sensors);Serial.print(" device(s).");Serial.println();

  
  for (int i = 0; i < num_sensors; i++) {
    // Read its address
    sensors.getAddress(addresses[i], i);

    // Set to use 12 bit precision -> is the maximum.
    // Other choices are 9, 10 and 11
    sensors.setResolution(addresses[i], 12);

    // Print out a message
    Serial.print("Device ");Serial.print(i); Serial.print(" address is: "); printAddress(addresses[i]);Serial.println();
  }
  
}



//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Loop---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void loop() {

  //--------------------------------------------
  //DS18B20

  // Send the command to get temperatures
  sensors.requestTemperatures(); 

  //Last HEX of in order of the sensor positions
  //0x3C is the first sensor physically in my project, 0xF1 the second and so on
  byte sensorPosition[5] = {0x3C,0xF1, 0xA1, 0x9A, 0xF8};
  
  for(int i=0; i<num_sensors; i++){
    float temp_measurement = sensors.getTempCByIndex(i);
     Serial.print(getLastHexOfAddress(addresses[i]),HEX);Serial.print(" - Temperature: ");Serial.print(temp_measurement);Serial.println("C");
     byte LastHexOfAddress = getLastHexOfAddress(addresses[i]);
     int rowForSensor = findSensorPosition(LastHexOfAddress, sensorPosition);
     //...
     //...
  }

}

////####################################################################################################
////---------------------------------------------------------------------------------------------------
////-------------------------------------------Functions-----------------------------------------------
////---------------------------------------------------------------------------------------------------
////####################################################################################################

//==================================================================

// Function to print a device address
void printAddress(DeviceAddress addresses)
{
  for (int i = 0; i < 8; i++)
  {
    if (addresses[i] < 16) {
      Serial.print("0");
    }
    Serial.print(addresses[i], HEX);
    if (i < 7) {
      Serial.print(":");
    }
  }
}

//==================================================================

//Get the last Hex address of a sensor address
byte getLastHexOfAddress(DeviceAddress addresses)
{

    //Serial.print(addresses[7], HEX);
    return (addresses[7]);
}

//Need to compare the address with the position of the sensors to display them in the right order on the display.
int findSensorPosition(byte sensorLastHex, byte sensorPosition[]){

  int numOfPositions = sizeof(sensorPosition);
  for(int i=0; i<=numOfPositions; i++){
    if(sensorPosition[i]==sensorLastHex){
      return i;
    }
  }
  //If sensor address is not known print the sensor into row 5 (starting with 0)
  return 5;
}
