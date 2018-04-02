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
	// initally move to "IN" position
	myState = MOVEIN;
	position = 0;
	targetPosition = 5;
	speed = 1000;
	idle = false;
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

bool TribeMember::isIdle()
{
	return idle;
}

void TribeMember::setPosition(int newPosition)
{
	position = newPosition;
}

void TribeMember::determineReaction(double loudness)
{
	if (myState == IN) {
		if (loudness > 1.5) {
			// stay in this state and
			// reset timeout if loudness
			// is above lower threshold
			startWaitTime = millis();
			idle = true;
		}
		if (millis() - startWaitTime > 5000) {
			// leave state and move to full out
			// if loudness has been below threshold
			// for full wait time
			myState = MOVEOUT;
			speed = 2;
			targetPosition = 175;
			startWaitTime = millis();
			idle = false;
		}
	}
	if (myState == HALF) {
		if (loudness > 2.0) {
			// retract further to IN state if loudness
			// is above higher threshold
			myState = MOVEIN;
			speed = 1000;
			targetPosition = 5;
			idle = false;
		} else if (loudness < 1.5 && millis() - startWaitTime > 5000) {
			// move further out if loudness was below threshold
			// for full wait time
			myState = MOVEOUT;
			speed = 2;
			targetPosition = 175;
			idle = false;
		}
	}
	if (myState == OUT && millis() - startWaitTime > 2000) {
		if (loudness > 2.0) {
			myState = MOVEIN;
			speed = 1000;
			targetPosition = 5;
			idle = false;
		} else if (loudness > 1.5) {
			myState = MOVEHALF;
			speed = 1000;
			targetPosition = 90;
			idle = false;
		}
	}
	if (myState == MOVEOUT) {
		if (loudness > 2.0) {
			myState = MOVEIN;
			speed = 1000;
			targetPosition = 5;
			idle = false;
		} else if (loudness > 1.5 && position > 90) {
			myState = MOVEHALF;
			speed = 1000;
			targetPosition = 90;
			idle = false;
		} else if (position == targetPosition) {
			myState = OUT;
			idle = true;
		}
	}
	if (myState == MOVEHALF) {
		if (loudness > 2.0) {
			myState = MOVEIN;
			speed = 1000;
			targetPosition = 5;
			idle = false;
		} else if (position == targetPosition) {
			myState = HALF;
			startWaitTime = millis();
			idle = true;
		}
	}
	if (myState == MOVEIN) {
		if (position == targetPosition) {
			myState = IN;
			startWaitTime = millis();
			idle = true;
		}
	}
}
