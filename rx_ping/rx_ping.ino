// ask_receiver.pde
// -*- mode: C++ -*-
// Simple example of how to use RadioHead to receive messages
// with a simple ASK transmitter in a very simple way.
// Implements a simplex (one-way) receiver with an Rx-B1 module

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>
#include <NewTone.h>
#include "pitches.h"


RH_ASK driver(2000, 6, 100);
LiquidCrystal lcd(7,9,10,11,12,13);

struct dataStruct{
  int distance;
  unsigned long counter;
}myData;
String dist_string, count_string;
bool a;
int b, d;

const int speakerPin = 4;
int c_chord[] = {
  NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4,  NOTE_E4, NOTE_G4, NOTE_C5,
  };
int melody[] = {
   NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
  };

void setup()
{
    lcd.begin(16,4);
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
    Serial.println("init succeeded");
    
    for(int note = 0; note < 8; note++ ){
      int noteDuration = 1000 / noteDurations[note];
      NewTone(speakerPin, melody[note], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noNewTone(speakerPin);
    }
    
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
  int i;
  
  // Message with a good checksum received, dump it.
  driver.printBuffer("Got:", buf, buflen);
  memcpy(&myData, buf, sizeof(myData));
  d = int(myData.distance);
  lcd.setCursor(0,0);
  lcd.print("Receiving...");
  delay(10);
  Serial.println("");
  Serial.print(" Distance: ");
  Serial.print(myData.distance);
  
  dist_string = "Distance: " + String(myData.distance) + " cm  ";
  count_string = "Count: " + String(myData.counter);
  lcd.setCursor(0,1);
  lcd.print ("----------------");
  lcd.setCursor(0,2);
  lcd.print(dist_string);
  lcd.setCursor(0,3);
  lcd.print(count_string);
  Serial.print("  counter: ");
  Serial.println(myData.counter);

  if (d > 2 && d < 15){
      b = 0;
  }
  else if (d > 14 && d < 25) {
      b = 1;
  }
  else if (d > 24 && d < 35){
      b =  2;
  }
  else if (d > 34 && d < 45){
      b =  3;
  }
  else if (d > 44 && d < 55){
      b =  4;
  }
  else if (d > 54 && d < 65){
      b =  5;
  }  
  else if (d > 66 && d < 75){
      b =  6;
  }  
  else{
      b = 1000;
  }
  if (b < 500) {
      NewTone(speakerPin, c_chord[b], 350);
      delay(150);
      noNewTone(speakerPin);
    }
  
    }
}
