/*
 * ledCode.h
 * 
 * Updates the buffer by listening to the UART port. Flips a flag,
 *   creates a lock via RAII, updates the buffer, and unlocks the
 *   lock using lock_guard's deconstructor.
 * 
 * Author: Jack Justice - 12/20/2020
 */

#ifndef SERIALCODE_H
#define SERIALCODE_H

#include <stdint.h>
#include <TeensyThreads.h>

void setupUART()
{
    while(!Serial) {}
    Serial.begin(115200);
}

void readUART(void *data)
{
    // Save the address of the structure to a pointer
    charData *messageData = (charData *) data;
    
    // counter that counts the number of characters used in the buffer but caps at 31
    static int count = 0;

    // Print initial ">> "
    Serial.print(F(">> "));

    while(1)
    {   
        // Needed to solve timing bug regarding mutex locks
        delay(1);
        
        // Check if text is available
        if(Serial.available())
        {
            // lock mutex using RAII to release the lock once out of the if scope
            std::lock_guard<std::mutex> lock(messageData->UART_lock);

            Serial.print((char)Serial.peek());

            if(Serial.peek() != '\r' && Serial.peek() != '\n') // Check for either carriage return or new line
            {
                if(count < messageData->serialBufferSize)
                {
                    messageData->serialBuffer[count] = Serial.read();
                    count++;
                }
                else Serial.read();
            }
            else
            {
                // Dump the '\r' and '\n'
                Serial.read();

                // change uart flag to true
                messageData->serialUpdate = true;

                // Null-terminate and flush the UART
                if(count < messageData->serialBufferSize) count++;

                messageData->serialBuffer[count] = '\0';
                Serial.flush();
                count = 0;

                // Print new line then another ">> "
                Serial.println();
                Serial.print(F(">> "));
            }
        }
    }
}

#endif