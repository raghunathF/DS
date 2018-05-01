/*
 * DAC.c
 *
 * Created: 12/17/2017 6:23:03 PM
 *  Author: RaghunathReddy Jangam
 */
 #include <asf.h>
 #include "dacc.h"
 
 void configure_dac(void)
 {
	 struct dac_config config_dac;
	 dac_get_config_defaults(&config_dac);
	 config_dac.reference = DAC_REFERENCE_AVCC;
	 dac_init(&dac_instance_ds, DAC, &config_dac);
 }
 
 void configure_dac_channel(void)
 {
	 
	 struct dac_chan_config config_dac_chan;
	 dac_chan_get_config_defaults(&config_dac_chan);
	 dac_chan_set_config(&dac_instance_ds, DAC_CHANNEL_0, &config_dac_chan);
	 dac_chan_enable(&dac_instance_ds, DAC_CHANNEL_0);
	 
 }
 
 void configure_dac_pins()
 {
	 // Enable output on the I/O line
	 struct port_config config_port_pin;
	 port_get_config_defaults(&config_port_pin);
	 config_port_pin.direction = PORT_PIN_DIR_OUTPUT;
	 port_pin_set_config(DISTANCE, &config_port_pin);
 }
 
 void enable_dac()
 {
	 dac_enable(&dac_instance_ds);
 }
 
 void init_dac()
 {
	 configure_dac_pins();
	 configure_dac();
	 configure_dac_channel();
	 enable_dac();
 }


