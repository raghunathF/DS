/*
 * timer.h
 *
 * Created: 12/17/2017 6:20:48 PM
 *  Author: raghu
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#include <asf.h>
void config_ds();

extern volatile uint16_t pulse_width;
extern volatile uint16_t rising_edge;
extern volatile bool ready_distance_digital;


#define ECHO_PIN_EIC PIN_PA09A_EIC_EXTINT7
#define ECHO_PIN_MUX PINMUX_PA09A_EIC_EXTINT7
#define ECHO_EIC_LINE 7





#endif /* TIMER_H_ */