#include <Servo.h>

#define trigPin1 5
#define echoPin1 6
#define trigPin2 9
#define echoPin2 10
#define moisturePin A0
#define fullThreshold 4 // Threshold distance to consider the dustbin full (in centimeters)
#define dustbinHeight 20 // Height of the dustbin (in centimeters)
#define moistureThreshold 800 // Threshold value for moisture sensor

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(moisturePin, INPUT);
  servoMotor.attach(11);
}

void loop() {
  long duration1, distance1, duration2, distance2;
  
  // Ultrasonic Sensor 1 (for triggering servo motor)
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 * 0.0343) / 2;
  
  // Ultrasonic Sensor 2 (for measuring dustbin fullness)
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 * 0.0343) / 2;
  
  // Moisture Sensor Reading
  int moistureValue = analogRead(moisturePin);
  
  // Print sensor readings to serial monitor
  Serial.print("Distance (Sensor 1): ");
  Serial.print(distance1);
  Serial.println(" cm");
  Serial.print("Distance (Sensor 2): ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print("Moisture: ");
  Serial.println(moistureValue);
  
  // Check if the dustbin is full
  if (distance2 <= fullThreshold) {
    Serial.println("Dustbin is full!");
    // Trigger servo motor
    servoMotor.write(90); // Rotate servo to 90 degrees
    delay(1000); // Wait for servo to complete rotation (adjust as needed)
    servoMotor.write(0); // Rotate servo back to 0 degrees
    // Here you can add code to trigger an alert or perform any other action
  } else {
    Serial.println("Dustbin is not full.");
  }

  // Check moisture level
  if (moistureValue >= moistureThreshold) {
    Serial.println("Object is dry.");
  } else {
    Serial.println("Object is wet.");
  }
  
  // Wait for a short time before taking the next measurement
  delay(6000); // Adjust the delay time according to your requirements
}

