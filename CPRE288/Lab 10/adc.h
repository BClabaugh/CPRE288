/*
 * adc.h
 *
 *  Created on: March 19, 2024
 *      Author: Corey & Blake
 */



// header file

#ifndef ADC_H_
#define ADC_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>

void adc_init(void);

uint16_t adc_read(void);

uint16_t adc_sample_averager(void);


#endif /* ADC_H_ */
