/*
 * charData.h
 * 
 * Defines what the character data structure is.
 * 
 * Contains a mutex lock, an update flag, and a buffer
 * 
 * Author: Jack Justice - 12/20/2020
 */

#ifndef CHARDATA_H
#define CHARDATA_H

#include <TeensyThreads.h>

typedef struct CHAR_DATA
{
    std::mutex UART_lock;
    bool serialUpdate = false; // False == don't update; True == update
    static const int serialBufferSize = 32;
    char serialBuffer[serialBufferSize + 1] = "";
} charData;

#endif