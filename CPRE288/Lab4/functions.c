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
#include "movement.h"


// sends strings and optionally values to PuTTY
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

// initializes memory for CyBot data struct
cyBOT_Scan_t *scan_alloc()
{
	return calloc(1, sizeof(cyBOT_Scan_t));
}

// frees memory from CyBot data struct
void scan_data_free(cyBOT_Scan_t *self)
{
    free(self);
}

// initializes memory for our object data struct
full_scan_data_t *full_scan_alloc()
{
  return calloc(1, sizeof(full_scan_data_t));
}

// frees memory from our object data struct
void full_scan_data_free(full_scan_data_t *self)
{
    free(self);
}

// prints a rotating banner on the lcd screen (3 rotations)
void lcd_rotatingBanner(char* message)
{
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

// function to scan the CyBot surroundings
void scan_path(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data){
  cyBOT_Scan(0, scan_data);
  timer_waitMillis(100);

  int i;
  for (i=0; i <= 180; i+=2)
  {
    cyBOT_Scan(i, scan_data);


    full_scan_update(scan_data, full_scan_data, i);
    scan_send(scan_data, i);
  }
  find_objects(full_scan_data);
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
  full_scan_data_send(full_scan_data);
  object_data_send(full_scan_data, scan_data);
}

// updates individual scan values in our data struct
void full_scan_update(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data, int i){
  full_scan_data -> sound_dist_arr[i/2] = scan_data -> sound_dist;
  full_scan_data -> IR_raw_val_arr[i/2] = scan_data -> IR_raw_val;

  timer_waitMillis(45); //open_interface.c when updating there data struct says to wait
}

// detecting object logic
void find_objects(full_scan_data_t *full_scan_data){
  reset_objects(full_scan_data);
  int i;
  for(i=0; i <= 90; i+=1)
  {
    //3 meter vision (1.5 currently)
    if(full_scan_data -> sound_dist_arr[i] >= 100 || i==0 || i==1 || i==2){
      continue;
    }
    //object first detection
    else{
      int j;
      for(j=i+1; j<=90; j+=1){
        int h = j;
        if(full_scan_data -> sound_dist_arr[j] > 100 && h - i > 2){
          //i is the first angle the object was detected
          //j-1 is the last angle the object was detected

          //finding open object memory
          int k;
          for(k=0; k <= 7; k+=1){
            //22-----i =11
            //74-----i =37
            if(full_scan_data -> obj_num[k] == 0){
              //objects numbered 1-8
              full_scan_data -> obj_num[k] = k + 1;
              // int obj_mid_angle = (2*(i + ((i - (j - 1))/2)));
              full_scan_data -> obj_angle[k] = (2*(i + (((j - 1) - i)/2)));
              // int obj_mid_in_arr = (i + (((j - 1) - i)/2));
              full_scan_data -> obj_dist[k] = full_scan_data -> sound_dist_arr[(i + (((j - 1) - i)/2))];
              // int obj_rad_len = 2*((j - 1) - i);
              full_scan_data -> obj_radial_len[k] = 2*((j - 1) - i);
              //chord length formula: 2*radius*sin(angle_across/2)
              //(2*(full_scan_data -> sound_dist_arr[i])*sin((2*((j - 1) - i))/2));
              //2*sqrt(pow(full_scan_data -> sound_dist_arr[i], 2) - pow(full_scan_data -> sound_dist_arr[(i + (((j - 1) - i)/2))],2));
              full_scan_data -> obj_width[k] = (  full_scan_data -> sound_dist_arr[(i + (((j - 1) - i)/2))]  )*(2*((j - 1) - i));

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

// Resets object information
void reset_objects(full_scan_data_t *self){
  int i;
  for (i=0; i <= 7; i+=1)
  {
    if(self -> obj_num[i] != 0){
      self -> obj_num[i] = 0;
      self -> obj_angle[i] = 0;
      self -> obj_dist[i] = 0;
      self -> obj_radial_len[i] = 0;
      self -> obj_width[i] = 0;
    }
  }
}

// prints individual scan data to PuTTY 
void scan_send(cyBOT_Scan_t *scan_data, int deg){
  sendBytes("Degrees: ", deg);
  cyBot_sendByte('\t');
  sendBytes("Distance: ", scan_data -> sound_dist);
  cyBot_sendByte('\r');
  cyBot_sendByte('\n');
  //sendBytes("IR: ", scan_data -> IR_raw_val);
}

// prints all values in our data struct to PuTTY
void full_scan_data_send(full_scan_data_t *self){
  int i;
  for(i=0; i <= 90; i+=1){
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

// prints object information to PuTTY
void object_data_send(full_scan_data_t *self, cyBOT_Scan_t *scan_data){
    int i;
    for(i=0; i <= 7; i+=1){
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
    //spacing/format in PuTTY terminal
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
    smallest_object(self, scan_data);
    sendBytes("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%", -10000);
    cyBot_sendByte('\r');
    cyBot_sendByte('\n');
}

// finds the smallest object of detected objects
void smallest_object(full_scan_data_t *self, cyBOT_Scan_t *scan_data){
  int sml_obj = 0;
  int i;
  for (i=1; i <= 7; i+=1)
  {
    if(self -> obj_num[i] != 0){
      if(self -> obj_radial_len[i] < self -> obj_radial_len[sml_obj]){
        sml_obj = i;
      }
    }
  }
  // pointing CyBot sensor at smallest object
  cyBOT_Scan(self -> obj_angle[sml_obj], scan_data);
}

void controlled_driving(full_scan_data_t *self, oi_t *sensor_data, cyBOT_Scan_t *scan_data){
  char ch = 'm';
  while(ch != 'q'){
    ch = cyBot_getByte();
    if(ch == 'w'){
      move_forward(sensor_data, 50);
    }
    if(ch == 'x'){
      move_backward(sensor_data, 50);
    }
    if(ch == 'a'){
      turn_left(sensor_data, 15);
    }
    if(ch == 'd'){
      turn_right(sensor_data, 30);
    }
    if(ch == 't'){
      scan_path(scan_data, self);
    }
  }  
}





