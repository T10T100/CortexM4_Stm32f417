#ifndef VM_CLASS
#define VM_CLASS
#include "device.h"
#include "Thread.h"
#include "syncClass.h"
#include "stack.h"
#include "contextSwitching.h"

extern "C"
void *RuntimeStartup (void *, void *);

int SystemEventBurner (Runnable *);
int SystemEventBurner2 (Runnable *);  

enum /*class*/ {
    VReady = 0, /*Ready to start, may only once*/
    VPending = 1, /*Have preserved frame*/
    VWaiting = 2, /*Wait for somekind signal*/
    VEvent = 3,   /*Can be an event burner routine*/
    EndOfThreadTypesEnum
};

    class Runtime : public Synchronizer<Runtime> {
    private :
        MemoryAllocator allocator;
        ArrayList<Runnable> listOfRunnables;
        Runnable *running;
        ArrayListBase<Runnable> arrayOfRunnables[EndOfThreadTypesEnum];
        
        void *manageThreads (void *frame, int32_t param)
        {
            if (syncFetch(this) == false) { 
                return frame;
            }
            if (param == 2) {
                RuntimeFrame *f = (RuntimeFrame *)frame;
                addRunnable ((Runnable_t) f->R0, 0, 480);
                param = 0;
            }
            if (running != nullptr) {
                running->setFrame(frame);
                arrayOfRunnables[running->getStatus()].addLast(running);
            }
            running = nullptr;
            for (int i = 0; i < EndOfThreadTypesEnum; i++) {
                if (arrayOfRunnables[i].isEmpty() == false) {
                    running = arrayOfRunnables[i].removeFirst();
                    break;
                }
            }
            if (running == nullptr) {
                syncRelease(this);
                return frame; 
            }
            void *p = acceptRunnableStatus(frame, running, param);
            syncRelease(this);
            return p;
        }
        
        SVC_arg manageSVC (SVC_arg arg)
        {
            static uint32_t a0 = arg.a0;
            static uint32_t a1 = arg.a1;
            static uint32_t a2 = arg.a2;
            return arg;
        }
        

        void *acceptRunnableStatus (void *link, Runnable *r, int32_t param)
        {
            switch ((int)r->getStatus()) {
                case 0 :
                        RuntimeFrame *f = (RuntimeFrame *)(running->getStackRoof() - (sizeof(RuntimeFrame) * 4));
                        return acceptLink((RuntimeFrame *)link, f, param);
                    break;
                        
                case 1 : 
                        return (void *)running->getFrame();
                
                    break;
                        
                default :
                        return (void *)r->getFrame(); 
            }
            return (void *)r->getFrame();  
        }
        
        void *acceptLink (RuntimeFrame *x, RuntimeFrame *link, int32_t param)
        {
                        if (param == 1) {
                            link->R11 = (uint32_t)running->getRunnable();
                            return (void *)link; 
                        } else {
                            *link = *x;
                            link->PC = (uint32_t)running->getRunnable();
                            running->setStatus(Running);
                            return (void *)link;
                        }            
        }
        
    public :
            
    
        /*Friends*/
        friend void *server(void *frame, int32_t link);
        friend SVC_arg serverSVC (SVC_arg);
        /*Friends*/
    
    
        void *psalloc (uint32_t size)
        {
            return (void *)((uint32_t)allocator.New(size) + size - 4);
        }
        void free (void *p)
        {
            //allocator.Delete(p);
        }
    
        
    
        Runtime ()
        {
            running = nullptr;
        }
        void operator () (uint32_t heapStart, uint32_t heapSize)
        {
           void *error = nullptr;
           this->allocator(heapStart, heapSize);
           addRunnable(SystemEventBurner, 0);
           addRunnable(SystemEventBurner2, 0);
           running->setStatus(Stopped);
           error = RuntimeStartup (0, \
                                    0 /*(void *)((uint32_t)allocator.New(4096 * 4) + 4040 * 4)*/);
        }
        
        Runnable *addRunnable (Runnable_t runnable, uint32_t args)
        {
            while (syncFetch(this) == false) {
                
            }
            Runnable *r = (Runnable *)((uint32_t)allocator.New(sizeof(Runnable) + (200 * 4)));
            (*r)(runnable, (uint32_t)r + sizeof(Runnable) + 200 * 4, 0);
            arrayOfRunnables[VReady].addFirst(r);
            syncRelease(this);
            return r;
        }
        Runnable *addRunnable (Runnable_t runnable, uint32_t args,Word stackSize/*in words*/)
        {
            while (syncFetch(this) == false) {
                
            }
            Runnable *r = (Runnable *)((uint32_t)allocator.New(sizeof(Runnable) + (stackSize * 4)));
            (*r)(runnable, (uint32_t)r + sizeof(Runnable) + stackSize * 4, 0);
            arrayOfRunnables[VReady].addFirst(r);
            syncRelease(this);
            return r;
        }
        
        
};



#endif


/*End of file*/

