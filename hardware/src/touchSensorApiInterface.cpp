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
        vm::startCritical();
        server->fireChannel( adapter->getAction() - 1 );
        vm::endCritical();
        server->close();
        vm::close();
    }
}