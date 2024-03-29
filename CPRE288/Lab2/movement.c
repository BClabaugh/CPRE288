/*
 * movement.c
 *
 *  Created on: Jan 30, 2024
 *      Author: clab22
 */


#include "open_interface.h"
#include "math.h"



void move_forward(oi_t *sensor_data, double distance_mm){
  double sum = 0;
  oi_setWheels(300,300);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    sum += sensor_data -> distance;
  }
  oi_setWheels(0,0);
}

void move_backward(oi_t *sensor_data, double distance_mm){
  double sum = 0;
  oi_setWheels(-150,-150);
  while(sum <= distance_mm){
    oi_update(sensor_data);
    sum += abs(sensor_data -> distance);
  }
  oi_setWheels(0,0);
}

void turn_right(oi_t *sensor_data, double degrees){
  double sum = 0;
  oi_setWheels(-100,100);
  while(sum <= degrees - 25){
    oi_update(sensor_data);
    sum += abs(sensor_data -> angle);
  }
  oi_setWheels(0,0);
}

void turn_left(oi_t *sensor_data, double degrees){
  double sum = 0;
  oi_setWheels(100,-100);
  while(sum <= degrees-13){
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
  move_backward(sensor_data, 150);
  if(direction){
    turn_right(sensor_data, 90);
    move_forward(sensor_data, 250);
    turn_left(sensor_data, 90);
  }
  if(!direction){
    turn_left(sensor_data, 90);
    move_forward(sensor_data, 250);
    turn_right(sensor_data, 90);
  }
  move_forward(sensor_data, 150);
  oi_setWheels(0,0);
}


void two_meter_race(oi_t *sensor_data){
  double sum = 0;
  while(sum < 2000){
    oi_setWheels(250,250);
    oi_update(sensor_data);
    if(sensor_data->bumpLeft){
      avoidance(sensor_data,0);
    }else if(sensor_data->bumpRight){
        avoidance(sensor_data,1);
    }else{
        sum += abs(sensor_data -> distance);
    }
  }
  oi_setWheels(0,0);
}



