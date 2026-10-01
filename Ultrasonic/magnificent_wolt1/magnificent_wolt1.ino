// C++ code
//
int led = 3;
int trig = 5;
int echo = 6;
float input = 0;

float myMap(int in, int inmin,int inmax, int oumin, int oumax) {
  return (float) (in-inmin)*(oumax-oumin)/(inmax-inmin)+oumin;
}
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  
  int duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;
  if(distance <= 200 && distance >= 20) {
  input = myMap(distance, 20, 200, 0, 255);
  analogWrite(led, input);
  }
  else {
    input = 0;
    analogWrite(led, input);
  }
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" | Brightness: ");
  Serial.println(input);
}