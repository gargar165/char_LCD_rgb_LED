/*
 * char_LCD_rgb_LED.ino
 * 
 * Main file of project.
 * 
 * Contains usual setup functions and loop function.
 * Inside the loop function is a debug_print function,
 *   but it doesn't need to be enabled unless necessary.
 * 
 * Author: Jack Justice - 12/20/2020
 */

// System libraries
#include <TeensyThreads.h>

// User defines
#define DEBUG

// User headers
#include "charData.h"
#include "ledData.h"
#include "joystickCode.h"
#include "ledCode.h"
#include "lcdCode.h"
#include "serialCode.h"

// Objects for LED and character LCD/UART
charData messageData;
ledData  ledStatus;

// Debug that reads from UART buffer in messageData every half second
#ifdef DEBUG
#include <elapsedMillis.h>
elapsedMillis counter;

void debugPrint()
{
    if(messageData.serialUpdate && (counter > 500))
    {
        Serial.print(F(">> "));
        Serial.println(messageData.serialBuffer);

        counter = 0;
    }
}
#endif

// Sets up I/O, prints message, then attaches main threads
void setup()
{
    // Could multithread start-up here with a malloc'd int
    setupLCD();
    setupLED();
    setupUART();
    readyLCD(); // Then have all the once the threads are done, free the int and run this

    Serial.println(F("System on, listening to UART!"));
    Serial.println(F("WARNING: WILL ONLY WORK IN ARDUINO SERIAL CONSOLE"));

    threads.addThread(readUART, &messageData);
    threads.addThread(printLCD, &messageData);
    threads.addThread(joystickListener, &ledStatus);
    threads.addThread(updateLED, &ledStatus);
}

// Do nothing unless if DEBUG is defined
void loop()
{
#ifdef DEBUG
    debugPrint();
#endif
}
