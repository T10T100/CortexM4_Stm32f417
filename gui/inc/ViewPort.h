#ifndef VIEWPORT_CLASS
#define VIEWPORT_CLASS

#include "dimensions.h"
#include "gui_defs.h"

class ViewPort  : public Dimension<MaxGuiRange>  {
    private :
        int32_t Xm, Ym;
        float Xk, Yk;
        int32_t trueX;
        int32_t trueY;
        int32_t moveX;
        int32_t moveY;

    public :
        ViewPort () {}
        ViewPort (Dimension<int32_t> d) : Dimension<MaxGuiRange> (d)
        {
            Xm = Ym = 0;
            Xk = Yk = 0.3;
            trueX = 0;
            trueY = 0;
            moveX = moveY = 0;
        }
        ViewPort (ViewPort &wp)
        {
            x = wp.x;
            y = wp.y;
            w = wp.w;
            h = wp.h;
            trueX = 0;
            trueY = 0;
            moveX = moveY = 0;
        }
        void operator () (Dimension<MaxGuiRange> d)
        {
            Dimension<MaxGuiRange>::operator = (d);
            Xm = Ym = 0;
            Xk = Yk = 0.3;
            trueX = 0;
            trueY = 0;
            moveX = moveY = 0;
        }
    
        Dimension<MaxGuiRange> translate (Dimension<MaxGuiRange> d)
        {
            return d;
        }
        
        void move (int dx, int dy)
        {
            this->x += dx;
            this->y += dy;
            trueX -= dx;
            trueY -= dy;
            moveX = dx;
            moveY = dy;
        }
        
        void move (Point<MaxGuiRange> p)
        {
            this->x += p.x;
            this->y += p.y;
            trueX -= p.x;
            trueY -= p.y;
            moveX = p.x;
            moveY = p.y;
        }
		
		
		void set (int x, int y)
		{
            Xm = Ym = 0;
            Xk = Yk = 0.6;
			this->x = x;
			this->y = y;
		}
        Box<MaxGuiRange> getView ()
        {
            /*
            Xm += ((float)this->x - Xm) * Xk;
            Ym += ((float)this->y - Ym) * Yk;
            Box<int32_t> box = {Xm, Ym, w, h};
            */
            Box<MaxGuiRange> box = {x, y, w, h};
            return box;
        }
        
        
        
        bool testTrueViewPoint (int32_t x, int32_t y)
        {
            return this->testPoint(w - x, h - y);
        }
        
        void setTrueView (int32_t x, int32_t y)
        {
            trueX = x - this->x;
            trueY = y - this->y;
        }
        
        void setTrueView (Point<MaxGuiRange> p)
        {
            trueX = p.x - this->x;
            trueY = p.y - this->y;
        }
        
        Point<MaxGuiRange> getTrueView ()
        {
            Point<MaxGuiRange> b = {trueX, trueY};
            return b;
        }
        Point<MaxGuiRange> getMove ()
        {
            Point<MaxGuiRange> b = {moveX, moveY};
            return b;
        }
};



#endif


/*End of file*/

