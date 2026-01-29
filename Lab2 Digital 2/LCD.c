/*
 * LCD.c
 *
 * Created: 22/01/2026 07:05:44 p. m.
 *  Author: David Carranza
 */ 

#include "LCD.h"

void LCD_PORT(char DATO){
	
	//PORTD D2 - D7
	uint8_t PORTD_TEMP = (LCD_PORTD & ~PORTD_MASK) | (DATO & PORTD_MASK);
	LCD_PORTD = PORTD_TEMP;
	
	//PORTB D0 - D1
	uint8_t PORTB_TEMP = (LCD_PORTB & ~PORTB_MASK) | (DATO & PORTB_MASK);
	LCD_PORTB = PORTB_TEMP;
}

// Lectura
void LCD_LECTURA(void){
	ENABLE_1();
	_delay_us(1);
	ENABLE_0();
	_delay_us(50);
}

void INICIAR_LCD(void){
	// Configuración de salidas
	//Controles
	CONTROL_DDR |= (1<<PIN_RS)|(1<<PIN_WR)|(1<<PIN_ENABLE);
	LCD_DDRD |= PORTD_MASK;
	LCD_DDRB |= PORTB_MASK;
	
	// Estado inicial
	LCD_CONTROL &= ~((1<<PIN_RS)|(1<<PIN_WR)|(1<<PIN_ENABLE));
	_delay_ms(50);
	COMANDO_LCD(0x38); //MODO 8 bits (0011 1000)
	_delay_ms(5);
	COMANDO_LCD(0x38); //MODO 8 bits (0011 1000)
	_delay_ms(200);
	COMANDO_LCD(0x0C); // Display On, Cursor Off, Blick Off
	COMANDO_LCD(0x01); // Clear
	_delay_ms(2);
	COMANDO_LCD(0x06); // Incrementar Cursor Derecha
	
}

void COMANDO_LCD(uint8_t COMANDO){
	
	RS_0();				//RS = 0
	WR_WRITE();			//WR = 0
	LCD_PORT(COMANDO);	// Manda los comandos a LCD_PORT
	LCD_LECTURA();
}

void LCD_WRITE_CHAR(char DATO){
	
	RS_1();			//RS = 1
	WR_WRITE();		//WR = 0
	LCD_PORT(DATO);	// Manda los datos a LCD_PORT
	LCD_LECTURA();
}

void LCD_WRITE_STRING(char *TEXTO){
	
	while(*TEXTO){
		LCD_WRITE_CHAR(*TEXTO);
		TEXTO++;

	}
	
}

void CURSOR(uint8_t FILA, uint8_t COLUMNA){
	
	uint8_t LOCATION = 0;
	if(FILA == 0){
		LOCATION = 0x80 + COLUMNA;
		
	}
	
	else
	{
		LOCATION = 0xC0 + COLUMNA;
		
	}
	COMANDO_LCD(LOCATION);
	
	
}