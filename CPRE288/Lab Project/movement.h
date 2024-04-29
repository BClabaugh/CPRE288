/*
 * movement.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Corey & Blake
 */



// header files

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


void move_forward(oi_t *sensor_data, double distace_mm);

void move_backward(oi_t *sensor_data, double distace_mm);

void move_forward_spd(oi_t *sensor_data, double distace_mm, int spd);

void move_backward_spd(oi_t *sensor_data, double distace_mm, int spd);

void turn_right(oi_t *sensor_data, double degrees);

void turn_left(oi_t *sensor_data, double degrees);

void turn_right_spd(oi_t *sensor_data, double degrees, int spd);

void turn_left_spd(oi_t *sensor_data, double degrees, int spd);

void square(oi_t *sensor_data);

void avoidance(oi_t *sensor_data, bool direction);

int auto_forward(oi_t *sensor_data, double distance_mm, int spd, int spd2);


#endif /* MOVEMENT_H_ */
