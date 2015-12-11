#ifndef __SCREENDRIVER
#define __SCREENDRIVER
#include "gui_defs.h"

#ifdef tftili9486
#include "TFTili9486.h"
#else 
#error "please choose startup graphic controller"
#endif

#include "syncClass.h"
#include "viewPort.h"

#define __abs__(x) (x < 0 ? -x : x)

template <typename GraphicController, typename FrameBuffer>
    class ScreenDriver : public Synchronizer<ScreenDriver <GraphicController, FrameBuffer> > {
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
                //CriticalObject critical;
                Synchronize<ScreenDriver <GraphicController, FrameBuffer> > sync(this);
                if (sync.test() == false) {
                    return;
                }
                this->controller->driverFill(color);
            }
            void fill (FrameBuffer *buffer)
            {
                Synchronize<ScreenDriver <GraphicController, FrameBuffer> > sync(this);
                if (sync.test() == false) {
                    return;
                }
                controller->driverFill(buffer->getBuffer(), buffer->getBox());
            }
            template <typename Color>
            void fill (FrameBuffer *buffer, ViewPort &viewPort, Color color = 0x0f80)
            {
                //CriticalObject critical;
                Synchronize<ScreenDriver <GraphicController, FrameBuffer> > sync(this);
                if (sync.test() == false) {
                    return;
                }
                Box<uint16_t> b = {0, 0, 480, 320};
                controller->driverFill(buffer->getBuffer(), b, viewPort.getView());
            }
            
            
            
            
            
            /*       int nw = __abs__(vpx) - buffer->getWidth();
                if (vpx > 0) {
                    controller->driverFill (color, __abs__(vpx), 0, nw, controller->getH());
                    
                } else {
                    controller->driverFill (color, 0, 0, nw, controller->getH());
                }
                
                int nh = __abs__(vpy) - buffer->getHeight();
                if (vpy < 0) {
                    if (vpx < 0) {
                        controller->driverFill (color, __abs__(vpx), __abs__(vpy), nh, controller->getW());
                    } else {
                        controller->driverFill (color, 0, __abs__(vpy), nh, controller->getW() - __abs__(vpx));
                    }
                    
                } else {
                    if (vpx < 0) {
                        controller->driverFill (color, __abs__(vpx), 0, nh, controller->getW());
                    } else {
                        controller->driverFill (color, 0, 0, nh, controller->getW() - __abs__(vpx));
                    }
                }*/
            
            
            
            
            template <typename Image>
            void fill (Image &image)
            {
                Synchronize<ScreenDriver <GraphicController, FrameBuffer> > sync(this);
                if (sync.test() == false) {
                    return;
                }
            }
            template <typename Image>
            void fill (Image &image, int scaleX, int scaleY)
            {
                Synchronize<ScreenDriver <GraphicController, FrameBuffer> > sync(this);
                if (sync.test() == false) {
                    return;
                }
            }
        
    };

#endif /*__SCREENDRIVER*/



