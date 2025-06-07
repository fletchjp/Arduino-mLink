# Arduino-mLink

Arduino codes using mLink components which connect using the I2C method.

I am going to put here some of the codes I have been developing for Arduinos to use mLink components.

These are developments in one way and another of the examples supplied by [Hobby Components](https://hobbycomponents.com/).

These codes all need the [mLink Arduino library](https://github.com/HobbyComponents/mLink) which will need to be downloaded and installed. The current version of the library is v2.2.2.

The mLink library has a lot of useful examples. One of them is the [mLink I2C scanner](https://github.com/HobbyComponents/mLink/tree/main/examples/mLink_I2C_Scanner) which can be used to check the I2C addresses of the mLink components connected to an Arduino.

For each of the mLink devices there are pages on the [Hobby Components](https://hobbycomponents.com/) web site which explain how to connect up the I2C wiring.

Many of my examples extend the mLink library examples and make use of the [TaskManagerIO library](https://tcmenu.github.io/documentation/arduino-libraries//taskmanager-io/) to control the mLink device. This avoids the need to use delay() in the code. Examples using this library will have Task in the filename.

I am going to take this a step at a time so that it is easy for those not familiar to get the idea.

Please contact me in the case of difficulty.

John Fletcher (john@bunbury28.plus.com}

## mLink_Button_Pad_Read_Task

Demonstration of the mLink 6 Button component.

## mLink_Char_LCD_Hello_World_Task

Demonstration of the mLink character LCD display. It also shows the way to use TaskManagerIO to run a task once only.

Notice that when using the mLink display there is no need to specify anything except the I2C address to get it running.

## Other Arduino codes

Here is a link to [MERG-Arduino-Software](https://github.com/fletchjp/MERG-Arduino-Software) which has other Arduino codes.
