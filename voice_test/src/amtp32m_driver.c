//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
	* 2015-12-02	 Cris		  modified the cpu_serial_mode_stop()¡Adue to control the power.You need to control data_pin & clock_pin to low.
	                              prevent power comsuption.	                              

*/
//===========================================================================		
#include	"voice_test.h"


//===========================================================================		
/*
  @brief		cpu serial mode start
  
  @details		This routine will send the Start Bit.
  
*/
//===========================================================================
void	cpu_serial_mode_start(void)
{
	voice_clock_gpio_cfg(1);
	voice_data_gpio_cfg(1);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);		
	voice_data_gpio_cfg(0);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);
	voice_clock_gpio_cfg(0);		
}

//===========================================================================		
/*
  @brief		voice clock gpio config.
  
  @details		config voice data pin hi or low. 
  
  @note			aMTPxxM-Datasheet.
  
  @param[in]  	pins_state			0 -> output low¡A1 -> output hi

*/
//===========================================================================
void	voice_clock_gpio_cfg(uint8_t  pins_state)
{
	if(pins_state == 0)	
	{
		_VOICE_CLOCK = 0;
	}
	else
	{
		_VOICE_CLOCK = 1;
	}	
}

//===========================================================================		
/*
  @brief		voice data gpio config.
  
  @details		config voice data pin hi or low.  			
  
  @note			aMTPxxM-Datasheet.
  
  @param[in]  	pins_state			0 -> output low¡A1 -> output hi
*/
//===========================================================================
void	voice_data_gpio_cfg(uint8_t  pins_state)
{
	if(pins_state == 0)	
	{
		_VOICE_DATA = 0;
	}
	else
	{
		_VOICE_DATA = 1;
	}	
}

//===========================================================================		
/*
  @brief		write data
  
  @details		This routine will write a byte to the device.

  @param[in]  	data		// the data you want to write.
   
*/
//===========================================================================
void	cpu_serial_mode_byte_wirte(uint8_t  data)
{
	uint8_t		i,j;
	
	for(i = 0 ; i < 8 ; i++)
	{
		j = data & 0x01;
		
		if(j == 0)	
		{
			voice_data_gpio_cfg(0);
		}
		else
		{
			voice_data_gpio_cfg(1);
		}
		
		cpu_serial_mode_clock();
		data = data >> 1;		
	}	
}

//===========================================================================		
/*
  @brief		cpu serial mode clock
  
  @details		This routine will send the clock pulse.
  
*/
//===========================================================================
void	cpu_serial_mode_clock(void)
{
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);
	voice_clock_gpio_cfg(1);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);
	voice_clock_gpio_cfg(0);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);	
}

//===========================================================================		
/*
  @brief		cpu serial mode start
  
  @details		This routine will send the Stop Bit.
  
  @note			due to control the power.You need to control data_pin & clock_pin to low.
	            prevent power comsuption.	            
  
*/
//===========================================================================
void	cpu_serial_mode_stop(void)
{
	voice_clock_gpio_cfg(0);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);
	voice_data_gpio_cfg(1);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);
	voice_clock_gpio_cfg(1);
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);	
	voice_data_gpio_cfg(1);
	
	//
	delay_10_tcyx_wdt(VOICE_DELAY_VAL);	
	voice_clock_gpio_cfg(0);
	voice_data_gpio_cfg(0);
}

//===========================================================================		
/*
  @brief		voice_busy_state_get
  
  @details		check the voice is play off or not.
  
  @return		1 -> PLAYING_VOICE.
                0 -> PLAY_VOICE_STOP.
  
*/
//===========================================================================
uint8_t		voice_busy_state_get(void)
{
	if(_VOICE_BUSY)	
	{
		return	PLAYING_VOICE;
	}
	else
	{
		return	PLAY_VOICE_STOP;
	}
}





