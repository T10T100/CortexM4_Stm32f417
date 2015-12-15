#ifndef GRAPHIC_FRAME
#define GRAPHIC_FRAME

#include "dimensions.h"
#include "memory_template.h"

template <typename Color, typename Range>
    class GraphicFrame  : public Dimension<Range>{
    private :
        Color *buffer;
        GraphicFrame (Color *buffer, Dimension<Range> d) : Dimension<Range>(d)
        {
            this->buffer = buffer;
        }
    public :
    
        void  fill (Color color)
            {
                    //if (this->Screen->Test()) return -1;
                    //this->Screen->Trunc(&rect);
                    
                    int32_t D = this->w * this->h;
                    for (int32_t  x = D ; x > 0;  x--)  {
                            buffer[x] = color;
                    }
            }
        void  fillAnd (Color color)
            {
                    //if (this->Screen->Test()) return -1;
                    //this->Screen->Trunc(&rect);
                    
                    int32_t D = this->w * this->h;
                    for (int32_t  x = D ; x > 0;  x--)  {
                            buffer[x] |= color;
                    }
            }
        
        Color *getBuffer ()
        {
            return this->buffer;
        }
        friend class GraphicFrameFactory;
};
    

    class GraphicFrameFactory  {
        public:
            GraphicFrameFactory ()
            {
                
            }
            
            template <typename Color, typename Range>
            GraphicFrame<Color, Range> *newFrame (Dimension<Range> d)
            {
                Color *b = (Color *) new Color[d.getWidth() * d.getHeight()];
                if (b == nullptr) {
                    return nullptr;
                }
                GraphicFrame<Color, Range> *frame = (GraphicFrame<Color, Range> *) new GraphicFrame<Color, Range>(b, d);
                if (frame == nullptr) {
                    delete(b);
                    return nullptr;
                }
                return frame;
            }
            
    };
    




#endif

/*End of file*/

