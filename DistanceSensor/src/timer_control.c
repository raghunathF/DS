/*
 * timer_control.c
 *
 * Created: 12/17/2017 6:21:20 PM
 *  Author: raghu
 */ 

#include <asf.h>
#include "timer_control.h"

uint16_t read_ds_digital()
{
	uint16_t digital_value = 0;
	while(ready_distance_digital == false );
	ready_distance_digital = false;
	digital_value = pulse_width;
	return digital_value;
}


uint16_t filter_digital()
{
	 //Previous value greater than certain 100
	 uint16_t digital_filter_value = 0;
	 static uint16_t present_raw_value = 0;
	 static uint16_t infinite_value = 0;
	 static uint16_t previous_raw_value = 0;
	 static bool init_filter = true;
	 static uint8_t attempts = 0;
	 
	 present_raw_value = read_ds_digital();
	 infinite_value   = ((infinite_value*4)+ present_raw_value)/5;
	 
	 if(init_filter == true)
	 {
		 init_filter = false;
		 infinite_value = present_raw_value;
	 }
	 
	 if(abs(previous_raw_value - infinite_value) > THRESHOLD_FILTER_DIFF )
	 {
			 if(attempts  < NO_ATTEMPTS)
			 {
				 digital_filter_value = previous_raw_value;
				 attempts++;
			 }
			 else
			 {
				 attempts = 0;
				 digital_filter_value = infinite_value;
				 previous_raw_value   = infinite_value;
				 
			 }
	 }
	 else
	 {
		 previous_raw_value	  = infinite_value;
		 digital_filter_value = infinite_value;
	 }
	 
	return digital_filter_value;
}


