/**
 * @file main.c
 * @author Corey & Friends
 */

#include "Timer.h"
#include "lcd.h"
#include "servo.h"
#include "adc.h"
#include "ping.h"
#include "open_interface.h"
#include "movement.h"
#include "functions.h"
#include "uart-interrupt.h"
#include "final.h"
#include "math.h"




int main(void) {
	//-------------Initializing-------------------
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    timer_init();
    lcd_init();
    uart_interrupt_init();
    full_scan_data_t *full_scan_data = full_scan_alloc();
	adc_init();
	ping_init();
	servos_init();


  
  //---------------- Lab Project -----------------


//	while(1)
//	{
//	    oi_update(sensor_data);
//	    lcd_printf("%s%d\n%s%d\n%s%d\n%s%d", "L:", sensor_data->cliffLeftSignal, "LF:", sensor_data->cliffFrontLeftSignal, "RF:", sensor_data->cliffFrontRightSignal, "R:", sensor_data->cliffRightSignal);
//	}



	//sound();
  controlled_driving(full_scan_data, sensor_data);











  //---------------Uninitializing---------------
  full_scan_data_free(full_scan_data);
  oi_free(sensor_data);
}
	
	

