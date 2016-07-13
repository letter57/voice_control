//========================================================================
/*
	* 名       稱 : 
	* 廠 內 代 號 : 
    * 公 司 名 稱 : WFE
	* 使 用 晶 片 : PIC18F26K20
	* 時       脈 : 內部16M Hz
	* 編  譯  器  : C18
	* 撰 寫 日 期 :
	* 配 合 硬 體 : demo board 1
	* Change Logs :
	* Date           Author       Version				
	  
	* 2015-03-23     Cris	      the first version
	  1.音源來自語音IC，經過調音IC(MS6260)，然後再經過功放，播放至喇叭.
	    測試其聲音效果.	
*/
//=========================================================================== 


//===========================================================================
#include	"voice_test.h"

//===========================================================================
//
//===========================================================================
system_mode_t		system_mode;


//===========================================================================
/*
  @brief		Configuration Bits.
  @details
  @note
*/
//===========================================================================
#ifdef _DEBUGCODESTART    

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF, PWRT = ON, BOREN = SBORDIS, BORV = 27, WDTEN = OFF, WDTPS = 256  
#pragma config CCP2MX = PORTC, PBADEN = OFF, LPT1OSC = OFF, HFOFST = OFF, MCLRE = ON, STVREN = ON
#pragma config LVP = OFF, XINST = OFF, DEBUG = ON      
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF 
 
#else

#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF, PWRT = ON, BOREN = SBORDIS, BORV = 27, WDTEN = OFF, WDTPS = 256  
#pragma config CCP2MX = PORTC, PBADEN = OFF, LPT1OSC = OFF, HFOFST = OFF, MCLRE = ON, STVREN = ON
#pragma config LVP = OFF, XINST = OFF, DEBUG = OFF     
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTC = OFF, WRTB = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF 
 
#endif

//===========================================================================
// 函式宣告
//===========================================================================
void	HighIntVectorCode(void);
void	LowIntVectorCode(void);

void 	HighIntServiceRoutine(void);
void 	LowIntServiceRoutine(void);


void	initial_system(void);
void	initial_ram(void);
void	initial_peripheral(void);

//===========================================================================
// 高優先權中斷向量位址
//===========================================================================
#pragma code HighIntVector = 0x008      
void	HighIntVectorCode(void)
{
	_asm 
	goto HighIntServiceRoutine
	_endasm
}
#pragma code

//===========================================================================
// 低優先權中斷向量位址
//===========================================================================
#pragma code LowIntVector = 0x018      
void	LowIntVectorCode(void)
{
	_asm 
	goto LowIntServiceRoutine
	_endasm
}
#pragma code

//===========================================================================
// 高優先權中斷服務程式
//===========================================================================
#pragma interrupt HighIntServiceRoutine
void	HighIntServiceRoutine(void)
{
	
}
#pragma code


//===========================================================================
// 低優先權中斷服務程式
//===========================================================================
#pragma interruptlow LowIntServiceRoutine
void	LowIntServiceRoutine(void)
{
	updata_timer3();				  	
  	
} 
#pragma code


//===========================================================================
//		主程式
//===========================================================================
void	main(void)
{
	initial_system();
	
	initial_peripheral();

	initial_ram();
	
	while(1)
	{
		ClrWdt();
		
		switch(system_mode)
		{
//===================================================
			case	SONG_MENU_MODE:
			
			song_menu_mode();
			
			break;	
									
//===================================================
		}
		
	}
	
}

//===========================================================================
/*
  @brief		Initial System.

  @details		初始化單晶片時脈、Watch Dog及週邊硬體設置.	
*/
//===========================================================================
void	initial_system(void)
{
	OSCCON = 0b01110000;		 // 16MHz
	OSCTUNE |= 0b10000000;       // 31.25KHz 由 HFINTOSC / 512 提供.
	
	WDTCON = 1;					// Enable WDT
	
	// initial i/o
	PORTA = 0;
	LATA = 0b00000000;
  	TRISA = 0b00000000;

  	PORTB = 0;
  	LATB = 0b00000000;
  	TRISB = 0b00110000;

  	PORTC = 0;
  	LATC = 0b00000000;
  	TRISC = 0b00001110;	  	
  	
  	PIE1 = 0;
	PIE2 = 0;	
	
	// priority levels on interrupt, BOR Software Enable bit.	
	RCON = 0b11000000;
	
	// PORTB pull-up resistors are disabled.
  	INTCON = 0b00000000;
  	INTCON2 = 0b10000000;
  	INTCON3 = 0b00000000;

	//Interrupt priority
	IPR1 = 0;
	IPR2 = 0;

	// The following registers are used to control the operation of the ADC.
	ADCON0 = 0x00;
	ADCON1 = 0x00;
	ADCON2 = 0x00;
	
	// configure as digital or analog I/O.
	ANSEL = 0;
	ANSELH = 0;


	//When set, each bit of the WPUB register enables the corresponding pin pull-up
	WPUB = 0b00000000;  	
	IOCB = 0;

	// Enable WDT.
	WDTCON = 1;								
}

//===========================================================================
/*
  @brief		Initial ram.

  @details		初始化所使用的記憶體及設置記憶體初始值.		
*/
//===========================================================================
void	initial_ram(void)
{
	memset(&buzzer, 0, sizeof(buzzer));
	memset(&scan_key, 0, sizeof(scan_key));
	
	system_mode = SONG_MENU_MODE;
}

//===========================================================================
/*
  @brief		initial_peripheral.

  @details
*/
//===========================================================================
void	initial_peripheral(void)
{
	initial_timer0();
	initial_timer3();
	
	enable_golbal_int();
}
