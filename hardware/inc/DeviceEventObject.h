#ifndef DEVICE_EVENT_OBJECT
#define DEVICE_EVENT_OBJECT
#include "eventObject.h"
#include "eventListener.h"

template <typename Object>
class DeviceEventObject : public EventObject<Object> {
    private :
    
    public : 
        DeviceEventObject (Object o) : EventObject<Object>(o)
        {
            
        }
    
};




#endif


/*End of file*/

