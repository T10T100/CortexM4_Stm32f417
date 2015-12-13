#include "touchSensorApiInterface.h"
#include "touchScreenAdapter.h"
#include "vmapi.h"
#include "vm.h"

uint32_t touchSensorDriverID = TouchSensorDriverID;


int touchSensorServer (void *r)
{
    auto server = (ServerInterface<DefaultServerListener> *)r;
    auto adapter = (SensorAdapter *)server->getUserObject();
    for (;;)
    {
        auto action = adapter->getAction();
        uint32_t t = 0;
        for (int32_t i = 0; action; i++, action >>= 1) {
            if (action & 1) {
                server->fireChannel(i + 1);
            }
        }
        server->close();
        vm::close();
    }
}