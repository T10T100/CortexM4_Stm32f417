#ifndef VM_CLASS
#define VM_CLASS
#include "device.h"
#include "Thread.h"
#include "syncClass.h"
#include "stack.h"


int SystemEventBurner (Runnable *);
int SystemEventBurner2 (Runnable *);  

    class Runtime : public Synchronizer<Runtime> {
    private :
        MemoryAllocator allocator;
        ArrayList<Runnable> listOfRunnables;
        Iterator<ArrayList<Runnable>, Runnable> *runnablesIterator;
        Runnable *running;
    
        void *manageThreads (void *frame, void *link)
        {
             RuntimeFrame *a = (RuntimeFrame *)frame;
            if (syncFetch(this) == false) { 
                return frame;
            }
            if (listOfRunnables.isEmpty() == true) {
                syncRelease(this);
                return frame;
            }
            if (running != nullptr) {
                running->setFrame(frame);
            }
            if (runnablesIterator->hasThis() == false) {
                runnablesIterator = listOfRunnables.iterator();
            } 
            running = runnablesIterator->getThis();
            if (running->getStatus() == Stopped) {
                RuntimeFrame *f = (RuntimeFrame *)(running->getStackRoof() - (4 * sizeof(RuntimeFrame)));
                *f = *((RuntimeFrame *)frame);
                f->PC = (uint32_t)running->getRunnable();
                running->setStatus(Running);
                syncRelease(this);
                return (void *)f;
            } 
            syncRelease(this);
            return (void *)running->getFrame();
        }
        
    public :
        
        friend void *server(void *frame, void *link);
    
        Runtime ()
        {
            running = nullptr;
        }
        void operator () (uint32_t heapStart, uint32_t heapSize)
        {
           this->allocator(heapStart, heapSize);
           addRunnable(SystemEventBurner, 0);
           addRunnable(SystemEventBurner2, 0);
           runnablesIterator = listOfRunnables.iterator();
        }
        
        Runnable *addRunnable (Runnable_t runnable, uint32_t args)
        {
            while (syncFetch(this) == false) {
                
            }
            Runnable *r = (Runnable *)((uint32_t)allocator.New(sizeof(Runnable) + (480 * 4)));
            (*r)(runnable, (uint32_t)r + sizeof(Runnable) + 478 * 4);
            listOfRunnables.addFirst(r);
            syncRelease(this);
            return r;
        }
        
        
};



#endif


/*End of file*/

