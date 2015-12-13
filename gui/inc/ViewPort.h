#ifndef VIEWPORT_CLASS
#define VIEWPORT_CLASS

#include "dimensions.h"
#include "gui_defs.h"

class ViewPort  : public Dimension<MaxGuiRange>  {
    private :
        float Xm, Ym;
        float Xk, Yk;
    

    public :
        ViewPort () {}
        ViewPort (Dimension<MaxGuiRange> d) : Dimension<MaxGuiRange> (d)
        {
            Xm = Ym = 0;
            Xk = Yk = 0.3;
        }
        void operator () (Dimension<MaxGuiRange> d)
        {
            Dimension<MaxGuiRange>::operator=(d);
            Xm = Ym = 0;
            Xk = Yk = 0.3;
        }
    
        Dimension<MaxGuiRange> translate (Dimension<MaxGuiRange> d)
        {
            return d;
        }
        
        void move (int dx, int dy)
        {
            this->x += dx;
            this->y += dy;
        }
		
		
		void set (int x, int y)
		{
            Xm = Ym = 0;
            Xk = Yk = 0.6;
			this->x = x;
			this->y = y;
		}
        Box<int32_t> getView ()
        {
            /*
            Xm += ((float)this->x - Xm) * Xk;
            Ym += ((float)this->y - Ym) * Yk;
            Box<int32_t> box = {Xm, Ym, w, h};
            */
            Box<int32_t> box = {x, y, w, h};
            return box;
        }
};



#endif


/*End of file*/

