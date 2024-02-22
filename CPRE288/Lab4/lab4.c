/**
 * lab4_template.c
 *
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "functions.h"
#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

//#warning "Possible unimplemented functions"
//#define REPLACEME 0



int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
  	cyBot_uart_init(); // Don't forget to initialize the cyBot UART before trying to use it
	
	// YOUR CODE HERE
	button_init(); 
	uint8_t buttonNum;
	
	while(1)
	{
      // YOUR CODE HERE
	  buttonNum = button_getButton();
	  if(buttonNum == 0){
		continue;
	  }
	  else if(buttonNum == 4){
	    lcd_init();
		lcd_printf("%s", "Button 4");
		sendBytes("Button 4", -10000);
	  }
	  else if(buttonNum == 3){
	    lcd_init();
		lcd_printf("%s", "Button 3");
		sendBytes("Button 3", -10000);
	  }
	  else if(buttonNum == 2){
	    lcd_init();
		lcd_printf("%s", "Button 2");
		sendBytes("Button 2", -10000);
	  }
	  else if(buttonNum == 1){
	    lcd_init();
		lcd_printf("%s", "Button 1");
		sendBytes("Button 1", -10000);
	  }
	  cyBot_sendByte('\r');
  	  cyBot_sendByte('\n');
  	  timer_waitMillis(200);
	}
}
