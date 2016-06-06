#include <stdint.h>
#include "capextend_hw.h"

void system_init( void );

sbit RST at GPIOC_ODR.B2;

//Global Declatations
uint8_t address     = 0x2B;
uint8_t my_buffer         = 0;

void main() 
{
     //Local Decalartions
     uint8_t msb        = 0;
     uint8_t lsb        = 0;
     char uart_text[20] = { 0 };
     
     system_init();
     Delay_ms(100);
     
     GPIOD_ODR = 0xFF;

     while(1)
     {
          msb = capextend_read_msb_buttons();
          lsb = capextend_read_lsb_buttons();
          GPIOD_ODR = ( lsb | ( msb << 8 ) );

     }  //While

}  //Main

void system_init( void )
{
     //GPIOs
     GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 );
     GPIO_Digital_Output( &GPIOD_BASE, _GPIO_PINMASK_ALL );

     //Toggle Reset Pin
     RST = 0;
     Delay_ms(50);
     RST = 1;
     Delay_ms(200);
     
     //Initialize UART
     UART1_Init( 9600 );
     Delay_ms(100);
     UART1_Write_Text( "UART Initialized\r\n" );
     
     //Initialize I2C
     I2C1_Init_Advanced( 400000, &_GPIO_MODULE_I2C1_PB67 );
     UART1_Write_Text( "I2C Initialized\r\n" );
     
     //Initialize Cap Extend
     capextend_init( address );
     UART1_Write_Text( "Cap Extend Initialized\r\n" );
     
}
