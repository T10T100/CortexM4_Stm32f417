#ifndef VIEWPORT_CLASS
#define VIEWPORT_CLASS

#include "dimensions.h"
#include "gui_defs.h"

class ViewPort  : public Dimension<MaxGuiRange>  {
    private :
        

    public :
        ViewPort (Dimension<MaxGuiRange> d) : Dimension<MaxGuiRange> (d)
        {
            
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
			this->x = x;
			this->y = y;
		}
};



#endif


/*End of file*/

