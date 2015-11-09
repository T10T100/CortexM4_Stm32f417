#ifndef GRAPHIC_FRAME
#define GRAPHIC_FRAME

#include "dimensions.h"
#include "memory_template.h"

template <typename Factory, typename Color, typename Range>
    class GraphicFrame  : public Dimension<Range>{
    private :
        Color *buffer;
        GraphicFrame () : Dimension<Range>()
        {
            this->setDefaultSize();
        }
        void operator () (Color *buffer, Dimension<Range> d)
        {
            this->buffer = buffer;
            this->setSize(d);
        }
        void operator () (Color *buffer, int w, int h)
        {
            this->buffer = buffer;
            Dimension<Range> d = {0, 0, w, h};
            this->setSize(d);
        }
    public:
        
        Color *getBuffer ()
        {
            return this->buffer;
        }
        friend class Factory;
};
    
template <typename  Color, typename Range>
    class GraphicFrameFactory : public Allocator<GraphicFrame<GraphicFrameFactory<Color, Range>, Color, Range> >{
        public:
            GraphicFrameFactory ()
            {
                
            }
            GraphicFrame<GraphicFrameFactory, Color, Range> *newFrame (Dimension<Range> d)
            {
                GraphicFrame<GraphicFrameFactory, Color, Range> *frame = this->New(d.w * d.h);
                (*frame)((Color *)(frame + 1), d);
                return frame;
            }
    };
    




#endif

/*End of file*/

