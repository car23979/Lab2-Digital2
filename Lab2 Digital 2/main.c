/*
 * Lab2 Digital 2.c
 *
 * Created: 22/01/2026 03:36:18 p. m.
 * Author : David Carranza
 */ 

// Pantalla LCD Y ACD

#define F_CPU 16000000UL  // 16 MHz para Arduino Nano
#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "LCD.h"

// Función para convertir voltaje a string con formato "0.00V"
void DisplayVoltage(float voltage) {
	uint8_t int_part = (uint8_t)voltage;
	uint8_t dec_part = (uint8_t)((voltage - int_part) * 100);
	
	// Posicionar en segunda línea, columna 0
	LCD_SetCursor(0, 1);
	
	// Mostrar formato "0.00V"
	LCD_PrintChar(int_part + '0');      // Unidad
	LCD_PrintChar('.');                 // Punto decimal
	LCD_PrintChar((dec_part / 10) + '0');  // Décimas
	LCD_PrintChar((dec_part % 10) + '0');  // Centésimas
	LCD_PrintChar('V');                 // Unidad
}

int main(void) {
	float voltage;
	uint16_t adc_value;
	
	// Inicializar periféricos
	ADC_Init();
	LCD_Init();
	
	// Mensaje inicial
	LCD_SetCursor(0, 0);
	LCD_PrintString("POT S1 VOLTAJE:");
	
	// Variable para suavizado (filtro pasa-bajos)
	float filtered_voltage = 0.0;
	const float alpha = 0.2;  // Factor de suavizado (0.1 a 0.3)
	
	while(1) {
		// Leer ADC del canal 0 (S1 en PC0/A0)
		adc_value = ADC_Read(1);
		
		// Convertir a voltaje: V = (ADC * 5.0) / 1023
		voltage = (adc_value * 5.0) / 1023.0;
		
		// Aplicar filtro pasa-bajos para suavizar lectura
		filtered_voltage = alpha * voltage + (1 - alpha) * filtered_voltage;
		
		// Mostrar voltaje en formato "0.00V"
		DisplayVoltage(filtered_voltage);
		
		// Esperar antes de siguiente lectura
		_delay_ms(100);  // 10 Hz de actualización
	}
	
	return 0;
}