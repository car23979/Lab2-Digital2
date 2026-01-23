/*
 * ADC.h
 *
 * Created: 22/01/2026 03:42:41 p. m.
 *  Author: Admin
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
uint16_t adc_read(uint8_t channel);

#endif



#endif /* ADC_H_ */