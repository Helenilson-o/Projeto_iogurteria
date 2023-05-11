#ifndef _EEPROM_H
#define _EEPROM_H

// Rotina de escrita um byte na EEPROM
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

// Rotina de leitura de um byte da EEPROM
unsigned char EEPROM_read(unsigned int uiAddress);

#endif