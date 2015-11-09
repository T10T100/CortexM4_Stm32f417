

#include "Device.h"
#include "extern.h"




Runtime runtime;
Device device;

SpiSoftTypeDef spiLcd;
MemoryAllocator Heap;

void *Alloc (uint32_t size)
{
    return Heap.New(size);
}

int32_t Free (void *p)
{
    return Heap.Delete(p);
}

void *operator new[] (uint32_t size)
{
    return Alloc(size);
}
void operator delete[] (void *p)
{
    Free(p);
}

extern void CMSIS_Tick()
{
     HAL_IncTick();
}


/*
int32_t LcdDriverDef::ExtInput (b2D, uint32_t)
{
	return -1;
}

MemoryAllocator Heap;

SpiSoftTypeDef LcdSpi;
LcdDriverDef TFT(Lcd_Rgb_Port, LcdSpi, 0xffff0000);

void LcdDriverDef::BcklApply(uint8_t level)
{
	if (level)
	    DEV_Pin_Set(Lcd_light_Port, lcd_led_pin ); 
}

Frame2DManager<gbasic_t> FrameManager;

template <typename T>
void Frame2D<T>::DmaTransfer(ColorTypeDef *dst, ColorTypeDef *src, uint32_t lenght)
{
	//HAL_DMA_Start(&DmaHandleGraphic, (uint32_t)src, (uint32_t)dst, lenght);
}
ScreenManager ScreenMang;


*/


