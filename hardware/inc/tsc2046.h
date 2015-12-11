

#ifndef __TSC2046
#define __TSC2046
#include <stdint.h>
#include <math.h>
#include "Dimensions.h"

#define SENSOR_ONTOUCH_RATE 50

struct TouchMcuPreset {
	unsigned start: 1;
	unsigned address: 3;
	unsigned mode: 1;
	unsigned single: 1;
	unsigned sleep: 2;
};

#define SLIDE_REF 30.0F
#define TOUCH_REF 280.0F
#define TOUCH_END_MOVE 5.0F

enum {
	__12BIT__RES,
	__8BIT__RES,
};


class SensorMcu {
	public:
      /*SensorMcu (uint8_t __resx = __12BIT__RES, uint8_t __resy = __12BIT__RES, uint8_t __resz = __12BIT__RES);*/ 
      void Init (uint8_t __resx = __12BIT__RES, uint8_t __resy = __12BIT__RES, uint8_t __resz = __12BIT__RES);
    private:       
	  int32_t Kx, Ky;
	  int16_t xOff, yOff;

	  uint8_t Buffer[2];
	  uint8_t Apply (TouchMcuPreset &Preset);
      uint8_t xPreset, yPreset, zPreset;
	
	  virtual int16_t SerialRead (uint8_t *, uint16_t); 
	  virtual int16_t SerialWrite (uint8_t *, uint16_t);
    
	  int32_t Read  (uint8_t);
	  int32_t ReadX ();
	  int32_t ReadY ();
	  int32_t ReadZ ();
	  int32_t Settling (int16_t, int16_t, int16_t, int16_t);
	  Point<int32_t> ReadPos ();  
    
    friend class SensorAdapter;
};


#endif
