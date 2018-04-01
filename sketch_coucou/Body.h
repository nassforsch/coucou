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

#ifndef BODY_H
#define BODY_H
#include <Adafruit_PWMServoDriver.h>

class Body {
  public:
    Body();
    ~Body();

	void reactToLoudness(double loudness);	
	int getPosition();
    
  private:
	int position = 0; // current servo target position
	unsigned long startWaitTime = 0; // starting time of waiting period (in millis)
	enum state { IN, HALF, OUT } myState = IN;
	
};

#endif // ndef BODY_H