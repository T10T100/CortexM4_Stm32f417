#ifndef DEFAULT_CURSOR_OBJECT
#define DEFAULT_CURSOR_OBJECT

#include "graphic.h"
#include "ArrayListStatic.h"
namespace gwt {

    template <typename Color>
    class DefaultCursor : public Dimension<MaxGuiRange>,
                          public DefaultArrayListBaseNode<DefaultCursor<Color> >        {
        private :
            const tImage<uint16_t> *icon; 
            int32_t reminderLifeTime;
            Graphic<Color> *graphic;
            Color background;
            Color foreground;
            
        
        public :
            DefaultCursor () {}
            DefaultCursor (Graphic<Color> *graphic)
            {
                this->graphic = graphic;
                background = ColorWhite;
                foreground = ColorBlack;
                reminderLifeTime= 0;
                icon = nullptr;
            }
            void operator () (Graphic<Color> *graphic)
            {
                this->graphic = graphic;
                background = ColorWhite;
                foreground = ColorBlack;
                reminderLifeTime = 0;
                icon = nullptr;
            }
            ~DefaultCursor ()
            {
                delete(this);
            }
            

            
            void repaint ()
            {
                if (icon != nullptr) {
                    Box<MaxGuiRange> b = {x, y, icon->W, icon->H};
                    graphic->fill(b, icon, 0);
                }
                if (reminderLifeTime > 0) {
                    this->w = 2 * reminderLifeTime;
                    this->h = this->w;
                    graphic->circle(x, y, reminderLifeTime, background);
                    reminderLifeTime -= 4;
                }
            }
            
            void setIcon (const tImage<uint16_t> *icon)
            {   if (icon != nullptr) {
                    this->icon = icon;
                }
            }
            
            void remaind ()
            {
                reminderLifeTime = 24;
            }
            
            void setBackground (Color color)
            {
                background = color;
            }
            void setForeground (Color color)
            {
                foreground = color;
            }
        
    };


};


#endif


/*End of file*/

