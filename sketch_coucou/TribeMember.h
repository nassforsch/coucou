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

namespace TribeMemberConst {
	const int moveTimeout = 200; // wait at for this time in ms when driving at full speed before allowing to turn off servos
	const int maxPosition = 1000; // set end of movement range to 100%
	const int minPosition = 0; // set beginning of movement range to 0%
	const int halfPosition = 500; // set half out position to 50% of relevant movement range
	const int inPosition = 5; // set hidden ("in") position to 5% of relevant movement range
	const int outPosition = 995; // set out position to 95% of relevant movement range
	const int positionFuzziness = 2; // increments that we may be off but still consider we have reached the target position
	
	// Depending on your servo make, the pulse width min and max may vary, you 
	// want these to be as small/large as possible without hitting the hard stop
	// for max range. You'll have to tweak them as necessary to match the servos you
	// have!
	const int minServoPulseLength = 150; // this is the 'minimum' pulse length count (out of 4096)
	const int maxServoPulseLength = 550; // this is the 'maximum' pulse length count (out of 4096)
}

class TribeMember {
  public:
    TribeMember(int fastSpeed, int slowSpeed, double loudNoise, double mediumNoise, int freezeTimeout);
    ~TribeMember();
	
	void determineReaction(double loudness);	
	int getPosition();
	int getTargetPosition();
	int getSpeed();
	void setPosition(int newPosition);
	bool isIdle();
    
  private:
	// configuration of TribeMember
	int fastSpeed = 0;
	int slowSpeed = 0;
	double loudNoise = 0;
	double mediumNoise = 0;
	int freezeTimeout = 0;
		
	// state related information
	bool idle = false;
	int targetPosition = 0;
	int position = 0; // current servo target position
	int speed = 0; // degrees per second
	unsigned long startWaitTime = 0; // starting time of waiting period (in millis)
	unsigned long startMoveTime = 0; // starting time of moving perion (in millis)
	enum stateOptions { IN, HALF, OUT, MOVEIN, MOVEHALF, MOVEOUT } myState = IN;
	
};

#endif // ndef TRIBEMEMBER_H