#include "ds1307.h"
#include "i2c.h"
#include <stdint.h>

void DS1307_Inic(){
	I2C_WrReg(AddrDS1307,CNTRL_REG,0x10);
}
// Retorna horas, minutos, segundos em BCD
void DS1307_GetTime(uint8_t *hora,uint8_t *mins,uint8_t *segs){
	*hora=I2C_RdReg(AddrDS1307,HORA_REG); // Leitura das horas
	*mins=I2C_RdReg(AddrDS1307,MINS_REG); // Leitura dos minutos
	*segs=I2C_RdReg(AddrDS1307,SEGS_REG); // Leitura dos segundos
	if(*hora & 0x40) // Modo de 12hr:
	*hora &= 0x1F; // Usa-se os 5 bits LSBs (pm bit=temp & 0x20)
	else
	*hora &= 0x3F; // Modo 24hr: usa-se 6 bits LSBs
}
// Retorna mes, dia, ano em BCD
void DS1307_GetDate(uint8_t *dia,uint8_t *mes,uint8_t *ano) {
	*dia=I2C_RdReg(AddrDS1307,DIA_REG); // Leitura do dia
	*mes=I2C_RdReg(AddrDS1307,MES_REG); // Leitura do ms
	*ano=I2C_RdReg(AddrDS1307,ANO_REG); // Leitura do ano
}
// Ajusta horas, minutos, segundos
void DS1307_SetTime(uint8_t hora,uint8_t mins,uint8_t segs){
	// Ajusta as horas
	I2C_WrReg(AddrDS1307,HORA_REG,hora);
	// Ajusta os minutos
	I2C_WrReg(AddrDS1307,MINS_REG,mins);
	// Ajusta os segundos
	I2C_WrReg(AddrDS1307,SEGS_REG,segs);
}
// Ajusta mes, dia, ano
void DS1307_SetDate(uint8_t dia,uint8_t mes,uint8_t ano){
	// Ajusta dia
	I2C_WrReg(AddrDS1307,DIA_REG,dia);
	// Ajusta mes
	I2C_WrReg(AddrDS1307,MES_REG,mes);
	// Ajusta ano
	I2C_WrReg(AddrDS1307,ANO_REG,ano);
}