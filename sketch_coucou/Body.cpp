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
#include <Servo.h>

Body::Body(int _motorPin)
{
	myServo = new Servo();
	myServo->attach(_motorPin);
}

Body::~Body()
{
}

void Body::moveToFullOut()
{
	while (currentPosition <= 175) {
		myServo->write(++currentPosition);
		delay(15);							// wait 15 ms to reach position
	}
}

void Body::moveToHalfOut()
{
	while (currentPosition < 90) {
		myServo->write(++currentPosition);
		delay(15);							// wait 15 ms to reach position
	}
	while (currentPosition > 90) {
		myServo->write(--currentPosition);
		delay(15);							// wait 15 ms to reach position
	}
}

void Body::moveToHiding()
{
		while (currentPosition > 5) {
		myServo->write(--currentPosition);
		delay(15);							// wait 15 ms to reach position
	}
}