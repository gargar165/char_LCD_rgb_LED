#ifndef STORAGEDATA_H
#define STORAGEDATA_H

#include <SdFat.h>

typedef struct STORAGE
{
    SdFat32 sd;   // Hardware access to the SD
    File32  file; // File handler

    // 1 == FAT16/32; 2 == exFAT; 3 == Both!
    constexpr static const int sdFatType = 1;

    // True == DMA; False == FIFO
    constexpr static const bool dmaEnabled = true;
} Storage_t;

void setupStorage(Storage_t *sd_card)
{
    // turn on dma if enabled
    if(sd_card->dmaEnabled)
    {
        if(!sd_card->sd.begin(SdioConfig(DMA_SDIO))) Serial.println(F("System --- ***WARNING***: DMA ON SDIO SETUP FAILED. CONTINUING."));
        else Serial.println(F("System --- DMA SDIO successfully started."));
    }
    else
    {
        if(!sd_card->sd.begin(SdioConfig(FIFO_SDIO))) Serial.println(F("System --- ***WARNING***: FIFO ON SDIO SETUP FAILED. CONTINUING."));
        else Serial.println(F("System --- FIFO SDIO successfully started."));
    }
    return;
}

void testStorage(void *data)
{
    // Save the address of the structure to a pointer
    Storage_t *sd_card = (Storage_t *) data;
    char filename[] = "test.bin\0";
    sd_card->file = sd_card->sd.open(filename, FILE_WRITE);

    if(!sd_card->sd.exists(filename))
    {
        Serial.print(F("System --- ***ERROR***: \""));
        Serial.print(filename);
        Serial.println(F("\" cannot be opened."));
    }
    else
    {
        Serial.print(F("System --- \""));
        Serial.print(filename);
        Serial.println(F("\" was successfully created."));
    }

    sd_card->file.write("just some test data\n");
    sd_card->file.close();

    char current_directory[] = "\\"; 
    Serial.print(F("File Directory of \""));
    Serial.print(current_directory);
    Serial.println("\"");
    sd_card->sd.ls("/", LS_R);
    return;
}

#endif