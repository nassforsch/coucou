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


Body::Body()
{
	myState = IN;
	position = 5;
	startWaitTime = millis();
}

Body::~Body()
{
}

int Body::getPosition()
{
	return position;
}

void Body::reactToLoudness(double loudness)
{
	if (myState == IN) {
		if (loudness > 1.5) {
			startWaitTime = millis();
		}
		if (millis() - startWaitTime > 5000) {
			myState = OUT;
			position = 175;
			startWaitTime = millis();
		}
	}
	if (myState == HALF) {
		if (loudness > 2.0) {
			myState = IN;
			position = 5;
			startWaitTime = millis();
		} else if (loudness < 1.5 && millis() - startWaitTime > 5000) {
			myState = OUT;
			position = 175;
			startWaitTime = millis();
		}
	}
	if (myState == OUT && millis() - startWaitTime > 2000) {
		if (loudness > 2.0) {
			myState = IN;
			position = 5;
			startWaitTime = millis();
		} else if (loudness > 1.5) {
			myState = HALF;
			position = 90;
			startWaitTime = millis();
		}
	}
}
