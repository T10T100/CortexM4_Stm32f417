#ifndef GUI_ENGINE
#define GUI_ENGINE

#include "ContentPane.h"
#include "FontFactory.h"
#include "ViewPort.h"
#include "vmapi.h"

extern const DefaultFontStorage Font;

typedef int (guiHandler) (void *);

extern void *guiEngine;

__weak int sensorTouchHandler   (void *);
__weak int sensorClickHandler   (void *);
__weak int sensorReleaseHandler (void *);
__weak int sensorPressHandler   (void *);



class GuiEngine {
    private :
        GraphicFrameFactory frameFactory;
        ArrayListBase<GContentPane<ColorDepth> > contentPanes;
    
        FontFactory<DefaultFontStorage, DefaultCharStorage_t> fontFactory;
    
        ViewPort viewPort;
    
        GraphicFrame<ColorDepth, MaxGuiRange> *activeFrame;
    
        FontCharSet<DefaultFontStorage, DefaultCharStorage_t> *defaultFontSet;
    
        int32_t selectedComponentId;
    
        void setListeners ();
    
        template <typename C>
        int32_t fireComponentTouch (ArrayListBase<C> list, TouchStruct arg)
        {
            C *it = list.getFirst();
            int32_t id = 0;
            while (it != nullptr) {
                id = it->fireSensorTouchPane(arg);
                if (id >= 0) {
                    return id;
                }
                it = it->nextLink;
            }
            return -1;
        }
        template <typename C>
        int32_t fireComponentClick (ArrayListBase<C> list, TouchStruct arg)
        {
            C *it = list.getFirst();
            int32_t id = 0;
            while (it != nullptr) {
                id = it->fireSensorClickPane(arg);
                if (id >= 0) {
                    return id;
                }
                it = it->nextLink;
            }
            return -1;
        }
        template <typename C>
        int32_t fireComponentRelease (ArrayListBase<C> list, TouchStruct arg)
        {
            C *it = list.getFirst();
            int32_t id = 0;
            while (it != nullptr) {
                id = it->fireSensorReleasePane(arg);
                it = it->nextLink;
            }
            return id;
        }
        template <typename C>
        int32_t fireComponentPress (ArrayListBase<C> list, TouchStruct arg)
        {
            C *it = list.getFirst();
            int32_t id = 0;
            while (it != nullptr) {
                id = it->fireSensorPressPane(arg);
                if (id >= 0) {
                    return id;
                }
                it = it->nextLink;
            }
            return -1;
        }

    public :
        GuiEngine ()
        {
            
        }
        void init ()
        {
            guiEngine = this;
            viewPort.setSize(0, 0, 480, 320);
            defaultFontSet = fontFactory.collectFont(&Font);
            setListeners();
            selectedComponentId = SilentComponent;
        }
        
        GraphicFrame<ColorDepth, MaxGuiRange> *newFrame (int x, int y, int w, int h)
        {
            Dimension<MaxGuiRange> d(x, y, w, h);
            activeFrame = frameFactory.newFrame<ColorDepth, MaxGuiRange>(d);
            return activeFrame;
        }
        
        GContentPane<ColorDepth> *newContentPane (GraphicFrame<ColorDepth, MaxGuiRange> *frame)
        {
            GContentPane<ColorDepth> * contentPane = (GContentPane<ColorDepth> *) new GContentPane<ColorDepth>(frame); 
            contentPanes.addFirst(contentPane);
            contentPane->getGraphic()->setCharSet( defaultFontSet );
            contentPane->getGraphic()->setDrawCharSet( defaultFontSet );
            return contentPane;
        }
        
        GraphicFrame<ColorDepth, MaxGuiRange> *getActiveFrame ()
        {
            return activeFrame;
        }
        
        
        ViewPort &getViewPort ()
        {
            return viewPort;
        }
        
        /**/
        
        int fireSensorTouch (TouchStruct arg)
        {
            if (selectedComponentId < 0) {
                viewPort.move(arg.move);
            }
            viewPort.setTrueView(arg.local);
            arg.local = viewPort.getTrueView();
            selectedComponentId = fireComponentTouch(contentPanes, arg);
            return 0;
        }
        
        int fireSensorClick (TouchStruct arg)
        {
            viewPort.setTrueView(arg.local);
            arg.local = viewPort.getTrueView();
            selectedComponentId = fireComponentClick(contentPanes, arg);
            return 0;
        }
        
        int fireSensorRelease (TouchStruct arg)
        {
            arg.local = viewPort.getTrueView();
            selectedComponentId = fireComponentRelease(contentPanes, arg);
            return 0;
        }
        
        int fireSensorPress (TouchStruct arg)
        {
            arg.local = viewPort.getTrueView();
            selectedComponentId = fireComponentPress(contentPanes, arg);
            return 0;
        }
        
        /**/
};



#endif


/*End of file*/


