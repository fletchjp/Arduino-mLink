// mLink_Relay_Blink.ino
// Adding test of what size of relay is available.

/* FILE:    Alternative_Blink_Relay_0.ino
   DATE:    27/03/25
   VERSION: 1.0

   This sketch demonstrates an alternative way to control 
   the relays using the mLink library. It utilizes the RLY_ON() 
   and RLY_OFF() macros to turn a relay on or off by specifying 
   its index.

   Note: These commands are only compatible with module firmware 
   version 1.01 or higher.
*/


#include "mLink.h"          // Include the library

mLink mLink;                // Create an instance of the library

#define I2C_ADD 0x52        // Default I2C address

bool is_relay(byte add)
{
  byte type = mLink.read(add, MLINK_MOD_TYPE_REG);
  return type == 0x02;
}

byte no_of_relays(byte add)
{
   if (!is_relay(add)) { 
    return 0;
   } else {
      byte relays = 0;
      byte subType = mLink.read(add, MLINK_MOD_SUBTYPE_REG);
      switch(subType)
      {
        case 0x00:
          //Serial.print("1 Channel Relay");
          relays = 1;
          break;

        case 0x01:
          //Serial.print("2 Channel Relay");
          relays = 2;
          break;

        case 0x02:
          //Serial.print("4 Channel Relay");
          relays = 4;
          break;
      }
      return relays;
   }

}

void setup() 
{
  mLink.init();             // Initialise the library
  Serial.begin(115200);
  Serial.println("Relay blink with check of how many relays there are");
  if (is_relay(I2C_ADD)) {
     Serial.print("Relay board with ");
     Serial.print(no_of_relays(I2C_ADD));
     Serial.println(" relays");
  } else {
     Serial.println("This does not have a relay");
  }
}

void loop() 
{
  mLink.RLY_ON(I2C_ADD, 0); // Turn relay 0 on
  delay(10000);
  
  mLink.RLY_OFF(I2C_ADD, 0); // Turn relay 0 off
  delay(10000);
}
