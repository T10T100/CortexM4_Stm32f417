#ifndef GFILL_INTERFACE
#define GFILL_INTERFACE

#include "GcontentPaneInterface.h"

template <typename Color>
class GFill : public virtual GPaneInterface<Color> {
    private :
        
    public :
GFill (){}
GFill(GraphicFrame<Color, MaxGuiRange> *frame)
{
    GPaneInterface<Color>::operator () (frame);
}

int32_t fill (Color color)
{
	
	register int32_t x = this->x;
	register uint32_t y = this->y;
	register uint32_t D = this->h * x;
	
    for (int32_t __x = D + this->h * this->w; __x > D; __x -= this->h) {
        for (uint32_t __y = this->h + y - 1; __y > y; __y--) {
            this->frame[(uint32_t)__y + (uint32_t)__x] = color;
        }
    }
	return 0;
}

int32_t fill (Dimension<MaxGuiRange> rect, Color color)
{
	//this->Screen->Trunc(&rect);
	
	register int32_t x = rect.x;
	register uint32_t y = rect.y;
	register uint32_t h = this->h;
	register uint32_t D = h * x;
	
    for (int32_t __x = D + h * rect.w; __x > D; __x -= h) {
        for (uint32_t __y = rect.h + y - 1; __y > y; __y--) {
            this->frame[__y + __x] = color;
        }
    }
	return 0;
}

int32_t fill (int32_t xt0, int32_t yt0, int32_t xt, int32_t yt, Color color)
{
	Dimension<int32_t> rect(xt0, yt0, xt, yt);
	return this->fill (rect, color);
}

template <typename Plane>
int32_t fillX (Plane rect, Color color, uint8_t jitter)
{
	Color *ftarget = this->Frame;
	Color *target = nullptr;
	//this->Screen->Trunc(&rect);
	
	register uint32_t H = this->h;
	register uint32_t x0 = (uint32_t)rect.x * H;
	register uint32_t y0 = (uint32_t)rect.y;
	register uint32_t h = (uint32_t)rect.h * H;
	register uint32_t w = (uint32_t)rect.w;
	uint32_t Key = 0;
	
    for (uint32_t __y = y0 + w; __y > y0; __y--) {  
       for (uint32_t __x = x0 + h; __x > x0; __x -= H) {
				target = ftarget + __y + __x + H;
				if (*(target) == color && *(target - H) != color )
					 Key ^= 1;
			  if (Key)*(target) = color;
			
			}
			Key = 0;
		}
	return 0;	
}

template <typename Plane>
int32_t fillY (Plane rect, Color color)
{
	Color *ftarget = this->Frame;
	Color *target = nullptr;
	this->Screen->Trunc(&rect);
	
	register uint32_t H = this->h;
	register uint32_t x0 = rect.x * H;
	register uint32_t y0 = rect.y;
	register uint32_t h = rect.h * H;
	register uint32_t w = rect.w;
	uint32_t Key = 0;
	
    for (uint32_t __x = x0 + h; __x > x0; __x -= H) {  
      for (uint32_t __y = y0 + w; __y > y0; __y--) {
				target = ftarget + __y + __x - 1;
				if (*(target + 1) == color && *target != color)
					 Key ^= 1;
			  if (Key)*(target + 1) = color;
			}
			Key = 0;
		}
	return 0;	
}
template <typename Plane, typename img_t>
void fill (Plane box, img_t *image, Color color)
            {

                int32_t wm = image->W;
                int32_t hm = image->H;

                Color *dest = this->frame;
                const Color *src = image->Image;
                
               
                int32_t S = hm * wm;
                for (int xi = 0, xt = box.x * this->h; xi < wm; xt += this->h, xi++) {  
                        for (uint32_t yt = box.y + xt, yi = xi, t = S + xi; yi < t; yt++, yi += image->W) {
                            if (src[yi] != ColorMaskReference) {
                                dest[yt] = src[yi];   
                            } else {}
                        }
                  }
            }
    
};


#endif


/*End of file*/

