/*
 * servo.c
 *
 *  Created on: April 2, 2024
 *      Author: Corey & Blake
 */


#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "servo.h"
#include "Timer.h"


void servos_init(void){
    // enable clock to Timer 1
    SYSCTL_RCGCTIMER_R |= 0x02;
    // wait for Timer peripherals to be ready
    while ((SYSCTL_PRTIMER_R & 0x02) == 0) {};
    // enable clock to GPIO port B
    SYSCTL_RCGCGPIO_R |= 0x02;
    // wait for GPIOB peripherals to be ready
    while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
    // make PB5 output
    //GPIO_PORTB_DIR_R |= 0x20;
    // enable alternate functions on PB5
    GPIO_PORTB_AFSEL_R |= 0x20;
    // enable digital functionality on PB5
    GPIO_PORTB_DEN_R |= 0x20;
    // enable alternate functionality on PB5 to Timer 3B
    GPIO_PORTB_PCTL_R &= ~0x00F00000;
    GPIO_PORTB_PCTL_R |= 0x00700000;
    

    // disable Timer 1B
    TIMER1_CTL_R &= ~0x0100;
    //configure 16-bit timer mode
    TIMER1_CFG_R &= ~0x7;
    TIMER1_CFG_R |= 0x4;
    //periodic mode
    TIMER1_TBMR_R &= ~0x0F;
    TIMER1_TBMR_R |= 0x0A;
    //configure output state to default
    TIMER1_CTL_R &= ~0x4000;

    // start time to make period of PWM signal 20 ms is 0x04E200

    //load start into GPTMTAILR
    TIMER1_TBILR_R = 0xE200;
    //activate prescale, creating 24-bit
    TIMER1_TBPR_R = 0x04;

    //configure match value
    TIMER1_TBMATCHR_R &= ~0xFFFFFFFF;
    //TIMER1_TBMATCHR_R |= 0x0000000;
    //configure prescale match value
    TIMER1_TBPMR_R &= ~0xFFFF;
    //TIMER1_TBPMR_R |= 0x0000;


    // Configure and enable the timer
    TIMER1_CTL_R |= 0x0100;
    
}


uint32_t servos_move(uint16_t degrees){
    // 0 degrees (1 ms high) match_val = 304000 = 0x04A380
    // 90 degrees (1.5 ms high) match_val = 296000 = 0x048440
    // 180 degrees (2 ms high) match_val = 288000 = 0x046500




    uint32_t pre_pos = TIMER1_TBPMR_R;
    pre_pos = pre_pos << 16;
    pre_pos |= TIMER1_TBMATCHR_R;
    //int deg_diff = ((pre_pos - (304000 + 8500)) / (-88-60));
    int deg_diff = ((pre_pos - (304000 + 8500)) / (-88-60));

    //uint32_t match_val = ((-88-60) * degrees) + (304000 + 8500);
    uint32_t match_val = ((-88-60) * degrees) + (304000 + 8500);

    deg_diff = abs(match_val - deg_diff);
    deg_diff = abs(degrees - deg_diff);
    int wait_time = 0.5;//0.4
    if (deg_diff > 60 && deg_diff <= 120){
        wait_time *=2;
    }
    else if (deg_diff > 120){
        wait_time *=3;
    }

    //TIMER1_CTL_R &= ~0x0100;

    //configure match value
    //TIMER1_TBMATCHR_R &= ~0xFFFFFFFF;
    TIMER1_TBMATCHR_R = (match_val & 0x0000FFFF); // bits 15-0 of match_val

    //configure prescale match value
    //TIMER1_TBPMR_R &= ~0xFFFF;
    TIMER1_TBPMR_R = ((match_val >> 16) & 0x000000FF); // bits 23-16 of match_val

    //TIMER1_CTL_R |= 0x0100;

//    lcd_printf("%08X\n%08X", TIMER1_TBMATCHR_R, TIMER1_TBPMR_R);
//      lcd_printf("%08X\n", match_val);

    timer_waitMillis(wait_time * 1000);
    return match_val;
}


