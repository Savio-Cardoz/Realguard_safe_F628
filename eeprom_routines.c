#include <xc.h>
#include "eeprom_routines.h"

void eepromWriteCode(unsigned char eepromWriteAddr, unsigned char codeLenght, char *codeBuffer)
{
    eeprom_write(eepromWriteAddr, codeLenght);    // Store no. of chars in code
    for(unsigned char i=0; i <= codeLenght; i++)
    {
        eepromWriteAddr++;
        eeprom_write(eepromWriteAddr, *(codeBuffer + i));
    }
}

char* eepromReadCode(unsigned char codeNo)
{
    static unsigned char eepromReadAddr;
    unsigned char codeLenght = 0, codeCount = 0;
    
    do{
        eepromReadAddr += codeLenght;
        codeLenght = eeprom_read(eepromReadAddr);
        codeCount++;
    }
    while(codeCount < codeNo);
    
    for(unsigned char i=0; i <= (codeLenght - 2); i++)
    {
        eepromReadAddr++;
        eepromCodeBuffer[i] = eeprom_read(eepromReadAddr);
    }
    return eepromCodeBuffer;
}
