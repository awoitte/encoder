#include <Arduino.h>
#include "Encoder.h"

#define LED_PIN 0
#define ENCODER_PIN_A 4
#define ENCODER_PIN_B 3

#define ENCODER_MAX 1023
#define ENCODER_MIN 0

static int encoderPosition = ENCODER_MIN;
static int previousPosition = ENCODER_MIN;
static struct Encoder encoder;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, encoderPosition);
  encoder = encoderSetup(ENCODER_PIN_A, ENCODER_PIN_B);
}

void loop()
{
  encoderPosition += encoderLoop(&encoder);

  if (encoderPosition < ENCODER_MIN)
    encoderPosition = ENCODER_MIN;
  if (encoderPosition > ENCODER_MAX)
    encoderPosition = ENCODER_MAX;

  if (previousPosition != encoderPosition)
  {
    previousPosition = encoderPosition;

    analogWrite(LED_PIN, encoderPosition / 4); // read at 4x resolution because the specific encoder I'm using changes state 4x between notches
  }
}
