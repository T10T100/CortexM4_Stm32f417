
#include "tsc2046.h"

void SensorMcu::Init (uint8_t __resx, uint8_t __resy, uint8_t __resz)
{
	this->Kx = this->Ky = 1;
	this->xOff = this->yOff = 0;
    TouchMcuPreset preset;
	
	preset.start = 1;
	preset.address = 0x01;
	preset.mode = __resx;
	preset.single = 0;
	preset.sleep = 0x00;
    this->xPreset = this->Apply(preset);
	
	preset.address = 0x05;
	preset.mode = __resy;
    this->yPreset = this->Apply(preset);
	
	preset.address = 0x03;
	preset.mode = __resz;
    this->zPreset = this->Apply(preset);
    xOff = 70;
    yOff = 50;
		
    Kx = 1;
    Ky = 1;	
}

uint8_t SensorMcu::Apply (TouchMcuPreset &Preset)
{
uint8_t __byte =    (Preset.start   << 7) |
                    (Preset.address << 4) | 
	                (Preset.mode    << 3) | 
	                (Preset.single  << 2) | 
	                (Preset.sleep   << 0) ;	
return __byte;
}

int32_t SensorMcu::Read  (uint8_t preset)
{
	int32_t __temp;
    Buffer[0] = preset;
    Buffer[1] = 0;
	this->SerialWrite(Buffer, 1);
	this->SerialRead(Buffer, 2);
	__temp = *(uint16_t *)Buffer;
	if (! (preset & 0x08))
	    __temp = __temp >> 4;
	else __temp = __temp >> 8;
	return __temp;	
}
int32_t SensorMcu::ReadX ()
{
	return this->Read(this->xPreset);
}
int32_t SensorMcu::ReadY ()
{
	return this->Read(this->yPreset);
}
int32_t SensorMcu::ReadZ ()
{
	return this->Read(this->zPreset);
}



Point<int32_t> SensorMcu::ReadPos ()
{
	Point<int32_t> __pos;
	__pos.x = (int32_t)this->ReadX();
	__pos.y = (int32_t)this->ReadY();
	
	return __pos;
}

