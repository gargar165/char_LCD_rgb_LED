/*
 * joystickCode.h
 * 
 * Contains pin structure for wiring and setup. Also handles
 *   updating the RGB values in the ledData object.
 * 
 * Author: Jack Justice - 12/20/2020
 */

#ifndef JOYSTICKCODE_H
#define JOYSTICKCODE_H

#include <TeensyThreads.h>

typedef struct JOYSTICKPINS
{
    static const int xPosition = 22;
    static const int yPosition = 23;
    //static const int button = 21;
} joystickPins;
joystickPins joystick;

void joystickListener(void *data)
{
    // Save the address of the structure to a pointer
    ledData *ledStatus = (ledData *) data;
    ledStatus->xPosition = analogRead(joystick.xPosition);
    ledStatus->yPosition = analogRead(joystick.yPosition);

    while(1)
    {
        // Possible timing error, adding delay(5)
        delay(3);

        ledStatus->xPosition = analogRead(joystick.xPosition);
        ledStatus->yPosition = analogRead(joystick.yPosition);

        // shift right if over the hysteresis, left if under the hysteresis
        if(ledStatus->xPosition > ledStatus->PosUp)
        {
            if(ledStatus->red == 0xFF && (ledStatus->green >= 0x00 && ledStatus->green < 0xFF) && ledStatus->blue == 0x00) // red to yellow
            {
                ledStatus->green++;
            } 
            else if((ledStatus->red <= 0xFF && ledStatus->red > 0x00) && ledStatus->green == 0xFF && ledStatus->blue == 0x00) // yellow to green
            {
                ledStatus->red--;
            }
            else if(ledStatus->red == 0x00 && ledStatus->green == 0xFF && (ledStatus->blue < 0xFF && ledStatus->blue >= 0x00)) // green to cyan
            {
                ledStatus->blue++;
            }
            else if(ledStatus->red == 0x00 && (ledStatus->green <= 0xFF && ledStatus->green > 0x00) && ledStatus->blue == 0xFF) // cyan to blue
            {
                ledStatus->green--;
            }
            else if((ledStatus->red < 0xFF && ledStatus->red >= 0x00) && ledStatus->green == 0x00 && ledStatus->blue == 0xFF) // blue to purple
            {
                ledStatus->red++;
            }
            else if(ledStatus->red == 0xFF && ledStatus->green == 0x00 && (ledStatus->blue <= 0xFF && ledStatus->blue > 0x00)) // purple to red
            {
                ledStatus->blue--;
            }
        }
        else if(ledStatus->xPosition < ledStatus->PosDown)
        {
            if(ledStatus->red == 0xFF && ledStatus->green == 0x00 && (ledStatus->blue < 0xFF && ledStatus->blue >= 0x00)) // red to purple
            {
                ledStatus->blue++;
            } 
            else if((ledStatus->red <= 0xFF && ledStatus->red > 0x00) && ledStatus->green == 0x00 && ledStatus->blue == 0xFF) // purple to blue
            {
                ledStatus->red--;
            }
            else if(ledStatus->red == 0x00 && (ledStatus->green < 0xFF && ledStatus->green >= 0x00) && ledStatus->blue == 0xFF) // blue to cyan
            {
                ledStatus->green++;
            }
            else if(ledStatus->red == 0x00 && ledStatus->green == 0xFF && (ledStatus->blue <= 0xFF && ledStatus->blue > 0x00)) // cyan to green
            {
                ledStatus->blue--;
            }
            else if((ledStatus->red < 0xFF && ledStatus->red >= 0x00) && ledStatus->green == 0xFF && ledStatus->blue == 0x00) // green to yellow
            {
                ledStatus->red++;
            }
            else if(ledStatus->red == 0xFF && (ledStatus->green > 0x00 && ledStatus->green <= 0xFF) && ledStatus->blue == 0x00) // yellow to red
            {
                ledStatus->green--;
            }
        }
    }
}

#endif