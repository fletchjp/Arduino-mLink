# Arduino-mLink

Arduino codes using mLink components

I am going to put here some of the codes I have been developing for Arduinos to use mLink components.

These are developments in one way and another of the examples supplied by [Hobby Components](https://hobbycomponents.com/).

These codes all need the [mLink Arduino library](https://github.com/HobbyComponents/mLink) which will need to be downloaded and installed. The current version of the library is v2.2.2.

Many of these examples make use of the [TaskManagerIO library](https://tcmenu.github.io/documentation/arduino-libraries//taskmanager-io/) to control the mLink device. This avoids the need to use delay() in the code. Examples using this library will have Task in the filename.

## mLink_Button_Pad_Read_Task

Demonstration of the mLink 6 Button component.
