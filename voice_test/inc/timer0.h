//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
*/
//===========================================================================		
#ifndef	__TIMER0_H__
#define	__TIMER0_H__

//===========================================================================		
/*
  @brief		time sequence                  
*/
//===========================================================================		
#define		TIMER0_SEQUENCE_20MS		625
#define		TIMER0_SEQUENCE_40MS		1250
#define		TIMER0_SEQUENCE_64MS		2000
#define		TIMER0_SEQUENCE_80MS		2500
#define		TIMER0_SEQUENCE_100MS		3125
#define		TIMER0_SEQUENCE_250MS		7812
#define		TIMER0_SEQUENCE_500MS		15625
#define		TIMER0_SEQUENCE_1000MS		31250

//===========================================================================		
//
//===========================================================================		
void	initial_timer0(void);
void	close_timer0(void);
uint16_t	timer0_tick_get(void);
void	timer0_timing_updata(void);

//===========================================================================		
//
//===========================================================================		
#endif 