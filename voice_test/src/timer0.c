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
*/
//===========================================================================
time_sequence_t		timer0;				// Structure used to main timer sequence.

//===========================================================================		
/*
  @brief		initial timer0.  
  
  @details		No interrupt & initial timer tick.
  
  @note			(1) Osc/4/prescalar = 16M/4/128，t=1/f, t = 32us
                (2) 最大時間 32us * 65536 = 2s
*/
//===========================================================================		
void	initial_timer0(void)
{
	INTCONbits.TMR0IE = 0;		// Disable interrupt.
	INTCONbits.TMR0IF = 0;		// Clear interrupt flag.
	INTCON2bits.TMR0IP = 0;		// Low priority.
	
	//Clear timer0-related registers
	TMR0H = 0;          			
  	TMR0L = 0;	
  	
  	// Timer0 on, 16-bit, internal timer, 1:128 prescalar	
  	T0CON = 0b10000110;		
}

//===========================================================================		
/*
  @brief		close_timer0 
  
  @details		
  
  @note			
*/
//===========================================================================		
void	close_timer0(void)
{
	INTCONbits.TMR0IE = 0;		// Disable interrupt.
	INTCONbits.TMR0IF = 0;		// Clear interrupt flag.
	T0CON = 0;
}

//===========================================================================		
/*
  @brief		tick get.  
  
  @param[out]   timer0_tick.data_buf_int      get timer0 tick       
*/
//===========================================================================		
uint16_t	timer0_tick_get(void)
{
	union_data_int_t	timer0_tick;
	
	timer0_tick.union_data_int_low = TMR0L;
	timer0_tick.union_data_int_hi = TMR0H;
	
	return	timer0_tick.data_buf_int;	
}

//===========================================================================		
/*
  @brief		timer0_timing_updata.  
  
  @details  	更新每個時序的時間.
*/
//===========================================================================		
void	timer0_timing_updata(void)
{
	timer0.time_sequence_20ms = timer0_tick_get();
	timer0.time_sequence_40ms = timer0_tick_get();
	timer0.time_sequence_64ms = timer0_tick_get();
	timer0.time_sequence_80ms = timer0_tick_get();
	timer0.time_sequence_250ms = timer0_tick_get();
	timer0.time_sequence_500ms = timer0_tick_get();
	timer0.time_sequence_1000ms = timer0_tick_get();
	
}