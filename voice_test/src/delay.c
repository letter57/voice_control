//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
	* 2015-10-15	 Cris		  osc修改為16M.
*/
//===========================================================================		
#include	"voice_test.h"

//===========================================================================		
/*
  @brief		delay.
  
  @details		delay 1ms.
  
  @note			(1)需注意指令週期.
  				(2)Delay1KTCYx的計算方式: 1/( osc / 4 ) * 1000 = 0.5 ms .
                
                
  @param[in]	cnt			delay count. unit 1ms              
*/
//===========================================================================
void	delay_1k_tcyx_wdt(uint8_t  m_sec)
{
	while(m_sec)
	{
		ClrWdt();
		Delay1KTCYx(4);
		m_sec--;		
	}	
}

//===========================================================================		
/*
  @brief		delay.
  
  @details		delay 5us.
  
  @note			(1)需注意指令週期.
  				(2)Delay1KTCYx的計算方式: 1/( osc / 4 ) * 10 = 5 us .
                
                
  @param[in]	cnt			delay count. unit 5us              
*/
//===========================================================================
void	delay_10_tcyx_wdt(uint8_t  u_sec)
{
	while(u_sec)
	{
		ClrWdt();
		Delay10TCYx(2);
		u_sec--;		
	}	
}

//===========================================================================		
/*
  @brief		delay_sec_wdt.
  
  @details		delay 1s.
  
  @note			(1)需注意指令週期.
  				(2)Delay1KTCYx的計算方式:  1/( osc / 4 ) * 1000 = 0.128s.
                (3)Delay100TCYx的計算方式: 1/( osc / 4 ) * 100 = 0.0128s .
                
  @param[in]	sec			delay count. unit 1s              
*/
//===========================================================================
void	delay_sec_wdt(uint8_t  sec)
{
	uint8_t		cnt;
	
	// Set Internal RC Oscillator Frequency = 31.25 KHz.
	OSCCON = 0b00000000;
	
	while(sec)
	{
		cnt = 7;
		 // 7000 + 800 , 實際是 7812.5
		while(cnt)	
		{
			ClrWdt();
			Delay1KTCYx(1);
			cnt--;
		}
		
		ClrWdt();
		Delay100TCYx(8);
		sec--;
	}
	
	// Set Internal RC Oscillator Frequency = 16 MHz.
	OSCCON = 0b01110000;
}