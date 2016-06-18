//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
*/
//===========================================================================		
#ifndef	__MS6260_H__
#define	__MS6260_H__

//===========================================================================		
//
//===========================================================================		
// MS6260 Addr
#define		MS6260_ADDR				0x88

// MS6260 Command
#define		AUDIO_TURN_OFF			0xFF
#define		AUDIO_MUTE_ENABLE		0x79
#define		AUDIO_MUTE_DISABLE		0x78

#define		AUDIO_AX_MAX			10
#define		AUDIO_BX_MAX			8
#define		AUDIO_CX_MAX			16


//===========================================================================		
//
//===========================================================================		
typedef struct
{
	uint8_t		audio_ax_buffer;
	uint8_t		audio_bx_buffer;
	uint8_t		audio_cx_buffer;
	
}audio_t;

//===========================================================================		
//
//===========================================================================		


//===========================================================================		
//
//===========================================================================		
extern	const rom uint8_t  audio_ax_tbl[];
extern	const rom uint8_t  audio_bx_tbl[];
extern	const rom uint8_t  audio_cx_tbl[];

void	audio_data_set(void);
void	audio_command_set(uint8_t  command);
void	audio_turn_on(void);
void	audio_turn_off(void);
void	audio_db_set(uint8_t  audio_ax_level, uint8_t  audio_bx_level, uint8_t  audio_cx_level);
//===========================================================================		
//
//===========================================================================		
#endif