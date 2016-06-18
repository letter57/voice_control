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


//===========================================================================
/*
  @brief		initial timer3.

  @details		Enable interrupt & initial timer tick.

  @note			(1) Osc/4/prescalar = 16M/4/1，t=1/f, t = 0.25us
                (2) interrupt time 0.25us * (65536 - 65136) = 100us
                (3) sleep前，要確保TMR3IF為0，否則會喚醒.看datasheet的 INTERRUPT LOGIC.
                (4) wakeup條件如下
                    TMR3IE = 1
                    TMR3IF = 1
                    TMR3IP = 0
                    IPEN   = 1
*/
//===========================================================================
void	initial_timer3(void)
{
	PIE2bits.TMR3IE = 1;		// Disable interrupt.
	PIR2bits.TMR3IF = 0;		// Clear interrupt flag.
	IPR2bits.TMR3IP = 0;		// Low priority.

	//Clear timer3-related registers
	TMR3H = TIMER3_H_VAL;
  	TMR3L = TIMER3_L_VAL;

  	// Timer3 on, 16-bit, internal timer, 1:1 prescalar
  	T3CON = 0b00000001;
}

//===========================================================================
/*
  @brief		close timer3.


*/
//===========================================================================
void	close_timer3(void)
{
	PIE2bits.TMR3IE = 0;
	PIR2bits.TMR3IF = 0;
	T3CON = 0;
}

//===========================================================================
/*
  @brief		updata timer3.

  @details		timer3 expire. updata timer3 & execution some action.
*/
//===========================================================================
void	updata_timer3(void)
{
	if(PIE2bits.TMR3IE & PIR2bits.TMR3IF)
	{
		PIR2bits.TMR3IF = 0;

		TMR3H += TIMER3_H_VAL;
		TMR3L += TIMER3_L_VAL;
						
		buzzer_scan_freq();
		buzzer_count_time();
	}
}
