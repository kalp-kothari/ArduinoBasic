// C++ code
//
#include <Servo.h>
Servo s1, s2;
int pm = A0;
void setup()
{
  s1.attach(3);
  s2.attach(5);
  pinMode(pm, INPUT);
}

void loop()
{
  int input = analogRead(pm);
  int input1 = map(input, 0, 1023, 0, 180);
  int input2 = map(input, 0, 1023, 180,0);
  s1.write(input1);
  s2.write(input2);
  
}