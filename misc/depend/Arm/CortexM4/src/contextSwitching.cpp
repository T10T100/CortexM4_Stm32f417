
#include "contextSwitching.h"

extern void CMSIS_Tick();
extern void *server(void *, void *);

extern "C"
void *StackSwitch (void *frame, void *link)
{
    CMSIS_Tick();
    return server (frame, link);
}

extern "C"
void *StackSwitchPSV (void *frame, void *)
{
    return frame;
}


