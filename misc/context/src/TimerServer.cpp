#include "TimerServer.h"
#include "vmapi.h"
#include "main.h"

int timerServer (void *r)
{
    static TimerInterface *i = (TimerInterface *)r;
    for (;;) {
        i->fireAll();
        HAL_Delay(1);
        i->close();
        vm::close();
    }
}
/*End of file*/

