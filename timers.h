#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef _TIMERS_H
#define _TIMERS_H


#define TC1_RUN  (1<<CS12);
#define TC1_STOP (0<<CS12);
#define TC0_RUN  (1<<CS02) | (1<<CS00);
#define TC0_STOP (0<<CS00) | (0<<CS00);

unsigned char timeout5s=1,hora,mins,segs,mes,dia,ano;
unsigned int conta_5s;
void inic_timer0(){
		// T/C0: Clock: 15,625 kHz
		// Modo Normal. Tclk=9,984 ms
		DDRC|=(1<<DDC3); // Pino PB5 como saída.
		PORTC=0b00001000; // Desliga o LED em PB5
		TCCR0A=0x00;
		TCCR0B= TC0_STOP;
		TCNT0=100; // TCNT0 = 256 - (fclk*tempo_desejado(ms))/prescale*1000
		// T/C0: Interrupção habilitada
		TIMSK0=0x01;
		sei(); // Habilitação global de interrupções
}

// Timer 0 overflow interrupt service routine
ISR(TIMER0_OVF_vect){
	TCNT0=100; // Para gerar um tempo de 10ms
	conta_5s--; // Decrementa contador de 10ms
	if(conta_5s==0) { // Se tempo alcançado
		conta_5s=35; // Reinicia contador de 10ms
		PORTC^=(1<<PC3);
		timeout5s = 0;
	}
}

void inic_tc1_1s(){
	// Timer/Counter 1: Clock: 62,500 kHz
	// Mode: Normal top=0xFFFF. Timer Period: 1 s
	// Timer1 Overflow Interrupt: Off
	lcd_puts("===IOGURTERIA===");
	
	TCCR1A=(0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);
	TCCR1B=(0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(0<<CS10);
	TCNT1H=0x0B;
	TCNT1L=0xDC;
	// Habilita Interrupção do Timer/Counter 1
	TIMSK1 |= (1<<TOIE1);
	sei();
}

ISR(TIMER1_OVF_vect){
	TCNT1L=0xDC;
	TCNT1H=0x0B;
	unsigned char disp_buff[17];
	DS1307_GetTime(&hora,&mins,&segs);
	DS1307_GetDate(&dia,&mes,&ano);
	converteDados();
	sprintf(disp_buff,"%02d:%02d",hora,mins);
	lcd_gotoxy(5,0);
	lcd_puts(disp_buff);
	sprintf(disp_buff," %02d/%02d",dia,mes);
	lcd_puts(disp_buff);
}

#endif  _TIMERS_H