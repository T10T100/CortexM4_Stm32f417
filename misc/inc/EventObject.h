#ifndef EVENT_OBJECT
#define EVENT_OBJECT

template <typename Object>
class EventObject {
    private:
        Object *object;
    public :
        EventObject (Object &o)
        {
            this->object = &o;
        }
        Object *getUserObject ()
        {
            return this->object;
        }
    
};


#endif


/*End of file*/


