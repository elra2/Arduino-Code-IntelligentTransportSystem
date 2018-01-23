/* Arduino code to read in ultrasonic sensors for obstacle avoidance
 * Single mode code for one HC-SR04 reading to detect an obstacle 
 * and move the tritrack away from it accordingly.
 *  --- 17ELD002, R ASANTE, Group G - Created: 22/01/2018
*/

#include <Servo.h>

#define L_Trig 12
#define L_Echo 13

Servo servo_CH1;
Servo servo_CH2;

void setup() {
  Serial.begin (9600);
  pinMode(L_Trig, OUTPUT);
  pinMode(L_Echo, INPUT);

  //TriTrack Wheel Setup 
  servo_CH1.attach(8);
  servo_CH2.attach(9);
}

void loop() {
  long LEFT_SENS_duration;
  long LEFT_SENS_distance;


 //Begin Range Read
  digitalWrite(L_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(L_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(L_Trig, LOW);
 //End Range Read
  
  LEFT_SENS_duration = pulseIn(L_Echo, HIGH);
  LEFT_SENS_distance = (LEFT_SENS_duration/2) / 29.1;

    if (LEFT_SENS_distance < 10){
    Serial.println("TURN RIGHT");
    turnRight();
    delayMicroseconds(500);
    }
    else if (LEFT_SENS_distance > 10){
    Serial.println("SAFE");
    delayMicroseconds(500);
    forward();
    }
  
  Serial.println(LEFT_SENS_distance);
  delay(500);
}


void forward() {
  servo_CH1.write(45);
  servo_CH2.write(45);
}

void reverse() {
  servo_CH1.write(180);
  servo_CH2.write(0);
}

void turnRight() {
  servo_CH1.write(180);
  servo_CH2.write(180);
}
void turnLeft() {
  servo_CH1.write(0);
  servo_CH2.write(0);
}

void stopRobot() {
  servo_CH1.write(90);
  servo_CH2.write(90);
}
