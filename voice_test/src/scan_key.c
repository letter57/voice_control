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
scan_key_t	scan_key;


//===========================================================================		
/*
  @brief		read_key.
  
  @details		讀取key的狀態值.
               
*/
//===========================================================================
void	read_key(void)
{
	scan_key.key_temp = 0;
	
	if(_KEY1 == 0)	
	{
		scan_key.key_temp = scan_key.key_temp | 0x01;			
	}	
	
	if(_KEY2 == 0)	
	{
		scan_key.key_temp = scan_key.key_temp | 0x02;			
	}	
}

//===========================================================================		
/*
  @brief		deal_read_key.
  
  @details		處理讀取key的狀態值.               
*/
//===========================================================================
void	deal_read_key(void)
{
	scan_key.key_ram = 0;
	
	switch(scan_key.key_temp)	
	{
		case	0:									break;
		case	1:		scan_key.key_ram = 1;		break;
		case	2:		scan_key.key_ram = 2;		break;	
		case	4:		scan_key.key_ram = 3;		break;
		case	8:		scan_key.key_ram = 4;		break;
		case	16:		scan_key.key_ram = 5;		break;
		case	32:		scan_key.key_ram = 6;		break;
		case	64:		scan_key.key_ram = 7;		break;
		case	128:	scan_key.key_ram = 8;		break;
		default:		scan_key.key_ram = 255;		break;
		
	}	
}

//===========================================================================		
/*
  @brief		deal_read_key.
  
  @details		確認key的狀態並賦予key_code值.               
*/
//===========================================================================
void	check_get_key(void)
{
	if(scan_key.key_ram != 0)	
	{
		if(scan_key.key_ram == scan_key.key_ram_bak)
		{
			scan_key.release_key_cnt = 0;
			
			if(scan_key.key_cnt < 250)
			{
				scan_key.key_cnt++;	
			}
//===========================================================================
// short key
			if(scan_key.key_cnt == WAKEUP_KEY_DEBOUNCE)
			{
				switch(scan_key.key_ram)	
				{
					case	1:		scan_key.key_code = 1;		break;
					case	2:		scan_key.key_code = 2;		break;			
					case	3:		scan_key.key_code = 3;		break;
					case	4:		scan_key.key_code = 4;		break;
					case	5:		scan_key.key_code = 5;		break;
					case	6:		scan_key.key_code = 6;		break;
					case	7:		scan_key.key_code = 7;		break;
					case	8:		scan_key.key_code = 8;		break;					
				}				
			}
//===========================================================================
// long key
			
		}
		else
		{
			scan_key.key_ram_bak = scan_key.key_ram;
		}		
	}
//===========================================================================
// release
	else
	{
		scan_key.release_key_cnt++;
		
		if(scan_key.release_key_cnt > WAKEUP_KEY_RELEASE_DEBOUNCE) 
		{
			scan_key.release_key_cnt = 0;
			scan_key.key_cnt = 0;	
			scan_key.key_ram_bak = 0;
			scan_key.key_code = 0;
		}		
	}	
}