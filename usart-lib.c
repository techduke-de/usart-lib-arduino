/*-------------------*/
/*Autor: Jean-Marcel Herzog*/
/*veröffentlicht am: 23.07.2017*/
/*Kontakt: support@techduke.de*/
/*http://www.techduke.de*/
/*-------------------*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUDRATE
#define BAUDRATE 9600
#endif

#ifndef BAUD_PRESCALLER
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)
#endif


#include <avr/io.h>

void USART_init(void){
	UBRR0H = (uint8_t) (BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t) (BAUD_PRESCALLER);
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

unsigned char USART_receive(void){
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void USART_send(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void USART_sendString(char* stringInp){
	while(*StringPtr != 0x00){
		USART_send(*StringInp);
		StringInp++;
	}
}