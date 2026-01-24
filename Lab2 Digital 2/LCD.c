/*
 * LCD.c
 *
 * Created: 22/01/2026 07:05:44 p. m.
 *  Author: David Carranza
 */ 

#define F_CPU 16000000UL

#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

// Pulso en Enable
static void LCD_PulseEnable(void) {
	PORTD |= (1 << LCD_EN_PIN);
	_delay_us(1);
	PORTD &= ~(1 << LCD_EN_PIN);
	_delay_us(100);
}

// Enviar comando (8 bits)
void LCD_Command(uint8_t cmd) {
	// RS en bajo para comando
	PORTD &= ~(1 << LCD_RS_PIN);
	
	// Colocar comando en bus de datos (D4-D7)
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);
	LCD_PulseEnable();
	
	// Enviar nibble bajo (para modo 8 bits, enviar ambos nibbles)
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((cmd & 0x0F) << 4);
	LCD_PulseEnable();
	
	// Delay para comandos que necesitan más tiempo
	if (cmd == LCD_CLEAR_DISPLAY || cmd == LCD_RETURN_HOME) {
		_delay_ms(2);
		} else {
		_delay_us(50);
	}
}

// Enviar dato (8 bits)
void LCD_Data(uint8_t data) {
	// RS en alto para dato
	PORTD |= (1 << LCD_RS_PIN);
	
	// Colocar dato en bus de datos (D4-D7)
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	LCD_PulseEnable();
	
	// Enviar nibble bajo
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
	LCD_PulseEnable();
	
	_delay_us(50);
}

// Inicializar LCD en modo 8 bits
void LCD_Init(void) {
	// Configurar pines como salidas
	DDRD |= (1 << LCD_RS_PIN) | (1 << LCD_EN_PIN) | LCD_DATA_MASK;
	
	// Esperar inicialización del LCD
	_delay_ms(50);
	
	// Secuencia de inicialización 8 bits
	LCD_Command(0x30);
	_delay_ms(5);
	LCD_Command(0x30);
	_delay_us(150);
	LCD_Command(0x30);
	_delay_us(50);
	
	// Configurar LCD: 8 bits, 2 líneas, 5x8 puntos
	LCD_Command(LCD_8BIT_2LINE);
	_delay_us(50);
	
	// Display ON, cursor OFF
	LCD_Command(LCD_DISPLAY_ON);
	_delay_us(50);
	
	// Modo de entrada (incremento, no shift)
	LCD_Command(LCD_ENTRY_MODE);
	_delay_us(50);
	
	// Limpiar display
	LCD_Clear();
}

// Limpiar display
void LCD_Clear(void) {
	LCD_Command(LCD_CLEAR_DISPLAY);
	_delay_ms(2);
}

// Posicionar cursor
void LCD_SetCursor(uint8_t x, uint8_t y) {
	uint8_t address;
	
	if (y == 0) {
		address = 0x80 + x;  // Primera línea
		} else {
		address = 0xC0 + x;  // Segunda línea
	}
	
	LCD_Command(address);
}

// Imprimir string
void LCD_PrintString(const char *str) {
	while (*str) {
		LCD_Data(*str++);
	}
}

// Imprimir carácter
void LCD_PrintChar(char c) {
	LCD_Data(c);
}

// Imprimir float con formato específico
void LCD_PrintFloat(float value, uint8_t decimalPlaces) {
	char buffer[10];
	
	// Convertir float a string con formato
	// Para "0.00V", necesitamos 2 decimales
	dtostrf(value, 4, decimalPlaces, buffer);  // 4 = ancho total incluyendo punto
	
	LCD_PrintString(buffer);
}