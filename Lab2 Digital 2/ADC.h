/*
 * ADC.h
 *
 * Created: 22/01/2026 03:42:41 p. m.
 *  Author: David Carranza
 */ 


#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
float ADC_ReadVoltage(uint8_t channel);

#endif