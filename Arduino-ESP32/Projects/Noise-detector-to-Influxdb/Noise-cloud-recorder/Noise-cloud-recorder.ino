//Based on: https://how2electronics.com/capacitive-soil-moisture-sensor-esp8266-esp32-oled-display/

#include "AACredentials.h"
#include "AAGlobalConfig.h"

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#define DEVICE "ESP32"
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#define DEVICE "ESP8266"
#endif

//####################################################################################################
//Sensor pin configs
 
const int sensorPin = 34;

//Variables
long int counts = 0;
int firstLoop = true;

//####################################################################################################
//Influx

// InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

// Data point
Point sensor("Vibration-recorder-test");

 //####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Setup---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################

void setup() {
  //#################################
   Serial.begin(9600);
   pinMode(sensorPin,INPUT);
   interrupts();
   digitalWrite(sensorPin, LOW);               
   attachInterrupt(sensorPin, Noise_impulse, RISING); 
   
  //#################################
  // Setup wifi
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to wifi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  //#################################
  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  //#################################
  
}
 

//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Loop---------------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################
void loop() {
  
  //#################################
  //Prints noise counts to serial console
  Serial.print("Vibration: "); Serial.println(counts);
  

  
  //#################################
  // Clear fields for reusing the point. Tags will remain untouched
  sensor.clearFields();
  
  if(firstLoop != true){ //Does not record the first iterration
    sensor.addField("Vibration counts",counts);
  }
  counts = 0; //Resets counter back to 0
  firstLoop = false; //Set to false if the loop run at least once
  //#################################
  
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  //#################################
    //Delay until next iterrarion 
  int waitingTime_ms = 15000;
  Serial.print("--------> Wait "); Serial.print(waitingTime_ms);Serial.println(" ms, until next sensor data request <--------");
  delay(waitingTime_ms);
  Serial.println("------------------------------------------");

}


//####################################################################################################
//---------------------------------------------------------------------------------------------------
//-------------------------------------------Functions-----------------------------------------------
//---------------------------------------------------------------------------------------------------
//####################################################################################################

//Interrupt function which will called if PIN 26 has a falling voltage
void Noise_impulse() {             
    counts++; //Increase counter for each interrupt (It captures each event form the sensor)
    //Serial.print("Interrupt"); Serial.println(counts);

}
