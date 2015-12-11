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
        }
        void operator () (Dimension<MaxGuiRange> d)
        {
            Dimension<MaxGuiRange>::operator=(d);
            Xm = Ym = 0;
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
			this->x = x;
			this->y = y;
		}
        Box<MaxGuiRange> getView ()
        {
            return getBox();
        }
};



#endif


/*End of file*/

