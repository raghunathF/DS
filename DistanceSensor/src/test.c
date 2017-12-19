/*
 * test.c
 *
 * Created: 12/19/2017 10:48:42 AM
 *  Author: raghu
 */ 
#include <asf.h>
#include "test.h"
#include "timer_control.h"

void test()
{
	static volatile uint16_t  digital_value[1000] ;
	static int count = 0;
	digital_value[count] = filter_digital();
	count++;
	if(count == 400)
	{
		count = 0;
	}
	//delay_cycles_ms(10);
}