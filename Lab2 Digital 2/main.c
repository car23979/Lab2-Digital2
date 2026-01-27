/*
 * Lab2 Digital 2.c
 *
 * Created: 22/01/2026 03:36:18 p. m.
 * Author : David Carranza
 */ 

// Pantalla LCD Y ACD

#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "LCD.h"

// Función para convertir voltaje a string con formato "0.00V"
void DisplayVoltage(uint16_t adc_value) {
	uint16_t mv = (adc_value * 5000UL) / 1023;	
	// Posicionar en segunda línea, columna 0
	LCD_SetCursor(0, 1);
	
	// Mostrar formato "0.00V"
	LCD_Data((mv / 1000) + '0');
	LCD_Data('.');
	LCD_Data(((mv % 1000) / 100) + '0');
	LCD_Data(((mv % 100) / 10) + '0');
	LCD_Data('V');
}

int main(void) {
	uint16_t adc_value;
	
	// Inicializar periféricos
	ADC_Init();
	LCD_Init();
	
	// Mensaje inicial
	LCD_SetCursor(0, 0);
	LCD_PrintString("POT S1 VOLTAJE:");
	
	while (1) {
		// Leer ADC del canal 0 (S1 en PC0/A0)
		adc_value = ADC_Read(0);
		// Mostrar voltaje en formato "0.00V"
		DisplayVoltage(adc_value);
		// Esperar antes de siguiente lectura
		_delay_ms(200);  // 20 Hz de actualización
	}
}