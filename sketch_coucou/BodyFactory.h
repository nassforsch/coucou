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

#ifndef BODYFACTORY_H
#define BODYFACTORY_H
#include <Adafruit_PWMServoDriver.h>
#include "Body.h"

class BodyFactory {
  public:
    BodyFactory();
    ~BodyFactory();

	// return new Body instance initalized to use shared servo driver
    Body* createBody();
    
  private:
	// shared servo driver for all Body objects
	Adafruit_PWMServoDriver *pwm;
	// counter to determine next servo slot to be used
	// based on order of creation of Body objects
	unsigned int nextServo = 0;
};

#endif // ndef BODYFACTORY_H