#ifndef G_CONTENT_PANE
#define G_CONTENT_PANE
#include "memory_template.h"
#include "gui_defs.h"
#include "graphicFrameClass.h"
#include "graphic.h"
#include "GLabel.h"


template <typename Color>
class GContentPane {
    private :
          GraphicFrame<ColorDepth, uint16_t> *frame;
          Graphic<Color> *graphic;
    
    
          /*Content -> */
          ArrayListBase<GLabel<Color> > listOfLabels;
    
    public :
        GContentPane (GraphicFrame<Color, uint16_t> *frame)
        {
            this->frame = frame;
            Box<uint16_t> box = frame->getBox();
            graphic = (Graphic<Color>*) new Graphic<Color>(frame);        
        }
        void fill (Color color)
        {
            frame->fill(color);
        }
        ~GContentPane ()
        {
            delete(graphic);
            delete(this);
        }
        
        Graphic<Color> *getGraphic ()
        {
            return graphic;
        }
        
        GraphicFrame<ColorDepth, uint16_t> *getFrame ()
        {
            return frame;
        }
        
        void add (GLabel<Color> *label)
        {
            listOfLabels.addFirst(label);
        }
        void repaintLabels ()
        {
            GLabel<Color> *it = listOfLabels.getFirst();
            while (it != nullptr) {
                it->repaint();
                it = it->nextLink;
            }
        }
        
        
        void repaint ()
        {
            repaintLabels();
        }
    
};





#endif 


/*End of file*/

