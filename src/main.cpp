#include <Arduino.h>
#include <Ultrasonic.h>

// Buzzer time in ms
#define BUZZER_TIME_FULL 2000
#define BUZZER_TIME_HALF 1000
#define BUZZER_TIME_QUARTER 500
const int buzzerTime[3] = {
    BUZZER_TIME_FULL,
    BUZZER_TIME_HALF,
    BUZZER_TIME_QUARTER,
};

// Buzzer pin
#define BUZZER_PIN 8

// Ultrasonic pins
#define TRIG_PIN 10
#define ECHO_PIN 9

// Led pins
const int leds[3] = {11, 12, 13};

#define READ_INTERVAL 100

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);
int distance;
int timeLeft = 0;
size_t lastLedQuantity = 0;

void setup()
{
  for (size_t i = 0; i < 3; i++)
  {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);
}

void toggleLeds(size_t ledQuantity)
{
  for (size_t i = 0; i < ledQuantity; i++)
  {
    digitalWrite(leds[i], HIGH);
  }

  for (size_t i = ledQuantity; i < 3; i++)
  {
    digitalWrite(leds[i], LOW);
  }
}

void updateLedQuantity(size_t ledQuantity)
{
  if (ledQuantity != lastLedQuantity)
  {
    timeLeft -= (buzzerTime[lastLedQuantity - 1] - buzzerTime[ledQuantity - 1]);

    lastLedQuantity = ledQuantity;
  }
}

void activateBuzzer(size_t ledQuantity)
{
  digitalWrite(BUZZER_PIN, HIGH);
  delay(READ_INTERVAL / 2);
  digitalWrite(BUZZER_PIN, LOW);

  timeLeft = buzzerTime[ledQuantity - 1];
  delay(READ_INTERVAL / 2);
}

void operateActuators(size_t ledQuantity)
{
  toggleLeds(ledQuantity);

  updateLedQuantity(ledQuantity);

  if (ledQuantity > 0 && timeLeft <= 0)
    activateBuzzer(ledQuantity);
  else
    delay(READ_INTERVAL);

  timeLeft -= READ_INTERVAL;
}

void loop()
{
  distance = ultrasonic.read();

  if (distance > 30)
    return operateActuators(0);
  else if (distance >= 20)
    return operateActuators(1);
  else if (distance >= 10)
    return operateActuators(2);
  else
    return operateActuators(3);
}