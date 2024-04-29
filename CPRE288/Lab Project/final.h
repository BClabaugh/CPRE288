/*
 * final.h
 *
 *  Created on: Apr 21, 2024
 *      Author: coreybh
 */

#ifndef FINAL_H_
#define FINAL_H_


#include "open_interface.h"
#include "functions.h"
#include "open_interface.h"
#include "Timer.h"
#include "math.h"
#include "movement.h"
#include "uart-interrupt.h"
#include "adc.h"
#include "ping.h"
#include "servo.h"


int scan(full_scan_data_t *full_scan_data);

void controlled_driving(full_scan_data_t *self, oi_t *sensor_data);

//void autonomous(full_scan_data_t *self, oi_t *sensor_data);
//
//int auto_drive_sml_obj(full_scan_data_t *self, oi_t *sensor_data, int sml_obj);
//
//int sml_obj_positioning(full_scan_data_t *self, oi_t *sensor_data, int closest_sml, int closest_sml2);
//
//int into_dest(full_scan_data_t *self, oi_t *sensor_data, int closest_sml, int closest_sml2);
//
//int auto_drive_trig_oneOBJ(full_scan_data_t *self, oi_t *sensor_data);
//
//int auto_drive_trig_twoOBJ(full_scan_data_t *self, oi_t *sensor_data);

//int auto_drive_away(full_scan_data_t *self, oi_t *sensor_data);






#endif /* FINAL_H_ */
