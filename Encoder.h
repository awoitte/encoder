/*

Tiny Arduino Encoder Library

Designed to be extremely small, elegant, and without the need for interrupts.
Originally created to fit on an ATTiny13A, it should work on any Arduino compatible board.

Code modified from: https://playground.arduino.cc/Main/RotaryEncoders/#sourceblock3
"Unnamed Library" no other attribution given.

Alicia Woitte <aliciawoitte@gmail.com>

*/

#include <Arduino.h>

static int isFwd;

struct Encoder
{
    int pinA;
    int pinB;
    int previousState;
    int state;
};

/**
 *
 * Initializes pins for encoder input and returns object to track state
 * @param  {int} pinA : encoder pin
 * @param  {int} pinB : encoder pin (other one)
 * @return {struct}   : encoder object
 */
struct Encoder encoderSetup(int pinA, int pinB)
{
    struct Encoder encoder;
    encoder.pinA = pinA;
    encoder.pinB = pinB;
    encoder.previousState = 0;
    encoder.state = 0;

    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

    // enable pull-up resistors
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);

    return encoder;
}

/**
 *
 * Reads from pins to update encoder state object. Should be run once each loop.
 * @param  {struct*} Encoder : encoder object
 * @return {int}             : change in position since last loop (1 for forwards, 0 for no change, -1 for backwards)
 */
int encoderLoop(struct Encoder *encoder)
{
    int change = 0;

    // encode each possible state into a single number
    encoder->state = (digitalRead(encoder->pinB) * 2) + digitalRead(encoder->pinA);

    if (encoder->state != encoder->previousState)
    {
        // assuming : loop frequency is >= the encoders state changing frequency
        isFwd = ((encoder->previousState == 0) && (encoder->state == 1)) || ((encoder->previousState == 1) && (encoder->state == 3)) ||
                ((encoder->previousState == 3) && (encoder->state == 2)) || ((encoder->previousState == 2) && (encoder->state == 0));

        if (isFwd)
            change = 1;
        else
            change = -1;
    }
    encoder->previousState = encoder->state;

    return change;
}
