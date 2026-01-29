/*
 * ADC.c
 *
 * Created: 22/01/2026 03:42:54 p. m.
 *  Author: David Carranza
 */ 

#include "ADC.h"


void ADC_CONF() {
	// Configurar referencia AVcc (5V) y ajuste a derecha
	ADMUX = (1 << REFS0);
	
	// Habilitar ADC y prescaler de 64
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1);
	
	// Primera lectura descartada (para estabilizar)
	ADC_READ(0);
}


// Leer el canal
uint16_t ADC_READ(uint8_t canal) {
	
	// Seleccionar canal y mantener configuración de referencia
	ADMUX = (ADMUX & 0xF0) | (canal & 0x0F);
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	// Esperar fin de conversión
	while (ADCSRA & (1 << ADSC));
	// Retornar valor de 10 bits
	return ADC;
}