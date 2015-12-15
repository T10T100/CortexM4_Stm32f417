#ifndef TOUCH_SCREEN_INTERFACE
#define TOUCH_SCREEN_INTERFACE

#define StubTouchDriver -1
#define tsc2046 1




#define DefaultTouchDriver tsc2046



#define SensorInertionConstant 0.3F /*So much - so faster - more missmatches*/
#define SensorAccelerationInertConstant 0.3F 


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
#include "gui_Defs.h"

typedef struct SensorDataStruct {
    Point<MaxGuiRange> coordinates;
    Point<MaxGuiRange> move;
    int32_t clickCount;
    bool click;
    bool release;
    bool tousch;
} SensorDataStruct;

class SensorAdapter {
    private :
          Point<MaxGuiRange> position;
          Point<MaxGuiRange> acceleration;
          Point<MaxGuiRange> lastPosition;
          Point<MaxGuiRange> lastMove;
    
		  int32_t measuredPressure;
    
          SensorMcu Mcu;
          uint32_t lastAction;
    
          bool touchAction;
          bool releaseAction;
          bool stdby;
    
          float Kx, Ky;
          float offX, offY;
    
          Point<MaxGuiRange> normalize (Point<MaxGuiRange> p)
          {
              int32_t x = p.x << 4;
              int32_t y = p.y << 4;
              
              x = (x / 17) >> 3;
              y = (y / 25) >> 3;
              
              p.x = (int32_t)x + 0;
              p.y = (int32_t)y + 0;
              p.x = 480 - p.x;
              return p;
          }
    
    public :
        SensorAdapter () {}
        void operator () ()
        {
            this->Mcu.Init();
            lastAction = 0;
            Kx = 0.138F;
            Ky = 0.1F;
            offX = 70.0F;
            offY = 50.0F;
            lastMove.x = 0;
            lastMove.y = 0;
            lastPosition.x = 0;
            lastPosition.y = 0;
            position.x = 0;
            position.y = 0;
        }
        

        

        uint32_t TouchSensorIT ()
        {  
            //CriticalObject critical;
            
            lastAction = 0;
            measuredPressure = Mcu.ReadZ();
            if (this->measuredPressure > (int32_t)TOUCH_REF) {
                lastPosition = position;
                Point<int32_t> p = Mcu.ReadPos();
                position.x = p.x;
                position.y = p.y;
                position = normalize( position ); 
                
                acceleration.x += (lastMove.x - acceleration.x) / 2;
                acceleration.y += (lastMove.y - acceleration.y) / 2;
                
                if (touchAction == true) {
                    lastMove.x = -(lastPosition.x - position.x);
                    lastMove.y = position.y - lastPosition.y;
                }
                if (stdby == true) {
                    touchAction = true;
                    releaseAction = false;
                    stdby = false;
                    lastAction = onClickHandler + 1;
                } else {
                    lastAction = onAnyActionHandler + 1;
                }
                touchAction = true;
            }
            else {
                if (touchAction == true) {
                    releaseAction = true;
                    touchAction = false;
                    lastAction = onReleaseHandler + 1;
                } else {
                    stdby = true;
                }
                
                    
            }	
            return lastAction;           
        }
        
        SensorDataStruct getData ()
        {
            SensorDataStruct data = {
                position,
                lastMove,
                0,
                false,
                false,
                false,
            };
            return data;
        }
        
        uint32_t getAction ()
        {
            return lastAction;
        }
        
};







#endif

/*End of file*/

