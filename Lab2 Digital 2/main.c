/*
 * Lab2 Digital 2.c
 *
 * Created: 22/01/2026 03:36:18 p. m.
 * Author : David Carranza
 */ 

// Pantalla LCD Y ACD

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include "ADC.h"
#include "LCD.h"

void voltaje_to_string(uint16_t adc_value, char *buffer) {
	// Calcular voltaje: V = (adc_value * 5.0) / 1023
	// Usar enteros para evitar float: multiplicar por 5000 y dividir por 1023
	uint32_t mv = (adc_value * 5000UL) / 1023;
	
	// Separar dígitos
	uint8_t unidades = mv / 1000;
	uint8_t decimas = (mv % 1000) / 100;
	uint8_t centesimas = (mv % 100) / 10;
	
	// Formatear String "0.00V"
	buffer [0] = unidades + '0';
	buffer [1] = '.';
	buffer [2] = decimas + '0';
	buffer [3] = centesimas + '0';
	buffer [4] = 'V';
	buffer [5] = '\0';
	
	
	