// libraries
#include <Servo.h>
#include <QTRSensors.h>
#include <Ultrasonic.h>

Servo myLservo;  // create servo object to control your left SERVO
Servo myRservo;  // create a 2nd servo object to control your right SERVO

int sensorL; // left servo degrees
int sensorR; // right servo degrees

int distance; // distance variable
#define NUM_SENSORS             2  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// Setup QTR sensors and ultrasonic sensor
QTRSensorsAnalog qtra((unsigned char[]) {0, 1}, NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
Ultrasonic ultrasonic(9, 8);
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  myRservo.attach(10);  // attaches the servo on pin 10 to the servo object
  myLservo.attach(11);  // attaches the servo on pin 11 to the servo object
}

void loop()
{
  // read raw sensor values
  //qtra.read(sensorValues);
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum reflectance and 1023 means minimum reflectance
  sensorR = analogRead(A0); // Right servo is connected to analog A0
  sensorL = analogRead(A1); // Left servo is connected to analog A1

  // Pass INC as a parameter to get the distance in inches
  distance = ultrasonic.distanceRead();
  Serial.print(distance);
  delay(1000);
  
  if (sensorR <= 100  && sensorL <= 100){ // Move Forward
    myLservo.write(0);
    myRservo.write(180);
    }
  if (sensorR >= 150){ // When right sensor detects black tape
    myLservo.write(90);
    myRservo.write(90);
    }
  if (sensorL >= 150){ // When left sensor detects black tape
    myLservo.write(180);
    myRservo.write(180);
    }
  if (distance <= 10){ // When robot sees obstacle, it stops
    myLservo.write(90);
    myRservo.write(90);
    }
  // TESTING
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
  }
}
