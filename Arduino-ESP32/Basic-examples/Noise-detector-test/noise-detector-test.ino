const int sensorPin = 34; //<------- You might need to adjust this pin
int counts = 0;

void setup() {
   Serial.begin(9600);
   pinMode(sensorPin,INPUT);
   interrupts();
   digitalWrite(sensorPin, LOW);                 
   attachInterrupt(sensorPin, Noise_impulse, RISING);  
}

void loop() {
  Serial.print("Noise count: "); Serial.println(counts);
  counts = 0;
  delay(1000);
  Serial.println("----------------------");
  
}


//Interrupt function which will called if PIN 34 has a rising voltage
void Noise_impulse() {             
    counts++; //Increase counter for each interrupt
}
