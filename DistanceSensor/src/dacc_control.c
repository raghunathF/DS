
/*
 * dacc_control.c
 *
 * Created: 12/19/2017 4:30:04 PM
 *  Author: raghu
 */ 
#include <asf.h>

#include "dacc_control.h"
#include "dacc.h"
#include "timer_control.h"
static uint16_t digital_value[2];
void convert_digital()
{
	
	digital_value[0] = read_ds_digital();
	if(digital_value[0] > 0x1c00)
	{
		digital_value[0] = 0x1c00;
	}
	digital_value[1] = (digital_value[0]*0x3FF) / (0x1c00); //2AA -- 2.2V
	while(dac_chan_write( &dac_instance_ds , DAC_CHANNEL_0 , digital_value[1]) != STATUS_OK);
}
