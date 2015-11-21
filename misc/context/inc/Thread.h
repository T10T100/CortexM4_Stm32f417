#ifndef THREAD_RUNNABLE
#define THREAD_RUNNABLE
#include "stdint.h"
#include "memory_template.h"
#include "contextSwitching.h"
#include "arrayListStatic.h"

typedef uint32_t word;

enum RunnableStatus{
  Stopped = 0,
  Running = 1,
  Pending = 2,
};

typedef /*bit-band*/ struct {
    unsigned sleepTime:     16;
    int8_t priority;
    unsigned waitNotify:    1;
    unsigned waitThread:    1;
    unsigned waitEvent:     1;
    unsigned irreevant:     1;
    unsigned waitPipe:      1;
    unsigned waitDriver:    1;
    unsigned waitResource:  1;
    unsigned stackOverhead: 1;
    unsigned unrecognized:  1;
    unsigned tokeSignal:    1;
    
} TCB;

class Runnable : public DefaultArrayListBaseNode<Runnable> {
    private :
        int(*runnable)(Runnable *);
        int status;
        Word stackRoof;
        Word stackFloor;
        TCB tcb;
        void *frameSuspended;
        ArrayListBase<Runnable> *links;
    void initTcb (uint32_t priority)
    {
        tcb.irreevant = 0;
        tcb.sleepTime = 0;
        tcb.stackOverhead = 0;
        tcb.tokeSignal = 0;
        tcb.unrecognized = 0;
        tcb.waitDriver = 0;
        tcb.waitEvent = 0;
        tcb.waitNotify = 0;
        tcb.waitPipe = 0;
        tcb.waitResource = 0;
        tcb.waitThread = 0;
        tcb.priority = priority;
    }
    public :
        Runnable (uint32_t priority) : DefaultArrayListBaseNode<Runnable> ()
    {
        status = Stopped;
        runnable = nullptr;
        stackRoof = 0;
        stackFloor = 0;
        initTcb (priority);
        links = nullptr;
    }
    
    
    
    void operator () (int(*r)(Runnable *), Word stack, uint32_t priority)
    {
        status = Stopped;
        runnable = r;
        stackRoof = stack;
        stackFloor = stack;
        initTcb (priority);
    }
    
    
    bool equals (Runnable &)
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
    
    
    void *getRunnable ()
    {
        return (void *)this->runnable;
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
    int getStatus ()
    {
        return this->status;
    }
    template <typename Resource, typename Other>
    RunnableStatus setNextState ()
    {
        
    }
    
    
    template <typename A>
        bool assert (A a)
        {
            return false;
        }
    
};

typedef int (* Runnable_t) (Runnable *);


#endif


/*End of file*/

