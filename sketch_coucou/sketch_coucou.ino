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
#include "Tribe.h"

struct tribeMemberSettings {
	int fastSpeed;
	int slowSpeed;
	double loudNoise;
	double mediumNoise;
	int freezeTimout;
};

const int soundSensorPin = 7;
const int serialBaudRate = 9600;
const int numTribeMembers = 10;

const tribeMemberSettings tribeConfiguration[numTribeMembers] = {
	{1000, 10, 2.0, 1.5, 5000},
	{100, 50, 2.2, 2.0, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000},
	{50, 5, 2.0, 1.5, 5000}
};

Ear *myEar;
Tribe *myTribe;

long startTime = 0;

void setup() {
  // put your setup code here, to run once:
  myEar = new Ear(soundSensorPin);
  myTribe = new Tribe();
  for (int i=0; i<numTribeMembers; i++) {	
	myTribe->createTribeMember(tribeConfiguration[i].fastSpeed, tribeConfiguration[i].slowSpeed,
	tribeConfiguration[i].loudNoise, tribeConfiguration[i].mediumNoise, tribeConfiguration[i].freezeTimout);
  }
  Serial.begin(serialBaudRate);
}

void loop() {
   // put your main code here, to run repeatedly:
   //startTime = millis();
   double loudness = myEar->getLoudness();
   myTribe->update(loudness);
   Serial.println(loudness);
   //Serial.println(millis() - startTime);
}

