/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021, 2/17/2022
 */


#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "uart.h"
#include <stdio.h>

//#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors


//#warning "Possible unimplemented functions"
//#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();

  // initialize the cyBot UART1 before trying to use it

  // (Uncomment ME for UART init part of lab)
//	cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code

	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
//    SYSCTL_RCGCGPIO_R |= 0b000010;
//	while ((SYSCTL_PRGPIO_R & 0x02) == 0) {};
//	GPIO_PORTB_DEN_R |= 0x03;
//	GPIO_PORTB_AFSEL_R |= 0x03;
//    GPIO_PORTB_PCTL_R &= 0xFFFFFF00;     // Force 0's in the desired locations
//    GPIO_PORTB_PCTL_R |= 0x00000011;     // Force 1's in the desired locations
//		 // Or see the notes for a coding alternative to assign a value to the PCTL field
//
//    // (Uncomment ME for UART init part of lab)
//	cyBot_uart_init_last_half();  // Complete the UART device configuration


	uart_init();


		// Initialize the scan
	// cyBOT_init_Scan();
		// Remember servo calibration function and variables from Lab 3

	// YOUR CODE HERE
	int i;
	char ch;
	while(1){
	    char str[21] = "";
	    i=0;
	    while(i < 21){
	        ch = uart_receive();
	        if(ch == '\r'){
	            break;
	        }
	        str[i] = ch;
	        lcd_clear();
	        lcd_puts(str);
	        lcd_gotoLine(2);
	        i++;
	        lcd_printf("%s\n%d",str, i);
	        uart_sendChar(ch);
	    }
	    lcd_clear();
	    uart_sendChar('\r');
	    uart_sendChar('\n');
	}

}
