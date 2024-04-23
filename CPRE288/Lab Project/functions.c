/*
 * functions.c
 *
 *  Created on: Feb 6, 2024
 *      Author: clab22
 */


#include "functions.h"
#include "open_interface.h"
#include "Timer.h"
#include "math.h"
#include "movement.h"
#include "uart-interrupt.h"
#include "adc.h"
#include "ping.h"
#include "servo.h"



// sends strings and optionally values to PuTTY
void sendBytes(char* message, double data){
  char final_mes[100];

  if (data != -10000) {
    sprintf(final_mes, "%s %.3f", message, data);
  } else {
    strcpy(final_mes, message);
  }

  uart_sendStr(final_mes);
}

// sends strings and optionally int values to PuTTY
void sendBytesInt(char* message, double data){
  char final_mes[100];

  if (data != -10000) {
    sprintf(final_mes, "%s %.0f", message, data);
  } else {
    strcpy(final_mes, message);
  }

  uart_sendStr(final_mes);
}

// // initializes memory for CyBot data struct
// cyBOT_Scan_t *scan_alloc()
// {
// 	return calloc(1, sizeof(cyBOT_Scan_t));
// }

// // frees memory from CyBot data struct
// void scan_data_free(cyBOT_Scan_t *self)
// {
//     free(self);
// }

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




//---------------------------------------------------------------------------- scanning

// function to scan the CyBot surroundings
void scan_path(full_scan_data_t *full_scan_data){
  uart_sendChar('\r');
  uart_sendChar('\n');
  servos_move(0);
  timer_waitMillis(700);
  int i;
  for (i=0; i <= 180; i+=2)
  {
    servos_move(i);

    int scan_IR_ave = adc_sample_averager();
    float scan_ping_val = ping_getDistance();

    full_scan_update(full_scan_data, i, scan_IR_ave, scan_ping_val);
    scan_send(full_scan_data, i);
  }
  
  find_objects_pos(full_scan_data);
}

void scan_objs(full_scan_data_t *full_scan_data){
//  int k;
//  for(k=0; k <= 7; k++){
//    if(full_scan_data -> obj_mid_angle[k] != 0){
//      // averaging the IR value over 3 scans at each angle
//      int j;
//      float scan_ping_ave = 0;
//      for(j=0; j < 3; j+=1){
//        cyBOT_Scan(full_scan_data -> obj_mid_angle[k], scan_data);
//        scan_ping_ave += scan_data -> sound_dist;
//      }
//      scan_ping_ave = (scan_ping_ave / 3.0);
//
//      dist_scan_update(full_scan_data, full_scan_data -> obj_mid_angle[k], scan_ping_ave);
//
//    }
//  }

  find_objects_full(full_scan_data);
  uart_sendChar('\r');
  uart_sendChar('\n');
  full_scan_data_send(full_scan_data);
  object_data_send(full_scan_data);

}

// updates individual scan values in our data struct
void full_scan_update(full_scan_data_t *full_scan_data, int i, int scan_IR_ave, float scan_ping_val){
  full_scan_data -> sound_dist_arr[i/2] = scan_ping_val;
  full_scan_data -> IR_raw_val_arr[i/2] = scan_IR_ave;
  full_scan_data -> IR_val_arr[i/2]  = (420.160 * exp(-0.00244594 * (scan_IR_ave)) + 2.056);

  timer_waitMillis(15); //open_interface.c when updating there data struct says to wait
}

// updates object distance values in our data struct
void dist_scan_update(full_scan_data_t *full_scan_data, int i, float scan_ping_ave){
  full_scan_data -> sound_dist_arr[i/2] = scan_ping_ave;
  timer_waitMillis(15);
}

// detecting objects with IR sensor
void find_objects_pos(full_scan_data_t *full_scan_data){
  reset_objects(full_scan_data);
  int i;
  for(i=0; i <= 90; i+=1)
  {
    //3 meter vision (30 cm currently)
    if(full_scan_data -> IR_val_arr[i] > 50 || i==0 || i==1 || i==2){
      continue;
    }
    //object first detection
    else{
      int j;
      for(j=i+1; j<=90; j+=1){
        int h = j;
        if((full_scan_data -> IR_val_arr[j] > 50 && h - i > 3) || j == 90){
          //i is the first angle the object was detected
          //j-1 is the last angle the object was detected

          //finding open object memory
          int k;
          for(k=0; k <= 7; k+=1){
            
            if(full_scan_data -> obj_num[k] == 0){
              //objects numbered 1-8
              full_scan_data -> obj_num[k] = k + 1;

              int first_angle = i;
              int last_angle = j - 1;

              full_scan_data -> obj_fir_angle[k] = first_angle;
              full_scan_data -> obj_las_angle[k] = last_angle;
              
              int angle_difference = ((last_angle) - first_angle);
              int middle_angle_array = (first_angle + (angle_difference/2));

              full_scan_data -> obj_mid_angle[k] = (2 * middle_angle_array);

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

// gaining more information on objects with PING))) sensor
void find_objects_full(full_scan_data_t *full_scan_data){
  int k;
  for(k=0; k <= 7; k+=1){
    if(full_scan_data -> obj_num[k] != 0){

      int first_angle = full_scan_data -> obj_fir_angle[k];
      int last_angle = full_scan_data -> obj_las_angle[k];
      int angle_difference = ((last_angle) - first_angle);
      int middle_angle_array = (first_angle + (angle_difference/2));

      full_scan_data -> obj_dist[k] = full_scan_data -> sound_dist_arr[middle_angle_array];
      full_scan_data -> obj_IR_dist[k] = full_scan_data -> IR_val_arr[middle_angle_array];
      full_scan_data -> obj_radial_len[k] = (2 * angle_difference);
      //full_scan_data -> obj_width[k] = ( (2*angle_difference) / 360.0 )*( full_scan_data -> IR_val_arr[middle_angle_array] )*2*3.1415926;
      full_scan_data -> obj_width[k] = ( (2*angle_difference) / 360.0 )*( full_scan_data -> sound_dist_arr[middle_angle_array] )*2*3.1415926;

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
      self -> obj_mid_angle[i] = 0;
      self -> obj_fir_angle[i] = 0;
      self -> obj_las_angle[i] = 0;
      self -> obj_dist[i] = 0;
      self -> obj_IR_dist[i] = 0;
      self -> obj_radial_len[i] = 0;
      self -> obj_width[i] = 0;
    }
  }
}




//--------------------------------------------------------------------- sending info to putty

// prints individual scan data to PuTTY 
void scan_send(full_scan_data_t *full_scan_data, int deg){
  sendBytesInt("Degrees: ", deg);
  uart_sendChar('\t');
  sendBytes("Distance: ", full_scan_data -> sound_dist_arr[deg/2]);
  uart_sendChar('\t');
  sendBytes("IR raw: ", full_scan_data -> IR_raw_val_arr[deg/2]);
  uart_sendChar('\t');
  sendBytes("IR: ", full_scan_data -> IR_val_arr[deg/2]);
  uart_sendChar('\r');
  uart_sendChar('\n');
}

// prints all values in our data struct to PuTTY
void full_scan_data_send(full_scan_data_t *self){
  int i;
  for(i=0; i <= 90; i+=1){
      sendBytesInt("Degrees: ", i*2);
    uart_sendChar('\t');
    sendBytes("Distance: ", self -> sound_dist_arr[i]);
    uart_sendChar('\t');
    sendBytes("IR raw: ", self -> IR_raw_val_arr[i]);
    uart_sendChar('\t');
    sendBytes("IR: ", self -> IR_val_arr[i]);
    uart_sendChar('\r');
    uart_sendChar('\n');
  }
  uart_sendChar('\r');
  uart_sendChar('\n');
}

// prints object information to PuTTY
void object_data_send(full_scan_data_t *self){
    int i;
    for(i=0; i <= 7; i+=1){
        sendBytesInt("Obj num: ", self -> obj_num[i]);
        uart_sendChar('\t');
        sendBytesInt("angle: ", self -> obj_mid_angle[i]);
        uart_sendChar('\t');
        sendBytes("dist: ", self -> obj_dist[i]);
        uart_sendChar('\t');
        sendBytes("IR_dist: ", self -> obj_IR_dist[i]);
        uart_sendChar('\t');
        sendBytesInt("radial: ", self -> obj_radial_len[i]);
        uart_sendChar('\t');
        sendBytes("width: ", self -> obj_width[i]);
        uart_sendChar('\r');
        uart_sendChar('\n');
    }
    //spacing/format in PuTTY terminal
    uart_sendChar('\r');
    uart_sendChar('\n');
}




//------------------------------------------------------------------- logic after scan

// finds the smallest object of detected objects
int smallest_object(full_scan_data_t *self){
  int sml_obj = -1;
  int i;
  if(self -> obj_num[0] != 0)
  {
      sml_obj = 0;
      for (i=1; i <= 7; i+=1)
        {
          if(self -> obj_num[i] != 0){
            if(self -> obj_width[i] < self -> obj_width[sml_obj]){

              sml_obj = i;
            }
          }
        }
  }
  // pointing CyBot sensor at smallest object
  servos_move(self -> obj_mid_angle[sml_obj]);
  //cyBOT_Scan(self -> obj_mid_angle[sml_obj], scan_data);
  return sml_obj;
}

// finds the closest object of detected objects
int closest_object(full_scan_data_t *self){
  int clos_obj = 0;
  int i;
  for (i=0; i <= 7; i+=1)
  {
    if(self -> obj_num[i] != 0){
      if(self -> obj_dist[i] < self -> obj_dist[clos_obj]){

          clos_obj = i;
      }
    }
  }
  // pointing CyBot sensor at smallest object
  servos_move(self -> obj_mid_angle[clos_obj]);
  //cyBOT_Scan(self -> obj_mid_angle[sml_obj], scan_data);
  return clos_obj;
}

// finds the amount of pillars from scan
int sml_objs_count(full_scan_data_t *self){
  int sml_objs = 0;
  int i;
  for (i=0; i <= 7; i+=1)
  {
    if(self -> obj_num[i] != 0){
      if(self -> obj_width[i] < 6){
          sml_objs += 1;
      }
    }
  }
  return sml_objs;
}

// finds the pillars' object numbers from scan in array
void sml_objs_nums_arr(full_scan_data_t *self, int sml_objs, int arr[]){
  //int sml_objs_nums[sml_objs];
  int i;
  int j = 0;
  for (i=0; i <= 7; i+=1)
  {
    if(self -> obj_num[i] != 0){
      if(self -> obj_width[i] < 6){
          arr[j] = self -> obj_num[i];
          j += 1;
      }
    }
  }
}

//void controlled_driving(full_scan_data_t *self, oi_t *sensor_data, int sml_obj){
//  char ch = 'o';
//  while(ch != 'q'){
//    //ch = uart_receive();
//    if(ch == 'w'){
//      move_forward_spd(sensor_data, 50, 75);
//    }
//    if(ch == 'x'){
//      move_backward_spd(sensor_data, 50, -75);
//    }
//    if(ch == 'a'){
//      turn_left(sensor_data, 30);
//    }
//    if(ch == 'd'){
//      turn_right(sensor_data, 30);
//    }
//    if(ch == 'm'){
//      scan_path(self);
//    }
//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        auto_driving(self, sensor_data, sml_obj);
//    }
//    ch = uart_receive();
//  }
//}

//int auto_driving(full_scan_data_t *self, oi_t *sensor_data, int sml_obj){
//    int mid_ang = self -> obj_mid_angle[sml_obj];
//    if(mid_ang > 92){
//        turn_left(sensor_data, mid_ang - 90);
//    }
//    else if(mid_ang < 88){
//        turn_right(sensor_data, 90 - mid_ang);
//    }
//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        return 0;
//    }
//    int tog = 0;
//    tog = auto_forward(sensor_data, (10*((self -> obj_dist[sml_obj]) - 10)), 75);
//    if(tog == 1){
//        return 0;
//    }
//    return 0;
//
//}

void turning_init(oi_t *sensor_data){
    turn_left(sensor_data, 90);
    turn_left(sensor_data, 90);
    turn_left(sensor_data, 90);
    turn_left(sensor_data, 90);
    timer_waitMillis(7000);
    turn_right(sensor_data, 90);
    turn_right(sensor_data, 90);
    turn_right(sensor_data, 90);
    turn_right(sensor_data, 90);
}

// void ir_init_output(oi_t *sensor_data, cyBOT_Scan_t *scan_data){
//     int i;
//     int distance = 0;
//     move_backward_spd(sensor_data, 80, -50);
//     for(i=0; i<45; i++){
//         cyBOT_Scan(90, scan_data);
//         sendBytes("", scan_data -> IR_raw_val);
//         uart_sendChar('\t');
//         sendBytes("", distance);
//         uart_sendChar('\r');
//         uart_sendChar('\n');

//         move_backward_spd(sensor_data, 10, -50);
//         distance += 1;
//     }
// }

void sound()
{
    unsigned char notes[] = {88, 88, 88, 88, 88, 88, 88, 76, 87, 87, 87, 75, 97, 97, 97, 73, 93, 93, 92, 88};
    unsigned char duration[] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
    oi_loadSong(0, 20, notes, duration);
    oi_play_song(0);
}



void sound () {
    //oi_loadSong(int song_index, int num_notes, unsigned char *notes, unsigned char *duration);
    //oi_play_song(int index);
    //unsigned char notes[] = {60,62};
    //unsigned char duration[] = {16,16};
   
    unsigned char notes[] = {88,88,88,88,88,88,88,76,87,87,87,75,97,97,97,73,93,93,92,88};
    unsigned char duration[] = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};
   
    //oi_loadSong(0, 2, notes, duration);
    oi_loadSong(0, 20, notes, duration);
    oi_play_song(0);

    //return 0;

}


void cliff_detection (oi_t *sensor_data) {
    int cliff_left = 0;
    int cliff_front_left = 0;
    int cliff_front_right = 0;
    int cliff_right = 0;

    while (1) {
        oi_update(sensor_data);
        cliff_left = sensor_data -> cliffLeft;
        cliff_front_left = sensor_data -> cliffFrontLeft;
        cliff_front_right = sensor_data -> cliffFrontRight;
        cliff_right = sensor_data -> cliffRight;

        if (cliff_left == 1) {
            lcd_printf ("cliffLeft");
        }

        else if (cliff_front_left == 1) {
            lcd_printf ("cliffFrontLeft");
        }

        else if (cliff_front_right == 1) {
            lcd_printf ("cliffFrontRight");
        }

        else if (cliff_right == 1) {
            lcd_printf ("cliffRight");
        }
        else {
            lcd_printf ("Nada");
        }
    }
    //return;
}

