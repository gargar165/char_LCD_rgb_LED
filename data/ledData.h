/*
 * ledData.h
 * 
 * Defines what the LED data structure is.
 * 
 * Contains some constexpr, some positions to hold a 10-bit 
 *   value, and four numbers to determine the LED's color.
 * 
 * Author: Jack Justice - 12/20/2020
 */
#ifndef LEDDATA_H
#define LEDDATA_H

#include <TeensyThreads.h>

typedef struct LED_DATA
{
    int xPosition = 0.0;
    int yPosition = 0.0;
    constexpr static const int PosDown = 200;
    constexpr static const int PosUp = 800;

    uint8_t red   = 0xFF;
    uint8_t green = 0x00;
    uint8_t blue  = 0x00;
    uint8_t brightness = 0xFF;
} ledData;

#endif