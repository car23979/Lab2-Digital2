/*
 * LCD.h
 *
 * Created: 22/01/2026 07:05:59 p. m.
 *  Author: David Carranza
 */ 


#ifndef LCD_H_
#define LCD_H_


#include <stdint.h>

// Definición de pines
// Pines de Control
#define LCD_RS_PORT		PORTB
#define LCD_RS_DDR		DDRB
#define LCD_RS_PIN		PB0

#define LCD_EN_PORT		PORTB
#define LCD_EN_DDR		DDRB
#define LCD_EN_PIN		PB1

// Bus de datos (D0-D7)
#define LCD_DATA_PORT	PORTD
#define LCD_DATA_DDR	DDRD

// Funciones
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t col, uint8_t row);
void LCD_PrintString(const char *str);

#endif