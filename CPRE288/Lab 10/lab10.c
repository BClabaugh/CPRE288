/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"

// Uncomment or add any include directives that are needed



int main(void) {
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();
	servos_init();
	button_init();

	// YOUR CODE HERE


//	int time_diff = 0;
//	bool overflow = 0;
//	int overflow_tot = 0;
//	float time_diff_ms;
//	float time_diff_cm;
	while(1)
	{


//	    servos_move(90);
//	    lcd_printf("scan1");
//	    timer_waitMillis(2000);
//	    servos_move(0);
//	    lcd_printf("scan2");
//	    timer_waitMillis(2000);
//	    servos_move(180);
//	    lcd_printf("scan3");
//	    timer_waitMillis(2000);
	    uint8_t buttonNum;
	    int degrees = 90;
	    int i = 1;
	    servos_move(degrees);
	    uint32_t mtch_val;
	    while(1)
	        {

	          // YOUR CODE HERE
	          buttonNum = button_getButton();
	          if(buttonNum == 0){
	            continue;
	          }
	          else if(buttonNum == 1){
	              if((degrees>=0) && (degrees < 181)){

	                  degrees += 1 * i;
	                  mtch_val = servos_move(degrees);
	                  lcd_printf("%d\n%d",mtch_val,i);
	              }
	          }
	          else if(buttonNum == 2){
	              if((degrees>=0) && (degrees < 181)){

	                  degrees += 5 * i;
	                  mtch_val = servos_move(degrees);
	                  lcd_printf("%d\n%d",mtch_val,i);
	              }
	          }
	          else if(buttonNum == 3){

	            i *= -1;
	            mtch_val = servos_move(degrees);
	            lcd_printf("%d\n%d",mtch_val,i);
	          }
	          else if(buttonNum == 4){

	            if(i==-1){
	                degrees = 5;
	            }else{
	                degrees =175;
	            }
	            mtch_val = servos_move(degrees);
	            lcd_printf("%d\n%d",mtch_val,i);
	          }

	        }








//	    overflow = 0;
//	    time_diff_ms = 0;
//	    time_diff_cm = 0;
//	    time_diff = ping_getDistance();
//
//	    if(time_diff < 0){
//	        overflow = 1;
//	        overflow_tot++;
//	    }
//
//	    time_diff_ms = (time_diff * 62.5)/1000000;
//	    time_diff_cm = ((time_diff_ms / 2000) * 343) * 100;
//
//
//	    lcd_clear();
//	    //lcd_printf("%d\n%d", time_diff, overflow);
//	    lcd_printf("%d\n%d\n%f\n%f", time_diff, overflow_tot, time_diff_ms, time_diff_cm);
//
//	    timer_waitMillis(300);


	}

}
