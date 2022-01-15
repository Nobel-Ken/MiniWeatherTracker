# [Hardware] TempTrack
The Temptrack is an Arduino based Temprature and Humidity tracker that can record said data onto a MicroSD card. It can run for around 3-4 days on a single charge and can be powered externally via MicroUSB.

![IMG_2374](https://user-images.githubusercontent.com/17792367/149608589-3b2aad72-4ccb-433d-907b-60f3003e3f01.jpg)
![IMG_2372](https://user-images.githubusercontent.com/17792367/149608591-2d003a05-8f77-41a0-9096-6cde5f5c9c98.jpg)

### Design
The brain of the TempTrack is a ATmega 382P microcontroller in the form of an Arduino. It reads data from a DHT11 Temprature and Humidity sensor which it then records onto a microSD card. Data is written to the microSD card via a SC card board which has an intagrated level-shifter to change the 5 volt logic of the Arduino to 3.3 volts for the card. A DS3231 real time clock (RTC) is used to get accurate times for the time stamps for the data written to the SD card. Power is provided by a 1000mah lithium polymer battery which is charge though a TP4056 charge controller. 

![TempTrack](https://user-images.githubusercontent.com/17792367/149609570-2f6d3003-adc7-487a-924a-0b252a370e10.png)


On bootup, the SD card is checked for validity, and assuming it passes, a green LED lights on the device. If the check fails, a red LED lights instead. After a sucsessful boot, if the record button is pushed, data logging begins. Duing data logging, the Arduino records data to its MicroSD card from the DHT11 and the RTC once every 5 seconds. After recording data, it enters a power hibernation mode to conserve power, waking only to record more data. This continues untill the record button is hit again which triggers an interupt that wakes the Arduino. 

