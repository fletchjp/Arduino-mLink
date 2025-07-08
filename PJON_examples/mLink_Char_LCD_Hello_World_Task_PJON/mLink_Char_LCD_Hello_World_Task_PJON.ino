// mLink_Char_LCD_Hello_World_Task.ino
// Adapted by John Fletcher (john@bunbury28.plus.com)
// This now uses TaskManagerIO.
// It also checks for an Arduino NANO Every. 
// Add sending using PJON Software Bit Bang Blink with Response examples.

/* FILE:    mLink_Char_LCD_Hello_World.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to print some text at a particular location on one
of the mLink character LCD modules.

Supported mLink products:

mLink 1602 Character LCD Blue (SKU: HCMODU0190A)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/

#include <TaskManagerIO.h>
#include "mLink.h"                      // Include the library
#include <PJONSoftwareBitBang.h>


PJONSoftwareBitBang bus(44);

void receiver_function(uint8_t *payload, uint16_t length, const PJON_Packet_Info &packet_info) {
  /* Make use of the payload before sending something, the buffer where payload points to is
     overwritten when a new message is dispatched */
  if(payload[0] == 'B') {
    Serial.println("BLINK");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(30);
    digitalWrite(LED_BUILTIN, LOW);
    bus.reply("B", 1);
  }
};

mLink mLink;                            // Create an instance of the library

#define I2C_ADD 0x56                    // Default I2C address

void hello_world();

void setup() 
{

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Initialize LED 13 to be off

  bus.strategy.set_pin(12);
  bus.begin();
  bus.set_receiver(receiver_function);

  Serial.begin(115200);
  Serial.println("Char LCD Hello World with Task and PJON");
  #if defined(ARDUINO_AVR_NANO_EVERY)
    Serial.println("ARDUINO_AVR_NANO_EVERY");
    Serial.println("Serial1 is available");
    #if defined(AVR_NANO_4809_328MODE)
      Serial.println("Simulation of 328 mode is available"); 
    #endif
  #else
     Serial.println("Not an ARDUINO_AVR_NANO_EVERY");
  #endif
  mLink.init();                         // Initialise the library
  mLink.cLCD_on(I2C_ADD,1);             // Turns on the display
  mLink.cLCD_contrast(I2C_ADD,10);
  mLink.cLCD_backlight(I2C_ADD,10);
  mLink.cLCD_clear(I2C_ADD);
  taskManager.schedule(onceSeconds(5),hello_world);

}

void hello_world() 
{
  mLink.cLCD_backlight(I2C_ADD,10);
  mLink.cLCD_cursor(I2C_ADD, 5, 0);     // Set the cursor to col 5 row 0
  mLink.cLCD_print(I2C_ADD, "Hello");   // Print something
  
  mLink.cLCD_cursor(I2C_ADD, 5, 1);     // Set the cursor to col 5 row 1
  mLink.cLCD_print(I2C_ADD, "PJON World");   // Print something
}

void loop() {
  taskManager.runLoop();
  bus.update();
  bus.receive(1000);

}
