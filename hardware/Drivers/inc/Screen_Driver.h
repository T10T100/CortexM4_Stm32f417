#ifndef __SCREENDRIVER
#define __SCREENDRIVER
#include "gui_defs.h"

#ifdef tftili9486
#include "TFTili9486.h"
#else 
#error "please choose startup graphic controller"
#endif


template <typename GraphicController, typename FrameBuffer>
    class ScreenDriver {
        private :
        GraphicController *controller;
        char *name;
        public:
            ScreenDriver (GraphicController &c)
            {
                this->controller = &c;
            }
            ScreenDriver ()
            {
                
            }
            void operator () (GraphicController &c)
            {
                this->controller = &c;
            }
            
            void init (char *name)
            {
                this->name = name;
                this->controller->init(); 
            }
            void window (int x, int y, int w, int h)
            {
                this->controller->window(x, y, w, h);
            }
            
            template <typename Color>
            void fill (Color color)
            {
                this->controller->driverFill(color);
            }
            void fill (FrameBuffer &buffer)
            {
                
            }
            template <typename Image>
            void fill (Image &image)
            {
                
            }
            template <typename Image>
            void fill (Image &image, int scaleX, int scaleY)
            {
                
            }
        
    };

#endif /*__SCREENDRIVER*/



