/*
    coucou - Control software for art project
    Copyright (C) 2018 ADW

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

