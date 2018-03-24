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

#include "BodyFactory.h"
#include "Body.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

BodyFactory::BodyFactory()
{
	// create servo driver object that will be shared by all bodies created by the BodyFactory
	// called this way, it uses the default address 0x40
	pwm = new Adafruit_PWMServoDriver();
	pwm->begin();
	pwm->setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}

BodyFactory::~BodyFactory()
{
	destroy pwm;
}

Body* BodyFactory::createBody()
{
	// create new Body object with reference to servo driver
	// and increase next servo counter by one
	return new Body(&pwm, nextServo++);
}