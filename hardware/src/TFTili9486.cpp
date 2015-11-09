
#include "init.h"
#include "TFTili9486.h"


void LcdDriverDef::DummyCycle (uint32_t __cnt)
{
	while (__cnt--);
}
uint16_t LcdDriverDef::WrCmd8 (uint8_t __data)
{
           this->SPI_Port->Send_9bit_Data (0, __data); 
           return 0;
}
uint16_t LcdDriverDef::WrData8 (uint8_t __data)
{
           this->SPI_Port->Send_9bit_Data (1, __data); 
           return 0;
}		
uint8_t LcdDriverDef::Rd8 (void)
{
  this->WrCmd8( 0xDA);
	return this->SPI_Port->Read_8bit_Data();
}
uint16_t LcdDriverDef::RstHw (void)
{
	DEV_Pin_Set(Lcd_Reset_Port, LCD_Reset_Pin);
  HAL_Delay(1);
	DEV_Pin_Clr(Lcd_Reset_Port, LCD_Reset_Pin);
	HAL_Delay(1);
	DEV_Pin_Set(Lcd_Reset_Port, LCD_Reset_Pin);
  HAL_Delay(150);  
  return 0; 
}
void LcdDriverDef::DotClk (void)
{
	DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
	DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin); 
}
void LcdDriverDef::DotClk (uint32_t cnt)
{
  while (cnt--) {
      DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
	    DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin); 
	}		
}
void  LcdDriverDef::HsClk (void)
{
	DEV_Pin_Clr(Lcd_Den_Port, LCD_Den_Pin); 
	DEV_Pin_Clr(Lcd_Hsync_Port, LCD_Hsync_Pin);
  this->DotClk(3);
  DEV_Pin_Set(Lcd_Hsync_Port, LCD_Hsync_Pin);
  DEV_Pin_Set(Lcd_Den_Port, LCD_Den_Pin); 
}
void LcdDriverDef::VsClk (void)
{
	DEV_Pin_Clr(Lcd_Vsync_Port, LCD_Vsync_Pin); 
  this->HsClk();
  DEV_Pin_Set(Lcd_Vsync_Port, LCD_Vsync_Pin); 
}
void LcdDriverDef::PutColor (ColorTypeDef color)
{
	DEV_fPort_Out (Lcd_Rgb_Port, color);
}
uint32_t LcdDriverDef::Fill (ColorTypeDef __color, uint16_t __x, uint16_t __y)
{
  this->PutColor(__color);
  for (int i = __x; i > 0; i--) {
      for (int t = __y; t > 0; t--) {
          this->DotClk();								
      }
      this->HsClk();
  }
  this->VsClk();
  return 0;
}
 
uint32_t LcdDriverDef::Fill (const tImage &Image, uint32_t __scaleX, uint32_t __scaleY)
{
  uint32_t Hcnt = 0;
  uint32_t Hscaled = Image.H * __scaleX;
  uint32_t Dcnt = __scaleY; 
  for (int i = 0; i < Hscaled; i++) {
      for (int t = 0; t < Image.W; t++) {
				   DEV_fPort_Out (this->RGB_Port, *(Image.Image + Hcnt +  t));
           while (Dcnt--) {
                 DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
	               DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);   
           } 
           Dcnt = __scaleY;
      }
      Hcnt = (i / __scaleX) * Image.W;
      this->HsClk();
  }
  this->VsClk();
  return 0;
}
uint32_t LcdDriverDef::Fill (Frame2D<gbasic_t> &Frame, b2D rect)
{
	uint32_t W = rect.w, H = rect.h;
	uint32_t h = Frame.GetH();
	uint32_t h0 = Frame.GetRect().y + rect.y;
	uint32_t D = (W + Frame.GetRect().x + rect.x) * h;
	uint32_t nClk = LCD_Clk_Pin << 16;
	ColorTypeDef *Memo = Frame.GetBuff();
	this->Window(0, 0, W, H);
	
  for (int32_t __x = D; __x > 0 ; __x -= h) { 
      for (uint32_t __y = h0; __y < H + h0; __y++) {
				  DEV_fPort_Out (this->RGB_Port, *(Memo + __y + __x));
          DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
          DEV_Pin_Set(Lcd_Clk_Port, nClk);  
      }
      this->HsClk();
  }
  this->VsClk();
  return 0;
}

bool Test (uint16_t x, uint16_t y)
{
		return false;
}
LcdDriverDef::LcdDriverDef (
                             GPIO_TypeDef *RGB_Port,  \
                             SpiSoftTypeDef &SPI_Port,\
                             uint32_t color_mask      )
{
  this->RGB_Port = RGB_Port;
  this->SPI_Port = &SPI_Port;
  this->Color_Mask = color_mask;
}

uint16_t LcdDriverDef::Window (uint16_t __X, uint16_t __Y, uint16_t __dW, uint16_t __dH)
	{
		__IntToByte __TransferA, __TransferB;
		__TransferA.Int = __Y;
		__TransferB.Int = __Y + __dH;
        
		this->WrCmd8(LcdCmdCASET);
		this->WrData8(__TransferA.Byte[1]);
		this->WrData8(__TransferA.Byte[0]);
		this->WrData8(__TransferB.Byte[1]);
		this->WrData8(__TransferB.Byte[0]);
		__TransferA.Int = __X;
		__TransferB.Int = __X + __dW;
		this->WrCmd8(LcdCmdPASET);
		this->WrData8(__TransferA.Byte[1]);
		this->WrData8(__TransferA.Byte[0]);
		this->WrData8(__TransferB.Byte[1]);
		this->WrData8(__TransferB.Byte[0]);
        
    this->DotClk(1);this->VsClk();
		return 0;
	}
	
uint16_t LcdDriverDef::Init (uint32_t __mode)
{
	this->RstHw();
	this->WrCmd8(LcdCmdSWRESET);//Soft Reset
	HAL_Delay(150);
	
	this->WrCmd8(LcdCmdPWCTRL1);//power control
	this->WrData8(0x15);//Vreg1out
	this->WrData8(0x12);//Vreg2out
	
	this->WrCmd8(LcdCmdPWCTRL2);//power control2
	this->WrData8(0x41);//VGH/VGL
	
	this->WrCmd8(LcdCmdVMCTRL);//VCOM Control 1
	this->WrData8(0x00);//nVM
	this->WrData8(0x4A);//VCM_REG [7:0] 
	this->WrData8(0x80);//VCM_REG_EN 
	
	this->WrCmd8(LcdCmdMADCTL);//memory access
	this->WrData8(0x48);//
    
	this->WrCmd8(LcdCmdCOLMOD);//Interface Pixel Format
	this->WrData8(0x50);//
	
	this->WrCmd8(LcdCmdIFMODE);//Interface Mode Control 
	this->WrData8(0x02);//
	
	this->WrCmd8(LcdCmdINVTR);//Display Inversion Control
	this->WrData8(0x00);//
	
	this->WrCmd8(LcdCmdDISCTRL);//RGB/MCU interface
	this->WrData8(0x20);//
  this->WrData8(0x0F);//source/Gate direction
	
	this->WrCmd8(LcdCmdSETIMAGE);//set image function
  this->WrData8(0x00);//disable 24 bit data input
	
	
	
  this->WrCmd8(LcdCmdAdjustControl3);//adjust control
	this->WrData8(0xA9);//
	this->WrData8(0x52);//
	this->WrData8(0x2C);//
	this->WrData8(0x82);//
	
	
	HAL_Delay(150);
	this->WrCmd8(LcdCmdSLPOUT);//Sleep Out
	HAL_Delay(150);
	this->WrCmd8(LcdCmdDISON);//Display On
	HAL_Delay(15);
    
  return 0;
}

void LcdDriverDef::Backlight(uint8_t level)
{
	this->BcklApply(level);
}

