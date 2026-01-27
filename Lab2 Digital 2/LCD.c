/*
 * LCD.c
 *
 * Created: 22/01/2026 07:05:44 p. m.
 *  Author: David Carranza
 */ 

#include "config.h"
#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>

// Pulso en Enable
static void LCD_PulseEnable(void) {
	LCD_EN_PORT |= (1 << LCD_EN_PIN);
	_delay_us(1);
	LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
	_delay_ms(2);
}

// Enviar comando (8 bits)
void LCD_Command(uint8_t cmd) {
	// RS en bajo para comando
	LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
	// Colocar comando en bus de datos (D4-D7)
	LCD_DATA_PORT = cmd;
	LCD_PulseEnable();
}

// Enviar dato (8 bits)
void LCD_Data(uint8_t data) {
	// RS en alto para dato
	LCD_RS_PORT |= (1 << LCD_RS_PIN);
	// Colocar dato en bus de datos (D4-D7)
	LCD_DATA_PORT = data;
	LCD_PulseEnable();
}

// Inicializar LCD en modo 8 bits
void LCD_Init(void) {
	// Configurar pines como salidas
	LCD_RS_DDR |= (1 << LCD_RS_PIN);
	LCD_EN_DDR |= (1 << LCD_EN_PIN);
	LCD_DATA_DDR = 0xFF;
	// Esperar inicialización del LCD
	_delay_ms(50);
	
	// Secuencia de inicialización 8 bits
	LCD_Command(0x38);	// 8 bits, 2 lineas
	LCD_Command(0x0C);	// Display On
	LCD_Command(0x06);	// Auto incremento
	LCD_Command(0x01);	// Clear
	_delay_ms(2);
}

// Limpiar display
void LCD_Clear(void) {
	LCD_Command(0x01);
	_delay_ms(2);
}

// Posicionar cursor
void LCD_SetCursor(uint8_t col, uint8_t row) {
	uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;
	LCD_Command(address);
}

// Imprimir string
void LCD_PrintString(const char *str) {
	while (*str) {
		LCD_Data(*str++);
	}
}