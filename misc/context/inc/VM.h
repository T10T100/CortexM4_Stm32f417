#ifndef VM_CLASS
#define VM_CLASS
#include "device.h"
#include "Thread.h"
#include "syncClass.h"
#include "stack.h"

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
        Iterator<ArrayList<Runnable>, Runnable> *runnablesIterator;
        Runnable *running;
        ArrayList<Runnable> arrayOfRunnables[EndOfThreadTypesEnum];
        
        void *manageThreads (void *frame, int32_t link)
        {
            if (syncFetch(this) == false) { 
                return frame;
            }
            if (link != 1 && running != nullptr) {
                running->setFrame(frame);
                arrayOfRunnables[VPending].addLast(running);
            }
            if (arrayOfRunnables[VReady].isEmpty() == false) {
                running = arrayOfRunnables[VReady].removeFirst();
                RuntimeFrame *f = (RuntimeFrame *)(running->getStackRoof() - (sizeof(RuntimeFrame) * 4));
                if (link == 1) {
                    syncRelease(this);
                    f->R11 = (uint32_t)running->getRunnable();
                    return (void *)f; 
                } else {
                    *f = *((RuntimeFrame *)frame);
                    f->PC = (uint32_t)running->getRunnable();
                    running->setStatus(Running);
                    syncRelease(this);
                    return (void *)f;
                }
            } else if (arrayOfRunnables[VPending].isEmpty() == false) {
                running = arrayOfRunnables[VPending].removeFirst();
            } else if (arrayOfRunnables[VWaiting].isEmpty() == false) {
                running = arrayOfRunnables[VWaiting].removeFirst();
            } else {
                syncRelease(this);
                return frame;
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
           addRunnable(SystemEventBurner2, 0);
           running->setStatus(Stopped);
           runnablesIterator = listOfRunnables.iterator();
           error = RuntimeStartup (0, \
                                    0 /*(void *)((uint32_t)allocator.New(4096 * 4) + 4040 * 4)*/);
        }
        
        Runnable *addRunnable (Runnable_t runnable, uint32_t args)
        {
            while (syncFetch(this) == false) {
                
            }
            Runnable *r = (Runnable *)((uint32_t)allocator.New(sizeof(Runnable) + (480 * 4)));
            (*r)(runnable, (uint32_t)r + sizeof(Runnable) + 478 * 4);
            arrayOfRunnables[VReady].addFirst(r);
            syncRelease(this);
            return r;
        }
        
        
};



#endif


/*End of file*/

