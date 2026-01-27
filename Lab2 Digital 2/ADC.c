/*
 * ADC.c
 *
 * Created: 22/01/2026 03:42:54 p. m.
 *  Author: David Carranza
 */ 

#include "config.h"
#include "ADC.h"
#include <avr/io.h>
#include <util/delay.h>  

void ADC_Init(void) {
	// Configurar referencia AVcc (5V) y ajuste a derecha
	ADMUX = (1 << REFS0);
	
	// Habilitar ADC y prescaler de 128 (16MHz/128 = 125kHz)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | 
			 (1 << ADPS1) | (1 << ADPS0);
	
	// Primera lectura descartada (para estabilizar)
	ADC_Read(0);
}

uint16_t ADC_Read(uint8_t channel) {
	// Limitar canal a 0-7
	channel &= 0x07;
	
	// Seleccionar canal y mantener configuración de referencia
	ADMUX = (ADMUX & 0xF0) | channel;
	
	// Pequeño delay para estabilizar multiplexor
	_delay_us(10);
	
	// Iniciar conversión
	ADCSRA |= (1 << ADSC);
	
	// Esperar fin de conversión
	while (ADCSRA & (1 << ADSC));
	
	// Retornar valor de 10 bits
	return ADC;
}