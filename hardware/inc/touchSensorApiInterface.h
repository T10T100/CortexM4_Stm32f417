#ifndef TOUCH_SENSOR_API_INTERFACE
#define TOUCH_SENSOR_API_INTERFACE

#define TouchSensorDriverID 0xf001f000

typedef int (*SensorHandler_t) (void *);

int touchSensorServer (void *);


enum ListOfSensorHandlers {
    onAnyActionHandler      = (1 << 0),
    onClickHandler          = (1 << 1),
    onReleaseHandler        = (1 << 2),
    onSlideUpHandler        = (1 << 3),
    onSlideDownHandler      = (1 << 4),
    onSlideLeftHandler      = (1 << 5),
    onSlideRightHandler     = (1 << 6),
    onLongPress             = (1 << 7),
    
    __EOF_HandlersList,
  
};


#endif


/*End of file*/

