#include "i2c.h"
#include <avr/io.h>
#define F_CPU 16000000UL
// Incializa a interface I2C com taxa: bit_rate(kHz)
void I2C_Inic(uint8_t bit_rate){
	uint16_t f_scl;
	TWSR|=1; // Prescaler de 4
	f_scl = bit_rate*1000;
	TWBR=((F_CPU/f_scl)-16)/2; // Carrega TWBR com cte p/ bit rate
	TWCR |= (1<<TWINT)|(1<<TWEN);// Habilita o TWI e a interrup.
}
// Envia Start Condition, espera por TWINT e cd.de status Start
unsigned char I2C_Start(){
	TWCR=TWI_START; // Envia cond. de START
	while(!TWI_RDY); // Espera resposta TWINT pelo HW
	if(TWI_STATUS!=START_ANSW) // Verifica cod. TWSR c/ mascara F8
	return 1; // Caso erro de START retorna 1
	return 0; // Start enviado corretamente
}
// Envia Endereo do Slave
unsigned char I2C_WrAddr(uint8_t addr){
	TWDR=addr; // Carrega SLA_W em TWDR
	TWCR=TWI_SEND; // Limpa TWINT e seta TWEN em TWICR
	while(!TWI_RDY); // Espera resposta TWINT pelo HW
	if(TWI_STATUS!=MT_SLA_ACK) // Verifica cod. TWSR c/ mascara F8
	return 1; // Erro escrita end. retorna 1
	return 0; // ACK recebido corretamente
}
// Envia Dado p/ o Slave, espera por TWINT e cd.de status Start
unsigned char I2C_SendData(uint8_t dado){
	TWDR=dado; // Carrega SLA_W em TWDR
	TWCR=TWI_SEND; // Limpa TWINT e seta TWEN em TWICR
	while(!TWI_RDY); // Espera resposta TWINT pelo HW
	if(TWI_STATUS!=MT_DATA_ACK) // Verifica cod. TWSR c/ mscara F8
	return 1; // Erro de envio de dado retorna 1


	return 0; // Dado enviado corretamente
}
// Envia condio de STOP
void I2C_Stop(){
	TWCR=TWI_STOP; // Envia STOP
	while(TWCR & (1<<TWSTO)); // Espera envio de STOP
}
// Leitura dado c/ retorno NACK (Data Package Last Read)
unsigned char I2C_GetNACK(void){
	TWCR = TWI_NACK; // Envia NACK indicando Last Byte
	while(!TWI_RDY); // Espera pela cond. READY
	return TWDR; // Retorna dado no reg de dados
}
// Escreve dado em registro de dispositivo TWI
void I2C_WrReg(uint8_t DevAddr,uint8_t DevReg,uint8_t data){
	I2C_Start(); // Envia cond. de START
	I2C_WrAddr(DevAddr+I2C_WR); // Envia end. do dispositivo
	I2C_SendData(DevReg); // Envia end. do registro
	I2C_SendData(data); // Envia dado para o registro
	I2C_Stop(); // Envia cond. de STOP
}
// L dado de registro de dispositivo TWI
unsigned char I2C_RdReg(uint8_t DevAddr,uint8_t DevReg){
	unsigned char data=0;
	I2C_Start(); // Envia cond. de START
	I2C_WrAddr(DevAddr); // Envia End. do Dispositivo
	I2C_SendData(DevReg); // Envia End. do Registro
	I2C_Start(); // Envia cond. de START
	I2C_WrAddr(DevAddr+I2C_RD); // Envia ender. Dispositivo+READ
	data=I2C_GetNACK(); // Recebe byte do Reg. do Slave
	I2C_Stop(); // Envia cond. de STOP
	return data; // Retorna dado lido do Slave
}