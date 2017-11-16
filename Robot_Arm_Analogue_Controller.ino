//add servo library
#include <Servo.h>

//define our servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

//define our potentiometer
int pot1 = A1;
int pot2 = A2;
int pot3 = A3;
int pot4 = A4;

//variable to read the values from the analog pin (potentiometers)
int valPot1;
int valPot2;
int valPot3;
int valPot4;

void setup()
{
  //attaches our servos on pins PWM 2-3-4-5-6-7 to the servos
  servo1.attach(7);
  servo1.write(90);  //define servo1 start position
  servo2.attach(6);
  servo2.write(90); //define servo2 start position
  servo3.attach(5);
  servo3.write(90); //define servo3 start position
  servo4.attach(4);
  servo4.write(70); //define servo4 start position
  servo5.attach(3);
  servo5.write(90); //define servo3 start position
  servo6.attach(2);
  servo6.write(70); //define servo4 start position
}

void loop()
{
  //reads the value of potentiometers (value between 0 and 1023)

  valPot1 = analogRead(pot1);
  valPot1 = map (valPot1, 0, 1023, 0, 180); //scale it to use it with the servo (value between 0 and 180)
  servo1.write(valPot1); //set the servo position according to the scaled value

  valPot2 = analogRead(pot2);
  valPot2 = map (valPot2, 0, 1023, 0, 180);
  servo2.write(valPot2);
  
  valPot3 = analogRead(pot3);
  valPot3 = map (valPot3, 0, 1023, 0, 180);
  servo3.write(valPot3);

  valPot4 = analogRead(pot4);
  valPot4 = map (valPot4, 0, 1023, 0, 180);
  servo4.write(valPot4);

  valPot4 = analogRead(pot5);
  valPot4 = map (valPot4, 0, 1023, 0, 180);
  servo5.write(valPot4);

  valPot4 = analogRead(pot6);
  valPot4 = map (valPot4, 0, 1023, 0, 180);
  servo6.write(valPot4);
 }
