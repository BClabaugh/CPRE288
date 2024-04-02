/*
 * movement.c
 *
 *  Created on: March 19, 2024
 *      Author: Corey & Blake
 */


#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "adc.h"


void adc_init(void){
    // activate ADC0
    SYSCTL_RCGCADC_R |= 0x0001;
    // wait for ADC0 to be ready
    while((SYSCTL_PRADC_R & 0x0001) != 0x0001){};
    // enable clock to GPIO port B
    SYSCTL_RCGCGPIO_R |= 0b000010;
    // wait for GPIOB peripherals to be ready
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
    // make PB4 input
    GPIO_PORTB_DIR_R &= ~0x10;
    // enable alternate functions on PB4
    GPIO_PORTB_AFSEL_R |= 0x10;
    // disable digital functionality on PB4
    GPIO_PORTB_DEN_R &= ~0x10;
    // enable analog funcitionality on PB4
    GPIO_PORTB_AMSEL_R |= 0x10;
    
    // good by default
    // // configure for 125K samples/sec
    // ADC0_PC_R &= ~0xF;
    // ADC0_PC_R |= 0x1;
    // // Sequencer 3 is highest pripority
    // ADC0_SSPRI_R = 0x0123;

    // disable sample sequencer 3
    ADC0_ACTSS_R &= ~0x0008;
    // seq3 is software trigger
    ADC0_EMUX_R &= ~0xF000;
    // set channel 10
    ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R += 10;
    // no TS0 D0, yes IE0 END0
    ADC0_SSCTL3_R |= 0x0006;
    // disable SS3 interrupts (not completely needed)
    ADC0_IM_R &= ~0x0008;
    // enable sample sequencer 3
    ADC0_ACTSS_R |= 0x0008;

}


uint16_t adc_read(void){
    uint16_t data = 0;
    ADC0_PSSI_R |= 0x0008;

    while((ADC0_RIS_R & 0x08) == 0){}

    data = (uint16_t)(ADC0_SSFIFO3_R & 0xFFF);

    ADC0_ISC_R |= 0x0008;

    return data;
}

uint16_t adc_sample_averager(void){
    uint16_t sample_ave = 0;
    int i;
    // takes an average of 15 sample readings
    for(i=0; i < 15; i+=1){
      sample_ave += adc_read();
    }
    return (sample_ave / 15);
}
