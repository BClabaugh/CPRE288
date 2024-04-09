/*
 * servo.h
 *
 *  Created on: April 2, 2024
 *      Author: Corey & Blake
 */



// header file

#ifndef SERVO_H_
#define SERVO_H_

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include <stdbool.h>

void servos_init();

uint32_t servos_move(uint16_t degrees);


#endif /* SERVO_H_ */
