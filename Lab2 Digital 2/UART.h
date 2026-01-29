/*
 * UART.h
 *
 * Created: 29/01/2026 11:20:47 a. m.
 *  Author: Admin
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdint.h>

void UART_Init(unsigned int ubrr);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);
void UART_SendString(char *str);


#endif /* UART_H_ */