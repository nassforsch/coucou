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

#ifndef TRIBEMEMBER_H
#define TRIBEMEMBER_H

class TribeMember {
  public:
    TribeMember(int fastSpeed, int slowSpeed);
    ~TribeMember();
	
	void determineReaction(double loudness);	
	int getPosition();
	int getTargetPosition();
	int getSpeed();
	void setPosition(int newPosition);
	bool isIdle();
    
  private:
	// configuration of TribeMember
	unsigned int fastSpeed = 0;
	unsigned int slowSpeed = 0;
	
	// state related information
	bool idle = true;
	int targetPosition = 0;
	int position = 0; // current servo target position
	int speed = 1000; // degrees per second
	unsigned long startWaitTime = 0; // starting time of waiting period (in millis)
	unsigned long startMoveTime = 0; // starting time of moving perion (in millis)
	enum stateOptions { IN, HALF, OUT, MOVEIN, MOVEHALF, MOVEOUT } myState = IN;
	
};

#endif // ndef TRIBEMEMBER_H