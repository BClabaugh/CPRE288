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
    //scan_objs(full_scan_data);
    int sml_obj = 0;
    sml_obj = smallest_object(full_scan_data);
    return sml_obj;
}




//void controlled_driving(full_scan_data_t *self, oi_t *sensor_data){
//  //char ch = 'o';
//  while(command_byte != 'p'){
//    //ch = uart_receive();
//    if(command_byte == 'w'){
//        //sendBytes("\r\nForward\r\n", -10000);
//      //move_forward_spd(sensor_data, 50, 75);
//      auto_forward(sensor_data, 50, 75);
//    }
//    if(command_byte == 's'){
//        //sendBytes("\r\nBackward\r\n", -10000);
//      //move_backward_spd(sensor_data, 50, -75);
//      auto_forward(sensor_data, 50, -75);
//    }
//    if(command_byte == 'a'){
//        //sendBytes("\r\nTurn Left\r\n", -10000);
//      turn_left(sensor_data, 60);
//    }
//    if(command_byte == 'd'){
//        //sendBytes("\r\nTurn Right\r\n", -10000);
//      turn_right(sensor_data, 45);
//    }
//    if(command_byte == 'm'){
//        //sendBytes("\r\nScan\r\n", -10000);
//        scan(self);
//    }
//    if(command_byte == 'x'){
//        //sendBytes("\r\nSound\r\n", -10000);
//        sound();
//
//    }
//    if(command_byte == 'y'){
//        scan(self);
//    }
//
//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        autonomous(self, sensor_data);
//    }
//    command_byte = 'o';
//    //ch = uart_receive();
//  }
//}


//polling-------------------------------------------------------------------------------------------------------
void controlled_driving(full_scan_data_t *self, oi_t *sensor_data){
  char ch = 'o';
  while(ch != 'p'){
    //ch = uart_receive();
    if(ch == 'w'){
        //sendBytes(" Forw\n", -10000);
      //move_forward_spd(sensor_data, 50, 75);
      auto_forward(sensor_data, 100, 75, 90);
      //sendBytes(" Forward\n", -10000);
    }
    else if(ch == 's'){
        //sendBytes(" Back\n", -10000);
      //move_backward_spd(sensor_data, 50, -75);
      auto_forward(sensor_data, 50, -75, -75);
      //sendBytes(" Back\n", -10000);
    }
    else if(ch == 'a'){
        //sendBytes("Left\n", -10000);
      turn_left(sensor_data, 30);
      //sendBytes("Left\n", -10000);
    }
    else if(ch == 'd'){
        //sendBytes("Right\n", -10000);
      turn_right(sensor_data, 45);
      //sendBytes("Right\n", -10000);
    }
    else if(ch == 'm'){
        //sendBytes("Scan\n", -10000);
        scan(self);
        //sendBytes("Scan\n", -10000);
    }
    else if(ch == 'x'){
        //sendBytes("Sound\n", -10000);
        sound();
        //sendBytes("Sound\n", -10000);
    }
    else if(ch == 'y'){
        scan(self);
    }
//    timer_waitMillis(1000);
//    else {
//        sendBytes("Error\n", -10000);
//        //timer_waitMillis(1500);
//        //sendBytes("Error\n", -10000);
//    }

//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        autonomous(self, sensor_data);
//    }
    command_byte = 'o';
    ch = uart_receive();
  }
}



//void autonomous(full_scan_data_t *self, oi_t *sensor_data)
//{
//    int tog = 0;
//    while(tog != 1)
//    {
//        int sml_obj = scan(self);
//        int sml_obj_count = sml_objs_count(self);
//        //int sml_obj_arr[sml_obj_count];
//        int obj_count = objs_count(self);
//        //sml_objs_nums_arr(self, sml_obj_count, sml_obj_arr);
//
//
//        if(objs_count == 0)
//        {
//            sendBytes("No Objects Detected", -10000);
//            tog = auto_forward(sensor_data, (300), 75);
//        }
//        else if(sml_obj_count == 1)
//        {
//            sendBytes("One Pillar detected", -10000);
//            tog = auto_drive_sml_obj(self, sensor_data, sml_obj);
//        }
//        else if(sml_obj_count > 1)
//        {
//            sendBytes("More than one Pillar detected", -10000);
//            //figuring out the closest 2 small objects
//            int closest_sml = 0;
//            int closest_sml2 = 1;
//            if((self -> obj_dist[closest_sml2]) > (self -> obj_dist[closest_sml])){
//                closest_sml = 1;
//                closest_sml2 = 0;
//            }
//            if(sml_obj_count > 2)
//            {
//                sendBytes("More than two Pillar detected", -10000);
//                int i;
//                for(i = 2; i < sml_obj_count; i+=1)
//                {
//                    if((self -> obj_dist[i]) < (self -> obj_dist[closest_sml])){
//                        closest_sml2 = closest_sml;
//                        closest_sml = i;
//                    }
//                    else if((self -> obj_dist[i]) < (self -> obj_dist[closest_sml2])){
//                        closest_sml2 = i;
//                    }
//                }
//            }
//
//            if( abs((self -> obj_dist[closest_sml2]) - (self -> obj_dist[closest_sml])) > 8 ){
//                //need positioning
//                sendBytes("Positioning Needed", -10000);
//                tog = sml_obj_positioning(self, sensor_data, closest_sml, closest_sml2);
//            }
//            else{
//                //entering destination
//                sendBytes("Entering Destination", -10000);
//                tog = into_dest(self, sensor_data, closest_sml, closest_sml2);
//            }
//        }
//        else if(obj_count == 1)
//        {
//            sendBytes("One Object Detected", -10000);
//            tog = auto_drive_trig_oneOBJ(self, sensor_data);
//        }
//        else if(obj_count > 1)
//        {
//            sendBytes("More than One Object Detected", -10000);
//            //tog = auto_drive_trig_twoOBJ(self, sensor_data);
//            tog = auto_drive_trig_oneOBJ(self, sensor_data);
//        }
//        else{
//            sendBytes("IDK, Never should be here", -10000);
//            turn_right(sensor_data, 30);
//        }
//
//        if(command_flag_toggle == 1){
//            command_flag_toggle = 0;
//            tog=1;
//        }
//    }
//}
//
//
////int sml_obj_positioning(full_scan_data_t *self, oi_t *sensor_data, int sml_obj, int sml_obj_arr[]){
//int sml_obj_positioning(full_scan_data_t *self, oi_t *sensor_data, int closest_sml, int closest_sml2){
//    float h = self -> obj_dist[closest_sml2];
//    float d = self -> obj_dist[closest_sml];
//
////    if(self -> obj_dist[sml_obj_arr[0]] > self -> obj_dist[sml_obj_arr[1]]){
////        h = self -> obj_dist[sml_obj_arr[0]];
////        d = self -> obj_dist[sml_obj_arr[1]];
////    }
////    else{
////        d = self -> obj_dist[sml_obj_arr[0]];
////        h = self -> obj_dist[sml_obj_arr[1]];
////    }
////    float ang = (abs((self -> obj_mid_angle[sml_obj_arr[0]]) - (self -> obj_mid_angle[sml_obj_arr[1]])))*(M_PI /180);
//    float ang = (abs((self -> obj_mid_angle[closest_sml]) - (self -> obj_mid_angle[closest_sml2])))*(M_PI /180);
//    float Y =sqrt(pow(h,2)+pow(d,2)-2*d*h*cosf(ang))/2;
//    float sigma = acos((pow(h,2)+pow(Y,2)-pow(d, 2))/(2*h*Y));
//    float h_dist = (Y)/(cos(sigma));
//    float drive_dist = h - h_dist;
//
//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        return 1;
//    }
//    int tog = 0;
//    tog = auto_forward(sensor_data, (10*drive_dist), 45);
//
//    return tog;
//
//}
//
////int sml_obj_positioning(full_scan_data_t *self, oi_t *sensor_data, int sml_obj, int sml_obj_arr[]){
//int into_dest(full_scan_data_t *self, oi_t *sensor_data, int closest_sml, int closest_sml2){
//    int mid_ang = self -> obj_mid_angle[closest_sml];
//    int mid_ang2 = self -> obj_mid_angle[closest_sml2];
//
//    int big_theta;
//    int ang_to_turn;
//    if(mid_ang > mid_ang2)
//    {
//        big_theta = mid_ang - mid_ang2;
//        ang_to_turn = mid_ang2 + (big_theta / 2);
//    }
//    else{
//        big_theta = mid_ang2 - mid_ang;
//        ang_to_turn = mid_ang + (big_theta / 2);
//    }
//
//    float dist_to_drive =sqrt(  pow(20,2) +  pow((self -> obj_dist[closest_sml2]),2)  );
//
//    if((ang_to_turn < 90))
//    {
//        //turn right
//        turn_right(sensor_data, (90 - ang_to_turn));
//        auto_forward(sensor_data, ((dist_to_drive +40)*10), 45);
//    }
//    else if((ang_to_turn > 90))
//    {
//        //turn left
//        turn_left(sensor_data, (ang_to_turn - 90));
//        auto_forward(sensor_data, ((dist_to_drive + 40)*10), 45);
//    }
//
//    sound();
//    return 1;
//
//}
//
//int auto_drive_sml_obj(full_scan_data_t *self, oi_t *sensor_data, int sml_obj){
//    int mid_ang = self -> obj_mid_angle[sml_obj];
//    if(mid_ang > 92){
//        turn_left(sensor_data, mid_ang - 90);
//    }
//    else if(mid_ang < 88){
//        turn_right(sensor_data, 90 - mid_ang);
//    }
//    if(command_flag_toggle == 1){
//        command_flag_toggle = 0;
//        return 1;
//    }
//    int tog = 0;
//    if(self -> obj_dist[sml_obj] > 20){
//        tog = auto_forward(sensor_data, (10*((self -> obj_dist[sml_obj])/3)), 75);
//    }
//    return tog;
//
//}
//
//int auto_drive_trig_oneOBJ(full_scan_data_t *self, oi_t *sensor_data){
//    //sendBytes("Starting Math", -10000);
//    int tog = 0;
//    int clos_obj = closest_object(self);
//    int mid_ang = self -> obj_mid_angle[clos_obj];
//    //sendBytes("Doing Math 1", -10000);
//    float close_obj_dist = self -> obj_dist[clos_obj];
//    float dist_to_drive = close_obj_dist * 10;
//
//    //sendBytes("Doing Math 2", -10000);
//
//    float theta = asin(30/close_obj_dist);
//
//    uart_sendChar('\r');
//    uart_sendChar('\n');
//    sendBytes("Math Complete\r\n", -10000);
//    sendBytes("distance to ride: ", dist_to_drive);
//    uart_sendChar('\r');
//    uart_sendChar('\n');
//
//    if(mid_ang < 90 && (mid_ang+theta) < 90)
//    {
//        //drive straight
//        sendBytes("Driving Straight", -10000);
//        tog = auto_forward(sensor_data, dist_to_drive, 45);
//    }
//    else if(mid_ang > 90 && (mid_ang-theta) > 90)
//    {
//        sendBytes("Driving Straight", -10000);
//        //drive straight
//        tog = auto_forward(sensor_data, dist_to_drive, 45);
//    }
//    else if(mid_ang <= 90)
//    {
//        sendBytes("Turn left", -10000);
//        //turn left
//        turn_left(sensor_data, (mid_ang + theta - 90));
//        tog = auto_forward(sensor_data, dist_to_drive, 45);
//    }
//    else if(mid_ang > 90)
//    {
//        sendBytes("Turn right", -10000);
//        //turn right
//        turn_right(sensor_data, (mid_ang - theta));
//        tog = auto_forward(sensor_data, dist_to_drive, 45);
//    }
//    else{
//        sendBytes("IDK, shouldnt get here", -10000);
//        turn_right(sensor_data, 30);
//    }
//    if(command_flag_toggle == 1 || tog == 1){
//        command_flag_toggle = 0;
//        return 1;
//    }
//    sendBytes("Complete One Object Avoidance", -10000);
//    return 0;
//}
//
//int auto_drive_trig_twoOBJ(full_scan_data_t *self, oi_t *sensor_data){
//    int tog = 0;
//    int clos_obj = closest_object(self);
//    int mid_ang = self -> obj_mid_angle[clos_obj];
//    float close_obj_dist = self -> obj_dist[clos_obj];
//    float dist_to_drive = close_obj_dist * 10;
//
//    int clos_obj2 = closest_2nd_object(self, clos_obj);
//    int mid_ang2 = self -> obj_mid_angle[clos_obj2];
//    float close_obj_dist2 = self -> obj_dist[clos_obj2];
//    float dist_to_drive2 = close_obj_dist2 * 10;
//
//    float theta = asin(22/close_obj_dist);
//    float theta2 = asin(22/close_obj_dist2);
//
//    int big_theta = 0;
//    int ang_to_turn = 0;
//    if(mid_ang > mid_ang2)
//    {
//        big_theta = mid_ang - mid_ang2;
//        ang_to_turn  = mid_ang2 + (big_theta / 2);
//
//    }
//    else{
//        big_theta = mid_ang2 - mid_ang;
//        ang_to_turn  = mid_ang + (big_theta / 2);
//    }
//
//    bool shootTheGap = false;
//
//    if(big_theta > (theta + theta2))
//    {
//        shootTheGap = true;
//    }
//
//    if(shootTheGap && (ang_to_turn < 90))
//    {
//        //turn right
//        turn_right(sensor_data, (90 - ang_to_turn));
//        tog = auto_forward(sensor_data, ((dist_to_drive + dist_to_drive2)/2), 45);
//    }
//    else if(shootTheGap && (ang_to_turn > 90))
//    {
//        //turn left
//        turn_left(sensor_data, (ang_to_turn - 90));
//        tog = auto_forward(sensor_data, ((dist_to_drive + dist_to_drive2)/2), 45);
//    }
//    else if(!shootTheGap && (abs(mid_ang - 90) > abs(mid_ang2 - 90)) )
//    {
//        // mid_ang2 is closed to the center --------------------------------------------------
//        if(mid_ang > mid_ang2)
//        {
//            //turn right
//            if(mid_ang2 < 90){
//                if((mid_ang2 - theta2) > 90){
//                    //no need to turn
//                    tog = auto_forward(sensor_data, dist_to_drive2, 45);
//                }
//                else{
//                    //turn right
//                    turn_right(sensor_data, ((90 - mid_ang2) + theta2));
//                    tog = auto_forward(sensor_data, dist_to_drive2, 45);
//                }
//            }
//            else{
//                turn_right(sensor_data, (theta2 - (mid_ang2 - 90)));
//                tog = auto_forward(sensor_data, dist_to_drive2, 45);
//            }
//        }
//        else{
//            //turn left
//            if(mid_ang2 < 90){
//                if((mid_ang2 + theta2) < 90){
//                    //no need to turn
//                    tog = auto_forward(sensor_data, dist_to_drive2, 45);
//                }
//                else{
//                    //turn left
//                    turn_left(sensor_data, (theta2 - (90 - mid_ang2)));
//                    tog = auto_forward(sensor_data, dist_to_drive2, 45);
//                }
//            }
//            else{
//                turn_left(sensor_data, (theta2 + (mid_ang2 - 90)));
//                tog = auto_forward(sensor_data, dist_to_drive2, 45);
//            }
//        }
//    }
//    else if(!shootTheGap && (abs(mid_ang - 90) < abs(mid_ang2 - 90)))
//    {
//        // mid_ang is closed to the center -----------------------------------------
//        if(mid_ang < mid_ang2)
//        {
//            //turn right
//            if(mid_ang < 90){
//                if((mid_ang - theta) > 90){
//                    //no need to turn
//                    tog = auto_forward(sensor_data, dist_to_drive, 45);
//                }
//                else{
//                    //turn right
//                    turn_right(sensor_data, ((90 - mid_ang) + theta));
//                    tog = auto_forward(sensor_data, dist_to_drive, 45);
//                }
//            }
//            else{
//                turn_right(sensor_data, (theta - (mid_ang - 90)));
//                tog = auto_forward(sensor_data, dist_to_drive, 45);
//            }
//        }
//        else{
//            //turn left
//            if(mid_ang2 < 90){
//                if((mid_ang2 + theta) < 90){
//                    //no need to turn
//                    tog = auto_forward(sensor_data, dist_to_drive, 45);
//                }
//                else{
//                    //turn left
//                    turn_left(sensor_data, (theta - (90 - mid_ang)));
//                    tog = auto_forward(sensor_data, dist_to_drive, 45);
//                }
//            }
//            else{
//                turn_left(sensor_data, (theta + (mid_ang - 90)));
//                tog = auto_forward(sensor_data, dist_to_drive, 45);
//            }
//        }
//    }
//    else{
//        turn_right(sensor_data, 30);
//    }
//
//    if(command_flag_toggle == 1 || tog == 1){
//        command_flag_toggle = 0;
//        return 1;
//    }
//    return 0;
//}

//int auto_drive_away(full_scan_data_t *self, oi_t *sensor_data){
//    int clos_obj = closest_object(self);
//    int mid_ang = self -> obj_mid_angle[clos_obj];
//    float close_obj_dist = self -> obj_dist[clos_obj];
//    float dist_to_drive = close_obj_dist * 10;
//    if(close_obj_dist > 300){
//        close_obj_dist -= 200;
//    }
//    else{
//        close_obj_dist -= 100;
//    }
//
//    int tog = 0;
//    if(mid_ang < 45 && close_obj_dist > 30)
//    {
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang < 45)
//    {
//        turn_left(sensor_data, 30);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang < 90 && close_obj_dist >30)
//    {
//        turn_left(sensor_data, 25);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang < 90)
//    {
//        turn_left(sensor_data, 50);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang >= 90 && close_obj_dist >30)
//    {
//        turn_right(sensor_data, 25);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang >= 90)
//    {
//        turn_right(sensor_data, 50);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang > 135  && close_obj_dist > 30)
//    {
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//    else if(mid_ang > 135)
//    {
//        turn_right(sensor_data, 30);
//        tog = auto_forward(sensor_data, dist_to_drive , 75);
//    }
//
//    if(command_flag_toggle == 1 || tog == 1){
//        command_flag_toggle = 0;
//        return 1;
//    }
//    return 0;
//}

