/* Arduino code to read in ultrasonic sensors for obstacle avoidance 
* Multiple HC SR04 will need to move together on the moving tritrack to detect obstacles  
* and move the tritrack away from it accordingly. 
*  --- 17ELD002, R ASANTE, Group G - Created: 22/01/2018*/
//40 full backwards
//140 forwards
//declare 90

#include <Servo.h>
#define L_Trig 4
#define L_Echo 5
#define R_Trig 2
#define R_Echo 3
#define output_mbed 2
Servo servo_CH1;
Servo servo_CH2;   
long duration;  
long distance;
void setup() {  
  Serial.begin (9600);  
  pinMode(L_Trig, OUTPUT);  
  pinMode(R_Trig, OUTPUT);  
  pinMode(R_Echo, INPUT);  
  pinMode(L_Echo, INPUT);  
  pinMode (output_mbed, OUTPUT);
  //TriTrack Wheel Setup   
  servo_CH1.attach(8); //CH1 wire  
  servo_CH2.attach(9); //CH2 wire}
void loop() {
  //Serial.print("Right");  
  //Serial.println(SonarSensor(L_Trig, L_Echo));  
  //Serial.print("Left");   
  //Serial.println(SonarSensor(R_Trig, R_Echo));
 if (SonarSensor(L_Trig, L_Echo) <= 10 or SonarSensor(R_Trig, R_Echo) <= 10){
   if(SonarSensor(L_Trig, L_Echo) > SonarSensor(R_Trig, R_Echo)) {      
     Serial.println("TURN LEFT");      
     turnLeft();    
   }    
   else if(SonarSensor(R_Trig, R_Echo) > SonarSensor(L_Trig, L_Echo)) {      
     Serial.println("TURN RIGHT");      
     turnRight();    
   }    
   else {         
     forward();    
     Serial.println("SAFE");    
   }  
 }  
  delay(100);
}
long SonarSensor(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW); //Clear Sensor ReadingsdelayMicroseconds(2);digitalWrite(trigPin, HIGH); //Begin ScandelayMicroseconds(10);digitalWrite(trigPin, LOW); //End Scanduration = pulseIn(echoPin, HIGH);distance = (duration/2) / 29.1;return distance;}
void forward() {  
  servo_CH1.write(140);  
  servo_CH2.write(140);}
void reverse() {  
  servo_CH1.write(40);  
  servo_CH2.write(40);
}
void turnRight() {  
  servo_CH1.write(140);  
  servo_CH2.write(40);  
}
  void turnLeft() {
    servo_CH1.write(40); 
    servo_CH2.write(135);
  }
void stopRobot() {
  servo_CH1.write(90); 
  servo_CH2.write(90);
}
