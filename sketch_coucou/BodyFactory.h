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
#include <LinkedList.h>
#include "Body.h"

class BodyFactory {
  public:
    BodyFactory();
    ~BodyFactory();

	// return new Body instance initalized to use shared servo driver
    Body* createBody();
	
	// carry out movements of all bodies
	void moveBodies();
    
  private:
	LinkedList<Body*> *bodyList;
  
	// shared servo driver for all Body objects
	Adafruit_PWMServoDriver *pwm;
	
	int  updateInterval = 50;      // interval between updates
	unsigned long lastUpdate = 0; // last update of position
	
};

#endif // ndef BODYFACTORY_H