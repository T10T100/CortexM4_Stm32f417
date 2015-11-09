#include "init.h"
#include "gpio_ex.h"

SRAM_HandleTypeDef            hsram;
FMC_NORSRAM_TimingTypeDef     SRAM_Timing;
DMA_HandleTypeDef             DmaHandle,
                              DmaHandleGraphic;
SPI_HandleTypeDef             SpiHandle;
TIM_HandleTypeDef             TimHandle;
TIM_HandleTypeDef             Tim2_Handle;

void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

void ClockEnable (void)
{
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();
  __GPIOE_CLK_ENABLE();
	__GPIOF_CLK_ENABLE();
	__GPIOG_CLK_ENABLE();
	__GPIOH_CLK_ENABLE();
  __ADC1_CLK_ENABLE();
  __ADC2_CLK_ENABLE();
  __DAC_CLK_ENABLE();
  __FSMC_CLK_ENABLE();
  __SPI2_CLK_ENABLE();
  __DMA2_CLK_ENABLE();
  __TIM1_CLK_ENABLE();
  __TIM2_CLK_ENABLE();
}

void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;//RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  /* STM32F405x/407x/415x/417x Revision Z devices: prefetch is supported  */
  if (HAL_GetREVID() == 0x1001)
  {
    /* Enable the Flash prefetch */
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}

void HsramInit (void)
{
  hsram.Instance  = FSMC_NORSRAM_DEVICE;
  hsram.Extended  = FSMC_NORSRAM_EXTENDED_DEVICE;
  
  SRAM_Timing.AddressSetupTime       = 4;
  SRAM_Timing.AddressHoldTime        = 0;
  SRAM_Timing.DataSetupTime          = 5;
  SRAM_Timing.BusTurnAroundDuration  = 0;
  SRAM_Timing.CLKDivision            = 4;
  SRAM_Timing.DataLatency            = 0;
  SRAM_Timing.AccessMode             = FSMC_ACCESS_MODE_A;

  hsram.Init.NSBank             = FSMC_NORSRAM_BANK1;
  hsram.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
  hsram.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram.Init.WrapMode           = FSMC_WRAP_MODE_ENABLE;
  hsram.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
  hsram.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
  hsram.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
  hsram.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;
  /* Initialize the SRAM controller */
  if(HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }    
}

void DacInit (void)
{

}

void AdcInit (void)
{

}

void AdcReinit (ADC_HandleTypeDef &AdcHandle, uint32_t arg0, uint32_t arg1)
{

}

void SpiInit (void)
{
  SpiHandle.Instance               = SPI2;
  SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  SpiHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  SpiHandle.Init.CLKPolarity       = SPI_POLARITY_HIGH;
  SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  SpiHandle.Init.CRCPolynomial     = 7;
  SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  SpiHandle.Init.NSS               = SPI_NSS_SOFT;
  SpiHandle.Init.TIMode            = SPI_TIMODE_ENABLE;
  SpiHandle.Init.Mode              = SPI_MODE_MASTER;  
  if(HAL_SPI_Init(&SpiHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

void DmaInit ()
{

  DmaHandle.Init.Channel = DMA_CHANNEL_1;                     /* DMA_CHANNEL_0                    */
  DmaHandle.Init.Direction = DMA_PERIPH_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_DISABLE;               /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; /* Peripheral data alignment : Word */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;    /* memory data alignment : Word     */
  DmaHandle.Init.Mode = DMA_CIRCULAR;                         /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            /* FIFO mode enabled                */        
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;  
  DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;                /* Memory burst                     */  
  DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;             /* Peripheral burst                 */
  /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
  DmaHandle.Instance = DMA2_Stream3;

  if (HAL_DMA_Init(&DmaHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }  
  DmaHandleGraphic.Init.Channel = DMA_CHANNEL_0;                     /* DMA_CHANNEL_0                    */
  DmaHandleGraphic.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandleGraphic.Init.PeriphInc = DMA_PINC_DISABLE;               /* Peripheral increment mode Enable */
  DmaHandleGraphic.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandleGraphic.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD; /* Peripheral data alignment : Word */
  DmaHandleGraphic.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;    /* memory data alignment : Word     */
  DmaHandleGraphic.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
  DmaHandleGraphic.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandleGraphic.Init.FIFOMode = DMA_FIFOMODE_DISABLE;            /* FIFO mode enabled                */        
  DmaHandleGraphic.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;  
  DmaHandleGraphic.Init.MemBurst = DMA_MBURST_SINGLE;                /* Memory burst                     */  
  DmaHandleGraphic.Init.PeriphBurst = DMA_PBURST_SINGLE;             /* Peripheral burst                 */
  /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
  DmaHandleGraphic.Instance = DMA1_Stream1;

  if (HAL_DMA_Init(&DmaHandleGraphic) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  } 
}

void TimInit (void)
{
  uint32_t __prescaler = (uint32_t) ((SystemCoreClock /2) / 1000) - 1;
  
  TimHandle.Instance = TIM1; 
  TimHandle.Init.Period = 50 - 1;
  TimHandle.Init.Prescaler = __prescaler;
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }
  
	
  if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    Error_Handler();
  }
	
	__prescaler = (uint32_t) ((SystemCoreClock /2) / 1000) - 1;
  
  Tim2_Handle.Instance = TIM2;
  Tim2_Handle.Init.Period = 1000 - 1;
  Tim2_Handle.Init.Prescaler = __prescaler;
  Tim2_Handle.Init.ClockDivision = 10;
  Tim2_Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&Tim2_Handle) != HAL_OK)
  {
    Error_Handler();
  }

  if(HAL_TIM_Base_Start_IT(&Tim2_Handle) != HAL_OK)
  {
    Error_Handler();
  }
	HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0 ,1);
  HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 0 ,1);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void GpioInit (void)
{

  DEV_Gpio_Init(Lcd_light_Port, lcd_led_pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
  DEV_Gpio_Init(Lcd_Miso_Port, LCD_MISO_Pin, GPIO_MODE_INPUT, GPIO_PULLDOWN);
  DEV_Gpio_Init(Lcd_Mosi_Port, LCD_MOSI_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
  DEV_Gpio_Init(Lcd_Sck_Port, LCD_SCK_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
  DEV_Gpio_Init(Lcd_Cs_Port, LCD_CS_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
	DEV_Gpio_Init(Lcd_Reset_Port, LCD_Reset_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
    
  DEV_Gpio_Init(Lcd_Clk_Port, LCD_Clk_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN);
  DEV_Gpio_Init(Lcd_Vsync_Port, LCD_Vsync_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN);
  DEV_Gpio_Init(Lcd_Hsync_Port, LCD_Hsync_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN);
  DEV_Gpio_Init(Lcd_Den_Port, LCD_Den_Pin, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN);
  
  DEV_Gpio_Init(Lcd_Rgb_Port, GPIO_PIN_All, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
	
  DEV_AltGpio_Init(GPIOD, 
								              	FSMC_D2  |
	                              FSMC_D3  |
	                              FSMC_NOE |
	                              FSMC_NWE | 
	                              FSMC_NE1 | 
	                              FSMC_D13 |
	                              FSMC_D14 |
	                              FSMC_D15 |
	                              FSMC_A16 |
	                              FSMC_A17 |
	                              FSMC_A18 |
	                              FSMC_D0  |
	                              FSMC_D1  ,
		                                       GPIO_MODE_AF_PP, GPIO_AF12_FSMC);
  DEV_AltGpio_Init(GPIOE, 
								                FSMC_NBL0 |
	                              FSMC_NBL1 |
	                              FSMC_D4   | 
	                              FSMC_D5   | 
	                              FSMC_D6   |         
                                FSMC_D7   |  
	                              FSMC_D8   | 
	                              FSMC_D9   | 
	                              FSMC_D10  |          
                                FSMC_D11  | 
	                              FSMC_D12  ,   
		                                       GPIO_MODE_AF_PP, GPIO_AF12_FSMC);
  DEV_AltGpio_Init(GPIOF, 
								                FSMC_A0 |
	                              FSMC_A1 |
	                              FSMC_A2 |
	                              FSMC_A3 |
	                              FSMC_A4 |
	                              FSMC_A5 |
	                              FSMC_A6 |
	                              FSMC_A7 |
	                              FSMC_A8 |
	                              FSMC_A9 ,   
		                                       GPIO_MODE_AF_PP, GPIO_AF12_FSMC);		
  DEV_AltGpio_Init(GPIOG, 
	                              FSMC_A10 |
	                              FSMC_A11 |
	                              FSMC_A12 |
	                              FSMC_A13 |
	                              FSMC_A14 |
	                              FSMC_A15 ,  
		                                       GPIO_MODE_AF_PP, GPIO_AF12_FSMC);		

  /*
  DEV_Gpio_Init(GPIOA, Dac_0, GPIO_MODE_ANALOG, GPIO_NOPULL);
  DEV_Gpio_Init(GPIOA, Dac_1, GPIO_MODE_ANALOG, GPIO_NOPULL);
  DEV_Gpio_Init(GPIOA, Adc_0, GPIO_MODE_ANALOG, GPIO_NOPULL);
  DEV_Gpio_Init(GPIOA, Adc_1, GPIO_MODE_ANALOG, GPIO_NOPULL);
  
  DEV_AltGpio_Init(GPIOB,  SCK_Pin, GPIO_MODE_AF_PP,  GPIO_AF5_SPI2);
  DEV_AltGpio_Init(GPIOB, MOSI_Pin, GPIO_MODE_AF_PP, GPIO_AF5_SPI2);
  DEV_AltGpio_Init(GPIOB, MISO_Pin, GPIO_MODE_AF_PP, GPIO_AF5_SPI2);
   
	DEV_Gpio_Init(Buzzer_Port, Buzz, GPIO_MODE_OUTPUT_PP, GPIO_PULLDOWN);
  DEV_Gpio_Init(GPIOD, FSMC_CLK, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
		

	
    
  DEV_Gpio_Init(GPIOE, CH_Amp_0 | CH_Amp_1 | CH_Amp_2, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP); 
  DEV_Gpio_Init(GPIOA, CH_Sel_0, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
  DEV_Gpio_Init(GPIOA, Buzz, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);
  DEV_Gpio_Init(GPIOB, AD_StdbyPin, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP);  
  
  DEV_Gpio_Init(GPIOC, CSO_Pin, GPIO_MODE_INPUT, GPIO_PULLDOWN);
  DEV_Gpio_Init(GPIOC, VSO_Pin, GPIO_MODE_INPUT, GPIO_PULLDOWN);
  DEV_Gpio_Init(GPIOE, BBPO_Pin, GPIO_MODE_INPUT, GPIO_PULLDOWN);
	*/
}


