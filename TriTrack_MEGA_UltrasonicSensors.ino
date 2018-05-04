/* Arduino code to read in ultrasonic sensors for obstacle avoidance 
* Multiple HC SR04 will need to move together on the moving tritrack to detect obstacles  
* and move the tritrack away from it accordingly.
*  --- 17ELD002, R ASANTE, Group G - Created: 22/01/2018 */
#include <Servo.h>
#define L_Trig 4
#define L_Echo 5
#define R_Trig 2
#define R_Echo 3
#define Edge_Trig 6 
#define Edge_Echo 7
#define turnleft 8
#define turnright 9
#define reverse 10
#define forward 11
#define stoptritrack 12

Servo servo_CH1; //Left leg
Servo servo_CH2; //right leg

long duration; 
long distance;
//reserse is 140

void setup() {
  Serial.begin (9600);
//Ultrasonic Sensors    
  pinMode(L_Trig, OUTPUT);   
  pinMode(R_Trig, OUTPUT);
  pinMode(Edge_Trig, OUTPUT);   
  pinMode(R_Echo, INPUT);    
  pinMode(L_Echo, INPUT);
  pinMode(Edge_Echo, INPUT);
  
//output signals
  pinMode(turnleft, OUTPUT);
  pinMode(turnright, OUTPUT);
  pinMode(reverse, OUTPUT);
  pinMode(forward, OUTPUT);
  pinMode(stoptritrack, OUTPUT);     
}

void loop() {
  // Serial.print("Right");    
  //Serial.println(SonarSensor(L_Trig, L_Echo));    
  // Serial.print("Left");     
  // Serial.println(SonarSensor(R_Trig, R_Echo));
  // Serial.print("EDGE WARNING");     
  // Serial.println(SonarSensor(Edge_Trig, Edge_Echo));

if (SonarSensor(Edge_Trig, Edge_Echo) > 10 && SonarSensor(Edge_Trig, Edge_Echo) > 10){   
  Serial.println("EDGE DETECTED");  
  digitalWrite(stoptritrack, HIGH);
}

if (SonarSensor(L_Trig, L_Echo) > 15 && SonarSensor(R_Trig, R_Echo) > 15){   
  Serial.println("SAFE");

} else if (SonarSensor(L_Trig, L_Echo) <= 11 or SonarSensor(R_Trig, R_Echo) <= 11){
  if (SonarSensor(L_Trig, L_Echo) <= 7 && SonarSensor(R_Trig, R_Echo) <= 7){      
    Serial.println("REVERSE");       
    digitalWrite(reverse, HIGH); 
  }   
  else if(SonarSensor(L_Trig, L_Echo) > SonarSensor(R_Trig, R_Echo)) {
    Serial.println("TURN LEFT"); 
    digitalWrite(turnleft, HIGH);           

  }      
  else if(SonarSensor(R_Trig, R_Echo) > SonarSensor(L_Trig, L_Echo)) {  
    Serial.println("TURN RIGHT");   
    digitalWrite(turnright, HIGH);
  }
} 
  delayMicroseconds(500);
}
long SonarSensor(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW); //Clear Sensor Readings
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); //Begin Scan
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); //End Scan  
  duration = pulseIn(echoPin, HIGH); 
  distance = (duration/2) / 29.1;  return distance;  
}  
