// ask_transmitter.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to transmit messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) transmitter with an TX-C1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
#include <LiquidCrystal.h>
#include <NewPing.h>

#define TRIG_PIN  3  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN  4  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DIST 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing myPing(TRIG_PIN,ECHO_PIN,MAX_DIST);
RH_ASK driver(2000,20,7);
LiquidCrystal lcd(5,6,10,11,12,13);

long duration;
int distanceCm, distanceInch;
String cm_string;
String count_string;
int a;

struct dataStruct{
  int distance;
  unsigned long counter;
}myData;

byte tx_buf[sizeof(myData)] = {0};

void setup()
{
    lcd.begin(16,2);
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
         Serial.println("init failed");
        
   
         
}

void loop()
{
  delay(100);
  a = myPing.ping_cm();
  myData.distance = a;
  memcpy(tx_buf, &myData, sizeof(myData) );
  byte zize=sizeof(myData);
  driver.send((uint8_t *)tx_buf, zize);
    
 // driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  cm_string = "Distance: " + String(a) + " cm    ";
  count_string = "Count: " + String(myData.counter);
  lcd.setCursor(0,0);
  lcd.print(cm_string);
  lcd.setCursor(0,2);
  lcd.print(count_string);
  
  myData.counter++;
}
