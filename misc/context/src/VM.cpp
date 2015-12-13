#include "VM.h"

extern Runtime runtime;
extern Device  device;

__value_in_regs DwArg vmtick (void *arg)
{
    return runtime.dispatch(arg);
}
__value_in_regs DwArg vmsvc (SVC_arg arg)
{
   return runtime.dispatchSVC(arg); 
}

__value_in_regs DwArg vmfault (SVC_arg arg)
{
    Graphic<ColorDepth> *g = device.contentPane->getGraphic();
    
    device.contentPane->fill(0xC000);
    auto frame = (RuntimeFrame *)arg.a3;
    g->setText("Hard Fault Error at address :  \n", 0xffff);
    
    g->apendText( "PC -> ", 0xffff);
    g->apendText( g->toHexString(frame->PC), 0xffff);
    g->apendText( ";\n", 0xffff);
    
    g->apendText( "(PC - 1) ->", 0xffff);
    g->apendText( g->toHexString( *(uint32_t *)(frame->PC) ), 0xffff);
    g->apendText( ";\n(PC) ->", 0xffff);
    g->apendText( g->toHexString( *(uint32_t *)(frame->PC - 4) ), 0xffff);
    g->apendText( ";\n", 0xffff);
    
    g->apendText( "XPSR -> ", 0xffff);
    g->apendText( g->toHexString(frame->XPSR), 0xffff);
    g->apendText( ";\n", 0xffff);
    
    g->apendText( "Thread -> ", 0xffff);
    g->apendText( runtime.running->getName() , 0xffff);
    g->apendText( ";\n", 0xffff);
    
    g->apendText( "Thread Stack address-> ", 0xffff);
    g->apendText( g->toHexString(arg.a3), 0xffff);
    g->apendText( ";\n", 0xffff);
    
    device.fill(device.contentPane->getFrame());
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
__value_in_regs DwArg VMHardFault (SVC_arg arg)
{
    return vmfault(arg);  
}

extern "C"
void *StackSwitchPSV (void *frame, int32_t link)
{
    return frame;
}


