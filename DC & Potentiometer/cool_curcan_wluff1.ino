// C++ code
//

int en3 = 3, in3 = 4, in4 = 2, en2 = 6, in1 = 7, in2 = 8, pm = A0;
void setup()
{
  pinMode(en3, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pm, INPUT);
}

void loop()
{
  int input = analogRead(pm);
  int input1 = map(input, 0, 1023, 0, 255);
  int input2 = map(input, 0, 1023, 255, 0);
  //One motor sppeds up while the other slows down
  digitalWrite(in3, HIGH);
  //digitalWrite(in3,LOW);
  digitalWrite(in4, LOW);
  //digitalWrite(in4, HIGH);
  analogWrite(en3, input1);
  
  digitalWrite(in1, HIGH);
  //digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  //digitalWrite(in2,HIGH);
  analogWrite(en2, input2);
}