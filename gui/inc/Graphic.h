#ifndef GRAPHIC_CLASS
#define GRAPHIC_CLASS
#include "Gui_Defs.h"
#include "graphicFrameClass.h"
#include "GPosition.h"
#include "printString.h"

template <typename Color>
class Graphic : public print::Print<Color> {
    private :
            
    
    
    
    public :
        Graphic (GraphicFrame<ColorDepth, MaxGuiRange> *f) : print::Print<Color>(f) 
        {
            
        }
    
    
};

#endif

/*End of file*/

