#ifndef GRAPHIC_COMPONENT_OBJECT
#define GRAPHIC_COMPONENT_OBJECT
#include "graphic.h"
#include "gPaletteComponent.h"

template <typename Color>
class GraphicObject :  public virtual GPaletteComponent<Color>,
                       public DefaultArrayListBaseNode<GraphicObject<Color> >
{
    private:
        void (*repaintHook) (void *);
        
    public :
        GraphicObject (Graphic<Color> *graphic) : GPaletteComponent<Color> (graphic),
                                           DefaultArrayListBaseNode<GraphicObject<Color> > ()
        {
            repaintHook = nullptr;
        }    

        virtual void repaint ()
        {
            if (repaintHook != nullptr) {
                (*repaintHook) (this);
            }
        }
        
        void setRepaintHook ( void (*repaintHook) (void *) )
        {
            this->repaintHook = repaintHook;
        }
};





#endif