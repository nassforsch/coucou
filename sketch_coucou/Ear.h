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