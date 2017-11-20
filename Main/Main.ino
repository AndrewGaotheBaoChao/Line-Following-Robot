#include <Servo.h>
#include <QTRSensors.h>

Servo myLservo;  // create servo object to control your left SERVO
Servo myRservo;  // create a 2nd servo object to control your right SERVO

#define NUM_SENSORS             2  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// sensors 0 through 5 are connected to analog inputs 0 through 5, respectively
QTRSensorsAnalog qtra((unsigned char[]) {0, 1}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  myRservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myLservo.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  // read raw sensor values
  qtra.read(sensorValues);
  // print the sensor values as numbers from 0 to 1023, where 0 means maximum reflectance and
  // 1023 means minimum reflectance
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t'); // tab to format the raw data into columns in the Serial monitor
    if (sensorValues[i] <= 1023 || sensorValues[i] >= 600){
        myLservo.write(0);
        myRservo.write(90);
      }
  }
  Serial.println();
  
  delay(250);
  
  myLservo.write(90); //servo should be STOPPED adjust with screw driver with Mr. St. Pierre's help
  myRservo.write(90); //servo should be STOPPED adjust with screw driver with Mr. St. Pierre's help

  //delay(2000);
  //myLservo.write(0); //full speed in ONE direction (Mr. Lenarduzzi's favourite band)
  //myRservo.write(180); //full speed in ONE direction (Mr. Lenarduzzi's favourite band)
  //delay(2000);
 
  //myLservo.write(180); //full speed in THE OTHER direction (Mr. Coulter's band name)
  //delay(2000);
 
  
}
