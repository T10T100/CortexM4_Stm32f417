#include "VM.h"

extern Runtime runtime;

extern void *server(void *frame, int32_t link)
{
   return runtime.manageThreads(frame, link); 
}

int SystemEventBurner (Runnable *r)
{
    for (;;) {
        
    }
}

int SystemEventBurner2 (Runnable *r)
{
    for (;;) {
        
    }
}

