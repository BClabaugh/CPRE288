
/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: clab22
 */


#include "open_interface.h"
#include "math.h"
#include "uart-interrupt.h"
#include "lcd.h"
#include "functions.h"



void move_forward(oi_t *sensor_data, double distance_mm){
  double sum = 0;
  oi_setWheels(300,300);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    //other maybe better way to calculate distance traveled
    sum += sensor_data -> distance;
  }
  oi_setWheels(0,0);
}

void move_forward_spd(oi_t *sensor_data, double distance_mm, int spd){
  double sum = 0;
  oi_setWheels(spd,spd);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    //other maybe better way to calculate distance traveled
    sum += sensor_data -> distance;
  }
  oi_setWheels(0,0);
}

void move_backward(oi_t *sensor_data, double distance_mm){
  double sum = 0;
  oi_setWheels(-100,-100);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    sum += abs(sensor_data -> distance);
  }
  oi_setWheels(0,0);
}

void move_backward_spd(oi_t *sensor_data, double distance_mm, int spd){
  double sum = 0;
  oi_setWheels(spd,spd);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    sum += abs(sensor_data -> distance);
  }
  oi_setWheels(0,0);
}

void turn_right(oi_t *sensor_data, double degrees){
  double sum = 0;
  int offset = 13; //27.5
  oi_setWheels(-100,100);
  while(sum <= degrees - offset){
    oi_update(sensor_data);
    sum += abs(sensor_data -> angle);
  }
  oi_setWheels(0,0);
}

void turn_right_spd(oi_t *sensor_data, double degrees, int spd){
  double sum = 0;
  int offset = 0;
  oi_setWheels(((-1)*spd), spd);
  while(sum <= degrees - offset){
    oi_update(sensor_data);
    sum += abs(sensor_data -> angle);
  }
  oi_setWheels(0,0);
}

void turn_left(oi_t *sensor_data, double degrees){
  int offset = 4;
  double sum = 0;
  oi_setWheels(100,-100);
  while(sum <= degrees - offset){
    oi_update(sensor_data);
    sum += sensor_data -> angle;
  }
  oi_setWheels(0,0);
}

void turn_left_spd(oi_t *sensor_data, double degrees, int spd){
  double sum = 0;
  int offset = 0;
  oi_setWheels(spd,(spd*(-1)));
  while(sum <= degrees - offset){
    oi_update(sensor_data);
    sum += sensor_data -> angle;
  }
  oi_setWheels(0,0);
}

void square(oi_t *sensor_data){
  move_forward(sensor_data, 500);
  turn_right(sensor_data, 90);

  move_forward(sensor_data, 500);
  turn_right(sensor_data, 90);

  move_forward(sensor_data, 500);
  turn_right(sensor_data, 90);

  move_forward(sensor_data, 500);
  turn_right(sensor_data, 90);
}

// direction: false = turn left and true = turn right
void avoidance(oi_t *sensor_data, bool direction){
  move_backward_spd(sensor_data, 150, -75);
//  if(!direction){
//    turn_right(sensor_data, 90);
//    move_forward_spd(sensor_data, 250, 75);
//    turn_left(sensor_data, 90);
//  }
//  if(direction){
//    turn_left(sensor_data, 90);
//    move_forward_spd(sensor_data, 250, 75);
//    turn_right(sensor_data, 90);
//  }
  //move_forward_spd(sensor_data, 150, 75);
  oi_setWheels(0,0);
}

void cliff_avoidance(oi_t *sensor_data, int direction){
  move_backward_spd(sensor_data, 150, -75);
//  if(direction==1){
//    turn_right(sensor_data, 90);
//  }
//  if(direction==2){
//    turn_right(sensor_data, 160);
//  }
//  if(direction==3){
//    turn_left(sensor_data, 160);
//  }
//  if(direction==4){
//    turn_left(sensor_data, 90);
//  }
  //move_forward_spd(sensor_data, 150, 75);
  oi_setWheels(0,0);
}


int auto_forward(oi_t *sensor_data, double distance_mm, int spd, int spd2){
  double sum = 0;
  while(sum < distance_mm){
    // toggle interrupt
    if(command_flag_toggle == 1){
      command_flag_toggle = 0;
      return 1;
    }

    //oi_setWheels(spd,spd);
    oi_setWheels(spd2,spd);
    oi_update(sensor_data);
    if(sensor_data->bumpLeft){
      sendBytes("Bump Left\n", -10000);
      avoidance(sensor_data,0);
      return 0;
    }
    else if(sensor_data->bumpRight){
      sendBytes("Bump Right\n", -10000);
      avoidance(sensor_data,1);
      return 0;
    }
    else if((sensor_data->cliffLeftSignal > 2750)){
      sendBytes("Left Boundary\n", -10000);
      cliff_avoidance(sensor_data,1);
      //lcd_printf("Left Boundary");
      return 0;
    }
    else if((sensor_data->cliffFrontLeftSignal > 2750)){
      sendBytes("Left Front Boundary\n", -10000);
      cliff_avoidance(sensor_data,2);
      //lcd_printf("Left Front Boundary");
      return 0;
    }
    else if((sensor_data->cliffFrontRightSignal > 2750)){
      sendBytes("Right Front Boundary\n", -10000);
      cliff_avoidance(sensor_data,3);
      //lcd_printf("Right Front Boundary");
      return 0;
    }
    else if((sensor_data->cliffRightSignal > 2700)){
      sendBytes("Right Boundary\n", -10000);
      cliff_avoidance(sensor_data,4);
      //lcd_printf("Right Boundary");
      return 0;
    }
    else if(sensor_data->cliffLeftSignal < 500){
        sendBytes("Cliff Left\n", -10000);
        cliff_avoidance(sensor_data,4);
        //lcd_printf("Cliff Right");
        return 0;
    }
    else if(sensor_data->cliffFrontLeftSignal < 500){
        sendBytes("Cliff Front Left\n", -10000);
        cliff_avoidance(sensor_data,4);
        //lcd_printf("Cliff Right");
        return 0;
    }
    else if(sensor_data->cliffFrontRightSignal < 500){
        sendBytes("Cliff Front Right\n", -10000);
        cliff_avoidance(sensor_data,4);
        //lcd_printf("Cliff Right");
        return 0;
    }
    else if(sensor_data->cliffRightSignal < 500){
        sendBytes("Cliff Right\n", -10000);
        cliff_avoidance(sensor_data,4);
        //lcd_printf("Cliff Right");
        return 0;
    }
    else{
        sum += abs(sensor_data -> distance);
    }
  }
  oi_setWheels(0,0);
  return 0;
}



