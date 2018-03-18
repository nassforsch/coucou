
#include "Ear.h"

int ledPin=13;
int sensorPin=7;

Ear *myEar;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  myEar = new Ear(sensorPin);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
   Serial.println(myEar->getLoudness());
}

