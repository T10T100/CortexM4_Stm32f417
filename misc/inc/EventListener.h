#ifndef EVENT_LISTENER
#define EVENT_LISTENER
#include "eventObject.h"

template <typename Source>
    class EventListener {
        private :
        public :
            EventListener ()
            {
                
            }
            bool equals (EventListener<Source> *s)
            {
                return true;
            }
            virtual void actionPerformed (EventObject<Source> &event);
            virtual void actionPerformed (EventObject<Source> *event);
    };


#endif

/*End of file*/

