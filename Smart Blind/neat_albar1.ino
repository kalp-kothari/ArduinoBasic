#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 4
#define ECHO_PIN 2
#define PIR_PIN 7
#define SERVO_PIN 3
#define LDR_PIN A1
#define POT_PIN A0
#define GREEN_LED 10
#define YELLOW_LED 9
#define RED_LED 8
#define SWITCH 6
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo blind;

#define OPEN_ANGLE 0
#define CLOSED_ANGLE 90
#define PERSON_TIME 3000
#define RELEASE_TIME 5000

unsigned long presenceStart = 0;
unsigned long personLeftTime = 0;
bool personDetected = false;
bool releaseWaiting = false;

long readUltrasonic()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 10000);
    if (duration == 0) return -1;

    return duration * 0.0343 / 2;
}

void greenLED()
{
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
}

void yellowLED()
{
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
}

void redLED()
{
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}

void showMessage(String line1, String line2)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
  	pinMode(SWITCH, INPUT);

    blind.attach(SERVO_PIN);

    lcd.init();
    lcd.backlight();

    blind.write(OPEN_ANGLE);
    greenLED();
  	if(digitalRead(SWITCH))
    showMessage("SMART BLIND", "AUTO MODE");
  	else
    showMessage("SMART BLIND", "MANUAL MODE");

    delay(1000);
}

void loop()
{
    long distance = readUltrasonic();
    int pir = digitalRead(PIR_PIN);
    int lightValue = analogRead(LDR_PIN);
    int potValue = analogRead(POT_PIN);

    int detectionRange = map(potValue, 0, 1023, 10, 100);

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" | Range: ");
    Serial.print(detectionRange);
    Serial.print(" | PIR: ");
    Serial.print(pir);
    Serial.print(" | LDR: ");
    Serial.print(lightValue);
    Serial.print(" | POT: ");
    Serial.println(potValue);

    if (distance == -1 && digitalRead(SWITCH))
    {
        blind.write(CLOSED_ANGLE);
        redLED();
        showMessage("TAMPER", "NO ECHO");
        delay(100);
        return;
    }
  else if (!digitalRead(SWITCH)){
    showMessage("SMART BLIND", "MANUAL MODE");
    delay(300);
    return;
  }

    bool objectPresent = distance <= detectionRange;

    if (objectPresent && pir == HIGH)
    {
        if (presenceStart == 0)
            presenceStart = millis();

        unsigned long presenceTime = millis() - presenceStart;

        if (presenceTime < PERSON_TIME)
        {
            yellowLED();

            if (presenceTime < 150)
                showMessage("DETECTING", "WAIT...");
        }
        else
        {
            personDetected = true;
            releaseWaiting = false;
            blind.write(CLOSED_ANGLE);
            redLED();
            showMessage("PRIVACY", "BLIND CLOSED");
        }
    }
    else
    {
        presenceStart = 0;

        if (personDetected)
        {
            if (!releaseWaiting)
            {
                releaseWaiting = true;
                personLeftTime = millis();
            }

            blind.write(CLOSED_ANGLE);
            redLED();

            unsigned long elapsed = millis() - personLeftTime;

            if (elapsed < RELEASE_TIME)
            {
                showMessage("PRIVACY", "WAITING...");
            }
            else
            {
                personDetected = false;
                releaseWaiting = false;
            }
        }

        if (!personDetected)
        {
            int angle = map(lightValue, 0, 1023, OPEN_ANGLE, CLOSED_ANGLE);

            blind.write(angle);
            greenLED();

            showMessage("AUTO", "L:" + String(lightValue) + " A:" + String(angle));
        }
    }

    delay(100);
}