#ifndef GPALETTE_COMPONENT_CLASS
#define GPALETTE_COMPONENT_CLASS
#include "graphic.h"

template <typename Color>
    class GPaletteComponent : public virtual Dimension<MaxGuiRange> {
    protected :
        Graphic<Color> *graphic;
        Color background;
        Color foreground;
        bool visible;
        bool enabled;
        

    public :  
        GPaletteComponent () {}        
        GPaletteComponent (Graphic<Color> *graphic) : Dimension<MaxGuiRange>()
        {
            this->graphic = graphic;
        }
        void operator () (Graphic<Color> *graphic)
        {
            this->graphic = graphic;
        } 
    
        virtual void repaint ()
        {
            graphic->fill(x, y, w, h, background);
        }
        
        
        void setBackground (Color color)
        {
            background = color;
        }
        void setForeground (Color color)
        {
            foreground = color;
        }
        void setVisible (bool value)
        {
            visible = value;
        }
        void setEnable (bool value)
        {
            enabled = value;
        }
        
        
        
        Color getBackground ()
        {
            return background;
        }
        Color getForeground ()
        {
            return foreground;
        }
        
        Graphic<Color> *getGraphic ()
        {
            return graphic;
        }
        
        
};




#endif

/*End of file*/

