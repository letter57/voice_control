//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
*/
//===========================================================================		
#ifndef	__AMTP32M_DRIVER_H__
#define	__AMTP32M_DRIVER_H__


//===========================================================================		
/*
  @brief		i/o definition.  		
*/
//===========================================================================		
#define		_VOICE_DATA		(LATCbits.LATC5)
#define		_VOICE_CLOCK	(LATCbits.LATC4)
#define		_VOICE_BUSY		(PORTCbits.RC3)

//===========================================================================		
/*
  @brief		value definition.  		
*/
//===========================================================================		
#define		VOICE_DELAY_VAL		1	

#define		PLAYING_VOICE		1
#define		PLAY_VOICE_STOP		0


//===========================================================================		
//
//===========================================================================		
void	cpu_serial_mode_start(void);
void	voice_clock_gpio_cfg(uint8_t  pins_state);
void	voice_data_gpio_cfg(uint8_t  pins_state);
void	cpu_serial_mode_byte_wirte(uint8_t  data);
void	cpu_serial_mode_clock(void);
void	cpu_serial_mode_stop(void);
uint8_t		voice_busy_state_get(void);

//===========================================================================		
//
//===========================================================================		
#endif
