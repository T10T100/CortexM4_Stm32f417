#ifndef GPALETTE_COMPONENT_CLASS
#define GPALETTE_COMPONENT_CLASS
#include "graphic.h"

template <typename Color>
    class GPaletteComponent : public virtual Dimension<MaxGuiRange> {
    protected :
        Graphic<Color> *graphic;
        void *contentPane;
        Color background;
        Color foreground;
        bool visible;
        bool enabled;
        bool forceRepaint;
        

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
        void setContentPane (void *value)
        {
            contentPane = value;
        }
        
        void setForceRepaint (bool value)
        {
            forceRepaint = value;
        }
        
        
        
        Color getBackground ()
        {
            return background;
        }
        Color getForeground ()
        {
            return foreground;
        }
        bool getForceRepaint ()
        {
            return forceRepaint;
        }
        Graphic<Color> *getGraphic ()
        {
            return graphic;
        }
        void *getContentPane ()
        {
            return contentPane;
        }
        
        
};




#endif

/*End of file*/

