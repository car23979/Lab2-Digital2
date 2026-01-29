/*
 * ADC.h
 *
 * Created: 22/01/2026 03:42:41 p. m.
 *  Author: David Carranza
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <stdint.h>

void ADC_CONF();
uint16_t ADC_READ(uint8_t canal);

#endif