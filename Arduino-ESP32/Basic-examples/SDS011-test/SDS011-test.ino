//Based on: https://github.com/FriskByBergen/SDS011/blob/master/arduino.ino

unsigned int Pm25 = 0;
unsigned int Pm10 = 0;

//Funtion to read 
void ProcessSerialData()
{
  uint8_t mData = 0;
  uint8_t i = 0;
  uint8_t mPkt[10] = {0};
  uint8_t mCheck = 0;
  while (Serial.available() > 0)
  {
    mData = Serial.read();     delay(2);//wait until packet is received
    if (mData == 0xAA) //head1 ok
    {
      mPkt[0] =  mData;
      mData = Serial.read();
      if (mData == 0xc0) //head2 ok
      {
        mPkt[1] =  mData;
        mCheck = 0;
        for (i = 0; i < 6; i++) //data recv and crc calc
        {
          mPkt[i + 2] = Serial.read();
          delay(2);
          mCheck += mPkt[i + 2];
        }
        mPkt[8] = Serial.read();
        delay(1);
        mPkt[9] = Serial.read();
        if (mCheck == mPkt[8]) //crc ok
        {
          Serial.flush();
          Pm25 = (uint16_t)mPkt[2] | (uint16_t)(mPkt[3] << 8);
          Pm10 = (uint16_t)mPkt[4] | (uint16_t)(mPkt[5] << 8);
          if (Pm25 > 9999)
            Pm25 = 9999;
          if (Pm10 > 9999)
            Pm10 = 9999;
          return;
        }
      }
    }
  }
}

void setup() {
    Serial.begin(9600, SERIAL_8N1);
    Pm25 = 0;
    Pm10 = 0;
}

void loop() {
  ProcessSerialData();

  Serial.println("==============================");
  Serial.print("Pm2.5 ");
  Serial.print(float(Pm25) / 10.0);
  Serial.println();//
  
  Serial.print("Pm10 ");
  Serial.println(float(Pm10) / 10.0);
  Serial.println("==============================\n");
  delay(500);

}
