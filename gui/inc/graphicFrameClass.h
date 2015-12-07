#ifndef GRAPHIC_FRAME
#define GRAPHIC_FRAME

#include "dimensions.h"
#include "memory_template.h"

template <typename Color, typename Range>
    class GraphicFrame  : public Dimension<Range>{
    private :
        Color *buffer;
        GraphicFrame () : Dimension<Range>()
        {
            this->setDefaultSize();
        }
    public :
        void operator () (Color *buffer, Dimension<Range> d)
        {
            this->buffer = buffer;
            this->setSize(d);
        }
        void operator () (Color *buffer, int w, int h)
        {
            this->buffer = buffer;
            this->setSize(0, 0, w, h);
        }
    
        void  fill (Color color)
            {
                    //if (this->Screen->Test()) return -1;
                    //this->Screen->Trunc(&rect);
                    
                    int32_t D = this->w * this->h;
                    for (int32_t  x = D ; x > 0;  x--)  {
                            buffer[x] = color;
                    }
            }
        
        Color *getBuffer ()
        {
            return this->buffer;
        }
        //friend class Factory;
};
    
template <typename  Color, typename Range>
    class GraphicFrameFactory : public Allocator<GraphicFrame <Color, Range> > {
        public:
            GraphicFrameFactory ()
            {
                
            }
            GraphicFrame<Color, Range> *newFrame (Dimension<Range> d)
            {
                GraphicFrame<Color, Range> *frame = this->New(d.getWidth() * d.getHeight());
                (*frame)((Color *)(frame + 1), d);
                return frame;
            }
            
    };
    




#endif

/*End of file*/

