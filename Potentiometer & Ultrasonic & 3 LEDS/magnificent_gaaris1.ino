int green = 9;
int yellow = 10;
int red = 11;

int trig = 2;
int echo = 3;
int pm = A0;

void setup()
{
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(pm, INPUT);

  Serial.begin(9600);
}

void loop()
{
  int potValue = analogRead(pm);
  int warningDistance = map(potValue, 0, 1023, 10, 50);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.034 / 2;
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);

  if (distance > warningDistance)
  {
    digitalWrite(green, HIGH);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Warning Distance: ");
    Serial.print(warningDistance);
    Serial.println(" cm | SAFE");
  }
  else if (distance > warningDistance / 2)
  {
    digitalWrite(yellow, HIGH);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Warning Distance: ");
    Serial.print(warningDistance);
    Serial.println(" cm | GETTING CLOSE");
  }
  else
  {
    digitalWrite(red, HIGH);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm | Warning Distance: ");
    Serial.print(warningDistance);
    Serial.println(" cm | DANGER");
  }

  delay(200);
}