
#include "contextSwitching.h"
#include "cpuControlBlock.h"

#define __svc_indirect_present__

extern void CMSIS_Tick();
extern void *server(void *,int32_t);
extern void *serverSVC(void *,int32_t);
extern void *psalloc (uint32_t);
extern SCB_CPUID readCpuId ();


extern "C"
    void *RuntimeInit (void *p)
    {
       SCB_CPUID cpuId =  readCpuId (); 
       /*TODO  Auxiliary Control Register of SCB - set DISMCYCINT, DISFOLD ? 
        Write SCR
        Writte CCR
        Write other control registers
        */
       return (void *)0;
    }

    
/*TODO 
    Read AIRCR 
    Read from ICSR
    
    */
extern "C"
void *StackSwitch (void *frame, int32_t link)
{
    CMSIS_Tick();
    return server (frame, link);
}

extern SVC_arg serverSVC (SVC_arg);
extern "C"
uint32_t CallSVC (SVC_arg arg)
{
    return serverSVC (arg).a3;
}

#ifdef __svc_indirect_present__
    uint32_t __svc(3) CallSVC (Word a0, Word a1, Word a2);
#endif


extern "C"
void *StackSwitchPSV (void *frame, int32_t link)
{
    return frame;
}


