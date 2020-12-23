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

    while(1)
    {   
        // Needed to solve timing bug regarding mutex locks
        delay(1);
        
        // Check if text is available
        if(Serial.available())
        {
            // lock mutex using RAII to release the lock once out of the if scope
            std::lock_guard<std::mutex> lock(messageData->UART_lock);

            // change uart flag to true
            messageData->serialUpdate = true;
            
            // Set a counter to 0
            int count = 0;

            // Fill the buffer until no more chars are available or if we are about to overflow
            while(Serial.available() && (count < messageData->serialBufferSize))
            {
                messageData->serialBuffer[count] = Serial.read();
                count++;
            }

            // Null-terminate and flush the UART
            messageData->serialBuffer[count] = '\0';
            Serial.flush();
        }
    }
}

#endif