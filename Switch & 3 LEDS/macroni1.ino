// C++ code
//

int s1 = 2, s2 = 3;
int red = 4, yellow = 5, green = 6;
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
}

void loop()
{
  if(digitalRead(s1)==HIGH && digitalRead(s2) == LOW){
    digitalWrite(red,HIGH);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);
  }
  else if(digitalRead(s1)==LOW && digitalRead(s2) == HIGH){
    digitalWrite(yellow,HIGH);
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
     
  }else if(digitalRead(s1)==HIGH && digitalRead(s2) == HIGH){
    digitalWrite(red,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,HIGH);
  }
    else {
    digitalWrite(red,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);
  }
}