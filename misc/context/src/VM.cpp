#include "VM.h"

extern Runtime runtime;

__value_in_regs DwArg vmtick (void *arg)
{
    return runtime.dispatch(arg);
}
__value_in_regs DwArg vmsvc (SVC_arg arg)
{
   return runtime.dispatchSVC(arg); 
}
__value_in_regs DwArg vmstart()
{
    return runtime.run();
}
int vminit (uint32_t heapStart, uint32_t heapSize)
{
    return runtime.init(heapStart, heapSize);
}

int eventServerFinish ()
{
    return 0;
}

extern void CMSIS_Tick();

extern "C"
    void *RuntimeInit (void *p)
    {
       /*TODO  Auxiliary Control Register of SCB - set DISMCYCINT, DISFOLD ? 
        Write SCR
        Writte CCR
        Write other control registers
        */
       return (void *)0;
    }


extern "C"
__value_in_regs DwArg VMTick (void *arg)
{
    CMSIS_Tick();
    return vmtick (arg);
}

extern "C"
void *VMInit (SVC_arg arg)
{
    return (void *)vminit(arg.a1, arg.a2);
}

extern "C"
__value_in_regs DwArg VMStart ()
{
    return vmstart();
}

extern "C"
__value_in_regs DwArg VMSvc (SVC_arg arg)
{
    return vmsvc(arg);  
}

extern "C"
void *StackSwitchPSV (void *frame, int32_t link)
{
    return frame;
}


