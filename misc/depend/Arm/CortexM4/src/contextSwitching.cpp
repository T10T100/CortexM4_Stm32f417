
#include "contextSwitching.h"
#include "cpuControlBlock.h"

extern void CMSIS_Tick();
extern void *server(void *,int32_t);
extern void *psalloc (uint32_t);
extern SCB_CPUID readCpuId ();

extern "C"
    void *RuntimeInit (void *p)
    {
       SCB_CPUID cpuId =  readCpuId (); 
       return (void *)0;
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


