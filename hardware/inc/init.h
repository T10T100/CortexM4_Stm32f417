




#ifndef __INIT
#define __INIT

#include "main.h"
#include "stdio.h"



enum PinBmEnumDef {
  LCD_MISO_Pin  =      GPIO_PIN_0,       
  LCD_MOSI_Pin  =      GPIO_PIN_1,       
  LCD_SCK_Pin   =      GPIO_PIN_2,       
  LCD_CS_Pin    =      GPIO_PIN_3,        
  LCD_Reset_Pin =      GPIO_PIN_4,         
  LCD_Den_Pin   =      GPIO_PIN_5,         
  LCD_Vsync_Pin =      GPIO_PIN_4,         
  LCD_Clk_Pin   =      GPIO_PIN_2,         
  LCD_Hsync_Pin =      GPIO_PIN_3,         
    
  SCK_Pin       =      GPIO_PIN_10,        
  MISO_Pin      =      GPIO_PIN_11,        
  MOSI_Pin      =      GPIO_PIN_12,        
  CS_Pin        =      GPIO_PIN_15,
  
  lcd_led_pin   =      GPIO_PIN_2,         
       
  PEN           =      GPIO_PIN_9,         
  BUSY          =      GPIO_PIN_8,         
	FSMC_D2       =      GPIO_PIN_0,
	FSMC_D3       =      GPIO_PIN_1,
	FSMC_NOE      =      GPIO_PIN_4,
	FSMC_NWE      =      GPIO_PIN_5, 
	FSMC_NE1      =      GPIO_PIN_7, 
	FSMC_D13      =      GPIO_PIN_8,
	FSMC_D14      =      GPIO_PIN_9,
	FSMC_D15      =      GPIO_PIN_10,
	FSMC_A16      =      GPIO_PIN_11,
	FSMC_A17      =      GPIO_PIN_12,
	FSMC_A18      =      GPIO_PIN_13,
	FSMC_D0       =      GPIO_PIN_14, 
	FSMC_D1       =      GPIO_PIN_15,  
	/*PD*/
	
	/*PE*/
	FSMC_NBL0     =      GPIO_PIN_0,
	FSMC_NBL1     =      GPIO_PIN_1,
	FSMC_D4       =      GPIO_PIN_7, 
	FSMC_D5       =      GPIO_PIN_8, 
	FSMC_D6       =      GPIO_PIN_9,         
    FSMC_D7       =      GPIO_PIN_10,  
	FSMC_D8       =      GPIO_PIN_11, 
	FSMC_D9       =      GPIO_PIN_12, 
	FSMC_D10      =      GPIO_PIN_13,         
    FSMC_D11      =      GPIO_PIN_14, 
	FSMC_D12      =      GPIO_PIN_15, 
	/*PE*/
	
	/*PF*/
	FSMC_A0       =      GPIO_PIN_0,
	FSMC_A1       =      GPIO_PIN_1,
	FSMC_A2       =      GPIO_PIN_2,
	FSMC_A3       =      GPIO_PIN_3,
	FSMC_A4       =      GPIO_PIN_4,
	FSMC_A5       =      GPIO_PIN_5,
	FSMC_A6       =      GPIO_PIN_12,
	FSMC_A7       =      GPIO_PIN_13,
	FSMC_A8       =      GPIO_PIN_14,
	FSMC_A9       =      GPIO_PIN_15,
	/*PF*/
	
	/*PG*/
	FSMC_A10      =      GPIO_PIN_0,
	FSMC_A11      =      GPIO_PIN_1,
	FSMC_A12      =      GPIO_PIN_2,
	FSMC_A13      =      GPIO_PIN_3,
	FSMC_A14      =      GPIO_PIN_4,
	FSMC_A15      =      GPIO_PIN_5,
	/*PG*/
      
           
          
          
         
        
           
           
	
          
          
        
		
};

#define Lcd_Miso_Port      GPIOC
#define Lcd_Mosi_Port      GPIOC
#define Lcd_Sck_Port       GPIOC
#define Lcd_Cs_Port        GPIOC

#define Lcd_Reset_Port     GPIOC
#define Lcd_Den_Port       GPIOH
#define Lcd_Vsync_Port     GPIOH
#define Lcd_Hsync_Port     GPIOH
#define Lcd_Clk_Port       GPIOH
#define Lcd_light_Port     GPIOE
#define Lcd_Rgb_Port       GPIOB

#define Spi3_Sck_Port      GPIOC
#define Spi3_Mosi_Port     GPIOC
#define Spi3_Miso_Port     GPIOC

#define Ad_Stdby_Port      GPIOB
#define Ad_Clk_Port        GPIOD

#define Adc_0_Port         GPIOA
#define Adc_1_Port         GPIOA
#define Adc_Trig_Port      GPIOA

#define Dac_0_Port         GPIOA
#define Dac_1_Port         GPIOA

#define Mux_In_Port        GPIOA
#define Mux_Amp_Port       GPIOE 

#define Buzzer_Port        GPIOA

#define Pal_Cso_Port       GPIOC
#define Pal_Vso_Port       GPIOC
#define Pal_Bbpo_Port      GPIOE

#define Fsmc_Clk_Port      Ad_Clk_Port
#define Fsmc_D0_Port       GPIOD
#define Fsmc_D1_Port       GPIOD
#define Fsmc_D2_Port       GPIOD
#define Fsmc_D3_Port       GPIOD
#define Fsmc_D4_Port       GPIOE
#define Fsmc_D5_Port       GPIOE
#define Fsmc_D6_Port       GPIOE
#define Fsmc_D7_Port       GPIOE

void SystemClock_Config(void);
void Error_Handler(void);
void HsramInit (void);
void SpiInit (void);
void DmaInit (void);
void TimInit (void);
void GpioInit (void);

void ClockEnable (void);


__weak void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
