/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: clab22
 */


#include "open_interface.h"
#include "math.h"
#include "uart-interrupt.h"



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
  int offset = 24; //27.5
  oi_setWheels(-75,75);
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
  int offset = 3.6;
  double sum = 0;
  oi_setWheels(75,-75);
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
  if(!direction){
    turn_right(sensor_data, 90);
    move_forward_spd(sensor_data, 250, 75);
    turn_left(sensor_data, 90);
  }
  if(direction){
    turn_left(sensor_data, 90);
    move_forward_spd(sensor_data, 250, 75);
    turn_right(sensor_data, 90);
  }
  move_forward_spd(sensor_data, 150, 75);
  oi_setWheels(0,0);
}


int auto_forward(oi_t *sensor_data, double distance_mm, int spd){
  int res = 0;
  double sum = 0;
  while(sum < distance_mm){
    // toggle intrupt
    if(command_flag_toggle == 1){
      command_flag_toggle = 0;
      return 1;
    }

    oi_setWheels(spd,spd);
    oi_update(sensor_data);
    if(sensor_data->bumpLeft){
      avoidance(sensor_data,0);
      res = 2;
    }
    else if(sensor_data->bumpRight){
      avoidance(sensor_data,1);
      res = 2;
    }
    else{
        sum += abs(sensor_data -> distance);
    }
  }
  oi_setWheels(0,0);
  return res;
}



