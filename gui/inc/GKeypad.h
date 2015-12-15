#ifndef GCEYPAD_OBJECT
#define GCEYPAD_OBJECT
#include "graphic.h"
#include "vmStdOut.h"
#include "gComponent.h"
#include "gPaletteComponent.h"
#include "gSelectable.h"

#ifndef DefaulLabelCharCapacity
#define DefaulLabelCharCapacity 48
#endif

extern char const *KeypadFormsArray[];

template <typename Color>
class GButton:  public  GComponent<Color>,
                 public virtual GPaletteComponent<Color>,
                 public GSelectable<Color>,
                 public DefaultArrayListBaseNode<GButton<Color> >,
                 public VmOut<char>  
{
                 private :
                     char text[DefaulLabelCharCapacity]; 
                     void draw ()
                     {
                         this->setSelectBorderWidth(6);
                     }
                 public :
                     GButton (Graphic<Color> *graphic) : GComponent<Color> (),
                                       GPaletteComponent<Color> (graphic),
                                       GSelectable<Color> (graphic), 
                                       DefaultArrayListBaseNode<GButton<Color> > (),
                                       VmOut<char>(text, DefaulLabelCharCapacity)
                    {
                        this->background = 0xefff;
                    }
                    ~GButton ()
                    {
                        delete(this);
                    }
                    
                    void setName (char *name)
                    {
                        this->clear();
                        this->print(name);
                    }
                    
                    void repaint ()
                    {
                        Dimension<MaxGuiRange> box(this->x, this->y, this->w, this->h);
                        this->graphic->fill(box, this->background);
                        this->drawSelection();
                        this->graphic->drawString(box, getStream(), this->foreground);
                    }   
                    
                    char *getName ()
                    {
                        return getStream();
                    }
};                     


#endif