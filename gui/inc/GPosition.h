#ifndef GPOSITION_CLASS
#define GPOSITION_CLASS
#include "Dimensions.h"
#include <stdint.h>

template <typename Range>
class GPosition {
    private :
             Dimension<Range> d;
             uint32_t  worldOffsetX;
             uint32_t worldOffsetY;
            //float focus;
        
        
    public :
            GPosition (Dimension<Range> d, int32_t x = 0, int32_t y = 0)
            {
                this->d = d;
                worldOffsetX = x;
                worldOffsetY = y;
            }
            GPosition (Box<Range> b, int32_t x = 0, int32_t y = 0)
            {
                this->d = b;
                worldOffsetX = x;
                worldOffsetY = y;
            }
            
                
};

#endif

/*End of file*/

