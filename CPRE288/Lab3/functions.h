/*
 * functions.h
 *
 *  Created on: Jan 30, 2024
 *      Author: clab22
 */



// header file

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "cyBot_Scan.h"

typedef struct {
    float sound_dist_arr[91];
    int IR_raw_val_arr[91];

    int obj_num[8];
    int obj_angle[8];
    float obj_dist[8];
    int obj_radial_len[8];
    float obj_width[8];
} full_scan_data_t


void sendBytes(char* message, double data);

cyBOT_Scan_t *scan_alloc();

void scan_data_free(cyBOT_Scan_t *self);

full_scan_data_t *scan_alloc();

void full_scan_data_free(cyBOT_Scan_t *self);

void lcd_rotatingBanner(char* message);

void scan_180(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data);

void scan_send(cyBOT_Scan_t *sensor_data, int deg);

void full_scan_update(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data, int j);

void find_objects(full_scan_data_t *full_scan_data);

void reset_objects(full_scan_data_t *self);

void full_scan_data_send(full_scan_data_t *self);

void object_data_send(full_scan_data_t *self);


#endif /* FUNCTIONS_H_ */
