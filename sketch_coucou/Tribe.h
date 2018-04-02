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

#ifndef TRIBE_H
#define TRIBE_H
#include <Adafruit_PWMServoDriver.h>
#include <LinkedList.h>
#include "TribeMember.h"

const int updateInterval = 50;      // interval between servo updates

class Tribe {
  public:
    Tribe();
    ~Tribe();

	// return new TribeMember instance initalized to use shared servo driver
    void createTribeMember(int fastSpeed, int SlowSpeed, double loudNoise, double mediumNoise, int freezeTimeout);
	
	// pass sensor input to all TribeMember objects
	void update(double loudness);
	
   
  private:
	LinkedList<TribeMember*> *tribeMemberList;
  
	// shared servo driver for all TribeMember objects
	Adafruit_PWMServoDriver *pwm;
	
	unsigned long lastUpdate = 0; // last update of position
	
	// carry out movements of all TribeMember objects
	void moveBodies();
 
	
};

#endif // ndef TRIBE_H