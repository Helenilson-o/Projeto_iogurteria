/*
 * Sistema_yogurteria.c
 *
 * Created: 09/05/2023 08:49:46
 * Author : HeleGod
 */ 

#define F_CPU 16000000UL
#define KEY_MAX 15

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "keypad3x4.h"
#include "alcd4bits.h"
#include "ds1307.h"
#include "timers.h"

// Function prototypes
unsigned char bcd2dec(unsigned char dado);
void converteDados();


void inic(){
	I2C_Inic();
	DS1307_Inic();
	lcd4bits_inic();
	inic_tc1_1s();
	inic_timer0();

}

// Converte BCD para decimal
unsigned char bcd2dec(unsigned char dado){
	uint8_t unidades,dezenas,valor;
	unidades = dado & 0x0f;
	dezenas = ((dado & 0xf0)>>4)*10;
	valor=unidades+dezenas;
	return valor;
}





/*
Esta função verifica se o caractere c está no intervalo válido de '0' a '9'.
Se estiver, o valor BCD correspondente é obtido subtraindo o valor ASCII de '0' do caractere c.
Caso contrário, ou seja, se o caractere estiver fora do intervalo válido, a função retorna 0 para
indicar um valor inválido.

Por exemplo, o caractere '0' tem um valor ASCII de 48, o caractere '1' tem um valor ASCII de 49 e assim por diante.

Ao subtrair o valor ASCII de '0' de um caractere numérico, como '5' - '0'
obtemos o valor numérico correspondente, neste caso, 5

*/
unsigned char char2bcd(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
		} else {
		// Valor inválido
		return 0;
	}
}

unsigned char str2bcd(const char* str) {
	unsigned char dezenas = char2bcd(str[0]) << 4;
	unsigned char unidades = char2bcd(str[1]);

	return dezenas | unidades;
}

// Converte todos dados lidos do RTC em BCD p/ decimal
void converteDados(){
	dia=bcd2dec(dia);
	mes=bcd2dec(mes);
	ano=bcd2dec(ano);
	hora=bcd2dec(hora);
	mins=bcd2dec(mins);
	segs=bcd2dec(segs);
}


void ajusta_rtc() {
	uint8_t i = 0;
	uint8_t key = 0;
	uint8_t str[2];
	TCCR0B = TC0_RUN;

	do{
		lcd_clear();
		lcd_puts("Hora(HH):");
		i = 0;
		while (i < 2) {
			key = read_keypad();
			//verifica se algo foi digitado e se está entre 0 e 9
			if (key != '\0' && key >= '0' && key <= '9') {
				conta_5s = 35;
				str[i++] = key;
				lcd_putchar(key);
			}
			if(!timeout5s){
				timeout5s = 1;
				TCCR0B = TC0_STOP;
				return;
			}
		}
		
		
		hora = str2bcd(str);
		
	}while(bcd2dec(hora) > 23);
//----------------------------------------------------------------------	
	do{
		lcd_clear();
		lcd_puts("Min(MM):");
		i = 0;
		while (i < 2) {
			key = read_keypad();
			//verifica se algo foi digitado e se está entre 0 e 9
			if (key != '\0' && key >= '0' && key <= '9') {
				conta_5s = 35;
				str[i++] = key;
				lcd_putchar(key);
			}
			if(!timeout5s){
				timeout5s = 1;
				TCCR0B = TC0_STOP;
				return;
			}
		}
		
		mins = str2bcd(str);
		
	}while(bcd2dec(mins) > 59);
//----------------------------------------------------------------------
	
	do{
		lcd_clear();
		lcd_puts("Dia(DD):");
		i = 0;
		while (i < 2) {
			key = read_keypad();
			//verifica se algo foi digitado e se está entre 0 e 9
			if (key != '\0' && key >= '0' && key <= '9') {
				conta_5s = 35;
				str[i++] = key;
				lcd_putchar(key);
			}
			if(!timeout5s){
				timeout5s = 1;
				TCCR0B = TC0_STOP;
				return;
			}
		}
		
		dia = str2bcd(str);
		
	}while(bcd2dec(dia) > 31 || bcd2dec(dia) < 1);
//----------------------------------------------------------------------
	do{
		lcd_clear();
		lcd_puts("Mes(MM):");
		i = 0;
		while (i < 2) {
			key = read_keypad();
			//verifica se algo foi digitado e se está entre 0 e 9
			if (key != '\0' && key >= '0' && key <= '9') {
				conta_5s = 35;
				str[i++] = key;
				lcd_putchar(key);
			}
			if(!timeout5s){
				timeout5s = 1;
				TCCR0B = TC0_STOP;
				return;
			}
		}
		mes = str2bcd(str);
		
	}while(bcd2dec(mes) > 12 || bcd2dec(mes) < 1);
	
	DS1307_SetTime(hora, mins, 0x23);  // Ajusta a hora no DS1307
	DS1307_SetDate(dia,mes,0x23); //Ajusta a data no DS1307
	lcd_clear();
	return;
}



int main(void){
	inic();
	conta_5s = 35;
	uint8_t key = 0;	
	while(1){
		lcd_puts("===IOGURTERIA===");
		key = read_keypad();
		if(key != '\0'){ // Se tecla pressionada. envia ao LCD
			if(key == '*'){
				ajusta_rtc();
			}
			if(key == '#'){
				//ajusta_temp();
			}
		
			if(key == '0'){
				//start_contr();
			
			}
		}

	}
}


