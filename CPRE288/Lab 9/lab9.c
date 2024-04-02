/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "ping.h"

// Uncomment or add any include directives that are needed



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	ping_init();

	// YOUR CODE HERE


	int time_diff = 0;
	bool overflow = 0;
	int overflow_tot = 0;
	float time_diff_ms;
	float time_diff_cm;
	while(1)
	{


	    overflow = 0;
	    time_diff_ms = 0;
	    time_diff_cm = 0;
	    time_diff = ping_getDistance();

	    if(time_diff < 0){
	        overflow = 1;
	        overflow_tot++;
	    }

	    time_diff_ms = (time_diff * 62.5)/1000000;
	    time_diff_cm = ((time_diff_ms / 2000) * 343) * 100;


	    lcd_clear();
	    //lcd_printf("%d\n%d", time_diff, overflow);
	    lcd_printf("%d\n%d\n%f\n%f", time_diff, overflow_tot, time_diff_ms, time_diff_cm);

	    timer_waitMillis(300);


	}

}
