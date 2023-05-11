#ifndef _DS1307_H
#define _DS1307_H
#include <stdint.h>
// Defs do RTC DS1307
#define AddrDS1307 0xD0 // End. DS1307 para leitura
#define SEGS_REG 0x00 // End. Reg. Segundos
#define MINS_REG 0x01 // End. Reg. Minutos
#define HORA_REG 0x02 // End. Reg. Horas
#define SEM_REG 0x03 // End. Reg. Dia da Semana
#define DIA_REG 0x04 // End. Reg. Dia
#define MES_REG 0x05 // End. Reg. Mes
#define ANO_REG 0x06 // End. Reg. Ano
#define CNTRL_REG 0x07 // End. Reg. Controle
#define RAM_BEGIN 0x08 // End. inicial RAM (56 bytes)
#define RAM_END 0x3F // End. final RAM
// Inicializa DS1307
void DS1307_Inic();
// Retorna horas, minutos, segundos em BCD
void DS1307_GetTime(uint8_t *hora,uint8_t *mins,uint8_t *segs);
// Retorna mes, dia, ano em BCD
void DS1307_GetDate(uint8_t *dia,uint8_t *mes,uint8_t *ano);
// Ajusta horas, minutos, segundos
void DS1307_SetTime(uint8_t hora,uint8_t mins,uint8_t segs);
// Ajusta mes, dia, ano
void DS1307_SetDate(uint8_t dia,uint8_t mes,uint8_t ano);
#endif