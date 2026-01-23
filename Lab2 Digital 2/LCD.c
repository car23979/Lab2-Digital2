/*
 * LCD.c
 *
 * Created: 22/01/2026 07:05:44 p. m.
 *  Author: David Carranza
 */ 


 #include "LCD.h"
 #include <avr/io.h>

 // Definición de pines
 #define LCD_PORT        PORTD
 #define LCD_DDR         DDRD
 #define LCD_RS          PIND0
 #define LCD_EN          PIND1
 
 // D0-D7 conectados a PD2-PD9

 void lcd_pulse_enable(void) {
	 LCD_PORT |= (1 << LCD_EN);
	 _delay_us(1);
	 LCD_PORT &= ~(1 << LCD_EN);
	 _delay_us(100);
 }

 void lcd_command(uint8_t cmd) {
	 // RS en bajo para comando
	 LCD_PORT &= ~(1 << LCD_RS);
	 
	 // Colocar comando en bus de datos
	 LCD_PORT = (LCD_PORT & 0x03) | (cmd & 0xFC);
	 lcd_pulse_enable();
 }

 void lcd_data(uint8_t data) {
	 // RS en alto para dato
	 LCD_PORT |= (1 << LCD_RS);
	 
	 // Colocar dato en bus de datos
	 LCD_PORT = (LCD_PORT & 0x03) | (data & 0xFC);
	 lcd_pulse_enable();
 }

 void lcd_init(void) {
	 // Configurar puertos como salida
	 LCD_DDR |= 0xFF;
	 
	 // Esperar inicialización de LCD
	 _delay_ms(50);
	 
	 // Secuencia de inicialización 8-bit
	 lcd_command(0x30);
	 _delay_ms(5);
	 lcd_command(0x30);
	 _delay_us(150);
	 lcd_command(0x30);
	 
	 // Configurar LCD: 8-bit, 2 líneas, 5x8
	 lcd_command(LCD_8BIT);
	 _delay_us(50);
	 
	 // Display ON, cursor OFF
	 lcd_command(LCD_ON);
	 _delay_us(50);
	 
	 // Modo de entrada
	 lcd_command(LCD_ENTRY);
	 _delay_us(50);
	 
	 // Limpiar display
	 lcd_clear();
 }

 void lcd_clear(void) {
	 lcd_command(LCD_CLEAR);
	 _delay_ms(2);
 }

 void lcd_gotoxy(uint8_t x, uint8_t y) {
	 uint8_t address;
	 
	 if (y == 0)
	 address = 0x80 + x;    // Primera línea
	 else
	 address = 0xC0 + x;    // Segunda línea
	 
	 lcd_command(address);
 }

 void lcd_puts(const char *str) {
	 while (*str) {
		 lcd_data(*str++);
	 }
 }

 void lcd_putc(char c) {
	 lcd_data(c);
 }