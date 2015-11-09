




#include "gpio_ex.h"
#include "init.h"

int32_t DEV_Gpio_Init (GPIO_TypeDef *port, int pin_bm, uint32_t mode, uint32_t pupd)
{
	GPIO_InitStruct.Mode     = mode;
    GPIO_InitStruct.Pull     = pupd;
    GPIO_InitStruct.Speed    = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Pin      = pin_bm;
	
	HAL_GPIO_Init(port, &GPIO_InitStruct);	
	return 0;
}

int32_t DEV_AltGpio_Init (GPIO_TypeDef *port, int pin_bm, uint32_t mode, uint32_t alt)
{
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Mode      = mode;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pin       = pin_bm;
  GPIO_InitStruct.Alternate = alt;
	
  HAL_GPIO_Init(port, &GPIO_InitStruct);	
	return 0;
}
/*
void DEV_Pin_Set (GPIO_TypeDef *port, uint32_t pin_bm)
{
	port->BSRR = pin_bm;
}

void DEV_Pin_Clr (GPIO_TypeDef *port, uint32_t pin_bm)
{
	port->BSRR = pin_bm << 16;
}

void DEV_Pin_Tog (GPIO_TypeDef *port, uint32_t pin_bm)
{
	port->ODR ^= pin_bm;
}

void DEV_Pin_Put (GPIO_TypeDef *port, uint32_t pin_bm, bool val)
{
	if (val) DEV_Pin_Set(port, pin_bm);
	else DEV_Pin_Clr(port, pin_bm);
}

void DEV_Port_Out (GPIO_TypeDef *port, uint32_t val, uint32_t mask)
{
	port->BSRR = mask;
	port->BSRR = val;
}

bool DEV_Pin_Read (GPIO_TypeDef *port, uint32_t pin_bm)
{
	return (bool)(port->IDR & pin_bm);
}
*/

void SpiSoftTypeDef::dummyWait (uint32_t _us)
{
	for (int i = _us; i > 0; i--)
			asm volatile ("nop \n\t");
}

void SpiSoftTypeDef::init (void)
{
	DEV_Pin_Set(Lcd_Cs_Port, LCD_CS_Pin);
	DEV_Pin_Clr(Lcd_Sck_Port, LCD_SCK_Pin);
	DEV_Pin_Clr(Lcd_Mosi_Port, LCD_MOSI_Pin);
}

void SpiSoftTypeDef::select (void)
{
	DEV_Pin_Clr(Lcd_Cs_Port, LCD_CS_Pin);
}

void SpiSoftTypeDef::deSelect (void)
{
	DEV_Pin_Set(Lcd_Cs_Port, LCD_CS_Pin);
}

void SpiSoftTypeDef::dummyClock (void)
{
	DEV_Pin_Clr(Lcd_Sck_Port, LCD_SCK_Pin);
	DEV_Pin_Set(Lcd_Sck_Port, LCD_SCK_Pin);
}

void SpiSoftTypeDef::send_9bit_Data (bool bit, uint8_t data)
{
	DEV_Pin_Clr(Lcd_Sck_Port, LCD_SCK_Pin);
	DEV_Pin_Put(Lcd_Mosi_Port, LCD_MOSI_Pin, bit);
	this->select();
	DEV_Pin_Set(Lcd_Sck_Port, LCD_SCK_Pin);
	for (int i = 7; i >= 0; i--) {
		  DEV_Pin_Clr(Lcd_Sck_Port, LCD_SCK_Pin);
		  DEV_Pin_Put(Lcd_Mosi_Port, LCD_MOSI_Pin, (data >> i) & 1);	
      DEV_Pin_Set(Lcd_Sck_Port, LCD_SCK_Pin);		
	}  
	this->deSelect();
}
			
uint8_t SpiSoftTypeDef::read_8bit_Data (void)		
{
	/*
	uint8_t Data = 0;
	this->Select();
	this->DummyClock();
	for (int i = 7; i >= 0; i--) {
		  DEV_Pin_Clr(Lcd_Sck_Port, LCD_SCK_Pin);
		  Data |= (MISO_Pin->Read() << i);
      DEV_Pin_Set(Lcd_Sck_Port, LCD_SCK_Pin);	
	} 
	this->DummyClock();
	this->DeSelect();
	return Data;
	*/
    return 0;
}

