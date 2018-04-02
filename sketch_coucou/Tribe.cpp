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

#include "Tribe.h"
#include "TribeMember.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <LinkedList.h>

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)
#define OE_PIN	  2   // pin for "output enable"

Tribe::Tribe()
{
	// create servo driver object that will be shared by all bodies created by the Tribe
	// called this way, it uses the default address 0x40
	pwm = new Adafruit_PWMServoDriver();
	bodyList = new LinkedList<TribeMember*>();

	pwm->begin();
	pwm->setPWMFreq(60);  // Analog servos run at ~60 Hz updates
	
	pinMode(OE_PIN, OUTPUT);
}

Tribe::~Tribe()
{
	delete pwm;
	delete bodyList;
}

TribeMember* Tribe::createTribeMember()
{
	// create new TribeMember object with reference to servo driver
	// and increase next servo counter by one
	TribeMember *newTribeMember = new TribeMember();
	bodyList->add(newTribeMember);
	return newTribeMember;
}

void Tribe::moveBodies()
{
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
		lastUpdate = millis();
		
		//digitalWrite(OE_PIN, LOW);
		
		for (int i=0; i<bodyList->size(); i++) {
			int targetPosition = (bodyList->get(i))->getTargetPosition();
			int speed =  (bodyList->get(i))->getSpeed();
			int position = (bodyList->get(i))->getPosition();
			int delta = targetPosition - position;
			if (delta > 0)
				position = position + constrain(delta,0,speed);
			else if (delta < 0)
				position = position + constrain(delta,-speed,0);
			(bodyList->get(i))->setPosition(position);
			int pulselength = map(position, 0, 180, SERVOMIN, SERVOMAX);
			Serial.println(pulselength);
			pwm->setPWM(i, 0, pulselength);
		}
		
		//digitalWrite(OE_PIN, HIGH);
	}
	
}
