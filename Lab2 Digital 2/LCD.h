/*
 * LCD.h
 *
 * Created: 22/01/2026 07:05:59 p. m.
 *  Author: David Carranza
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

// Comandos LCD
#define LCD_CLEAR		0x01	// Comando para limpiar pantalla
#define LCD_8BIT		0x38	// Comando para tener la LCD en 8Bits
#define LCD_HOME		0x02	// Comando para inicio
#define LCD_ON			0x0C	// Comando para encender pantalla
#define LCD_ENTRY		0x06	// Comando para Incremento

void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_clear(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_puts(const char *str);
void lcd_putc(char c);


#endif /* LCD_H_ */