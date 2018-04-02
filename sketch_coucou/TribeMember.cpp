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

TribeMember::TribeMember(int _fastSpeed, int _slowSpeed, double _loudNoise, double _mediumNoise, int _freezeTimeout)
:fastSpeed(_fastSpeed), slowSpeed(_slowSpeed), loudNoise(_loudNoise), mediumNoise(_mediumNoise), freezeTimeout(_freezeTimeout)
{
	// initally move fast to "IN" position, assume we are fully out
	myState = MOVEIN;
	position = TribeMemberConst::outPosition;
	targetPosition = TribeMemberConst::inPosition;
	speed = fastSpeed;
	idle = false;
	startMoveTime = millis();
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
		if (loudness > mediumNoise) {
			// stay in this state and
			// reset timeout if loudness
			// is above lower threshold
			startWaitTime = millis();
			idle = true;
		}
		if (millis() - startWaitTime > freezeTimeout) {
			// leave state and move to full out
			// if loudness has been below threshold
			// for full wait time
			myState = MOVEOUT;
			speed = slowSpeed;
			targetPosition = TribeMemberConst::outPosition;
			startWaitTime = millis();
			idle = false;
		}
	}
	if (myState == HALF) {
		if (loudness > loudNoise) {
			// retract further to IN state if loudness
			// is above higher threshold
			myState = MOVEIN;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::inPosition;
			idle = false;
			startMoveTime = millis();
		} else if (loudness < mediumNoise && millis() - startWaitTime > freezeTimeout) {
			// move further out if loudness was below threshold
			// for full wait time
			myState = MOVEOUT;
			speed = slowSpeed;
			targetPosition = TribeMemberConst::outPosition;
			idle = false;
		}
	}
	if (myState == OUT) {
		if (loudness > loudNoise) {
			myState = MOVEIN;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::inPosition;
			idle = false;
			startMoveTime = millis();
		} else if (loudness > mediumNoise) {
			myState = MOVEHALF;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::halfPosition;
			idle = false;
			startMoveTime = millis();
		}
	}
	if (myState == MOVEOUT) {
		if (loudness > loudNoise) {
			myState = MOVEIN;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::inPosition;
			idle = false;
			startMoveTime = millis();
		} else if (loudness > mediumNoise && position > TribeMemberConst::halfPosition) {
			myState = MOVEHALF;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::halfPosition;
			idle = false;
			startMoveTime = millis();
		} else if ((abs(position-targetPosition) < TribeMemberConst::positionFuzziness)) {
			myState = OUT;
			idle = true;
		}
	}
	if (myState == MOVEHALF) {
		if (loudness > loudNoise) {
			myState = MOVEIN;
			speed = fastSpeed;
			targetPosition = TribeMemberConst::inPosition;
			idle = false;
		} else if ((abs(position-targetPosition) < TribeMemberConst::positionFuzziness) && millis() - startMoveTime > TribeMemberConst::moveTimeout) {
			myState = HALF;
			startWaitTime = millis();
			idle = true;
		}
	}
	if (myState == MOVEIN) {
		if ((abs(position-targetPosition) < TribeMemberConst::positionFuzziness) && millis() - startMoveTime > TribeMemberConst::moveTimeout) {
			myState = IN;
			startWaitTime = millis();
			idle = true;
		}
	}
}
