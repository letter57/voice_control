//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
	* 2015-12-02	 Cris		  modified the cpu_serial_mode_stop()，due to control the power.You need to control data_pin & clock_pin to low.
	                              prevent power comsuption.	                              

*/
//===========================================================================		
#include	"voice_test.h"

//===========================================================================		
/*
  @brief		register definition.                  
*/
//===========================================================================
audio_t		audio;

//===========================================================================		
/*
  @brief	兩聲道同時-1dB/階                  
*/
//===========================================================================
const rom uint8_t  audio_ax_tbl[]=
{
	0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9		
};

//===========================================================================		
/*
  @brief	兩聲道同時-10dB/階                  
*/
//===========================================================================
const rom uint8_t  audio_bx_tbl[]=
{
	0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7
};

//===========================================================================		
/*
  @brief	兩聲道同時+1dB/階                
*/
//===========================================================================
const rom uint8_t  audio_cx_tbl[]=
{
	0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,	
	0xca,0xcb,0xcc,0xcd,0xce,0xcf
};

//===========================================================================		
/*
  @brief		
  
  @details		
  
*/
//===========================================================================
void	audio_data_set(void)
{
	i2c_start();
	i2c_byte_wirte(MS6260_ADDR);
	i2c_byte_wirte(audio.audio_ax_buffer);
	i2c_byte_wirte(audio.audio_bx_buffer);
	i2c_byte_wirte(audio.audio_cx_buffer);
	i2c_stop();
}

//===========================================================================		
/*
  @brief		
  
  @details		
  
  @param[in]	command		
  
*/
//===========================================================================
void	audio_command_set(uint8_t  command)
{
	i2c_start();
	i2c_byte_wirte(MS6260_ADDR);
	i2c_byte_wirte(command);
	i2c_stop();
}

//===========================================================================		
/*
  @brief		
  
  @details		
  
*/
//===========================================================================
void	audio_turn_on(void)
{
	audio_data_set();
	audio_command_set(AUDIO_MUTE_DISABLE);	
}

//===========================================================================		
/*
  @brief		
  
  @details		
  
*/
//===========================================================================
void	audio_turn_off(void)
{
	audio_command_set(AUDIO_MUTE_ENABLE);
	audio_command_set(AUDIO_TURN_OFF);	
}

//===========================================================================		
/*
  @brief		
  
  @details		
  
  @param[in]	audio_ax_level
  @param[in]	audio_bx_level
  @param[in]	audio_cx_level
  
*/
//===========================================================================
void	audio_db_set(uint8_t  audio_ax_level, uint8_t  audio_bx_level, uint8_t  audio_cx_level)
{
	if((audio_ax_level < AUDIO_AX_MAX) && (audio_bx_level < AUDIO_BX_MAX) && (audio_cx_level < AUDIO_CX_MAX))
	{
		audio.audio_ax_buffer = audio_ax_tbl[audio_ax_level];
		audio.audio_bx_buffer = audio_bx_tbl[audio_bx_level];
		audio.audio_cx_buffer = audio_cx_tbl[audio_cx_level];	
	}
	else
	{
		audio.audio_ax_buffer = audio_ax_tbl[0];
		audio.audio_bx_buffer = audio_bx_tbl[0];
		audio.audio_cx_buffer = audio_cx_tbl[0];
	}
}
