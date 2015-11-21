#include "VM.h"

extern Runtime runtime;

extern void *server(void *frame, int32_t link)
{
   return runtime.manageThreads(frame, link); 
}
extern SVC_arg serverSVC(SVC_arg arg)
{
   return runtime.manageSVC(arg); 
}



