#ifndef GLABEL_OBJECT
#define GLABEL_OBJECT
#include "graphic.h"
#include "vmStdOut.h"
#include "gComponent.h"
#include "gPaletteComponent.h"
#include "gSelectable.h"

#define DefaulLabelCharCapacity 48

template <typename Color>
class GLabel : public GComponent<Color>,
               public virtual GPaletteComponent<Color>,
               public GSelectable<Color>,
               public DefaultArrayListBaseNode<GLabel<Color> >,
               public VmOut<char>       {
private :
    char text[DefaulLabelCharCapacity];
public:
    GLabel (Graphic<Color> *graphic) : GComponent<Color> (),
                                       GPaletteComponent<Color> (graphic),
                                       GSelectable<Color> (graphic), 
                                       DefaultArrayListBaseNode<GLabel<Color> > (),
                                       VmOut<char>(text, DefaulLabelCharCapacity)
    {
        this->setSelectBorderWidth(2);
    }

    ~GLabel ()
    {
        delete(this);
    }
    
    void setText (char *str) 
    {
        clear();
        print(str);
    }
    void apendText (char *str) 
    {
        print(str);
    }
    
    
    void setText (int32_t val) 
    {
        clear();
        print(val);
    }
    void apendText (int32_t val) 
    {
        print(val);
    }
    void setText (uint32_t val) 
    {
        clear();
        print(val);
    }
    void apendText (uint32_t val) 
    {
        print(val);
    }
    
    void repaint ()
    {
        Dimension<MaxGuiRange> box = {this->x, this->y, this->w, this->h};
        this->graphic->fill(box, this->background);
        this->drawSelection();
        this->graphic->drawString(box, getStream(), this->foreground);
    }
    
};

#endif

/*End of file*/

