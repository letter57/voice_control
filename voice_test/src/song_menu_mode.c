//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version

*/
//===========================================================================		
#include	"voice_test.h"

//===========================================================================
/*
  @brief		register definition.

  @details
*/
//===========================================================================



//===========================================================================		
/*
  @brief		song_menu_mode
  
  @details		
  
  @note	
  
*/
//===========================================================================
void	song_menu_mode(void)
{
//===========================================================================
	if(timer0_tick_get() - timer0.time_sequence_40ms >= TIMER0_SEQUENCE_40MS)
	{
		timer0.time_sequence_40ms = timer0_tick_get();
		
		read_key();
		deal_read_key();
		check_get_key();
		song_menu_mode_updata_key();
	}		
//===========================================================================			
	
}

//===========================================================================		
/*
  @brief		song_menu_mode_updata_key
  
  @details		
  
  @note	
  
*/
//===========================================================================
void	song_menu_mode_updata_key(void)
{
	switch(scan_key.key_code)
	{
//===================================================
		case	1:
		
		scan_key.key_code = 0;
		
		buzzer_count_set(NORMAL_BEEP);
		
		volume_level_inc();
		volume_level_set();
		audio_turn_on();
		
		
		break;
		
//===================================================
		case	2:
		
		scan_key.key_code = 0;
		
		buzzer_count_set(NORMAL_BEEP);
				
		play_voice(0, PLAY_VOICE_WITHOUT_WAIT);
		
		break;
		
				
		
//===================================================
	}
	
}

