/* Arduino code to read in ultrasonic sensors for obstacle avoidance
 * Multiple HC SR04 will need to move together on the moving tritrack to detect obstacles 
 * and move the tritrack away from it accordingly.
 *  --- 17ELD002, R ASANTE, Group G - Created: 22/01/2018
*/

#include <"Servo.h">

#define L_Trig 12
#define L_Echo 13
#define R_Trig 10
#define R_Echo 11

Servo servo_CH1;
Servo servo_CH2;

void setup() {
  Serial.begin (9600);
  pinMode(L_Trig, OUTPUT);
  pinMode(R_Trig, OUTPUT);
  pinMode(R_Echo, INPUT);
  pinMode(L_Echo, INPUT);

  //TriTrack Wheel Setup 
  servo_CH1.attach(8);
  servo_CH2.attach(9);
}

void loop() {
  long LEFT_SENS_duration;
  long RIGHT_SENS_duration;
  long LEFT_SENS_distance;
  long RIGHT_SENS_distance;

 //Begin Range Read
 
  digitalWrite(L_Trig, LOW);
  digitalWrite(R_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(L_Trig, HIGH);
  digitalWrite(R_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(L_Trig, LOW);
  digitalWrite(R_Trig, LOW);

 //End Range Read
  
  RIGHT_SENS_duration = pulseIn(R_Echo, HIGH);
  LEFT_SENS_duration = pulseIn(L_Echo, HIGH);
  
  RIGHT_SENS_distance = (RIGHT_SENS_duration/2) / 29.1;
  LEFT_SENS_distance = (LEFT_SENS_duration/2) / 29.1;
  
  if (RIGHT_SENS_distance < 10 or LEFT_SENS_distance < 10) {
    if (RIGHT_SENS_distance < LEFT_SENS_distance){
    Serial.println("TURN LEFT");
    turnLeft();
    delayMicroseconds(1000)
    }
    else if (LEFT_SENS_distance < RIGHT_SENS_distance){
    Serial.println("TURN RIGHT");
    turnRight(); 
    delayMicroseconds(1000);
    }
    else if (LEFT_SENS_distance <= 4 && RIGHT_SENS_distance <= 4){
      Serial.println("Reverse");
      delayMicroseconds(1000);
    }
}
  else {
   Serial.println("Safe.");
   forward();
  }
  Serial.print(RIGHT_SENS_distance);
  delay(300);
}
void forward() {
  servo_CH1.write(0);
  servo_CH2.write(180);
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
