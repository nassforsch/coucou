
int ledPin=13;
int sensorPin=7;
float val = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin (9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(sensorPin);
  Serial.println(val);
}
