/*
 * functions.h
 *
 *  Created on: Jan 30, 2024
 *      Author: Corey & Blake
 */



// header file

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "cyBot_Scan.h"
#include "open_interface.h"

typedef struct {
    float sound_dist_arr[91];
    int IR_raw_val_arr[91];
    float IR_val_arr[91];

    int obj_num[8];
    int obj_fir_angle[8];
    int obj_las_angle[8];
    int obj_mid_angle[8];
    float obj_dist[8];
    float obj_IR_dist[8];
    int obj_radial_len[8];
    float obj_width[8];
} full_scan_data_t;


void sendBytes(char* message, double data);

void sendBytesInt(char* message, double data);

cyBOT_Scan_t *scan_alloc();

void scan_data_free(cyBOT_Scan_t *self);

full_scan_data_t *full_scan_alloc();

void full_scan_data_free(full_scan_data_t *self);

void scan_path(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data);

void scan_objs(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data);

void scan_send(cyBOT_Scan_t *sensor_data, int deg);

void full_scan_update(cyBOT_Scan_t *scan_data, full_scan_data_t *full_scan_data, int j, int scan_IR_ave);

void dist_scan_update(full_scan_data_t *full_scan_data, int j, float scan_ping_ave);

void find_objects_pos(full_scan_data_t *full_scan_data);

void find_objects_full(full_scan_data_t *full_scan_data);

void reset_objects(full_scan_data_t *self);

void full_scan_data_send(full_scan_data_t *self);

void object_data_send(full_scan_data_t *self,  cyBOT_Scan_t *scan_data);

int smallest_object(full_scan_data_t *self, cyBOT_Scan_t *scan_data);

void controlled_driving(full_scan_data_t *self, oi_t *sensor_data, cyBOT_Scan_t *scan_data, int sml_obj);

void ir_init_output(oi_t *sensor_data, cyBOT_Scan_t *scan_data);

int auto_driving(full_scan_data_t *self, oi_t *sensor_data, cyBOT_Scan_t *scan_data, int sml_obj);

void turning_init(oi_t *sensor_data);


#endif /* FUNCTIONS_H_ */
