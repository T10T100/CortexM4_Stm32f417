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
    class Box {
        public :
              Range x;
              Range y;
              Range w;
              Range h;
    };



template <typename Range>
class Dimension {
    private :
         
    public :
        Range x, y, w, h;
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
        Dimension (Dimension<Range> &d)
        {
            this->x  = d.x;
            this->y = d.y;
            this->w = d.w;
            this->h = d.h;
        }
        Dimension  (Box<Range> &b)
        {
            this->x  = b.x;
            this->y = b.y;
            this->w = b.w;
            this->h = b.h;
        }
        Dimension<Range> operator = (Dimension<Range> &d)
        {
            this->x  = d.x;
            this->y = d.y;
            this->w = d.w;
            this->h = d.h;
            return *this;
        }
        Dimension<Range> operator = (Box<Range> &b)
        {
            this->x  = b.x;
            this->y = b.y;
            this->w = b.w;
            this->h = b.h;
            return *this;
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
        void setSize (Box<Range> d)
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
            this->w = 100;
            this->h = 100;
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
       void setOrigins (Point<Range> p)
        {
            this->x = p.x - this->w / 2;
            this->y = p.y - this->h / 2;
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
        Box<Range> getBox ()
        {
            Box<Range> box = {
                    this->x,
                    this->y,
                    this->w,
                    this->h
            };
            return box;
        }
        Dimension<Range> getDimension ()
        {
            Dimension<Range> d(x, y, w, h);
            return d;
        }
        
        template <typename D>
        bool trunc (D &box)
        {   	
            if (box.x > this->w) {
                  box.x = this->w;
            }
            if (box.x + box.w > this->w) {
                  box.w = this->w - box.x;
            }
          if (box.y > this->h) {
                  box.y = this->h;
            }
            if (box.y + box.h > this->h) {
                  box.h = this->h - box.y;
            }
            
            box.x += this->x;
            box.y += this->y;
            return 0;
        }
        
};



#endif

/*End of file*/

