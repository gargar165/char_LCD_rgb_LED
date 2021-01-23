/*
 * ledCode.h
 * 
 * Updates the LED by listening to the red, green, and 
 *   blue variables in the structure passed through.
 * 
 * Author: Jack Justice - 12/20/2020
 */

#ifndef LEDCODE_H
#define LEDCODE_H

#include <TeensyThreads.h>

typedef struct LEDPINS
{
    static const int red = 15;
    static const int green = 14;
    static const int blue = 13;
} ledPins;
ledPins led;

void setupLED()
{
    pinMode(led.red, OUTPUT);
    pinMode(led.green, OUTPUT);
    pinMode(led.blue, OUTPUT);
}

void updateLED(void *data)
{
    // Save the address of the structure to a pointer
    ledData *ledStatus = (ledData *) data;

    while(1)
    {
        delay(1);
        analogWrite(led.red, ledStatus->red);
        analogWrite(led.green, ledStatus->green);
        analogWrite(led.blue, ledStatus->blue);
    }
}

#endif