/*
 * LCD.h
 *
 * Created: 22/01/2026 07:05:59 p. m.
 *  Author: Admin
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


#endif /* LCD_H_ */