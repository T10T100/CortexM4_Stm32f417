#ifndef GCIRCLE_CLASS
#define GCIRCLE_CLASS

#define SOFTWARE_GL

#ifdef SOFTWARE_GL

#include "GcontentPaneInterface.h"

template <typename Color>
class GCircle : public virtual GPaneInterface<Color> {
private :
    
public :
    GCircle (){}
    GCircle(GraphicFrame<Color, MaxGuiRange> *frame)
    {
        GPaneInterface<Color>::operator () (frame);
    }

    int32_t Sqr (int32_t val)
    {
      return val * val;
    }


    int32_t Pixel (int32_t x, int32_t y, Color color)
    {
      *(this->frame + y + x * this->h) = color;
        return 0;
    }
    int32_t Point (int32_t x0, int32_t y0, int32_t x, int32_t y, Color color)
    {
        int32_t h0 = (x + x0) * this->h + y0;
        int32_t h1 = (-x + x0) * this->h + y0;
        *(this->frame + y + h0) = color;
        *(this->frame - y + h1) = color;
        *(this->frame - y + h0) = color;
        *(this->frame + y + h1) = color;
        return 0;
    }


    int32_t fBotToTop (int32_t x0, int32_t y0, int32_t x, int32_t y, Color color)
    {
        uint32_t h = this->h;
        int32_t D = x0 * h + y0;
        int32_t D0 = x * h + D;
        int32_t D1 = -x * h + D;
        y0 = - y;
        y  = + y;
        for (; y > y0; y--) {
          *(this->frame + y + D0) = color;
              *(this->frame + y + D1) = color;
        }
        return 0;		
    }

    template <typename Plane>
    int32_t circle (Plane rect, int R, Color color)
    {
        
        //this->Screen->Trunc(&rect);
        int32_t y = R;
        int32_t sR = this->Sqr(R);
        int32_t x = 0;
        int32_t Dg = 0;
        int32_t Dd = 0;
        int32_t Dv = 0;
        int32_t sqrx = 0;
        int32_t sqry = 0;
        this->Pixel(rect.x,  y  + rect.y, color);
        this->Pixel(rect.x,  -y  + rect.y, color);
        for(;y >= 0;){
            sqrx = this->Sqr(x + 1) - sR;
            sqry = this->Sqr(y - 1);
            Dg = (sqrx + this->Sqr(y));
            Dd = (sqrx + sqry);
            Dv = (this->Sqr(x) + sqry - sR);
            if(Dd < 0){
                if(Dd > -labs(Dg)){ 	
                      x++;
                      y--;
                }
                else {
                    x++;
                }
            }
            else if(Dd > 0){
                if(Dd < labs(Dv)){
                      y--;
                      x++;
                }
                else {
                    y--;
                }
            }
            else {
                  y--;
                  x++;
            }
            this->Point(rect.x, rect.y, x, y, color);
        }
        return 0;
    }


    int32_t circle (int x0, int y0, int R, Color color)
    {
        Box<int> rect = {x0, y0, 0, 0};
        x0 = x0 - R;
        y0 = y0 - R;
        return this->circle(rect, R, color);
    }

    template <typename Plane>
    int32_t circleFilled (Plane rect, float R, Color color)
    {
        //this->Screen->Trunc(&rect);
        
        int32_t y = (int32_t)R;
        int32_t sR = this->Sqr((int32_t)R);
        int32_t x = 0;
        int32_t Dg = 0;
        int32_t Dd = 0;
        int32_t Dv = 0;
        int32_t sqrx = 0;
        int32_t sqry = 0;
        uint32_t tx = 0;
        this->fBotToTop(rect.x, rect.y, x, y, color);
        for(;y >= 0 ;){
            sqrx = this->Sqr(x + 1) - sR;
            sqry = this->Sqr(y - 1);
            Dg = (sqrx + this->Sqr(y));
            Dd = (sqrx + sqry);
            Dv = (this->Sqr(x) + sqry - sR);
            if(Dd < 0){
                if(Dd > -labs(Dg)){
                      x++;
                      y--;
                }
                else {
                    x++;
                }
            }
            else if(Dd > 0) {
                if(Dd < labs(Dv)){
                      y--;
                      x++;
                }
                else {
                    y--;
                }
            }
            else {
                  y--;
                  x++;
            }
            if (tx != x) {
                this->fBotToTop(rect.x, rect.y, x, y, color);
            } else {}
            tx = x;
        }
        return 0;
    }

/*
int32_t Round (Box<int> rect, float R, Color color, uint32_t z)
{
	Box<int> cut_rect = rect;
	this->Draw(rect, R, color);
	rect.x = rect.x + z;
	rect.y = rect.y + z;
	this->Draw(rect, R - z, color);
	//this->Screen->Fill.FillX(cut_rect, color);
	return 0;
}
*/
/*
int32_t Round (gbasic_t x0, gbasic_t y0, float R, ColorTypeDef color, uint32_t z)
{
	b2D rect = {x0, y0, 0, 0}, cut_rect = {x0, y0, (gbasic_t)(2 * R), (gbasic_t)(2 * R)};
	this->Draw(rect, R, color);
	rect.x = rect.x + z;
	rect.y = rect.y + z;
	this->Draw(rect, R - z, color);
	this->Screen->Fill.FillX(cut_rect, color);
	return 0;
}
*/

    int32_t Arc (Box<int> rect, float R, float A, Color color, float Ai)
    {
        return this->Arc(rect.x, rect.y, R, A, color, Ai);
    }

    int32_t Arc (int x0, int y0, float R, float A, Color color, float Ai)
    {
        float x = 0, y = R;
        float px = x0 + x, py = y0 + y;
        int32_t t = (int32_t)abs(floor(A / Ai));
        while (t--) {
            x = (float)x + y * Ai;
          y = (float)y - x * Ai; 
            this->Screen->Line.DrawDda(px, py, x + x0, y + y0, color);
            px = x + x0;
            py = y + y0;
        }
        
        return 0;
    }

    int32_t Segment (Box<int> rect, float R, float A, Color color, float Ai)
    {
        return this->Segment(rect.x, rect.y, R, A, color, Ai);
    }

    int32_t Segment (int x0, int y0, float R, float A, Color color, float Ai)
    {
        float x = 0, y = R;
        float px = x0, py = 0;
        int32_t t = (int32_t)abs(floor(A / Ai));
        Box<float> rect = {x0 - R, y0 - R, 2 * R, 2 * R};
        while (t--) {
            x = (float)x + y * Ai;
          y = (float)y - x * Ai; 
            this->Screen->Line.DrawDda(px, py, x + x0, y + y0, color);
            px = x + x0;
            py = y + y0;
        }
        x = 0, y = R - 10.0F;
        px = x0 + x, py = y0 + y;
        t = (int32_t)abs(floor(A / Ai));
        while (t--) {
            x = (float)x + y * Ai;
          y = (float)y - x * Ai; 
            this->Screen->Line.DrawDda(px, py, x + x0, y + y0, color);
            px = x + x0;
            py = y + y0;
        }
        this->Screen->Line.DrawDda(x0, y0, x + x0, y + y0, color);
        this->Screen->Fill.FillX(rect, color);
        return 0;
    }
     
    int32_t DrawFilled (int x, int y, float R, Color color)
    {
        Box<int> rect = {x, y, 0, 0};
        return this->circleFilled(rect, R, color);
    }
};

#else /*!SOFTWARE_GL*/

#endif /*SOFTWARE_GL*/

#endif

/*End of file*/

