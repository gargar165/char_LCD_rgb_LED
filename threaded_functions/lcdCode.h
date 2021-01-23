/*
 * lcdCode.h
 * 
 * Contains pin structure for wiring and setup. Updates
 *   the screen when the update flag is raised.
 * 
 * Author: Jack Justice - 12/20/2020
 */

#ifndef LCDCODE_H
#define LCDCODE_H

#include <TeensyThreads.h>
#include <LiquidCrystal.h>

typedef struct SCREENLCD
{
    static const int RS      = 26;
    static const int ENABLE  = 28;
    static const int D4      = 29;
    static const int D5      = 30;
    static const int D6      = 31;
    static const int D7      = 32;
    static const int COLUMNS = 16;
    static const int ROWS    = 2;
} screenLCD;
screenLCD screen;

LiquidCrystal lcd(screen.RS,
                  screen.ENABLE,
                  screen.D4,
                  screen.D5,
                  screen.D6,
                  screen.D7);

void setupLCD()
{
    lcd.begin(screen.COLUMNS, screen.ROWS);
    lcd.setCursor(0, 0);
    lcd.print("Open the Serial");
    lcd.setCursor(0, 1);
    lcd.print("Console!!");
}

void readyLCD()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ready.");
}

void printLCD(void *data)
{
    // Save the address of the structure to a pointer
    charData *messageData = (charData *) data;

    lcd.setCursor(0, 0);

    while(1)
    {
        // Needed to solve timing bug regarding mutex locks
        delay(1);

        if(messageData->serialUpdate)
        {
            lcd.clear();

            // lock down the flag, print to LCD, release flag by leaving the scope of the if statement
            std::lock_guard<std::mutex> lock(messageData->UART_lock);
            for(int i = 0; (i < messageData->serialBufferSize) && messageData->serialBuffer[i] != '\0'; i++)
            {
                if((i / (messageData->serialBufferSize / 2)) == 0)
                {
                    lcd.setCursor(i % (messageData->serialBufferSize / 2), 0);
                }
                else
                {
                    lcd.setCursor(i % (messageData->serialBufferSize / 2), 2);
                }
                
                lcd.print(messageData->serialBuffer[i]);
            }
            messageData->serialUpdate = false;
            
        }
    }
}

#endif