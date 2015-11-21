#ifndef SYNCHRONIZER
#define SYNCHRONIZER

template <typename Object>
/*public*/ class Synchronizer {
    public :
        Synchronizer ()
        {
            
        }
    protected :
        virtual bool syncFetch (Object &o)
        {
            if (synchro == true) {
                return false;
            } else {
                synchro = true;
                return true;
            }
        }
        virtual bool syncFetch (Object *o)
        {
            if (synchro == true) {
                return false;
            } else {
                synchro = true;
                return true;
            }
        }
        virtual void syncRelease (Object &o)
        {
            synchro = false;
        }
        virtual void syncRelease (Object *o)
        {
            synchro = false;
        }
    private :
        bool synchro;
    
};



#endif

/*End of file*/



