#ifndef GLINE_CLASS
#define GLINE_CLASS

#define SOFTWARE_GL

#ifdef SOFTWARE_GL

#include "GcontentPaneInterface.h"


#define labs(x)  ((x) < 0 ? (-x) : (x))

template <typename Color>
class Line_Class   : public virtual GPaneInterface<Color> {
	public:
	  Line_Class (GraphicFrame<Color, MaxGuiRange> *);
	  int32_t DrawDda (int32_t, int32_t, int32_t, int32_t, Color);
	  int32_t DrawVertical (Box<MaxGuiRange> rect, Color);
	  int32_t DrawHorizontal (Box<MaxGuiRange> rect, Color);
	  int32_t DrawDdaBold (int32_t, int32_t, int32_t, int32_t, Color);
	  int32_t DrawVerticalBold (Box<MaxGuiRange> rect, Color);
	  int32_t DrawHorizontalBold (Box<MaxGuiRange> rect, Color);
	  int32_t DrawVector (int32_t, int32_t, int32_t, int32_t, Color);
	  int32_t DrawVectorBold (int32_t, int32_t, int32_t, int32_t, Color);
	private:
	  int32_t Pixel (int32_t, int32_t, Color);
	  int32_t Point (int32_t, int32_t, int32_t, int32_t, Color);
	  int32_t fBotToTop (uint32_t, uint32_t, uint32_t, Color, uint8_t = 1);
	  int32_t fLeftToRight (uint32_t, uint32_t, uint32_t, Color, uint8_t = 1);
	  int8_t log2LaySize;
	
};

template <typename Color>
Line_Class<Color>::Line_Class(GraphicFrame<Color, MaxGuiRange> *frame)
{
    GPaneInterface<Color>::operator () (frame);
}

		
template <typename Color>
int32_t Line_Class<Color>::Pixel (int32_t x, int32_t y, Color color)
{
  *(this->frame + y + x * this->h) = color;
	return 0;
}

template <typename Color>
int32_t Line_Class<Color>::DrawDda (int32_t xt0, int32_t yt0, int32_t xt, int32_t yt, Color color)
{
        Box<int32_t> rect = {xt0, yt0, xt, yt};// = this->Screen->TruncLine(xt0, yt0, xt, yt);
        int32_t Xo = rect.x;
        int32_t Yo = rect.y;
        int32_t X  = rect.w;
        int32_t Y  = rect.h;
        int32_t dx = labs(X - Xo);
        int32_t dy = labs(Y - Yo);
        int32_t sx = X >= Xo ? 1 : -1;
        int32_t sy = Y >= Yo ? 1 : -1;
		if(dy <= dx)                    
		{
			int32_t d =  (dy<<1)-dx;                     
			int32_t d1 = dy<<1;
			int32_t d2 = (dy-dx)<<1;
			this->Pixel(Xo, Yo, color);            
			for(int32_t x = Xo+sx, y = Yo, i = 1; i<=dx; i++, x+=sx) 
			{
				if(d>0)            
				{
					d +=d2;
					y +=sy;
				}
				else d +=d1;
				this->Pixel(x, y,color);            
			}
		}
		else
		{
			int32_t d = (dx<<1)-dy;
			int32_t d1 = dx<<1;
			int32_t d2 = (dx-dy)<<1;
			this->Pixel(Xo, Yo,  color);
			for(int32_t x = Xo,y = Yo+sy,i = 1;i<=dy;i++,y+=sy)
			{
				if(d>0)
				{
					d+=d2;
					x+=sx;
				}
				else d+=d1;
				this->Pixel(x, y, color);
			}
		}  
  return 0;	
}

template <typename Color>
int32_t Line_Class<Color>::DrawDdaBold (int32_t xt0, int32_t yt0, int32_t xt, int32_t yt, Color color)
{
  //if (this->Screen->Test()) return -1;
	
	if (this->Z == 0) this->Z = 2;
	Box<int32_t> rect;// = this->Screen->TruncLine(xt0, yt0, xt, yt);
	int32_t Xo = rect.x;
    int32_t Yo = rect.y;
    int32_t X  =  rect.w;
    int32_t Y  =  rect.h;
	int32_t dx = labs(X - Xo);
    int32_t dy = labs(Y - Yo);
    int32_t sx = X >= Xo ? this->Z : -this->Z;
    int32_t sy = Y >= Yo ? this->Z : -this->Z;
		if(dy <= dx)                    
		{
			int32_t d =  (dy<<1)-dx;                     
			int32_t d1 = dy<<1;
			int32_t d2 = (dy-dx)<<1;           
			for(int32_t x = Xo+sx, y = Yo, i = 1; i<=dx/this->Z; i++, x+=sx) 
			{
				if(d>0)            
				{
					d +=d2;
					y +=sy;
				}
				else {
					  d +=d1;
				}
				this->fBotToTop(x, y, y + this->Z, color, this->Z);           
			}
		}
		else
		{
			int32_t d = (dx<<1)-dy;
			int32_t d1 = dx<<1;
			int32_t d2 = (dx-dy)<<1;
			for(int32_t x = Xo,y = Yo+sy,i = 1;i<=dy/this->Z;i++,y+=sy)
			{
				if(d>0)
				{
					d+=d2;
					x+=sx;
				}
				else {
					  d+=d1;
				}
				this->fLeftToRight(x, y, x + this->Z, color, this->Z);
			}
		}  
  return 0;	
}

template <typename Color>
int32_t Line_Class<Color>::DrawVector (int32_t x0, int32_t y0, int32_t R, int32_t A, Color color)
{
  //if (this->Screen->Test()) return -1;
	float x, y;
    x = x0 + R * sin((float)A);
    y = y0 + R * cos((float)A);
	return this->DrawDda(x0, y0, x, y, color);
}

template <typename Color>
int32_t Line_Class<Color>::DrawVectorBold (int32_t x0, int32_t y0, int32_t R, int32_t A, Color color)
{
    //if (this->Screen->Test()) return -1;
	float x, y;
    x = x0 + R * sin((float)A);
    y = y0 + R * cos((float)A);	
	return this->DrawDdaBold(x0, y0, x, y, color);	
}

template <typename Color>
int32_t Line_Class<Color>::DrawVertical (Box<MaxGuiRange> rect, Color color)
{
  //if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename Color>
int32_t Line_Class<Color>::DrawHorizontal (Box<MaxGuiRange> rect, Color color)
{
  //if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename Color>
int32_t Line_Class<Color>::DrawHorizontalBold (Box<MaxGuiRange> rect, Color color)
{
  //if (this->Screen->Test()) return -1;

  return 0;	
}

template <typename Color>
int32_t Line_Class<Color>::fBotToTop (uint32_t x0, uint32_t y0, uint32_t y, Color color, uint8_t z)
{
	uint32_t D = x0 * this->h;
	
	y0 += D;
	y += D;
	for (; y > y0; y--) {
	    for (int32_t tz = z * this->h; tz > 0; tz -= this->h) {
          *(this->frame + y + tz) = color;
			}
	}
	return 0;		
}

template <typename Color>
int32_t Line_Class<Color>::fLeftToRight (uint32_t x0, uint32_t y0, uint32_t x, Color color,  uint8_t z)
{
	uint32_t h0 = this->h;
	x0 = x0 * h0 + y0;
	x = x * h0 + y0;
	
  for (; x > x0; x -= h0) {
	    for (uint32_t tz = z; tz > 0; tz--) {
          *(this->frame + x + tz) = color;
			}
	}
	return 0;		
}

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/


#endif