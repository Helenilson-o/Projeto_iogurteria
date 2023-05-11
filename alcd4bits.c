#include "alcd4bits.h"

// Inicializa o LCD em 4-bits
void lcd4bits_inic(void)
{
	#if(!NIB_LSB_MSB)
	DATA_DD |= 0x0F; // Px0..3 pinos de saida
	#else
	DATA_DD |= 0xF0; // Px4..7 pinos de saida
	#endif
	CNTR_DD |= (1<<EN_LCD)|(1<<RS_LCD); // EN e RS pinos saida
	// UCSR0B=0; // Arduino: desabilitar UART p/ PortD
	_delay_ms(15); // Delay exigido
	RS_CMD(); // Seleciona registro de comando
	EN_LOW(); // Prepara sinal de Enable
	_delay_ms(20); // Espera um tempo para Vcc atingir 4,5V
	#if(!NIB_LSB_MSB)
	DATA_LCD = (DATA_LCD & 0xF0)|INIC; // Px0..3
	#else
	DATA_LCD = (DATA_LCD & 0x0F)|INIC<<4; // Px4..7
	#endif
	EN(); // Gera pulso de Enable
	_delay_ms(5); // Delay exigido
	EN(); // Gera pulso de Enable
	_delay_us(200); // Delay exigido
	EN(); // Gera pulso de Enable
	#if(!NIB_LSB_MSB)
	DATA_LCD = (DATA_LCD & 0xF0)|MODE; // Px0..3
	#else
	DATA_LCD = (DATA_LCD & 0x0F)|MODE<<4; // Px4..7
	#endif
	EN();
	lcd_cmd(0x28); // Interface 4 bits 2 linhas
	lcd_cmd(0x08); // Desliga LCD
	lcd_cmd(0x01); // Limpa LCD
	lcd_cmd(0x0c); // LCD ON, Cursor inativo, sem piscar
	lcd_cmd(0x80); // Cursor na linha 0 coluna 0
}

// Limpa o LCD
void lcd_clear()
{
	unsigned char dado;
	dado=CLR_LCD; // Carrega comando de limpar LCD
	RS_CMD(); // Seleciona registro de comando
	nibble2port(dado); // Envia nibble sup. do dado primeiro
	EN(); // Gera pulso de Enable
	dado<<=4; // Prepara nibble inf. do dado p/ envio
	nibble2port(dado); // Envia nibble inf. do dado
	EN(); // Gera pulso de Enable
	_delay_ms(2); // Delay de 2 ms se o envio de comando
}
// Posiciona o cursor do LCD em coluna,linha
void lcd_gotoxy(unsigned char col,unsigned char lin)
{
	unsigned char base,dado;
	if(lin==0 || lin==1){ // Considera-se LCD de linhas linhas
		switch(lin){
			case 0: base=0x80; // Linha 0: End. base 0x80
			break;
			case 1: base=0xC0; // Linha 1: End. base 0xC0
			break;
		default: base=0;}}

		else
		return; // Se parametro invalido retorna
		if(col>15) return; // Se parametro invalido retorna
		dado = base+col; // End. base + end. coluna
		lcd_cmd(dado); // Envia comando
		_delay_ms(2); // Delay de 2 ms se o envio de comando
	}
	// Escreve string no LCD
	void lcd_puts(unsigned char *s)
	{
		unsigned char i;
		for(i=0;s[i]!='\0';i++) // Varre string toda
		lcd_putchar(s[i]); // Envia caracteres da string
	}

	// Escreve caracter no LCD
	void lcd_putchar(unsigned char dado)
	{
		RS_DAT(); // Seleciona registro de dados
		nibble2port(dado); // Envia nibble sup. do dado primeiro
		EN(); // Gera pulso de Enable
		dado<<=4; // Prepara nibble inf. do dado p/ envio
		nibble2port(dado);; // Envia nibble inf. do dado
		EN(); // Gera pulso de Enable
	}
	// Escreve comando no LCD
	void lcd_cmd(unsigned char dado)
	{
		RS_CMD(); // Seleciona registro de comando
		nibble2port(dado); // Envia nibble sup. do dado primeiro
		EN(); // Gera pulso de Enable
		dado<<=4; // Prepara nibble inf. do dado p/ envio
		nibble2port(dado); // Envia nibble inf. do dado
		EN(); // Gera pulso de Enable
		_delay_ms(2); // Delay de 2 ms se o envio de comando
	}
	// Envio de um nibble para o LCD
	void nibble2port(unsigned char dado)
	{
		#if(!NIB_LSB_MSB)
		DATA_LCD = (DATA_LCD & 0xF0)|(dado>>4); // Px0..3
		#else
		DATA_LCD = (DATA_LCD & 0x0F)|(dado); // Px4..7
		#endif
	}