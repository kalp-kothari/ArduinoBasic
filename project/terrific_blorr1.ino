int echo = 3, trig = 2;
int en1 = 10, en3 = 9;
int in1 = 6, in2 = 7, in4 = 5, in3 = 4;
void setup()
{
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en3, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  
  int duration = pulseIn(echo, HIGH);
  int distance = duration * 0.0343 / 2;
  if (distance <= 100) {
    int speed1 = map(distance, 0, 100, 0, 255);
    analogWrite(en1, speed1);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    analogWrite(en3, speed1);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
}
  else if (distance > 100 && distance <=250) {
    int speed1 = map(distance, 100, 250, 0, 255);
    int speed2 = map(distance, 100, 250, 0, 255);
    analogWrite(en1, speed1);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    
    analogWrite(en3, speed2);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
}