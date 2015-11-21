#ifndef VM_CLASS
#define VM_CLASS
#include "device.h"
#include "Thread.h"
#include "syncClass.h"
#include "stack.h"

extern "C"
void *RuntimeStartup (void *);

int SystemEventBurner (Runnable *);
int SystemEventBurner2 (Runnable *);  

    class Runtime : public Synchronizer<Runtime> {
    private :
        MemoryAllocator allocator;
        ArrayList<Runnable> listOfRunnables;
        Iterator<ArrayList<Runnable>, Runnable> *runnablesIterator;
        Runnable *running;
    
        void *manageThreads (void *frame, int32_t link)
        {
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
            running = runnablesIterator->get();
            runnablesIterator->next();
            if (running->getStatus() == Stopped) {
                RuntimeFrame *f = (RuntimeFrame *)(running->getStackRoof() - (sizeof(RuntimeFrame) * 4));
                if (link != 1) {
                    *f = *((RuntimeFrame *)frame);
                } else {
                    syncRelease(this);
                    return (void *)running->getRunnable();
                }
                f->PC = (uint32_t)running->getRunnable();
                running->setStatus(Running);
                syncRelease(this);
                return (void *)f;
            } 
            syncRelease(this);
            return (void *)running->getFrame();
        }
        
    public :
        
        void *psalloc (uint32_t size)
        {
            return (void *)((uint32_t)allocator.New(size) + size - 4);
        }
        void free (void *p)
        {
            //allocator.Delete(p);
        }
    
        friend void *server(void *frame, int32_t link);
    
        Runtime ()
        {
            running = nullptr;
        }
        void operator () (uint32_t heapStart, uint32_t heapSize)
        {
           void *error = nullptr;
           this->allocator(heapStart, heapSize);
           addRunnable(SystemEventBurner, 0);
           running = addRunnable(SystemEventBurner2, 0);
           running->setStatus(Stopped);
           runnablesIterator = listOfRunnables.iterator();
           error = RuntimeStartup ((void *)((uint32_t)allocator.New(6024 * 4) + 6022 * 4));
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

