// C++ code
//
const int trig = 2, echo = 4;
int green = 8, red = 9;
long duration;
int distance;
void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration * 343 * 0.5 * 0.0001;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.print(" cm\n");
  
  if (distance <= 30) {
    digitalWrite(9, HIGH);
    digitalWrite(8,LOW);
  }
  else {
    digitalWrite(9, LOW);
    digitalWrite(8,HIGH);
  }
}