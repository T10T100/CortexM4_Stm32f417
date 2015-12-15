#ifndef GCOMPONENT_INTERFACE
#define GCOMPONENT_INTERFACE
#include "graphic.h"
#include "ArrayListStatic.h"

typedef int (*GActionHandler) (TouchStruct);

class GComponentListener : public DefaultArrayListBaseNode<GComponentListener> {
private :
    GActionHandler handler;
public :
    GComponentListener (GActionHandler h)
    {
        handler = h;
    }
    int run (TouchStruct arg)
    {
        return (*handler) (arg);
    }

};    

template <typename Color>
class GComponent : public virtual Dimension<MaxGuiRange> {
    protected :

        ArrayListBase<GComponentListener> touchListeners;
        ArrayListBase<GComponentListener> clickListeners;
        ArrayListBase<GComponentListener> releaseListeners;
        ArrayListBase<GComponentListener> pressListeners;
    
        template <typename C>
        int fireListeners (ArrayListBase<C> &list, TouchStruct arg)
        {
            if (this->testPoint(arg.local) == false) {
                return -1;
            }
            arg.local = this->normalize(arg.local);
            arg.object = this;
            C *it = list.getFirst();
            while (it !=nullptr) { 
                it->run(arg);
                it = it->nextLink;
            }
            return 1;
        }
        
        
        void addListener (ArrayListBase<GComponentListener> &listeners, GActionHandler h)
        {
            GComponentListener *l = (GComponentListener *) new GComponentListener(h);
            if (l == nullptr) {
                return ;
            }
            listeners.addFirst(l);
        }
    
    public :
        GComponent () : Dimension<MaxGuiRange>()
        {
            
        }
        

        int fireSensorTouch (TouchStruct arg)
        {
            return fireListeners(touchListeners, arg);
        }
        
        int fireSensorClick (TouchStruct arg)
        {
            return fireListeners(clickListeners, arg);
        }
        
        int fireSensorRelease (TouchStruct arg)
        {
            return fireListeners(releaseListeners, arg);
        }
        
        int fireSensorPress (TouchStruct arg)
        {
            return fireListeners(pressListeners, arg);
        }
        
        
        
        void addTouchListener (GActionHandler h)
        {
            addListener(touchListeners, h);
        }
        void addClickListener (GActionHandler h)
        {
            addListener(clickListeners, h);
        }
        void addReleaseListener (GActionHandler h)
        {
            addListener(releaseListeners, h);
        }
        void addPressListener (GActionHandler h)
        {
            addListener(pressListeners, h);
        }
        
        
        
        
        
    
};



#endif


/*End of file*/

