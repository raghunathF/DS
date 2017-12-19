/*
 * timer.c
 *
 * Created: 12/17/2017 6:23:54 PM
 *  Author: raghu
 */ 

#include <asf.h>
#include "timer.h"
struct tc_module tc_instance_ds;

void tc_callback_trigger(struct tc_module *const module_inst)
{
	tc_set_count_value(&tc_instance_ds, 0);
	port_pin_set_output_level(TRIGGER_PIN, true);
	delay_cycles_us(10); //this should actually be a 10 us delay because delay function is mysteriously misconfigured
	port_pin_set_output_level(TRIGGER_PIN, false);
}

void echo_detection_callback(void)
{
	bool pin_state = port_pin_get_input_level(ECHO_PIN);
	if(pin_state)
	{
		rising_edge = tc_get_count_value(&tc_instance_ds);
	}
	else
	{
		pulse_width = tc_get_count_value(&tc_instance_ds) - rising_edge;
		ready_distance_digital = true;
	}
}

void config_pins_ds()
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);

	// Set trigger pin to output
	config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(TRIGGER_PIN, &config_port_pin);
	port_pin_set_output_level(TRIGGER_PIN, false);
	
	// Echo pin to input -- check if pull up or pull down configuration
	config_port_pin.direction = PORT_PIN_DIR_INPUT;
	port_pin_set_config(ECHO_PIN, &config_port_pin);
}

void config_tc1_ds(void)
{
	struct tc_config config_tc_ds;
	tc_get_config_defaults(&config_tc_ds);
	
	config_tc_ds.counter_size = TC_COUNTER_SIZE_16BIT; //16
	config_tc_ds.clock_source = GCLK_GENERATOR_0;
	config_tc_ds.clock_prescaler = TC_CLOCK_PRESCALER_DIV8; //64 msec
	
	//Overflow occurs in 68msec
	//config_tc_ds.counter_16_bit.value = 18661; // Overflows in 62.5ms
	
	config_tc_ds.count_direction = TC_COUNT_DIRECTION_UP;
	tc_init(&tc_instance_ds, TC1, &config_tc_ds);
}

void tc1_callbacks_ds()
{
	tc_register_callback(&tc_instance_ds, tc_callback_trigger,TC_CALLBACK_OVERFLOW);
}

void enable_tc1_ds()
{
	tc_enable(&tc_instance_ds);
	tc_enable_callback(&tc_instance_ds, TC_CALLBACK_OVERFLOW);
}

void disable_tc1_ds()
{
	tc_disable(&tc_instance_ds);
	tc_disable_callback(&tc_instance_ds, TC_CALLBACK_OVERFLOW);
}


void config_extint_channel_ds(void)
{
	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);
	config_extint_chan.gpio_pin           = ECHO_PIN_EIC;
	config_extint_chan.gpio_pin_mux       = ECHO_PIN_MUX;
	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_DOWN;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	extint_chan_set_config(ECHO_EIC_LINE, &config_extint_chan);
}

void config_extint_callbacks_ds(void)
{
	extint_register_callback(echo_detection_callback,ECHO_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}


void config_extint_ds()
{
	config_extint_channel_ds();
	config_extint_callbacks_ds();
}



void enable_extint_ds()
{
	extint_chan_enable_callback(ECHO_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}

void disable_extint_ds()
{
	extint_chan_disable_callback(ECHO_EIC_LINE,EXTINT_CALLBACK_TYPE_DETECT);
}

void config_pins_timer_ds()
{
	config_pins_ds();
	config_tc1_ds();
	tc1_callbacks_ds();
	
}



void config_ds()
{
	config_pins_timer_ds();
	config_extint_ds();
	enable_tc1_ds();
	enable_extint_ds();
}
