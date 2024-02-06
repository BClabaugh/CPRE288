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

void sendBytes(char* message, double data);

cyBOT_Scan_t *scan_alloc();

void scan_free(cyBOT_Scan_t *self);

void lcd_rotatingBanner(char* message);


#endif /* FUNCTIONS_H_ */
