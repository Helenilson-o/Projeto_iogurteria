#include "eeprom.h"

#define F_CPU 16000000UL
#include <avr/io.h>

// Rotina de escrita um byte na EEPROM
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	// Espera pela finalização da última escrita
	while(EECR & (1<<EEPE));
	// Carrega registros de dados e endereços da EEPROM
	EEAR = uiAddress;
	EEDR = ucData;
	// Seta bit EEMPE para permitir a escrita na EEPROM
	EECR |= (1<<EEMPE);
	// Inicia escrita na EEPROM via bit EEPE=1
	EECR |= (1<<EEPE);
}

// Rotina de leitura de um byte da EEPROM
unsigned char EEPROM_read(unsigned int uiAddress)
{
	// Espera pela finalização da última escrita
	while(EECR & (1<<EEPE));
	// Carrega registro de endereço da EEPROM
	EEAR = uiAddress;
	// Inicia leitura na EEPROM via EERE=1
	EECR |= (1<<EERE);
	// Retorna dada lido na EEPROM
	return EEDR;
}