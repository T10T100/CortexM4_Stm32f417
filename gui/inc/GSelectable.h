#ifndef GSELECTABLE_INTERFACE
#define GSELECTABLE_INTERFACE
#include "gPaletteComponent.h"



template <typename Color>
class GSelectable : protected virtual GPaletteComponent<Color> {
    protected :
        Color selectColor;
        int16_t selectionLifeTime;
        bool selected;
        uint16_t selectBorderWidth;
    public :
        GSelectable () {}
        GSelectable (Graphic<Color> *graphic) : GPaletteComponent<Color> (graphic)
        {
            selectColor = 0x7112;
            selectionLifeTime = 0;
            selectBorderWidth = 2;
        }
        void operator () (Graphic<Color> *graphic)
        {
            selectColor = 0x7112; 
            selectionLifeTime = 0;
            selectBorderWidth = 2;
        }
        
        void drawSelection ()
        {
            if (selectionLifeTime > 0) {
                this->graphic->rectangle(this->getBox(), selectBorderWidth, selectColor);
                selectionLifeTime--;
            } else {
                selected = false;
            }
        }
    
        void setSelectBorderWidth (uint32_t value)
        {
            selectBorderWidth = value;
        }
        
        void setSelect ()
        {
            selected = true;
            selectionLifeTime = 10;
        }
        
        void setSelectColor (Color color)
        {
            selectColor = color;
        }
        
        
        
        bool isSelected ()
        {
            return selected;
        }
        
        
        
        
        
        
        Color getSelectColor ()
        {
            return selectColor;
        }
    
};



#endif

/*End of file*/

