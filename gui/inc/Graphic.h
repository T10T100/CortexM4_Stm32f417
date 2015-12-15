#ifndef GRAPHIC_CLASS
#define GRAPHIC_CLASS
#include "Gui_Defs.h"
#include "ViewPort.h"
#include "ArrayListStatic.h"
#include "graphicFrameClass.h"
#include "GPosition.h"
#include "printString.h"
#include "drawString.h"
#include "gline.h"
#include "GFill.h"
#include "GCircle.h"
#include "GRectangle.h"


typedef struct {
    Point<MaxGuiRange> local;
    Point<MaxGuiRange> move;
    int actrion;
    int clickCount;
    void *object;
} TouchStruct;

template <typename Color>
class Graphic : public print::Print<Color> ,
                public print::DrawString<Color>,
                public GFill<Color>,
                public GCircle<Color>,
                public Line_Class<Color>,
                public GRectangle<Color> {
    private :
            
    
    
    
    public :
        Graphic (GraphicFrame<ColorDepth, MaxGuiRange> *f) : print::Print<Color>(f),
                                                             print::DrawString<Color>(f),
                                                             GFill<Color> (f),
                                                             GCircle<Color> (f),
                                                             Line_Class<Color> (f),
                                                             GRectangle<Color> (f)
        {

        }
    
    
};

#endif

/*End of file*/

