#include <XBOXRECV.h>
#include <Servo.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#define LOOPTIME 50 //Define the delay between timed loop cycles. //was 25

//define ultrasonic sensor signal
#define leftsignal 21
#define rightsignal 22
#define forwardsignal 23
#define reversesignal 24
#define stopsignal 25

//Define where each servo is attahed//

#define SERVO1 2 //  Right Hat X        : Base Rotate

#define SERVO2 3 //  RightHat Y         : Shoulder Joint

#define SERVO3 4 //  LeftHat Y          : Wrist 
#define SERVO4 5 //  LeftHat Y          : Grabber

#define SERVO6 6 //  RightHatX          : Spin Claw
#define SERVO7 7//                      : Elbow

#define RWHEEL 8 //                     : Right Wheel TriTrack  - CHANNEL 1  LABEL
#define LWHEEL 9 //                     : Left Wheel TriTrack   - CHANNEL 2  LABEL

#define SERVO1_INIT 160 //Define initial servo position(initial Condition) & (initiates when "start" button pressed).
#define SERVO2_INIT 5
#define SERVO3_INIT 10
#define SERVO4_INIT 40
#define SERVO5_INIT 90
#define SERVO6_INIT 90
#define SERVO7_INIT 120
#define LWHEEL_INIT 90
#define RWHEEL_INIT 90

#define LWHEEL_STEP 5
#define RWHEEL_STEP 5
#define SERVO1_STEP 3       //Step Value for L/R Tripper [Base Joint]
#define SERVO7_STEP 8                            //Define step size for servos controlled by D-pad (larger is faster).
#define SERVO6_STEP 5
#define SERVO5_STEP 2

#define SERVO2_RATE 4/32000

      //Note: Org SERVO2_STEP 10
      //Define rate for servos controller by sticks (larger is faster).
#define SERVO3_RATE 2/32000 
#define SERVO4_RATE 2/32000
#define SERVO5_RATE 1/32000
#define SERVO6_RATE 4/32000  
#define SERVO1_RATE 2/32000    

#define SERVO1_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO2_DIRECTION -1 //Set to -1 to reverse servo direction.
#define SERVO3_DIRECTION 1 //Set to -1 to reverse servo direction. CLAW 1
#define SERVO4_DIRECTION 1 //Set to -1 to reverse servo direction.  CLAW 2
#define SERVO5_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO6_DIRECTION 1 //Set to -1 to reverse servo direction.
#define SERVO7_DIRECTION 1
#define LWHEEL_DIRECTION 1
#define RWHEEL_DIRECTION 1

#define SERVO1_MIN 2 //Define minimum servo angles.
#define SERVO2_MIN 2
#define SERVO3_MIN 2 //EDIT*** : Claw - Change Value to avoid collision
#define SERVO4_MIN 2 //EDIT*** : Claw - Change Value to avoid collision
#define SERVO5_MIN 2
#define SERVO6_MIN 2
#define SERVO7_MIN 35
#define LWHEEL_MIN 40
#define RWHEEL_MIN 40

#define SERVO1_MAX 270 //Define maximum servo angles.
#define SERVO2_MAX 178
#define SERVO3_MAX 178 // EDIT*** : Claw - Change Value to avoid collision
#define SERVO4_MAX 178 // EDIT*** : Claw - Change Value to avoid collision 
#define SERVO5_MAX 178
#define SERVO6_MAX 178
#define SERVO7_MAX 178
#define LWHEEL_MAX 140
#define RWHEEL_MAX 140

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
Servo lwheel;
Servo rwheel;

unsigned long previousTime = 0; //for loop timing
int i;

int s1 = SERVO1_INIT; //Define variables to store servo positions and set to initial positions
int s2 = SERVO2_INIT;
int s3 = SERVO3_INIT;
int s4 = SERVO4_INIT;
int s5 = SERVO5_INIT;
int s6 = SERVO6_INIT;
int s7 = SERVO7_INIT;
int sL = LWHEEL_INIT;
int sR = RWHEEL_INIT;

int readleft = 0;
int readright = 0;
int readforward = 0;
int readstop = 0;
int readreverse = 0;

//================================ Setup ================================//
void setup()            //setup loop
{ 
  //Ultrasonic Pin reading
  pinMode(leftsignal, INPUT);
  pinMode (rightsignal, INPUT);
  pinMode (reversesignal, INPUT);
  pinMode (forwardsignal, INPUT);
  pinMode (stopsignal, INPUT); 
  
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
  lwheel.detach();
  rwheel.detach();

}


//================================ Loop ================================//

void loop() { //Primary runtime loop

 readleft =  digitalRead(leftsignal);
 readright =  digitalRead(rightsignal);
 readreverse =  digitalRead(reversesignal);
 readforward =  digitalRead(forwardsignal);
 readstop =  digitalRead(stopsignal);
 
  Usb.Task(); //Task USB

  if(Xbox.XboxReceiverConnected || Xbox.Xbox360Connected) {
   for(uint8_t i=0;i<4;i++) {
      if(Xbox.Xbox360Connected[i]) {

  //This loop executes only when Xbox 360 controller is connected
       
    if(millis() - previousTime > LOOPTIME) { 

        //Start of timed 

          // ----- GRIPPER ----// - Pin 6, Servo 6
      if(Xbox.getButtonClick(L1,i)) { 
      servo6.attach(SERVO6);
      s6 = s6 + SERVO6_STEP*SERVO6_DIRECTION;
      }
      else if(Xbox.getButtonClick(R1,i)) {
      s6 = s6 - SERVO6_STEP*SERVO6_DIRECTION;
      }
      if(s6 > SERVO6_MAX) s6 = SERVO6_MAX;
      if(s6 < SERVO6_MIN) s6 = SERVO6_MIN;

          // ----- GRABBER ----// - Pin 7, Servo 7
      if(Xbox.getButtonClick(L2,i)) { 
      servo7.attach(SERVO7);
      s7 = s7 + SERVO7_STEP*SERVO7_DIRECTION;
      }
      else if(Xbox.getButtonClick(R2,i)) {
        s7 = s7 - SERVO7_STEP*SERVO7_DIRECTION;

      }
      if(s7 > SERVO7_MAX) s7 = SERVO7_MAX;
      if(s7 < SERVO7_MIN) s7 = SERVO7_MIN;

         // --- Up and Down for Base --- // Pin Servo 2, Pin 3 and Servo 3, Pin 4
if (Xbox.getAnalogHat(RightHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatY,i) < STICK_CENTER - DEADZONE) {
         servo2.attach(SERVO2);
  
          s2 = s2 + (Xbox.getAnalogHat(RightHatY,i) - STICK_CENTER)*SERVO2_RATE*SERVO2_DIRECTION;
          }
          if(s2 > SERVO2_MAX) s2 = SERVO2_MAX;
          if(s2 < SERVO2_MIN) s2 = SERVO2_MIN;
          
          if (Xbox.getAnalogHat(RightHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatY,i) < STICK_CENTER - DEADZONE) {
servo3.attach(SERVO3);  
          s3 = s3 + (Xbox.getAnalogHat(RightHatY,i) -  STICK_CENTER)*SERVO3_RATE*SERVO3_DIRECTION;
          }
          if(s3 > SERVO3_MAX) s3 = SERVO3_MAX;
          if(s3 < SERVO3_MIN) s3 = SERVO3_MIN;

 // ----- Base Left to Right ------  // Servo 1, Pin 2

        if (Xbox.getAnalogHat(RightHatX,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(RightHatX,i) < STICK_CENTER - DEADZONE) {
         servo1.attach(SERVO1);
            s1 = s1 + (Xbox.getAnalogHat(RightHatX,i) - STICK_CENTER)*SERVO1_RATE*SERVO1_DIRECTION;
          }
          if(s1 > SERVO1_MAX) s1 = SERVO6_MAX;
          if(s1 < SERVO1_MIN) s1 = SERVO6_MIN;

            
//---- Elbow ---- // Servo 4, Pin 5
if (Xbox.getAnalogHat(LeftHatY,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(LeftHatY,i) < STICK_CENTER - DEADZONE) { 
servo4.attach(SERVO4); 
            s4 = s4 + (Xbox.getAnalogHat(LeftHatY,i) -  STICK_CENTER)*SERVO4_RATE*SERVO4_DIRECTION;
          }
          if(s4 > SERVO4_MAX) s4 = SERVO4_MAX;
          if(s4 < SERVO4_MIN) s4 = SERVO4_MIN;

           if (Xbox.getAnalogHat(LeftHatX,i) > STICK_CENTER + DEADZONE || Xbox.getAnalogHat(LeftHatX,i) < STICK_CENTER - DEADZONE) {
            servo3.attach(4);          
            s3 = s3 + (Xbox.getAnalogHat(LeftHatX,i) - STICK_CENTER)*SERVO3_RATE*SERVO3_DIRECTION;
          }
          if(s3 > SERVO3_MAX) s3 = SERVO3_MAX;
          if(s3 < SERVO3_MIN) s3 = SERVO3_MIN;
    

         //WHEELS----------------------------------------
         
        if(Xbox.getButtonClick(UP,i)) { 
          TriTrackForward(); 
          }
          if(Xbox.getButtonClick(DOWN,i)) {
          TriTrackReverse();
          }
          if(Xbox.getButtonClick(LEFT,i)) {
          TriTrackLeft();
          }
          if(Xbox.getButtonClick(RIGHT,i)) {
          TriTrackRight();
          }

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
          
          
          if(Xbox.getButtonClick(A,i))   {        //Automation Mode - Ultrasonic Sensors
           if (readleft == HIGH){
            TriTrackLeft();
           }
           else if (readstop == HIGH){
            sL = 140;
            sR = 140;
           }
           else if (readforward == HIGH){
            TriTrackForward();
           }
           else if (readright == HIGH){
           TriTrackRight();
           }
           else if (readreverse == HIGH){
            TriTrackReverse();
           }
         }

          if(Xbox.getButtonClick(X,i))   {        //Unlock Wheels and employ manual mode
                                                  // Detaches all servos - waiting for button to re-engage
              lwheel.attach(8);
              rwheel.attach(9);
              StopTriTrack();
              }
              
          if(Xbox.getButtonClick(B,i))   {        // Safety Release
                                                  // Detaches all servos - waiting for button to re-engage
              servo1.detach();
              servo2.detach();
              servo3.detach();
              servo4.detach();
              servo5.detach();
              servo6.detach();
              servo7.detach();
              lwheel.detach();
              rwheel.detach();      
              }
                                          
                                                    //Safety Restore
                                                    //Also : Initializing Button : creative way to start robot
          if(Xbox.getButtonClick(Y,i))  {
           StopTriTrack();
          }
                
          
           if(Xbox.getButtonClick(START,i)) {       //Reset ALL Servos to initial positions when "start" button is pressed
            s1 = SERVO1_INIT;
            s2 = SERVO2_INIT;
            s3 = SERVO3_INIT;
            s4 = SERVO4_INIT;
            s5 = SERVO5_INIT;
            s6 = SERVO6_INIT;  
            s7 = SERVO7_INIT;                                 
            sL = LWHEEL_INIT;
            sR = RWHEEL_INIT;
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

void TriTrackForward(){
        lwheel.write(40);
        rwheel.write(40);
}


void TriTrackReverse(){
        lwheel.write(140);
        rwheel.write(140);
}

void TriTrackLeft(){
        rwheel.write(40);
        lwheel.write(140);
}

void TriTrackRight(){  
        rwheel.write(140);
        lwheel.write(40);
}

void StopTriTrack(){
        rwheel.write(90);
        lwheel.write(90);
}

