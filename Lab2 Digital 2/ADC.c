/*
 * ADC.c
 *
 * Created: 22/01/2026 03:42:54 p. m.
 *  Author: David Carranza
 */ 

#include "ADC.h"
#include <avr/io.h>

void adc_init(void) {
	// Configurar referencia AVcc (5V) y ajuste a derecha
	ADMUX = (1 << REFS0);
	
	// Habilitar ADC y prescaler de 128 (16MHz/128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t channel) {
	// Seleccionar canal (0-7) y mantener configuración de referencia
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
	
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	
	// Esperar fin de conversión
	while (ADCSRA & (1 << ADSC));
	
	// Retornar valor de 10 bits
	return ADC;
}