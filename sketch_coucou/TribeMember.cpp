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

#include "TribeMember.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


TribeMember::TribeMember()
{
	myState = IN;
	position = 5;
	startWaitTime = millis();
}

TribeMember::~TribeMember()
{
}

int TribeMember::getPosition()
{
	return position;
}

int TribeMember::getTargetPosition()
{
	return targetPosition;
}

int TribeMember::getSpeed()
{
	return speed;
}

void TribeMember::setPosition(int newPosition)
{
	position = newPosition;
}

void TribeMember::reactToLoudness(double loudness)
{
	if (myState == IN) {
		if (loudness > 1.5) {
			startWaitTime = millis();
		}
		if (millis() - startWaitTime > 5000) {
			myState = MOVEOUT;
			speed = 2;
			targetPosition = 175;
			startWaitTime = millis();
		}
	}
	if (myState == HALF) {
		if (loudness > 2.0) {
			myState = IN;
			speed = 1000;
			targetPosition = 5;
			startWaitTime = millis();
		} else if (loudness < 1.5 && millis() - startWaitTime > 5000) {
			myState = MOVEOUT;
			speed = 2;
			targetPosition = 175;
			startWaitTime = millis();
		}
	}
	if (myState == OUT && millis() - startWaitTime > 2000) {
		if (loudness > 2.0) {
			myState = IN;
			speed = 1000;
			targetPosition = 5;
			startWaitTime = millis();
		} else if (loudness > 1.5) {
			myState = MOVEHALF;
			speed = 1000;
			targetPosition = 90;
			startWaitTime = millis();
		}
	}
	if (myState == MOVEOUT) {
		if (loudness > 2.0) {
			myState = IN;
			speed = 1000;
			targetPosition = 5;
			startWaitTime = millis();
		} else if (loudness > 1.5 && position > 90) {
			myState = MOVEHALF;
			speed = 1000;
			targetPosition = 90;
		} else if (position == targetPosition) {
			myState = OUT;
		}
	}
	if (myState == MOVEHALF) {
		if (loudness > 2.0) {
			myState = IN;
			speed = 1000;
			targetPosition = 5;
			startWaitTime = millis();
		} else if (position == targetPosition) {
			myState = HALF;
		}
	}
	
}
