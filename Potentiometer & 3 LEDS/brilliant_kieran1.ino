int green = 3, yellow = 5, red = 6;
int pm = A0;

void setup()
{
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(pm, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int input = analogRead(pm);
  int input1;

  if(input <= 340)
  {
    input1 = map(input, 0, 340, 0, 255);
    analogWrite(green, input1);
    analogWrite(yellow, 0);
    analogWrite(red, 0);

    Serial.print("Potentiometer: ");
    Serial.print(input);
    Serial.print(" | Green ");
    Serial.println(input1);
  }
  else if(input <= 680)
  {
    input1 = map(input, 341, 680, 0, 255);
    analogWrite(green, 0);
    analogWrite(yellow, input1);
    analogWrite(red, 0);

    Serial.print("Potentiometer: ");
    Serial.print(input);
    Serial.print(" | Yellow ");
    Serial.println(input1);
  }
  else
  {
    input1 = map(input, 681, 1023, 0, 255);
    analogWrite(green, 0);
    analogWrite(yellow, 0);
    analogWrite(red, input1);

    Serial.print("Potentiometer: ");
    Serial.print(input);
    Serial.println(" | Red ");
    Serial.println(input1);
  }

  delay(100);
}