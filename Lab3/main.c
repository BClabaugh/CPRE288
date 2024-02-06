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
//  cyBOT_SERVO_cal();
  right_calibration_value = 232750;
  left_calibration_value = 1193500;
  //bot 11
  cyBOT_Scan_t *scan_data = scan_alloc();
  int i;
  //Servo calibration test
//  cyBOT_Scan_t scan;
//
//  for (i=0; i <= 180; i+=2)
//  {
//    cyBOT_Scan(i, &scan);
//  }

  //struct accessor
  //scanData -> sound_dist;
  //scanData -> IR_raw_val;

  //Part 1
//  char ch;
//  while(ch != 'q'){
//      ch = cyBot_getByte();
//      lcd_printf(&ch);
//      cyBot_sendByte(ch);
//      char str[10] = "This is ";
//      str[8] = ch;
//      sendBytes(str, -10000);
//  }

  
  //part 2
  for (i=0; i <= 180; i+=2)
  {
  cyBOT_Scan(i, scan_data);
  sendBytes("Degrees: ", i);
  cyBot_sendByte('\t');
  sendBytes("Distance: ", scan_data -> sound_dist);
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
  //sendBytes("IR: ", scan_data -> IR_raw_val);

  // Call a function to move robot
  //square(sensor_data);
  //turn_left(sensor_data, 90);
  //two_meter_race(sensor_data);
}


  scan_free(scan_data);
  oi_free(sensor_data);
}


