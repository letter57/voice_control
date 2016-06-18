//===========================================================================
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
*/
//===========================================================================
#ifndef	__COMMON_H__
#define	__COMMON_H__

//===========================================================================
//
//===========================================================================


//===========================================================================
/*
  @brief		system mode.
*/
//===========================================================================
typedef enum
{
	SONG_MENU_MODE,
	VOLUME_MENU_MODE
	
}system_mode_t;

//===========================================================================
/*
  @brief		union struct.
*/
//===========================================================================
typedef	union
{
	uint8_t	    data_buf_array[2];
	uint16_t	data_buf_int;

	struct
	{
		uint8_t		union_data_int_low;
		uint8_t		union_data_int_hi;
	};

}union_data_int_t;

//===========================================================================
/*
  @brief		common flag structure.
*/
//===========================================================================
typedef	struct
{
	union
	{
		uint8_t		common_flags;

		struct
		{
			unsigned	battery_flag		: 1 ;	
			unsigned	lock_unlock_flag	: 1 ;		
		};

	}flags;

}common_flag_t;

//===========================================================================
//
//===========================================================================
extern	system_mode_t		system_mode;
extern	union_data_int_t	random_wakeup;
extern	common_flag_t		common_flag;
//===========================================================================
//
//===========================================================================




//===========================================================================
//
//===========================================================================
void	lock_unlock_prompt(void);
void	battery_status_set(void);
uint8_t		battery_status_get(void);
void	lock_unlock_status_set(void);
uint8_t		lock_unlock_status_get(void);
void	lock_prompt(void);
void	unlock_prompt(void);
void    lock_sound_light_prompt(void);
void    unlock_sound_light_prompt(void);
void	lock_unlock_prompt_delay(void);
//===========================================================================
//
//===========================================================================
#endif
