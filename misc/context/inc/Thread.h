#ifndef THREAD_RUNNABLE
#define THREAD_RUNNABLE
#include "stdint.h"
#include "memory_template.h"
#include "contextSwitching.h"

typedef uint32_t word;

enum RunnableStatus{
  Stopped = 0,
  Running = 1,
  Pending = 2,
};


class Runnable {
    private :
        int(*runnable)(Runnable *);
        int status;
        uint32_t stackRoof;
        uint32_t stackFloor;
        void *frameSuspended;
    public :
    Runnable ()
    {
        status = Stopped;
        runnable = nullptr;
        stackRoof = 0;
        stackFloor = 0;
    }
    
    void operator () (int(*r)(Runnable *), uint32_t stack)
    {
        status = Stopped;
        runnable = r;
        stackRoof = stack;
        stackFloor = stack;
    }
    
    
    void *Run ()
    {
        status = Running;
        return 0;
    }
    
    
    
    void setRunnableAndRestart (int(*r)(Runnable *))
    {
        this->runnable = r;
    }
    
    
    bool equals (Runnable *)
    {
        return true;
    }
    void *getFrame ()
    {
        return this->frameSuspended;
    }
    void setFrame (void *frame)
    {
        this->frameSuspended = frame;
    }
    
    int getStatus ()
    {
        return this->status;
    }
    void *getRunnable ()
    {
        return this->runnable;
    }
    uint32_t getStackRoof ()
    {
        return this->stackRoof;
    }
    void setStatus (RunnableStatus status)
    {
        this->assert(status);
        this->status = status;
    }
    
    
    
    
    
    template <typename A>
        bool assert (A a)
        {
            
        }
    
};

typedef int (* Runnable_t) (Runnable *);


#endif


/*End of file*/

