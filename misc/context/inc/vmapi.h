#ifndef VMAPI_INTERFACE
#define VMAPI_INTERFACE

#include "contextSwitching.h"
#include "Thread.h"

/*
        All modules linked around this file may not be implemented 
        as an operating system. Maintain prorgram builds on call of methods 
        of class "Runtime"this class only implements the some core exceptions
        (like svc, sys_tick..),and can hold up  the whole list of supposed 
        classes that extends class "Runtime".All of object will be linked 
        and have an arbitrary service based on objects priorities. All of runtimes 
        has an individual memory heap, stack and may has strongly formatted program 
        space area, so they can be simply independed, and can work as overlaying
        executable (armV7-m has no mmu - so it still impossible there) for another 
        kernels. No special servers or system calls will be presented, but there is 
        possible to made new class with base class "Runtime" and overload some virtual 
        functions that can extends or simplify controlling an api calls. All of 
        api calls will walk throught the "SVC" assember instruction
        or __svc(n) int func (...); - so it propagates to be one more safe, thanks 
        to ARM designers!
*/

namespace vm {
  



/*Next enumeration contains numeric representation of 
  called supervisor  functions (UpCall) throught SVC exception*/
    
    
  enum VectorNum {
      __init         =  0, 
      __start        =  1,
      __create       =  2,
      __kill         =  3,
      __sleep        =  4,
      __pushEvent    =  5,
      __runtimeDispatchEvent = 6,
      __close        =  7,
      __addTimer     =  8,
      __addSensorListener = 9,
      __invokeServer = 10,
      
      
      
      __EOFVectorApi
      
  };      
    
/*
  */    

__value_in_regs int init (uint32_t heapStart, uint32_t heapSize);
__value_in_regs int start (); 
__value_in_regs int create (Runnable_t entryPoint, uint32_t priority);
__value_in_regs int kill (int cause);
__value_in_regs int sleep (int mills);
__value_in_regs int pushEvent (int (*eventListener) (void *));
__value_in_regs int runtimeDispatchEvent (int (*eventistener) (void *));
__value_in_regs int close (/*server*/); 
__value_in_regs int addTimer (int (*timerListener) (void *), uint32_t);
__value_in_regs int addSensorListener (int (*reqListener) (void *), int32_t);
__value_in_regs int invokeServer (int32_t id);
  
class CleanUp {
    private :
        
    public :
        CleanUp ()
        {
            
        }
        ~CleanUp ()
        {
            kill(-1);
        }
};
    
};





#endif


/*End of file*/


