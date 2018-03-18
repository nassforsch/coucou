
int ledPin=13;
int sensorPin=7;

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)

class Ear {
  public:
    Ear(int sensorPin);
    ~Ear();

    double getLoudness();
    
  private:
    int sensorPin;
};

Ear::Ear(int _sensorPin)
:sensorPin(_sensorPin)
{
  pinMode(sensorPin, INPUT);
}

Ear::~Ear()
{
}

// read from an analog pin and return voltage that corresponds to sound amplitude
// takes 50 ms for each run
double Ear::getLoudness()
{
   unsigned long startMillis = millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
 
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   unsigned int sample = 0;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(sensorPin);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   return (peakToPeak * 5.0) / 1024;  // convert to volts
}

Ear *myEar;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  myEar = new Ear(sensorPin);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly: 
   Serial.println(myEar->getLoudness());
}

