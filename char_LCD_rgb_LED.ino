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
#include <SdFat.h>

// User defines
#define DEBUG

// Data structures for the threads to use
#include "data\charData.h"
#include "data\ledData.h"
#include "data\networkData.h"
#include "data\storageData.h"

// Functions that are used by threads
#include "threaded_functions\joystickCode.h"
#include "threaded_functions\ledCode.h"
#include "threaded_functions\lcdCode.h"
#include "threaded_functions\serialCode.h"

// Objects for LED and character LCD/UART
charData    messageData;
ledData     ledStatus;
networkData localnetwork;
Storage_t   sd_card;

// Sets up I/O, prints message, then attaches main threads
void setup()
{
    // Could multithread start-up here with a malloc'd int
    setupLCD();
    setupLED();
    setupUART();
    setupStorage(&sd_card);
    readyLCD(); // Then have all the once the threads are done, free the int and run this
    testStorage(&sd_card);

    Serial.println(F("System --- System on, listening to UART!"));

    threads.addThread(readUART, &messageData);
    threads.addThread(printLCD, &messageData);
    threads.addThread(joystickListener, &ledStatus);
    threads.addThread(updateLED, &ledStatus);
}

// Do nothing unless if DEBUG is defined
void loop()
{
#ifdef DEBUG
    // What should I have here if I were to have debug statements..?
#endif
}
