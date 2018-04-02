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

#ifndef EAR_H
#define EAR_H

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)

class Ear {
  public:
    Ear(int sensorPin);
    ~Ear();

    double getLoudness();
    
  private:
    int sensorPin;
};

#endif // ndef EAR_H