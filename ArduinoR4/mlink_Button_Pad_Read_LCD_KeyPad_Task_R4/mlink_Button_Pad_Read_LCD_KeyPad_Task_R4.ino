// mLink_Button_Pad_Read_LCD_Task_R4.ino 
// Version for the Arduino UNO R4 Minima
// Combine Button Pad and LCD and add Task handling.
// Add Keypad as well. Now both devices write to the display.
// mLink devices must be addressed with the correct I2C address.

/* FILE:    mLink_Button_Pad_Read.ino
   DATE:    20/04/22
   VERSION: 1.0
   AUTHOR:  Andrew Davies
   

This sketch demonstrates how to check the button pads
to see if a button has been pressed and if so read it from
its buffer.

Supported mLink products:

mLink 6 Button Pad (SKU: HCMODU0193)
mLink 2004 Character LCD Blue (SKU: HCMODU0190B)

Please see Licence.txt in the library folder for terms of use.
*/


#include <TaskManagerIO.h>
#include "mLink.h"                                    // Include the library

mLink mLink;                                          // Create an instance of the library

// Note local duplication of the default values from the mlink library
#define I2C_ADD_BPAD BPAD_I2C_ADD            // 0x59 Default I2C address for Button PAD
#define I2C_ADD_LCD  CLCD_I2C_ADD            // 0x56 Default I2C address for LCD
#define I2C_ADD_KPAD 0x55                    // Default I2C address for KeyPad

// Function declarations.
// These are not needed in Arduino code.
// It is good practice to include them to document what functions are defined later.
void hello_world();
void button_and_display();


void setup() 
{
  Serial.begin(115200);
  delay(5000);
  Serial.println("Button Pad reading with display to LCD with KeyPad using a Task");
 #if defined(ARDUINO_AVR_NANO_EVERY)
    Serial.println("ARDUINO_AVR_NANO_EVERY");
    Serial.println("Serial1 is available");
    #if defined(AVR_NANO_4809_328MODE)
      Serial.println("Simulation of 328 mode is available"); 
    #endif
  #else
  #ifdef ARDUINO_ARCH_RP2040
    Serial.println("Running tests on a Pico");
#endif
#ifdef ARDUINO_MINIMA
    Serial.println("\nArduino R4 Minima");
#endif
#ifdef ARDUINO_UNOR4_WIFI
    Serial.println("\nArduino R4 Wifi");
#endif
     Serial.println("Not an ARDUINO_AVR_NANO_EVERY");
  #endif
  mLink.init();                             // Initialise the library
  mLink.cLCD_clear(I2C_ADD_LCD);

  taskManager.schedule(onceSeconds(5),hello_world);
  taskManager.schedule(repeatSeconds(1),button_and_display);
  taskManager.schedule(repeatSeconds(4),keypad);

}

void hello_world() 
{
  mLink.cLCD_backlight(I2C_ADD_LCD,10);
  mLink.cLCD_cursor(I2C_ADD_LCD, 5, 0);     // Set the cursor to col 5 row 0
  char hello[] = "Hello";
  char *phello = hello;
  mLink.cLCD_print(I2C_ADD_LCD, phello);   // Print something
  
  mLink.cLCD_cursor(I2C_ADD_LCD, 5, 1);     // Set the cursor to col 5 row 1
  char world[] = "R4 World";
  char *pworld = world;
  mLink.cLCD_print(I2C_ADD_LCD, pworld);   // Print something
}


void button_and_display() 
{  
  byte empty = mLink.bPad_Empty(I2C_ADD_BPAD);			  // Check to see if there is anything in the keypad buffer

  if(!empty)                                          
  { 
    byte key = mLink.read(I2C_ADD_BPAD, BPAD_BUFFER);      // If so then read a key from the buffer and print it
    char button[] = "Button: ";
    char* pbutton = button; 
    Serial.print("Button: ");                        
    Serial.println(key);
    Serial.flush();
    mLink.cLCD_cursor(I2C_ADD_LCD, 0, 2);     // Set the cursor to col 0 row 2
    mLink.cLCD_print(I2C_ADD_LCD, pbutton);   // Print label
    mLink.cLCD_print(I2C_ADD_LCD, key);       // Print key value
  }

}

void keypad() 
{  
  char key = mLink.read(I2C_ADD_KPAD, KEYPAD_4X4_KEY);     // Read the key status

  if(key)                                             // Has a key been pressed ?
  { 
    char keys[] = "Key: ";
    char* pkeys = keys; 
    Serial.print("Key: ");                            // If so then output the key to the serial monitor
    Serial.println(key);
    mLink.cLCD_cursor(I2C_ADD_LCD, 0, 3);     // Set the cursor to col 0 row 2
    mLink.cLCD_print(I2C_ADD_LCD, pkeys);   // Print label
    mLink.cLCD_print(I2C_ADD_LCD, key);       // Print key value
  };
}

void loop() {
   taskManager.runLoop();
}
