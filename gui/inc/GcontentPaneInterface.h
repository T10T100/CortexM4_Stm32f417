#ifndef GCONTENT_PANE_INTERFACE
#define GCONTENT_PANE_INTERFACE

#include "stdint.h"
#include "graphicFrameClass.h"
#include "Dimensions.h"
#include "gui_defs.h"

template <typename Color>
    class GPaneInterface :  public virtual Dimension<MaxGuiRange> {
        protected :
            Color *frame;
        public :
        GPaneInterface () {}
        GPaneInterface  (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            this->frame = frame->getBuffer();
            Dimension<MaxGuiRange>::setSize(frame->getBox());
        }
        void operator () (GraphicFrame<Color, MaxGuiRange> *frame)
        {
            this->frame = frame->getBuffer();
            Dimension<MaxGuiRange>::setSize(frame->getBox());
        }
            
        
    };


#endif


/*End of file*/

