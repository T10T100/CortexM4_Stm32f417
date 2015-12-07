
#include "vmapi.h"

  
extern "C" __value_in_regs Word upcall (SVC_arg a);

extern int vminit (uint32_t heapStart, uint32_t heapSize);

extern "C" void vmstart();

__value_in_regs int vm::init (uint32_t heapStart, uint32_t heapSize)
{
    return vminit(heapStart, heapSize);
}
__value_in_regs int vm::start ()
{
    vmstart();
    return 0;
}
__value_in_regs int vm::create (Runnable_t runnable, uint32_t priority)
{
    SVC_arg arg = {
        __create,
        (Word)runnable,
        priority,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::kill (int cause)
{
    SVC_arg arg = {
        __kill,
        (Word)cause,
        0,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::sleep (int sleep)
{
    SVC_arg arg = {
        __sleep,
        (Word)sleep,
        0,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::runtimeDispatchEvent ( int (*listener) (void *))
{
    SVC_arg arg = {
        __runtimeDispatchEvent,
        (Word)listener,
        0,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::pushEvent (int (*event) (void *))
{
    SVC_arg arg = {
        __pushEvent,
        (Word)event,
        0,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::close ()
{
    SVC_arg arg = {
        __close,
        (Word)1,
        0,
        0
    };
    return (int)upcall(arg);
}
__value_in_regs int vm::addTimer ( int (*t) (void *), uint32_t period)
{
    SVC_arg arg = {
        __addTimer,
        (Word)t,
        period,
        0
    };
    return (int)upcall(arg);
}

__value_in_regs int vm::addSensorListener ( int (*t) (void *), int32_t id)
{
    SVC_arg arg = {
        __addSensorListener,
        (Word)t,
        (Word)id,
        0
    };
    return (int)upcall(arg);
}

__value_in_regs int vm::invokeServer (int32_t id)
{
    SVC_arg arg = {
        __invokeServer,
        (Word)id,
        0,
        0
    };
    return (int)upcall(arg);
}

/*End of file*/

