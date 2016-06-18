//===========================================================================
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-10-02     Cris	      the first version

*/
//===========================================================================
#include	"voice_test.h"



//===========================================================================
/*
  @brief		voice time-out.

  @details      每一段語音的time-out時間.

  @note			100ms unit.
*/
//===========================================================================
rom uint8_t		voice_time_out_no[] =
{
	85, 13, 12, 17, 13, 13, 13, 17, 16, 13,
	12, 23, 22, 22, 19, 20, 21, 22, 22, 22,
	18, 17, 19, 17, 17, 18, 21, 19, 21, 22,
	22, 22, 20, 20, 21, 21, 21, 22, 18, 16,
	18, 17, 17, 17, 15, 15, 16, 16, 19, 19,
	19, 19, 19, 15, 13, 18, 15, 19, 27, 23,
	16, 21, 23, 21, 25, 23, 25, 23, 23, 23,
	19, 22, 21, 24, 17, 17, 17, 21, 20, 23,
	21, 23, 18, 16, 18, 21, 20, 23, 25, 10,
	10, 10, 10, 10, 10, 12, 13, 12, 13, 11,
	11, 11, 12, 11, 11, 11, 12, 10, 10, 10,
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
	10, 11, 14, 85, 110,50, 50, 50, 50, 50,
};

//===========================================================================
/*
  @brief		play voice

  @details		

  @note			加入time-out時間，防止_VOICE_BUSY失效，當機. 

  @param[in]  	paragraph				// 語音的段數.
  @param[in]	is_play_voice_delay		// 語音播畢才離開.

*/
//===========================================================================
void	play_voice(uint8_t  paragraph, uint8_t  is_play_voice_delay)
{
	cpu_serial_mode_start();
	cpu_serial_mode_byte_wirte(paragraph);
	cpu_serial_mode_stop();

	delay_1k_tcyx_wdt(1);

	if(is_play_voice_delay)
	{
		is_voice_play_off(paragraph);
	}
}

//===========================================================================
/*
  @brief		is_voice_play_off

  @details		判別語音是否播放完畢.

  @note			加入time-out時間，防止_VOICE_BUSY失效，當機. 

*/
//===========================================================================
void	is_voice_play_off(uint8_t  paragraph)
{
	uint8_t		time_cnt = 0;

	while(voice_busy_state_get())
	{
		delay_1k_tcyx_wdt(100);
		time_cnt++;

		if(time_cnt >= voice_time_out_get(paragraph))
		{
			break;
		}
	}
}

//===========================================================================
/*
  @brief		voice time-out.

  @details      每一段語音的time-out時間.

  @note			每一單位為100ms.

  @param[in]	paragraph			// 語音段數

  @return		reg_val				// 相對應段數的time-out時間.
*/
//===========================================================================
uint8_t		voice_time_out_get(uint8_t  paragraph)
{
	uint8_t		reg_val;

	if((paragraph >= VOICE_NORMAL_PARAGRAPH_MIN) && (paragraph <= VOICE_NORMAL_PARAGRAPH_MAX))
	{
		reg_val = voice_time_out_no[paragraph];
	}
	else
	{
		reg_val = voice_time_out_no[0];
	}

	return	reg_val;
}

