#ifndef TOUCH_SENSOR_API_INTERFACE
#define TOUCH_SENSOR_API_INTERFACE

#define TouchSensorDriverID 0xf001f000

typedef int (*SensorHandler_t) (void *);

int touchSensorServer (void *);


enum ListOfSensorHandlers {
    onAnyActionHandler      = (0),
    onClickHandler          = (1),
    onReleaseHandler        = (2),
    onSlideUpHandler        = (3),
    onSlideDownHandler      = (4),
    onSlideLeftHandler      = (5),
    onSlideRightHandler     = (6),
    onLongPress             = (7),
    
    __EOF_HandlersList,
  
};


#endif


/*End of file*/

