/*
 * ADC.h
 *
 * Created: 22/01/2026 03:42:41 p. m.
 *  Author: David Carranza
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);

#endif