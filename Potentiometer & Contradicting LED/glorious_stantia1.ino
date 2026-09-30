// C++ code
//

int green = 3, red = 5, pm = A0;
void setup()
{
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(pm, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int input = analogRead(pm);
  int map1 = map(input, 0, 1023, 0, 255);
  int map2 = map(input, 0, 1023, 255, 0);
  analogWrite(red, map1);
  analogWrite(green, map2);
  Serial.print("Red ");
  Serial.print(map1);
  Serial.print(" | Green: ");
  Serial.println(map2);
}