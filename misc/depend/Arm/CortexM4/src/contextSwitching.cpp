
#include "contextSwitching.h"

extern void CMSIS_Tick();
extern void *server(void *,int32_t);
extern void *psalloc (uint32_t);

extern "C"
    void *RuntimeInit (void *p)
    {
       return (void *)0x1000F000; 
    }

extern "C"
void *StackSwitch (void *frame, int32_t link)
{
    CMSIS_Tick();
    return server (frame, link);
}


extern "C"
void *StackSwitchPSV (void *frame, int32_t link)
{
    return frame;
}


