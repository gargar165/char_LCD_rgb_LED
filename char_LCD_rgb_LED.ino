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
#include <NativeEthernet.h>

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
uint8_t  myMAC[6];

// Pulled from vjmuzik's post
// https://forum.pjrc.com/threads/62932-Teensy-4-1-MAC-Address
void teensyMAC(uint8_t *mac)
{
    for(uint8_t i = 0; i < 2; i++) mac[i] = (HW_OCOTP_MAC1 >> ((1 - i) * 8)) & 0xFF;
    for(uint8_t i = 0; i < 4; i++) mac[i + 2] = (HW_OCOTP_MAC0 >> ((3 - i) * 8)) & 0xFF;

#ifdef DEBUG
    Serial.print(F("MAC Address: "));
    for(uint8_t i = 0; i < 6; i++)
    {
        Serial.print(mac[i], HEX);
        Serial.print(F(" "));
    }
    Serial.println();
#endif
}

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

    teensyMAC(myMAC);
}

// Do nothing unless if DEBUG is defined
void loop()
{
#ifdef DEBUG
    // What should I have here if I were to have debug statements..?
#endif
}
