#ifndef _I2C_H
#define _I2C_H
#include <inttypes.h>
// Macros p/ Registros de Controle de Status
#define TWI_START (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
#define TWI_STOP (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)
#define TWI_NACK (1<<TWINT)|(1<<TWEN)
#define TWI_ACK (1<<TWINT)|(1<<TWEN)|(1<<TWEA)
#define TWI_SEND (1<<TWINT)|(1<<TWEN)
#define TWI_RDY (TWCR & (1<<TWINT))
#define TWI_STATUS (TWSR & 0xF8)
// Cdigos de retorno do Reg. de Status Modo Master Transmitter
#define START_ANSW 0x08 // Start condition transmitido
#define TW_REP_START 0x10 // Repeated Start Cond. transmitido
#define MT_SLA_ACK 0x18 // SLA+W transmitido, ACK recebido
#define MT_SLA_NACK 0x20 // SLA+W transmitido, NACK recebido
#define MT_DATA_ACK 0x28 // Dado transmitido, ACK recebido
#define MT_DATA_NACK 0x30 // Dado transmitido, NACK recebido
#define MT_ARB_LOST 0x38 // Arbitr. Lost em SLA+W ou dado
// Cdigos de retorno do Reg. de Status Modo Master Receiver
#define MR_ARB_LOST 0x38 // Arbitr. Lost in SLA+R or NACK
#define MR_SLA_ACK 0x40 // SLA+R transmitido, ACK recebido
#define MR_SLA_NACK 0x48 // SLA+R transmitido, NACK recebido
#define MR_DATA_ACK 0x50 // Dado recebido, ACK retornado
// Cdigos de retorno do Reg. de Status Modo Slave Transmitter
#define ST_SLA_ACK 0xA8 // SLA+R recebido, ACK retornado
// arbitration lost in SLA+RW, SLA+R recebido, ACK retornado
#define ST_ARB_LOST_SLA_ACK 0xB0
#define ST_DATA_ACK 0xB8 // Dado transmitido, ACK recebido
#define ST_DATA_NACK 0xC0 // Dado transmitido, NACK recebido
// Last Data Byte transmitido, e ACK recebido
#define ST_LAST_DATA 0xC8
// Cdigos de retorno do Reg. de Status Modo Slave Receiver
#define SR_SLA_ACK 0x60 // SLA+W recebido, ACK retornado
// Arbitration Lost em SLA+RW, SLA+W recebido, ACK retornado
#define SR_ARB_LOST_SLA_ACK 0x68
#define SR_GCALL_ACK 0x70 // General Call recebido, ACK ret.
// arbitration lost in SLA+RW, General Call recebido, ACK ret.
#define SR_ARB_LOST_GCALL_ACK 0x78
#define SR_DATA_ACK 0x80 // Dado recebido, ACK retornado
#define SR_DATA_NACK 0x88 // Dado recebido, NACK retornado
// General Call Data recebido, e ACK retornado
#define SR_GCALL_DATA_ACK 0x90
// General Call Data recebido, e NACK retornado
#define SR_GCALL_DATA_NACK 0x98
// Stop/Repeated Start Condition recebido enquanto selecionado
#define SR_STOP 0xA0
// Constantes Simblicas
#define I2C_RD 1
#define I2C_WR 0
// Incializa a interface I2C com taxa: bit_rate(kHz)
void I2C_Inic(uint8_t bit_rate);
// Envia condio de START
unsigned char I2C_Start();
// Envia Endereo do Slave
unsigned char I2C_WrAddr(uint8_t addr);
// Envia Dado p/ o Slave
unsigned char I2C_SendData(uint8_t dado);
// Envia condio de STOP
void I2C_Stop();
// Leitura do dado com retorno de NACK (Data Package Last Read)
unsigned char I2C_GetNACK(void);
// Escreve dado em registro de dispositivo I2C
void I2C_WrReg(uint8_t DevAddr,uint8_t DevReg,uint8_t data);
// L dado de registro de dispositivo I2C
unsigned char I2C_RdReg(uint8_t DevAddr,uint8_t DevReg);
#endif