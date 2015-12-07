#include "TimerServer.h"
#include "vmapi.h"
#include "main.h"

int timerServer (void *r)
{
    static TimerInterface *i = (TimerInterface *)r;
    for (;;) {
        i->fireAll();
        i->close();
        HAL_Delay(1);
        vm::close();
    }
}
/*End of file*/

