/*
 * Lab2 Digital 2.c
 *
 * Created: 22/01/2026 03:36:18 p. m.
 * Author : David Carranza
 */ 

// Pantalla LCD Y ACD

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "ADC.h"
#include "LCD.h"
// Variables globales para UART
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

// Prototipos de funciones UART
void UART_Init(unsigned int ubrr);
void UART_Transmit(unsigned char data);
unsigned char UART_Receive(void);
void UART_SendString(char *str);

// Contador para S3
volatile int16_t contador = 0;

// Función para convertir voltaje a string con formato "0.00V"
int main(void) {
	
	
	char buffer[16];
	//ADC_1
	uint16_t valor_adc0 = 0;	// S1
	uint16_t valor_adc1 = 0;	// S2
	uint32_t LECTURA_ADC0 = 0;
	uint8_t PARTE_ENTERA = 0;
	uint8_t PARTE_DECIMAL = 0;

	// Inicializadores
	INICIAR_LCD();
	ADC_CONF();
	UART_Init(MYUBRR);
	
	// Mensaje inicial
	CURSOR(0,0);
	LCD_WRITE_STRING("BIENVENIDO");
	CURSOR(1,0);
	LCD_WRITE_STRING("S1:    S2:    S3:");
	_delay_ms(1000);
	
	
	COMANDO_LCD(0x01);
	_delay_ms(2);

	while (1) {
		
		// S1
		valor_adc0 = ADC_READ(1); // Canal A1

		LECTURA_ADC0 = ((uint32_t)valor_adc0 * 5000) / 1023;

		
		PARTE_ENTERA = LECTURA_ADC0 / 1000;
		PARTE_DECIMAL = (LECTURA_ADC0 % 1000) / 10;
		
		CURSOR(1,4);
		sprintf(buffer, "%d.%02d V   ", PARTE_ENTERA, PARTE_DECIMAL);
		LCD_WRITE_STRING(buffer);
		
		// S2
		valor_adc1 = ADC_READ(5); // Canal A5
		CURSOR(1, 11);  // Posición para S2
		sprintf(buffer, "%4d", valor_adc1);
		LCD_WRITE_STRING(buffer);
		
		// S3
		CURSOR(1, 16);  // Posición para S3
		sprintf(buffer, "%4d", contador);
		LCD_WRITE_STRING(buffer);
		
		// Envio de datos UART
		sprintf(buffer, "S1: %d.%02dV, S2: %d, S3: %d\r\n",
		PARTE_ENTERA, PARTE_DECIMAL, valor_adc1, contador);
		UART_SendString(buffer);
		
		// Recibir Comandos de UART
		if (UCSR0A & (1<<RXC0)) {  // Si hay dato recibido
			unsigned char comando = UART_Receive();
			
			if (comando == '+') {
				contador++;
				// Eco por UART
				UART_SendString("Contador incrementado\r\n");
			}
			else if (comando == '-') {
				contador--;
				// Eco por UART
				UART_SendString("Contador decrementado\r\n");
			}
		}
		
		_delay_ms(200);  // Espera entre lecturas

	}
}