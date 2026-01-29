/*
 * LCD.h
 *
 * Created: 22/01/2026 07:05:59 p. m.
 *  Author: David Carranza
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>


// Definición de pines
// Pines de Control
#define LCD_CONTROL	PORTB
#define CONTROL_DDR DDRB
#define PIN_RS		PINB4
#define PIN_WR		PINB3
#define PIN_ENABLE	PINB2

// Salidas D2 - D7
#define LCD_PORTD PORTD
#define LCD_DDRD  DDRD
#define	PORTD_MASK 0xFC		// Se reservan PD0 y PD1 para la UART (1111 1100)

// Funciones
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_PrintString(const char *str);

#endif