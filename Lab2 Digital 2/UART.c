/*
 * UART.c
 *
 * Created: 29/01/2026 11:20:36 a. m.
 *  Author: Admin
 */ 

#include "UART.h"

void UART_Init(unsigned int ubrr) {
	// Configurar baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	// Habilitar transmisor y receptor
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	// Configurar frame: 8 bits, 1 stop bit, sin paridad
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void UART_Transmit(unsigned char data) {
	// Esperar a que el buffer de transmisión esté vacío
	while (!(UCSR0A & (1<<UDRE0)));
	
	// Poner dato en el buffer
	UDR0 = data;
}

unsigned char UART_Receive(void) {
	// Esperar a que llegue un dato
	while (!(UCSR0A & (1<<RXC0)));
	
	// Devolver el dato recibido
	return UDR0;
}

void UART_SendString(char *str) {
	while (*str) {
		UART_Transmit(*str);
		str++;
	}
}