#ifndef GLABEL_OBJECT
#define GLABEL_OBJECT
#include "graphic.h"
#include "ArrayListStatic.h"
#include "vmStdOut.h"

#define DefaulLabelCharCapacity 48

template <typename Color>
class GLabel : public Dimension<int32_t> ,
               public DefaultArrayListBaseNode<GLabel<Color> >,
               public VmOut<char>   {
private :
    Graphic<Color> *graphic;
    Color background;
    Color foreground;
    char text[DefaulLabelCharCapacity];
public:
    GLabel () {}
    GLabel (Graphic<Color> *graphic)
    {
        this->graphic = graphic;
        background = ColorWhite;
        foreground = ColorBlack;
        VmOut::setStream(text, DefaulLabelCharCapacity);
    }
    void operator () (Graphic<Color> *graphic)
    {
        this->graphic = graphic;
        background = ColorWhite;
        foreground = ColorBlack;
        VmOut::setStream(text, DefaulLabelCharCapacity);
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
        Box<uint16_t> box = {x, y, w, h};
        graphic->fill(box, background);
        graphic->drawString(box, getStream(), foreground);
    }
    
    void setBackground (Color color)
    {
        background = color;
    }
    void setForeground (Color color)
    {
        foreground = color;
    }
};

#endif

/*End of file*/

