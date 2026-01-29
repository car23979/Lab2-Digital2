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

// Salidas D0 y D1
#define	LCD_PORTB PORTB
#define	LCD_DDRB  DDRB
#define	PORTB_MASK 0x03		// Mascara para (0000 0011)

//Habilitar y desabilitar RS, RW y Enable
#define	ENABLE_1()	LCD_CONTROL |= (1<<PIN_ENABLE)
#define	ENABLE_0()	LCD_CONTROL &= ~(1<<PIN_ENABLE)
#define	RS_0()		LCD_CONTROL &= ~(1<<PIN_RS)
#define	RS_1()		LCD_CONTROL |= (1<<PIN_RS)
#define	WR_WRITE()	LCD_CONTROL &= ~(1<<PIN_WR)
#define	WR_READ()	LCD_CONTROL |= (1<<PIN_WR)

// Funciones
void INICIAR_LCD(void); //INICIAR EL LCD
void COMANDO_LCD(uint8_t COMANDO); //Manda un comando
void LCD_WRITE_CHAR(char DATO); //Manda una Letra
void LCD_PORT(char DATO); //Manda los datos al PORTD y PORTB
void LCD_LECTURA(void); //
void LCD_WRITE_STRING(char *TEXTO ); //Manda un texto
void CURSOR(uint8_t FILA, uint8_t COLUMNA); //Mueve el cursor

#endif