/**
 * @file main.c
 * @author people
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
  scan_path(full_scan_data);
  scan_objs(full_scan_data);
  int sml_obj = 0;
  sml_obj = smallest_object(full_scan_data);
  controlled_driving(full_scan_data, sensor_data, sml_obj);










  //---------------Uninitializing---------------
  full_scan_data_free(full_scan_data);
  oi_free(sensor_data);
}
	
	

