/*
 * final.c
 *
 *  Created on: Apr 21, 2024
 *      Author: coreybh
 */
#include <math.h>
#include "final.h"
#define _USE_MATH_DEFINES


int scan(full_scan_data_t *full_scan_data){
    scan_path(full_scan_data);
    scan_objs(full_scan_data);
    int sml_obj = 0;
    sml_obj = smallest_object(full_scan_data);
    return sml_obj;
}


void controlled_driving(full_scan_data_t *self, oi_t *sensor_data){
  //char ch = 'o';
  while(command_byte != 'q'){
    //ch = uart_receive();
    if(command_byte == 'w'){
      move_forward_spd(sensor_data, 50, 75);
    }
    if(command_byte == 'x'){
      move_backward_spd(sensor_data, 50, -75);
    }
    if(command_byte == 'a'){
      turn_left(sensor_data, 30);
    }
    if(command_byte == 'd'){
      turn_right(sensor_data, 30);
    }
    if(command_byte == 'm'){
      scan_path(self);
    }
    if(command_flag_toggle == 1){
        command_flag_toggle = 0;
        autonomous(self, sensor_data);
    }











    ////////////////////////////////////////////////////// SHANE CODE IDK IF IT WORKS
    double distance_travelled = 0;
    double angle_travelled = 0;
    oi_update(sensor_data);
    distance_travelled += sensor_data -> distance;
    angle_travelled += sensor_data -> angle;
    sendBytes("Distance traveled: %s",distance_travelled)
    sendBytes("Angle traveled: %s",angle_travelled)


    bump_left = sensor_data -> bumpLeft;
    bump_right = sensor_data -> bumpRight;

    if(bump_left == 1) {
      sendBytes("FUCK, short obstacle on da left")
    }

    else if(bump_right == 1) {
      sendBytes("FUCK, short obstacle on da right")
    }




    cliff_left = sensor_data -> cliffLeft;
    cliff_front_left = sensor_data -> cliffFrontLeft;
    cliffFrontRight = sensor_data -> cliffFrontRight;
    cliffRight = sensor_data -> cliffRight;

    if(cliff_left == 1) {
      sendBytes("FUCK, cliff on da left")
    }

    else if(cliff_front_left == 1) {
      sendBytes("FUCK, cliff on da front left")
    }

    else if(cliffFrontRight == 1) {
      sendBytes("FUCK, cliff on da front right")
    }

    else if(cliffRight == 1) {
      sendBytes("FUCK, cliff on da right")
    }
    ////////////////////////////////////////////////////// SHANE CODE IDK IF IT WORKS














    command_byte = 'o';
    //ch = uart_receive();
  }
}

void autonomous(full_scan_data_t *self, oi_t *sensor_data)
{
    int tog = 0;
    while(tog != 1)
    {
        int sml_obj = scan(self);
        int sml_obj_count = sml_objs_count(self);
        int sml_obj_arr[sml_obj_count];


        sml_objs_nums_arr(self, sml_obj_count, sml_obj_arr);


        if(sml_obj == -1)
        {
            tog = auto_forward(sensor_data, (300), 75);
        }
        else if(sml_obj_count == 1)
        {
            tog = auto_drive_sml_obj(self, sensor_data, sml_obj);
        }
        else if(sml_obj_count > 1)
        {
            tog = sml_obj_positioning(self, sensor_data, sml_obj, sml_obj_arr);
        }
        else
        {
            //tog = auto_drive_away(self, sensor_data);
            tog = auto_drive_trig(self, sensor_data);
        }
        if(command_flag_toggle == 1){
            command_flag_toggle = 0;
            tog=1;
        }
    }
}


int sml_obj_positioning(full_scan_data_t *self, oi_t *sensor_data, int sml_obj, int sml_obj_arr[]){
    int mid_ang = self -> obj_mid_angle[sml_obj];
    if(mid_ang > 92){
        turn_left(sensor_data, mid_ang - 90);
    }
    else if(mid_ang < 88){
        turn_right(sensor_data, 90 - mid_ang);
    }

    float h = 0;
    float d = 0;
    if(self -> obj_dist[sml_obj_arr[0]] > self -> obj_dist[sml_obj_arr[1]]){
        h = self -> obj_dist[sml_obj_arr[0]];
        d = self -> obj_dist[sml_obj_arr[1]];
    }
    else{
        d = self -> obj_dist[sml_obj_arr[0]];
        h = self -> obj_dist[sml_obj_arr[1]];
    }
    float ang = (abs((self -> obj_mid_angle[sml_obj_arr[0]]) - (self -> obj_mid_angle[sml_obj_arr[1]])))*(M_PI /180);
    float Y =sqrt(pow(h,2)+pow(d,2)-2*d*h*cosf(ang))/2;
    float sigma = acos((pow(h,2)+pow(Y,2)-pow(d, 2))/(2*h*Y));
    float h_dist = (Y)/(cos(sigma));
    float drive_dist = h - h_dist;

    if(command_flag_toggle == 1){
        command_flag_toggle = 0;
        return 1;
    }
    int tog = 0;
    tog = auto_forward(sensor_data, (10*drive_dist), 45);

    return tog;

}

int auto_drive_sml_obj(full_scan_data_t *self, oi_t *sensor_data, int sml_obj){
    int mid_ang = self -> obj_mid_angle[sml_obj];
    if(mid_ang > 92){
        turn_left(sensor_data, mid_ang - 90);
    }
    else if(mid_ang < 88){
        turn_right(sensor_data, 90 - mid_ang);
    }
    if(command_flag_toggle == 1){
        command_flag_toggle = 0;
        return 1;
    }
    int tog = 0;
    tog = auto_forward(sensor_data, (10*((self -> obj_dist[sml_obj])/3)), 75);
    return tog;

}

int auto_drive_trig(full_scan_data_t *self, oi_t *sensor_data){
    int tog = 0;
    int clos_obj = closest_object(self);
    int mid_ang = self -> obj_mid_angle[clos_obj];
    float close_obj_dist = self -> obj_dist[clos_obj];
    float dist_to_drive = close_obj_dist * 10;








    if(command_flag_toggle == 1 || tog == 1){
        command_flag_toggle = 0;
        return 1;
    }
    return 0;
}

int auto_drive_away(full_scan_data_t *self, oi_t *sensor_data){
    int clos_obj = closest_object(self);
    int mid_ang = self -> obj_mid_angle[clos_obj];
    float close_obj_dist = self -> obj_dist[clos_obj];
    float dist_to_drive = close_obj_dist * 10;
    if(close_obj_dist > 300){
        close_obj_dist -= 200;
    }
    else{
        close_obj_dist -= 100;
    }

    int tog = 0;
    if(mid_ang < 45 && close_obj_dist > 30)
    {
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang < 45)
    {
        turn_left(sensor_data, 30);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang < 90 && close_obj_dist >30)
    {
        turn_left(sensor_data, 25);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang < 90)
    {
        turn_left(sensor_data, 50);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang >= 90 && close_obj_dist >30)
    {
        turn_right(sensor_data, 25);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang >= 90)
    {
        turn_right(sensor_data, 50);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang > 135  && close_obj_dist > 30)
    {
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }
    else if(mid_ang > 135)
    {
        turn_right(sensor_data, 30);
        tog = auto_forward(sensor_data, dist_to_drive , 75);
    }

    if(command_flag_toggle == 1 || tog == 1){
        command_flag_toggle = 0;
        return 1;
    }
    return 0;
}

