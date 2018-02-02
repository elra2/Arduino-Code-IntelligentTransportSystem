/*

PURPOSE        :     Servo controller (Xbox360 Wireless)
 
REFERENCES     :     Barrett Anderies          provided : Regression Formula                                             website : https://barrettsprojects.wordpress.com/
                     Kristian Sloth Lauszus    provided : USB Host-Shield Library                                        website : http://blog.tkjelectronics.dk/
                     Sergei Dines              provided : Modifications, commenting, user friendly and safe controlling  website : http://surgerobotics.com
LAST MODIFIED  :     5/04/2015
                                       
May 25, 2014
*/

#include <XBOXRECV.h>
#include <Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#define LOOPTIME 50 //Define the delay between timed loop cycles. //was 25

//Define where each servo is attahed//

#define SERVO1 3 //  Right Hat X        : Base Rotate

#define SERVO2 4 //  RightHat Y         : Shoulder Joint

#define SERVO3 5 //  LeftHat Y          : Wrist 
#define SERVO4 7 //  LeftHat Y          : Grabber
#define SERVO5 2 //  RIGHTHATX          : MAIN BASE

#define SERVO6 6 //  RightHatX          : Spin Claw
#define SERVO7 7

#define SERVO1_INIT 90 //Define initial servo position(initial Condition) & (initiates when "start" button pressed).
#define SERVO2_INIT 120
#define SERVO3_INIT 120
#define SERVO4_INIT 120
#define SERVO5_INIT 90
#define SERVO6_INIT 90
#define SERVO7_INIT 120

#define SERVO1_STEP 3       //Step Value for L/R Tripper [Base Joint]
#define SERVO7_STEP 8                            //Define step size for servos controlled by D-pad (larger is faster).

#define SERVO2_RATE 4/32000

      //Note: Org SERVO2_STEP 10
      //Define rate for servos controller by sticks (larger is faster).
#define SERVO3_RATE 4/32000 
#define SERVO4_RATE 5/32000
#define SERVO5_RATE 5/32000
#define SERVO6_RATE 8/32000    

#define SERVO1_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO2_DIRECTION -1 //Set to -1 to reverse servo direction.
#define SERVO3_DIRECTION -1 //Set to -1 to reverse servo direction. CLAW 1
#define SERVO4_DIRECTION 1 //Set to -1 to reverse servo direction.  CLAW 2
#define SERVO5_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO6_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO7_DIRECTION 1

#define SERVO1_MIN 2 //Define minimum servo angles.
#define SERVO2_MIN 2
#define SERVO3_MIN 2 //EDIT*** : Claw - Change Value to avoid collision
#define SERVO4_MIN 2 //EDIT*** : Claw - Change Value to avoid collision
#define SERVO5_MIN 2
#define SERVO6_MIN 2
#define SERVO7_MIN 35

#define SERVO1_MAX 178 //Define maximum servo angles.
#define SERVO2_MAX 178
#define SERVO3_MAX 178 // EDIT*** : Claw - Change Value to avoid collision
#define SERVO4_MAX 178 // EDIT*** : Claw - Change Value to avoid collision 
#define SERVO5_MAX 178
#define SERVO6_MAX 178
#define SERVO7_MAX 178

#define STICK_CENTER 0 //Value from controller when sticks are centered (127 for PS3 controller, 0 for xbox controller)
#define DEADZONE 7500  //Deadzone to prevent unwanted movement. Defined as 7500 for Xbox360 Controller


//================================ Global Variables ================================//

USB Usb;               //USBHub Hub1(&Usb); // Some dongles have a hub inside. Try this is your dongle isn't working.
XBOXRECV Xbox(&Usb);

Servo servo1; //Good
Servo servo2;
Servo servo3; //Good
Servo servo4; //Good
Servo servo5; //Good
Servo servo6; //Good
Servo servo7; //Good

unsigned long previousTime = 0; //for loop timing

int s1 = SERVO1_INIT; //Define variables to store servo positions and set to initial positions
int s2 = SERVO2_INIT;
int s3 = SERVO3_INIT;
int s4 = SERVO4_INIT;
int s5 = SERVO5_INIT;
int s6 = SERVO6_INIT;
int s7 = SERVO7_INIT;


//================================ Setup ================================//
void setup()            //setup loop
{ 
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Initiated"));
  
  servo1.detach();     //Initially All Servos Disabled // Waiting for Button to Initialize [ requirement of MAKE course]
  servo2.detach();
  servo3.detach();
  servo4.detach();
  servo5.detach();
  servo6.detach();
  servo7.detach();
  
  

	
      

}





//================================ Loop ================================//

void loop() { //Primary runtime loop
  
  Usb.Task(); //Task USB

  if(Xbox.XboxReceiverConnected || Xbox.Xbox360Connected) {
   for(uint8_t i=0;i<4;i++) {
      if(Xbox.Xbox360Connected[i]) {

  //This loop executes only when Xbox 360 controller is connected
       
    if(millis() - previousTime > LOOPTIME) { 

        //Start of timed 
 
if(Xbox.getButtonClick(L2,i)) { 

  
             s7 = s7 + SERVO7_STEP*SERVO7_DIRECTION;
            
             
            
          }
          
          else if(Xbox.getButtonClick(R2,i)) {
            s7 = s7 - SERVO7_STEP*SERVO7_DIRECTION;
            
     

          }
          if(s7 > SERVO7_MAX) s7 = SERVO7_MAX;
          if(s7 < SERVO7_MIN) s7 = SERVO7_MIN;
          

if (Xbox.getAnalogHat(RightHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatY,i) < STICK_CENTER - DEADZONE) {
         servo2.attach(3);
  
          s2 = s2 + (Xbox.getAnalogHat(RightHatY,i) - STICK_CENTER)*SERVO2_RATE*SERVO2_DIRECTION;
          }
          if(s2 > SERVO2_MAX) s2 = SERVO2_MAX;
          if(s2 < SERVO2_MIN) s2 = SERVO2_MIN;

if (Xbox.getAnalogHat(RightHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatY,i) < STICK_CENTER - DEADZONE) {

servo3.attach(4);  
          s3 = s3 + (Xbox.getAnalogHat(RightHatY,i) -  STICK_CENTER)*SERVO3_RATE*SERVO3_DIRECTION;
          }
          if(s3 > SERVO3_MAX) s3 = SERVO3_MAX;
          if(s3 < SERVO3_MIN) s3 = SERVO3_MIN;
            

if (Xbox.getAnalogHat(LeftHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(LeftHatY,i) < STICK_CENTER - DEADZONE) { 
servo4.attach(5);  
            s4 = s4 + (Xbox.getAnalogHat(LeftHatY,i) -  STICK_CENTER)*SERVO4_RATE*SERVO4_DIRECTION;
          }
          if(s4 > SERVO4_MAX) s4 = SERVO4_MAX;
          if(s4 < SERVO4_MIN) s4 = SERVO4_MIN;
          
          
          
           if (Xbox.getAnalogHat(LeftHatX,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(LeftHatX,i) < STICK_CENTER - DEADZONE) {
            servo5.attach(6);          
            s5 = s5 + (Xbox.getAnalogHat(LeftHatX,i) - STICK_CENTER)*SERVO5_RATE*SERVO5_DIRECTION;
          }
          if(s5 > SERVO5_MAX) s5 = SERVO5_MAX;
          if(s5 < SERVO5_MIN) s5 = SERVO5_MIN;
          
          if (Xbox.getAnalogHat(RightHatX,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatX,i) < STICK_CENTER - DEADZONE) {
   
            servo6.attach(2);
         //Servo6 Spin Claw Pin7
            s6 = s6 + (Xbox.getAnalogHat(RightHatX,i) - STICK_CENTER)*SERVO6_RATE*SERVO6_DIRECTION;
          }
          if(s6 > SERVO6_MAX) s6 = SERVO6_MAX;
          if(s6 < SERVO6_MIN) s6 = SERVO6_MIN;
          
          
                    
          if(Xbox.getButtonClick(LEFT,i)) { 


            //Gripper Servo PIN7
             s7 = s7 + SERVO7_STEP*SERVO7_DIRECTION;
            servo7.attach(7);
          }
          
          else if(Xbox.getButtonClick(RIGHT,i)) {
            s7 = s7 - SERVO7_STEP*SERVO7_DIRECTION;
            servo7.attach(7);
        
     

          }
          if(s7 > SERVO7_MAX) s7 = SERVO7_MAX;
          if(s7 < SERVO7_MIN) s7 = SERVO7_MIN;
          

          Serial.print("  s1 = ");  //Debug information about servo positions. Uncomment when you are determining servo limits.
          Serial.print(s1);
          Serial.print("  s2 = ");
          Serial.print(s2);
          Serial.print("  s3 = ");
          Serial.print(s3);
          Serial.print("  s4 = ");
          Serial.print(s4);
          Serial.print("  s5 = ");
          Serial.print(s5);
          Serial.print("  s6 = ");
          Serial.println(s6);
          Serial.print("  s7 = ");
          Serial.println(s7);
          
          
          if(Xbox.getButtonClick(B,i))   {           // Safety Release
                                                  // Detaches all servos - waiting for button to re-engage
              servo1.detach();
              servo2.detach();
              servo3.detach();
              servo4.detach();
              servo5.detach();
              servo6.detach();
              servo7.detach();
                                          }
                                          
                                                    //Safety Restore
                                                    //Also : Initializing Button : creative way to start robot
          if(Xbox.getButtonClick(Y,i))  {
            
                    
                    
                    servo1.detach();
                    servo2.detach();
                    servo3.detach();
                    servo4.detach();
                    servo5.detach();
                    servo6.detach();
                    servo7.detach();

           
            
          
           if(Xbox.getButtonClick(A,i)) {       //Reset ALL Servos to initial positions when "start" button is pressed
            s1 = SERVO1_INIT;
            s2 = SERVO2_INIT;
            s3 = SERVO3_INIT;
            s4 = SERVO4_INIT;
            s5 = SERVO5_INIT;
            s6 = SERVO6_INIT;  
            s7 = SERVO7_INIT;                                 }
            
                                       
                                       //Following are re-programmable detach buttons for other applications
                                       //Note : Does not have to be limited to just servos
                                       //I.e. could attach, detach led when servo is attached, detached
   
           
         }

previousTime = millis(); //save time at end of loop
        } //Timed loop  
      
        servo1.write(s1); //Write to servos.
        servo2.write(s2);
        servo3.write(s3);
        servo4.write(s4);
        servo5.write(s5);
        servo6.write(s6);
        servo7.write(s7);
        
     
                            }
}
          
    }

  }


 


