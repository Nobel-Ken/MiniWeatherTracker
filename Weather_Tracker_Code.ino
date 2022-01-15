include <LowPower.h>
#include <DHT.h>
#include <DS3231_Simple.h>
#include <SPI.h>
#include <SD.h>

DS3231_Simple Clock;
DHT dht(2, DHT11);

unsigned long elapsed;
int start,diff,LONG,LONGER;
float HUMID,TEMP;
DateTime MyDateAndTime;
DateTime MyTimestamp;

File myFile;

void setup(){
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  digitalWrite (4,LOW);
  digitalWrite (5,LOW);
  if (!SD.begin(SS)) {
    digitalWrite (4,HIGH);
    while (1);
  }
  dht.begin();
  Clock.begin();  
  Clock.disableAlarms();
  Clock.setAlarm(DS3231_Simple::ALARM_EVERY_SECOND);
  attachInterrupt(digitalPinToInterrupt(3), toggle, FALLING);
  if (SD.exists("TEMP.txt")){
    SD.remove("TEMP.txt");
  }
  if (SD.exists("HUMIDITY.txt")){
    SD.remove("HUMIDITY.txt");
  }
  if (SD.exists("ELAPSED.txt")){
    SD.remove("ELAPSED.txt");
  }
  if (SD.exists("TIME.txt")){
    SD.remove("TIME.txt");
  }
  if (SD.exists("DATE.txt")){
    SD.remove("DATE.txt");
  }
}

void loop(){
  MyDateAndTime = Clock.read();
  if (Clock.checkAlarms()==1&&start==1){
    diff = MyDateAndTime.Second-MyTimestamp.Second;
    if (diff<0){
      diff=(60+MyDateAndTime.Second)-MyTimestamp.Second;
    }
    while (diff<5){
      LowPower.powerDown(SLEEP_15MS, ADC_OFF, BOD_OFF);
      MyDateAndTime = Clock.read();
      diff = MyDateAndTime.Second-MyTimestamp.Second;
    if (diff<0){
      diff=(60+MyDateAndTime.Second)-MyTimestamp.Second;
    }
    }
    record();
    elapsed+=5;
    LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  }
  if (start == 1){
    digitalWrite (5,LOW);
  } else {
    digitalWrite (5,HIGH);
  }
}

void record(){
  myFile= SD.open("TIME.txt", FILE_WRITE);
  if (myFile==1){
    Clock.printTimeTo_HMS(myFile);
    myFile.println();
    myFile.close(); 
  }
  MyTimestamp = MyDateAndTime;
  myFile= SD.open("DATE.txt", FILE_WRITE);
  if (myFile==1){ 
    Clock.printDateTo_MDY(myFile);
    myFile.println();
    myFile.close(); 
  }
  HUMID=dht.readHumidity();
  TEMP=dht.readTemperature(true);
  myFile= SD.open("TEMP.txt", FILE_WRITE);
  if (myFile==1){ 
    myFile.println(TEMP);
    myFile.close(); 
  }
  myFile= SD.open("HUMIDITY.txt", FILE_WRITE);
  if (myFile==1){ 
    myFile.println(HUMID);
    myFile.close(); 
  }
  myFile= SD.open("ELAPSED.txt", FILE_WRITE);
  if (myFile==1){ 
    myFile.println(elapsed);
    myFile.close(); 
  }
}

void toggle(){
  start++;
  if (start>1){
    start=0;
  }
}

