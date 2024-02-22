/*
 * functions.c
 *
 *  Created on: Feb 6, 2024
 *      Author: clab22
 */


#include "functions.h"
#include "open_interface.h"
#include "cyBot_Scan.h"
#include "cyBot_uart.h"
#include "Timer.h"
#include "math.h"


void sendBytes(char* message, double data){
  int i;
  char final_mes[100];

  if (data != -10000) {
    sprintf(final_mes, "%s %.3f", message, data);
  } else {
    strcpy(final_mes, message);
  }
//  sprintf(final_mes,"%s", final_mes);
  for(i = 0; i < strlen(final_mes); i++){
    //printf("%c\n", final_mes[i]);
    cyBot_sendByte(final_mes[i]);
  }

}

cyBOT_Scan_t *scan_alloc()
{
	return calloc(1, sizeof(cyBOT_Scan_t));
}

void scan_data_free(cyBOT_Scan_t *self)
{
    free(self);
}

full_scan_data_t *scan_alloc()
{
  return calloc(1, sizeof(full_scan_data_t));
}

void full_scan_data_free(full_scan_data_t *self)
{
    free(self);
}

void lcd_rotatingBanner(char* message)
{
    int i;
    char* spaces = "                   ";
    char final_mes[100];
    sprintf(final_mes,"%s%s", spaces,message);
    int i = 0;
    while(i<=3){
        for(i=0;i<=strlen(final_mes);i++){
            lcd_printf("%.20s\n",final_mes+i);
            timer_waitMillis(300);
        }
        i += 1;
    }
}

void scan_180(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data){
  int i;
  //int j = 0;
  for (i=0; i <= 180; i+=2)
  {
    cyBOT_Scan(i, scan_data);
    full_scan_update(scan_data, full_scan_data, i);
    //j += 1;
    scan_send(scan_data, i);
  }
  find_objects(full_scan_data);
  full_scan_data_send(full_scan_data);
  object_data_send(full_scan_data);
}

void full_scan_update(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data, int i){
  full_scan_data -> sound_dist_arr[i/2] = scan_data -> sound_dist;
  full_scan_data -> IR_raw_val_arr[i/2] = scan_data -> IR_raw_val;

  timer_waitMillis(20); //open_interface.c when updating there data struct says to wait 
}

void find_objects(full_scan_data_t *full_scan_data){
  reset_objects(full_scan_data);
  for (int i=0; i <= 90; i++)
  {
    //3 meter vision
    if(full_scan_data -> sound_dist_arr[i] >= 150){
      continue;
    }
    //object first detection
    else{
      for(int j=i+1; j<=90; j++){
        if(full_scan_data -> sound_dist_arr[j] < 150){
          //i is the first angle the object was detected
          //j-1 is the last angle the object was detected

          //finding open object memory
          for(int k=0; k <= 7; k++){
            if(full_scan_data -> obj_num[k] == 0){
              //objects numbered 1-8
              full_scan_data -> obj_num[k] = k + 1;
              // int obj_rad_len = 2*(i - (j - 1));
              full_scan_data -> obj_angle[k] = (2*(i + ((i - (j - 1))/2)));
              // int obj_mid_in_arr = (i + ((i - (j - 1))/2));
              full_scan_data -> obj_dist[k] = full_scan_data -> sound_dist_arr[(i + ((i - (j - 1))/2))];
              // int obj_mid_angle = (2*(i + ((i - (j - 1))/2)));
              full_scan_data -> obj_radial_len[k] = 2*(i - (j - 1));
              //chord length formula: 2*radius*sin(angle_across/2)
              full_scan_data -> obj_width[k] = (2*(full_scan_data -> sound_dist_arr[i])*sin((2*(i - (j - 1)))/2));
              
              break; //break out of k loop so only one object is created at a time
            }
          }
          i += j; // so it doesn't look at data twice
          break; // break out of j loop
        }
      }
    }
  }
}

void reset_objects(full_scan_data_t *self){
  for (int i=0; i <= 7; i++)
  {
    if(self -> obj_num[i] != 0){
      self -> obj_num[i] = 0
      self -> obj_angle[i] = 0
      self -> obj_dist[i] = 0
      self -> obj_radial_len[i] = 0
      self -> obj_width[i] = 0
    }
  }
}

void scan_send(cyBOT_Scan_t *scan_data, int deg){
  sendBytes("Degrees: ", deg);
  cyBot_sendByte('\t');
  sendBytes("Distance: ", scan_data -> sound_dist);
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
  //sendBytes("IR: ", scan_data -> IR_raw_val);
}

void full_scan_data_send(full_scan_data_t *self){
  for (int i=0; i <= 90; i++)
  {
    sendBytes("Degrees: ", i*2);
    cyBot_sendByte('\t');
    sendBytes("Distance: ", self -> sound_dist_arr[i]);
    cyBot_sendByte('\t');
    sendBytes("IR: ", self -> IR_raw_val_arr[i]);
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
  }
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
}

void object_data_send(full_scan_data_t *self){
for (int i=0; i <= 7; i++)
  {
    sendBytes("Obj num: ", self -> obj_num[i]);
    cyBot_sendByte('\t');
    sendBytes("angle: ", self -> obj_angle[i]);
    cyBot_sendByte('\t');
    sendBytes("dist: ", self -> obj_dist[i]);
    cyBot_sendByte('\t');
    sendBytes("radial: ", self -> obj_radial_len[i]);
    cyBot_sendByte('\t');
    sendBytes("width: ", self -> obj_width[i]);
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
  }
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
}





