// mLink_Button_Pad_Read Task.ino
// Adapted by John Fletcher (john@bunbury28.plus.com)
// This now uses TaskManagerIO.
// It also checks for an Arduino NANO Every. 

/* FILE:    mLink_Button_Pad_Read_Task.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   
This sketch demonstrates how to check the button pads
to see if a button has been pressed and if so read it from
its buffer.

Supported mLink products:

mLink 6 Button Pad (SKU: HCMODU0193)

Please see Licence.txt in the library folder for terms of use.
*/

// Modified by JPF to change Serial speed and delay time. Added a first print.


//#include <TaskManagerIO.h>
#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

#define I2C_ADD BPAD_I2C_ADD                          // Default I2C address

long interval = 500;
void read_bpad();

void setup() 
{
  Serial.begin(115200);
  Serial.println("Button Pad reading with Task");
#ifdef ARDUINO_MINIMA
    Serial.println("\nArduino R4 Minima");
#endif
#ifdef ARDUINO_UNOR4_WIFI
    Serial.println("\nArduino R4 Wifi");
#endif
#if defined(ARDUINO_AVR_NANO_EVERY)
    Serial.println("ARDUINO_AVR_NANO_EVERY");
    Serial.println("Serial1 is available");
    #if defined(AVR_NANO_4809_328MODE)
      Serial.println("Simulation of 328 mode is available"); 
    #endif
  #else
     Serial.println("Not an ARDUINO_AVR_NANO_EVERY");
  #endif
  mLink.init();                                       // Initialise the library

  //taskManager.scheduleFixedRate(interval,read_bpad);

}

void read_bpad()
{  
  byte empty = mLink.bPad_Empty(I2C_ADD);			  // Check to see if there is anything in the keypad buffer

  if(!empty)                                          
  { 
    byte key = mLink.read(I2C_ADD, BPAD_BUFFER);      // If so then read a key from the buffer and print it

    Serial.print("Key: ");                            
    Serial.println(key);
  }

  //delay(1000);
}

void loop() {
   //taskManager.runLoop();
}
