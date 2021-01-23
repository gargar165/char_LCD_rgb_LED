#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <NativeEthernet.h>

class networkData
{
private:
    uint8_t myMAC[6]; // Holds MAC address

    void topTwoBytes();
    void bottomFourBytes();

public:
    networkData();
    ~networkData();

    void displayMAC();
};

networkData::networkData()
{
    // Pulled from vjmuzik's post
    // https://forum.pjrc.com/threads/62932-Teensy-4-1-MAC-Address
    topTwoBytes();
    bottomFourBytes();

#ifdef DEBUG
    displayMAC();
#endif
}

networkData::~networkData()
{
    // Scramble the data
    for(uint8_t i = 0; i < 6; i++)
    {
        this->myMAC[i] = 0xFF;
    }
    delete this;
}

void networkData::topTwoBytes()
{
#ifdef DEBUG
    Serial.print(F("Debug --- Hardware MAC Address: "));
#endif
    for(uint8_t i = 0; i < 2; i++) 
    {
        this->myMAC[i] = (HW_OCOTP_MAC1 >> ((1 - i) * 8)) & 0xFF;

        // Debug print if debug is defined
#ifdef DEBUG
        if(this->myMAC[i] < 0x10)
        {
            Serial.print(0, DEC);
        }
        Serial.print(this->myMAC[i], HEX);
        Serial.print(F(" "));
#endif
    }
};

void networkData::bottomFourBytes()
{
    for(uint8_t i = 0; i < 4; i++) 
    {
        this->myMAC[i + 2] = (HW_OCOTP_MAC0 >> ((3 - i) * 8)) & 0xFF;

        // Debug print if debug is defined
#ifdef DEBUG
        if(this->myMAC[i + 2] < 0x10)
        {
            Serial.print(0, DEC);
        }
        Serial.print(this->myMAC[i + 2], HEX);
        Serial.print(F(" "));
#endif
        }  
#ifdef DEBUG
        Serial.println();
#endif
};

void networkData::displayMAC()
{
    Serial.print(F("System --- Software MAC Address: "));
    for(uint8_t i = 0; i < 6; i++)
    {
        if(this->myMAC[i] < 0x10)
        {
            Serial.print(0, DEC);
        }
        Serial.print(this->myMAC[i], HEX);
        Serial.print(F(" "));
    }
    Serial.println();
    return;
}

#endif