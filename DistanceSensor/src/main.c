/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include "test.h"
#include "timer.h"
#include "dacc.h"
volatile uint16_t rising_edge=0;
volatile uint16_t pulse_width=0;

volatile bool ready_distance_digital = false ;

int main (void)
{
	system_init();
	delay_init();
	config_ds();
	init_dac();
	
	while(1)
	{
		//test();
		convert_digital();
	}
	/* Insert application code here, after the board has been initialized. */
}
