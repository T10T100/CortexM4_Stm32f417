#ifndef TOUCH_SCREEN_INTERFACE
#define TOUCH_SCREEN_INTERFACE

#define StubTouchDriver -1
#define tsc2046 1




#define DefaultTouchDriver tsc2046






#ifndef DefaultTouchDriver
#define DefaultTouchDriver StubTouchDriver
#endif

#if (DefaultTouchDriver == StubTouchDriver)
    #error "cannot implement touch input service"
#endif

#if (DefaultTouchDriver == tsc2046)
    #include "tsc2046.h"
#endif

#include "syncClass.h"
#include "vmapi.h"
#include "arrayListStatic.h"
#include "touchSensorApiInterface.h"

typedef struct SensorDataStruct {
    Point<int32_t> coordinates;
    int32_t clickCount;
    bool click;
    bool release;
    bool tousch;
} SensorDataStruct;

class SensorAdapter {
    private :
          Point<int32_t> lastDetectedPosition;
		  int32_t measuredPressure;
    
          SensorMcu Mcu;
          int32_t lastAction;
    
    
    public :
        SensorAdapter () {}
        void operator () ()
        {
            this->Mcu.Init();
            lastAction = -1;
        }
        
        bool SetUp (float x0, float y0, float x1, float y1)
        {
            return true;
        }

        
        Box<int16_t> Read ()
        {
          Box<int16_t> rect = {0, 0, 0, 0};
            
          rect.x = this->lastDetectedPosition.x;
          rect.y = this->lastDetectedPosition.y;
          return rect;    
        }

        void TouchSensorIT ()
        {  
            CriticalObject critical;
           
            this->measuredPressure += (Mcu.ReadZ() - this->measuredPressure) / 3;
            if (this->measuredPressure > (int32_t)TOUCH_REF) {
              this->lastDetectedPosition = Mcu.ReadPos(); 
              lastAction = onAnyActionHandler;
            }
            else {
            }		     
        }
        
        SensorDataStruct getData ()
        {
            SensorDataStruct data = {
                lastDetectedPosition,
                0,
                false,
                false,
                false,
            };
            return data;
        }
        
};







#endif

/*End of file*/

