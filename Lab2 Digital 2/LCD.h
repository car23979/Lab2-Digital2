/*
 * LCD.h
 *
 * Created: 22/01/2026 07:05:59 p. m.
 *  Author: David Carranza
 */ 


#ifndef LCD_H_
#define LCD_H_


#include <stdint.h>

// Definición de pines (ajustar según conexión)
#define LCD_RS_PIN     PIND2  // D2
#define LCD_EN_PIN     PIND3  // D3
// Pines de datos D4-D7 en puerto D
#define LCD_DATA_PORT  PORTD
#define LCD_DATA_DDR   DDRD
#define LCD_DATA_MASK  0xF0  // D4-D7 (bits 4-7)

// Comandos LCD
#define LCD_CLEAR_DISPLAY   0x01
#define LCD_RETURN_HOME     0x02
#define LCD_8BIT_2LINE      0x38
#define LCD_DISPLAY_ON      0x0C
#define LCD_ENTRY_MODE      0x06

// Funciones
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t x, uint8_t y);
void LCD_PrintString(const char *str);
void LCD_PrintChar(char c);
void LCD_PrintFloat(float value, uint8_t decimalPlaces);

#endif