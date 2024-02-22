// main file

#include "open_interface.h"
#include "movement.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "functions.h"
#include "Timer.h"
#include "lcd.h"

void main() {
  oi_t *sensor_data = oi_alloc();
  oi_init(sensor_data);

  timer_init();
  lcd_init();
  cyBOT_init_Scan(0b0111);
  cyBot_uart_init();
  cyBOT_Scan_t *scan_data = scan_alloc();
  full_scan_data_t *full_scan_data = scan_alloc();
//  cyBOT_SERVO_cal();
  right_calibration_value = 232750;
  left_calibration_value = 1193500;
  //bot 11
  
  //Servo calibration test
//  cyBOT_Scan_t scan;
//
//  for (i=0; i <= 180; i+=2)
//  {
//    cyBOT_Scan(i, &scan);
//  }


  //Lab 3-Part 1
//  char ch;
//  while(ch != 'q'){
//      ch = cyBot_getByte();
//      lcd_printf(&ch);
//      cyBot_sendByte(ch);
//      char str[10] = "This is ";
//      str[8] = ch;
//      sendBytes(str, -10000);
//  }

  
  //Lab 3-Part 2
  scan_180(scan_data, full_scan_data);
  
  //lab 3-Part 3

  // Call a function to move robot
  // square(sensor_data);
  // turn_left(sensor_data, 90);
  // two_meter_race(sensor_data);


  full_scan_data_free(full_scan_data);
  scan_data_free(scan_data);
  oi_free(sensor_data);
}


