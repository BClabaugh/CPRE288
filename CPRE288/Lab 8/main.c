// main file

#include "open_interface.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include "functions.h"
#include "Timer.h"
#include "lcd.h"
#include "uart-interrupt.h"
#include "adc.h"
#include "math.h"

void main() {
  //-------------Initializing-------------------
  oi_t *sensor_data = oi_alloc();
  oi_init(sensor_data);
  timer_init();
  lcd_init();
  cyBOT_init_Scan(0b0111);
  uart_interrupt_init();
  cyBOT_Scan_t *scan_data = scan_alloc();
  full_scan_data_t *full_scan_data = full_scan_alloc();
  adc_init();

  //-------------Servo calibration test-------------
  //bot 11
//  right_calibration_value = 232750;
//  left_calibration_value = 1193500;
  //bot 03
//  right_calibration_value = 280000;
//  left_calibration_value = 1246000;
  // bot 08: great
  right_calibration_value = 259000;
  left_calibration_value = 1240750;
  // bot 13
//  right_calibration_value = 238000;
//  left_calibration_value = 1214500;
  // bot 02: mid
//  right_calibration_value = 280000;
//  left_calibration_value = 1240750;

//  cyBOT_SERVO_cal();
//  cyBOT_Scan_t scan;
//  int i;
//  for (i=0; i <= 180; i+=2)
//  {
//    cyBOT_Scan(i, &scan);
//  }

//  ir_init_output(sensor_data, scan_data);


  // uart_sendChar('\r');
  // uart_sendChar('\n');
  // uart_sendChar('\r');
  // uart_sendChar('\n');
  // uart_sendChar('\r');
  // uart_sendChar('\n');
  // uart_sendChar('\r');
  // uart_sendChar('\n');
  
  //----------------Lab 7-----------------
  // scan_path(scan_data, full_scan_data);
  // scan_objs(scan_data, full_scan_data);
  // int sml_obj = 0;
  // sml_obj = smallest_object(full_scan_data, scan_data);
  // controlled_driving(full_scan_data, sensor_data, scan_data, sml_obj);


  //----------------Lab 8-----------------
  uint16_t IR_val;
  float IR_val_cm;
  cyBOT_Scan(90, scan_data);
  while(1){
      IR_val = adc_sample_averager();
      IR_val_cm = (319.729 * exp(-0.00200072 * (IR_val)) + 9.327);
      lcd_clear();
      lcd_printf("%d\n%.2f cm",IR_val, IR_val_cm);
      timer_waitMillis(5000);
  }





  



  //---------------Uninitializing---------------
  full_scan_data_free(full_scan_data);
  scan_data_free(scan_data);
  oi_free(sensor_data);
}


