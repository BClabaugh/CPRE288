/**
 * lab6_template.c
 *
 * Template file for CprE 288 Lab 6
 *
 * @author Diane Rover, 2/15/2020
 *
 */

//#include "Timer.h"
//#include "lcd.h"
//#include "cyBot_Scan.h"  // For scan sensors
//#include "uart.h"
//
//
//// Uncomment or add any include directives that are needed
//// #include "open_interface.h"
//// #include "movement.h"
//// #include "button.h"
//
//
//
//
//int main(void) {
//	timer_init(); // Must be called before lcd_init(), which uses timer functions
//	lcd_init();
//	uart_init();
//    cyBOT_init_Scan(0b0111);
//
//	cyBOT_Scan_t scan;
//	// YOUR CODE HERE
//	char ch = '0';
//	int i;
//
//	while(ch != '7')
//	{
//		ch = uart_receive_nonblocking();
//		//uart_sendChar(ch);
//	    if(ch == 'g'){
//	        for (i=0; i <= 180; i+=2){
//				ch = uart_receive_nonblocking();
//				//uart_sendChar(ch);
//				if(ch == 's'){
//					break;
//				}
//				else{
//				    uart_sendChar('0');
//				}
//				cyBOT_Scan(i, &scan);
//			}
//	    }
//	    else{
//	        uart_sendChar('0');
//	    }
//	}
//
//}
