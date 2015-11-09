#ifndef GC_DIMENSIONS
#define GC_DIMENSIONS


template <typename Range>
    class Point {
        public :
            union {
              Range x;
              Range w;
            };
            union {
              Range y;
              Range h;
            };         
    };



template <typename Range>
class Dimension {
    private :
         Range x, y, w, h;
    public :
        Dimension ()
        {
            this->x = 0;
            this->y = 0;
            this->w = 0;
            this->h = 0;
        }
        Dimension (int x, int y)
        {
            this->x  = x;
            this->y = y;
            this->w = 0;
            this->h = 0;
        }
        Dimension (int x, int y, int w, int h = 0)
        {
            this->x  = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
        
        
        void setSize (int x, int y, int w = 0, int h = 0)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }
        void setSize (Dimension d)
        {
            this->x = d.x;
            this->y = d.y;
            this->w = d.w;
            this->h = d.h;
        }
        void setDefaultSize ()
        {
            this->x = 0;
            this->y = 0;
            this->w = 480;
            this->h = 320;
        }
        void setX (int x)
        {
            this->x = x;
        }
        void setY (int x)
        {
            this->y = x;
        }
        void setW (int x)
        {
            this->w = x;
        }
        void setH (int x)
        {
            this->h = x;
        }
        
        
        
        
        int getX ()
        {
            return this->x;
        }
        int getY ()
        {
            return this->y;
        }
        int getWidth ()
        {
            return this->w;
        }
        int getHeight ()
        {
            return this->h;
        }
        Point<Range> getPlacement ()
        {
            Point<Range> p;
            p.x = this->x;
            p.y = this->y;
            return p;
        }
        Point<Range> getSize ()
        {
            Point<Range> p;
            p.w = this->w;
            p.h = this->h;
            return p;
        }
        Point<Range> getOrigins ()
        {
            Point<Range> p;
            p.x = this->x + this->w / 2;
            p.y = this->y + this->h / 2;
            return p;
        }
};



#endif

/*End of file*/

