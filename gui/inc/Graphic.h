#ifndef GRAPHIC_CLASS
#define GRAPHIC_CLASS
#include "Gui_Defs.h"
#include "graphicFrameClass.h"
#include "GPosition.h"
#include "printString.h"
#include "drawString.h"
#include "gline.h"
#include "GFill.h"

template <typename Color>
class Graphic : public print::Print<Color> ,
                public print::DrawString<Color>,
                public GFill<Color>,
                public Line_Class<Color> {
    private :
            
    
    
    
    public :
        Graphic (GraphicFrame<ColorDepth, MaxGuiRange> *f) : print::Print<Color>(f),
                                                             print::DrawString<Color>(f),
                                                             GFill<Color> (f),
                                                             Line_Class<Color> (f)
        {
            
        }
    
    
};

#endif

/*End of file*/

