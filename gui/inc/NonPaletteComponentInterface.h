#ifndef NON_PALETTE_INTERFACE
#define NON_PALETTE_INTERFACE
#include "graphic.h"
#include "gComponent.h"
#include "gPaletteComponent.h"
#include "gSelectable.h"

typedef int (*NonPaletteComponentRepaintHook) (void *);


template <typename Color>
class NonPaletteInterface : public GComponent<Color>,
                            public virtual GPaletteComponent<Color>,
                            public GSelectable<Color>,
                            public DefaultArrayListBaseNode<NonPaletteInterface<Color> >
{
private :
    void *object;
    int32_t objectId;
    NonPaletteComponentRepaintHook repaintHook;
public:
    NonPaletteInterface (Graphic<Color> *graphic) : GComponent<Color> (),
                                       GPaletteComponent<Color> (graphic),
                                       GSelectable<Color> (graphic), 
                                       DefaultArrayListBaseNode<NonPaletteInterface<Color> > ()
    {
        this->setSelectBorderWidth(2);
        this->object = nullptr;
        this->objectId = -1;
    }

    ~NonPaletteInterface ()
    {
        delete(this);
    }
    
 
    
    void repaint ()
    {
        if (repaintHook == nullptr) {
            Dimension<MaxGuiRange> box = {this->x, this->y, this->w, this->h};
            this->graphic->fill(box, this->background);
        } else {
            (*repaintHook)(this);
        }
    }
    
    void setUserObject (void *o, int32_t id)
    {
        this->object = o;
        this->objectId = id;
    }
    
    void setRepaintHook (NonPaletteComponentRepaintHook hook)
    {
        repaintHook = hook;
    }
    
    
    void *getUserObject ()
    {
        return object;
    }
    
    int32_t getUserObjectId ()
    {
        return objectId;
    }
    
};

#endif

/*End of file*/

