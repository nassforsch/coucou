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

#include "Body.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

Body::Body(Adafruit_PWMServoDriver *_pwm)
:pwm(_pwm)
{
}

Body::~Body()
{
}

void Body::moveToFullOut()
{
	while (currentPosition <= 175) {
		int pulselength = map(++currentPosition, 0, 180, SERVOMIN, SERVOMAX);
		pwm->setPWM(servonum, 0, pulselength);
		delay(15);							// wait 15 ms to reach position
	}
}

void Body::moveToHalfOut()
{
	if (currentPosition != 90) {
		currentPosition = 90;
		int pulselength = map(++currentPosition, 0, 180, SERVOMIN, SERVOMAX);
		pwm->setPWM(servonum, 0, pulselength);
		delay(1000);							// wait 15 ms to reach position
	}
}

void Body::moveToHiding()
{
		if (currentPosition > 5) {
			currentPosition = 5;
			int pulselength = map(++currentPosition, 0, 180, SERVOMIN, SERVOMAX);
			pwm->setPWM(servonum, 0, pulselength);
			delay(2000);							// wait 15 ms to reach position
		}
}