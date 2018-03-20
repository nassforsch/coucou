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
    Body(Adafruit_PWMServoDriver *pwm);
    ~Body();

    void moveToFullOut();
	void moveToHalfOut();
	void moveToHiding();
    
  private:
	int currentPosition = 0;
	int servonum = 0;
	Adafruit_PWMServoDriver *pwm;
	
};

#endif // ndef BODY_H