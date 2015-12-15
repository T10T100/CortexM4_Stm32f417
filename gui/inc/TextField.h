#ifndef TEXT_FIELD_OBJECT
#define TEXT_FIELD_OBJECT

#include "graphic.h"
#include "vmStdOut.h"
#include "gComponent.h"
#include "gPaletteComponent.h"
#include "gSelectable.h"

#define DefauTextFieldCharCapacity 48

int TextFieldsDEfaultCickListener (TouchStruct arg);
int TextFieldsDEfaultTouchListener (TouchStruct arg);
int TextFieldsDEfaultReleaseListener (TouchStruct arg);

template <typename Color>
class GTextField : public GComponent<Color>,
                  public virtual GPaletteComponent<Color>,
                  public GSelectable<Color>,
                  public DefaultArrayListBaseNode<GTextField<Color> >,
                  public VmOut<char>       {
private :
    char text[DefauTextFieldCharCapacity];
    int beginSelection;
    int endSelection;
    int cursor;
public:
    GTextField (Graphic<Color> *graphic) : GComponent<Color> (),
                                       GPaletteComponent<Color> (graphic),
                                       GSelectable<Color> (graphic), 
                                       DefaultArrayListBaseNode<GTextField<Color> > (),
                                       VmOut<char>(text, DefauTextFieldCharCapacity)
    {
        this->setSelectBorderWidth(2);
        this->addClickListener(TextFieldsDEfaultCickListener);
        this->addTouchListener(TextFieldsDEfaultTouchListener);
        this->addReleaseListener(TextFieldsDEfaultReleaseListener);
        this->background = 0xffff;
        beginSelection = 0;
        endSelection = 0;
    }

    ~GTextField ()
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
        if (beginSelection > endSelection) {
            this->graphic->fill(this->x + endSelection, this->y, beginSelection - endSelection, this->h, 0xF000);
        } else {
            this->graphic->fill(this->x + beginSelection, this->y, endSelection - beginSelection, this->h, 0xF000);
        }
        
        this->drawSelection();
        this->graphic->drawString(box, getStream(), this->foreground);
    }
    
    void setSelectionStart (int value)
    {
        beginSelection = value;
    }
    
    void setSelectionEnd (int value)
    {
        endSelection = value;
    }
    
    
    int getSelectionStart ()
    {
        return beginSelection;
    }
    
    int getSelectionEnd ()
    {
       return endSelection;
    }
    
};



#endif

/*End of file*/

