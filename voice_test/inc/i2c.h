//===========================================================================		
/*
	* Change Logs :
	* Date           Author       Notes
	* 2015-03-23     Cris	      the first version
*/
//===========================================================================		
#ifndef	__I2C_H__
#define	__I2C_H__

//===========================================================================		
//
//===========================================================================		
#define		_SCL_TRIS			(TRISCbits.TRISC1)
#define		_SCL				(PORTCbits.RC1)

#define		_SDA_TRIS			(TRISCbits.TRISC2)
#define		_SDA				(PORTCbits.RC2)	

//===========================================================================		
/*
  @brief		value definition.  		
  
  @details		delay parameter
*/
//===========================================================================		


//===========================================================================		
//
//===========================================================================		
void	sda_gpio_cfg(uint8_t  pins_state);
void	scl_gpio_cfg(uint8_t  pins_state);
void	i2c_start(void);
void	i2c_stop(void);
void	i2c_clock(void);
uint8_t  i2c_byte_wirte(uint8_t  data);
uint8_t		i2c_byte_read(void);
void	i2c_read_ack(void);
void	i2c_read_nack(void);
void	i2c_check_scl_state(void);
void	delay_i2c_1(void);
void	delay_i2c_2(void);

//===========================================================================		
//
//===========================================================================		
#endif 