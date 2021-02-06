//Based on: https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6

// defines pins numbers
const int trigPin = 26;
const int echoPin = 27;

// defines variables
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
  int distance;
  
  distance = getUltasonicDistance();
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");Serial.print(distance);Serial.println(" cm");
}

int getUltasonicDistance(){
  long duration;
  int distance;
  
  // Clears the trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigger into the HIGH state for 10 milli seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echo pin which is returning the sound wave travel time in milli seconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;
  
  return distance;
}
