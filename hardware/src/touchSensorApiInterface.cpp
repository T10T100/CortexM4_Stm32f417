#include "touchSensorApiInterface.h"
#include "touchScreenAdapter.h"
#include "vmapi.h"
#include "vm.h"

uint32_t touchSensorDriverID = TouchSensorDriverID;


int touchSensorServer (void *r)
{
    auto i = (ServerInterface<DefaultServerListener> *)r;
    for (;;)
    {
        auto adapter = (SensorAdapter *)i->getUserObject();
        adapter->TouchSensorIT();
        i->fireAll();
        /*
        switch () {
            case onAnyActionHandler: onAnyActionHandler_t (server);
                break;
            case onClickHandler: onClickHandler_t (server);
                break;
            case onReleaseHandler: onReleaseHandler_t (server);
                break;
            case onSlideUpHandler: onSlideUpHandler_t (server);
                break;
            case onSlideDownHandler: onSlideDownHandler_t (server);
                break;
            case onSlideLeftHandler: onSlideLeftHandler_t (server);
                break;
            case onSlideRightHandler: onSlideRightHandler_t (server);
                break;
            default :
                break;
        }
        */
        i->close();
        vm::close();
    }
}