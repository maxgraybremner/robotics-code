//include servo and I2C libraries 
#include<Servo.h>
#include<Wire.h>

//define sensor and motor pins
int light_sensor = A0;
float temp_sensor = A1;
int soil_sensor = A2;
int servoMotor = 6;
Servo myServo;
int servoAngle = 0;


void setup(){
  //begine serial monitor
  Serial.begin(9600);
  //begin I2C communication
  Wire.begin();
  //initialise servo motor
  myServo.attach(servoMotor);
  //define sensor inputs 
  pinMode(light_sensor, INPUT);
  pinMode(temp_sensor, INPUT);
  pinMode(soil_sensor, INPUT);
}

void loop()
{
//map the moisture sensor to a percentage
int moisture = map(analogRead
(soil_sensor), 0, 876, 0, 99);
  
//map temp sensor to display celcius 
int temp = map(analogRead
(temp_sensor), 20, 359, -40, 125);

//map light sensor as a percentage
int light = map(analogRead
(light_sensor), 0, 290, 0, 99);
  
 //send sensor data  
 Wire.beginTransmission(1);
 Wire.write(temp);
 Wire.write(light);
 Wire.write(moisture);
 Wire.endTransmission();
 delay(100);
  
//-------------servo motor logic-------------------//
  
//first condition - if 
//moisture is below 25% AND
//temp is above 10 degrees AND
//light is abover 25%
if (moisture <= 25 && temp >= 10 && light >= 25){
  	servoAngle = 180;
    myServo.write(servoAngle);
  	//open the servo valve all the way
  
//second condition - if 
//moisture is below 35% AND
//temp is above 10 degrees AND
//light is abover 30%
} else if(moisture <= 35 && temp >= 10 && light >= 30) {
  	servoAngle = 120;
    myServo.write(servoAngle);
  	//open servo valve 2/3 of the way 
  
//Third condition - if 
//moisture is below 45% AND
//temp is above 24 degrees AND
//light is abover 80%
} else if (moisture <= 45 && temp >= 24 && light >= 60){
    servoAngle = 60;
    myServo.write(servoAngle);
  	//open servo valve 1/3 of the way

//else valve is closed 
} else {
  servoAngle = 0;
  myServo.write(servoAngle);
  }
}


