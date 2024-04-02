/**
 * lab6-interrupt_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

#include "Timer.h"
#include "lcd.h"
#include "cyBot_Scan.h"  // For scan sensors
#include "uart-interrupt.h"

// Uncomment or add any include directives that you want to use
// #include "open_interface.h"
// #include "movement.h"
// #include "button.h"

// Your code can use the global variables defined in uart-interrupt.c
// They are declared with the extern qualifier in uart-interrupt.h, which makes the variables visible to this file.



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	uart_interrupt_init();
	cyBOT_init_Scan(0b0111);


	int i;
	cyBOT_Scan_t scan;
	// OPTIONAL
	//assign a value to command_byte if you want to know whether that ASCII code is received
	//note that command_byte is global shared variable read by the ISR
	//for example, try using a tab character as a command from PuTTY

	while(1)
	{

	    if(command_flag_go == 1){
	        command_flag_go = 0;

	        for (i=0; i <= 180; i+=5){
	           cyBOT_Scan(i, &scan);
	           if(command_flag_stop == 1){
	               command_flag_stop = 0;
	               break;
	           }
	        }
	    }

	}

}
