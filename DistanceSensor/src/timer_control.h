/*
 * timer_control.h
 *
 * Created: 12/17/2017 6:21:37 PM
 *  Author: raghu
 */ 

uint16_t read_ds_digital();
uint16_t filter_digital();

extern volatile bool ready_distance_digital;
extern volatile uint16_t pulse_width;

#define THRESHOLD_FILTER_DIFF 40
#define NO_ATTEMPTS 3