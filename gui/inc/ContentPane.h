#ifndef G_CONTENT_PANE
#define G_CONTENT_PANE

#include "memory_template.h"
#include "ArrayListStatic.h"
#include "gui_defs.h"
#include "graphicFrameClass.h"
#include "graphic.h"
#include "GLabel.h"
#include "GSlide.h"
#include "GKeypad.h"
#include "textField.h"
#include "NonPaletteComponentInterface.h"
#include "GraphicComponent.h"
#include "DefaultCursorObject.h"


enum ComponentTypeId {
    SilentComponent = -1,
    ComponentLabelTypeId = 0,
    ComponentSliderTypeId = 1,
    ComponentButtonTypeId = 2, 
    ComponentTextFieldTypeId = 3,


    NonPaletteComponentTypeId = 33,    
};



template <typename Color>
  class GContentPane : protected Allocator<void *>,
                       public virtual Dimension<MaxGuiRange>,
                       public GComponent<Color>,
                       public GPaletteComponent<Color>,
                       public DefaultArrayListBaseNode<GContentPane<Color> > {
    private :
        GraphicFrame<ColorDepth, MaxGuiRange> *frame;
    
        ArrayListBase<GLabel<Color> > gLabels;
        ArrayListBase<GSlide<Color> > gSliders;
        ArrayListBase<GButton<Color> > gButtons;
        ArrayListBase<GTextField<Color> > gTextFields;
        ArrayListBase<GraphicObject<Color> > gGraphics;
        ArrayListBase<NonPaletteInterface<Color> > gComponents;
    
        int32_t selectedComponentId;
        int32_t selectedComponentType;
        void *selectedComponent;
        bool test (ViewPort &w,  Box<int> p)
        {
            if (w.testTrueViewPoint( p.x, p.y ) == true) {
                    return true;
            }
            if (w.testTrueViewPoint( p.x + p.w, p.y ) == true) {
                    return true;
            }
            if (w.testTrueViewPoint( p.x, p.y + p.h ) == true) {
                    return true;
            }
            if (w.testTrueViewPoint( p.x + p.w, p.y + p.h ) == true) {
                    return true;
            }
            return false;
        }
    
        template <typename Element>
        void repaint (ArrayListBase<Element> &list, ViewPort &w)
        {
            Element *it = list.getFirst();
            while (it != nullptr) {
                if ( test(w, it->getBox()) == true || it->getForceRepaint() == true) {
                    it->repaint();
                }
                it = it->nextLink;
            }
        }
        template <typename Element>
        int fireSensorTouch(ArrayListBase<Element> &components, TouchStruct arg)
        {
            if (this->testPoint(arg.local) == false) {
                return -1;
            }
            Element *it = components.getFirst();
            while (it != nullptr) {
                selectedComponentId = it->fireSensorTouch(arg);
                if (selectedComponentId > 0) {
                    selectedComponent = it;
                    return selectedComponentId;
                }
                it = it->nextLink;
            }
            return -1;
        }
        template <typename Element>
        int fireSensorClick(ArrayListBase<Element> &components, TouchStruct arg)
        {
            
            if (selectedComponentId >= 0) {
                return selectedComponentId;
            }
            if (this->testPoint(arg.local) == false) {
                return -1;
            }
            GComponent<Color>::fireSensorClick(arg);
            Element *it = components.getFirst();
            while (it != nullptr) {
                selectedComponentId = it->fireSensorClick(arg);
                if (selectedComponentId > 0) {
                    selectedComponent = it;
                    return selectedComponentId;
                }
                it = it->nextLink;
            }
            return -1;
        }
        template <typename Element>
        int fireSensorRelease(ArrayListBase<Element> &components, TouchStruct arg)
        {
            /*
            Element *it = components.getFirst();
            selectedComponentId = -1;
            while (it != nullptr) {
                if (it->fireSensorRelease(arg) > 0) {return;}
                it = it->nextLink;
            }
            */
            return -1;
        }
        template <typename Element>
        int fireSensorPress(ArrayListBase<Element> &components, TouchStruct arg)
        {
            
            if (this->testPoint(arg.local) == false) {
                return -1;
            }
            GComponent<Color>::fireSensorPress(arg);
            Element *it = components.getFirst();
            while (it != nullptr) {
                selectedComponentId = it->fireSensorPress(arg);
                if (selectedComponentId > 0) {
                    selectedComponent = it;
                    return selectedComponentId;
                }
                it = it->nextLink;
            }
            return -1;
        }
        GContentPane (GraphicFrame<Color, MaxGuiRange> *frame) : GComponent<Color>(),
                                                                 GPaletteComponent<Color>()
        {
            this->frame = frame;
            Box<MaxGuiRange> box = frame->getBox();
            this->setSize(box);
            GPaletteComponent<Color>::operator () ( (Graphic<Color>*) new Graphic<Color>(frame) );      
            selectedComponentId = -1;
            selectedComponentType = SilentComponent;
            selectedComponent = nullptr;
        }
        ~GContentPane ()
        {
            delete(this);
        }
        friend class GuiEngine;
    public :
        
        
        
        void fill (Color color)
        {
            frame->fill(color);
        }
        
        void fill ()
        {
            frame->fill(this->background);
        }
        
        
        template <class C> 
        C *createComponent (uint32_t x, uint32_t y, uint32_t w, uint32_t h)
        {
            auto c = (C *) new C(this->graphic);
            c->setSize(x, y, w, h);
            c->setContentPane(this);
            return c;
        }
        
        void addLabel (GLabel<Color> *l)
        {
            /*if (list.contain(c) == false)*/
            gLabels.addFirst(l);
        }
        void addSlider (GSlide<Color> *S)
        {
            /*if (list.contain(c) == false)*/
            gSliders.addFirst(S);
        }
        void addButton (GButton<Color> *K)
        {
            /*if (list.contain(c) == false)*/
            gButtons.addFirst(K);
        }
        void addTextFied (GTextField<Color> *c)
        {
            /*if (list.contain(c) == false)*/
            gTextFields.addFirst(c);
        }
        //
        void addNonPalette (NonPaletteInterface<Color> *I)
        {
            /*if (list.contain(c) == false)*/
            gComponents.addFirst(I);
        }
        void addGraphic (GraphicObject<Color> *I)
        {
            /*if (list.contain(c) == false)*/
            gGraphics.addFirst(I);
        }
        
        
        void removeGraphic (GraphicObject<Color> *I)
        {
            /*if (list.contain(c) == false)*/
            gGraphics.remove(I);
        }
        
        GraphicFrame<ColorDepth, MaxGuiRange> *getFrame ()
        {
            return frame;
        }
        
        
        
        
        void repaint (ViewPort &w)
        {
            if (this->visible == false || this->enabled == false) {
                return;
            }
            repaint(gTextFields, w);
            repaint(gSliders, w);
            repaint(gLabels, w);
            repaint(gButtons, w);
            repaint(gComponents, w);
            repaint(gGraphics, w);
        }
        
        int32_t fireSensorTouchPane (TouchStruct arg)
        {
            if (this->enabled == false) {
                return -1;
            }
            if (selectedComponentId >= 0) {
                switch (selectedComponentType) {
                case ComponentLabelTypeId:
                        ( (GLabel<Color> *)selectedComponent )->fireSensorTouch(arg);
                    break;
                case ComponentSliderTypeId:
                        ( (GSlide<Color> *)selectedComponent )->fireSensorTouch(arg);
                    break;
                case ComponentButtonTypeId:
                        ( (GButton<Color> *)selectedComponent )->fireSensorTouch(arg);
                    break;
                case ComponentTextFieldTypeId:
                        ( (GTextField<Color> *)selectedComponent )->fireSensorTouch(arg);
                    break;
                case NonPaletteComponentTypeId:
                        ( (NonPaletteInterface<Color> *)selectedComponent )->fireSensorTouch(arg);
                    break;
                
                default :
                    break;
                };
                if (this->testPoint(arg.local) == true) {
                    GComponent<Color>::fireSensorTouch(arg);
                }
                return selectedComponentId;
            }
            int32_t id = fireSensorTouch(gButtons, arg);
            if (id >= 0) {
                selectedComponentType = ComponentButtonTypeId;
                return id;
            }
            id = fireSensorTouch(gLabels, arg);
            if (id >= 0) {
                selectedComponentType = ComponentLabelTypeId;
                return id;
            }
            id = fireSensorTouch(gSliders, arg);
            if (id >= 0) {
                selectedComponentType = ComponentSliderTypeId;
                return id;
            }
            id = fireSensorTouch(gTextFields, arg);
            if (id >= 0) {
                selectedComponentType = ComponentTextFieldTypeId;
                return id;
            }
            id = fireSensorTouch(gComponents, arg);
            if (id >= 0) {
                selectedComponentType = NonPaletteComponentTypeId;
                return id;
            }
            return -1;
        }
        
        int32_t fireSensorClickPane (TouchStruct arg)
        {
            if (this->enabled == false) {
                return -1;
            }
            int32_t id = fireSensorClick(gButtons, arg);
            if (id >= 0) {
                selectedComponentType = ComponentButtonTypeId;
                return id;
            }
            id = fireSensorClick(gLabels, arg);
            if (id >= 0) {
                selectedComponentType = ComponentLabelTypeId;
                return id;
            }
            id = fireSensorClick(gSliders, arg);
            if (id >= 0) {
                selectedComponentType = ComponentSliderTypeId;
                return id;
            }
            id = fireSensorClick(gTextFields, arg);
            if (id >= 0) {
                selectedComponentType = ComponentTextFieldTypeId;
                return id;
            }
            id = fireSensorClick(gComponents, arg);
            if (id >= 0) {
                selectedComponentType = NonPaletteComponentTypeId;
                return id;
            }
            return -1;
        }
        
        int32_t fireSensorReleasePane (TouchStruct arg)
        {
            if (this->enabled == false) {
                return -1;
            }
            GComponent<Color>::fireSensorRelease(arg);
            switch (selectedComponentType) {
                case ComponentLabelTypeId:
                        ( (GLabel<Color> *)selectedComponent )->fireSensorRelease(arg);
                        selectedComponent = nullptr;
                    break;
                case ComponentSliderTypeId:
                        ( (GSlide<Color> *)selectedComponent )->fireSensorRelease(arg);
                        selectedComponent = nullptr;
                    break;
                case ComponentButtonTypeId:
                        ( (GButton<Color> *)selectedComponent )->fireSensorRelease(arg);
                        selectedComponent = nullptr;
                    break;
                case ComponentTextFieldTypeId:
                        ( (GTextField<Color> *)selectedComponent )->fireSensorRelease(arg);
                        selectedComponent = nullptr;
                    break;
                case NonPaletteComponentTypeId:
                        ( (NonPaletteInterface<Color> *)selectedComponent )->fireSensorRelease(arg);
                        selectedComponent = nullptr;
                    break;
                default :
                    break;
            };
            selectedComponentType = -1;
            selectedComponentId = -1;
            return selectedComponentId;
        }
        
        int32_t fireSensorPressPane (TouchStruct arg)
        {
            if (this->enabled == false) {
                return -1;
            }
            if (selectedComponentId >= 0) {
                switch (selectedComponentType) {
                case ComponentLabelTypeId:
                        ( (GLabel<Color> *)selectedComponent )->fireSensorPress(arg);
                    break;
                case ComponentSliderTypeId:
                        ( (GSlide<Color> *)selectedComponent )->fireSensorPress(arg);
                    break;
                case ComponentButtonTypeId:
                        ( (GButton<Color> *)selectedComponent )->fireSensorPress(arg);
                    break;
                case ComponentTextFieldTypeId:
                        ( (GButton<Color> *)selectedComponent )->fireSensorPress(arg);
                    break;
                case NonPaletteComponentTypeId:
                        ( (NonPaletteInterface<Color> *)selectedComponent )->fireSensorPress(arg);
                        selectedComponent = nullptr;
                    break;
                default :
                    break;
                };
                if (this->testPoint(arg.local) == true) {
                    GComponent<Color>::fireSensorPress(arg);
                }
                return selectedComponentId;
            }
            int32_t id = fireSensorPress(gLabels, arg);
            id = fireSensorPress(gButtons, arg);
            if (id >= 0) {
                selectedComponentType = ComponentButtonTypeId;
                return id;
            }
            if (id >= 0) {
                selectedComponentType = ComponentLabelTypeId;
                return id;
            }
            id = fireSensorPress(gSliders, arg);
            if (id >= 0) {
                selectedComponentType = ComponentSliderTypeId;
                return id;
            }
            id = fireSensorPress(gTextFields, arg);
            if (id >= 0) {
                selectedComponentType = ComponentTextFieldTypeId;
                return id;
            }
            id = fireSensorPress(gComponents, arg);
            if (id >= 0) {
                selectedComponentType = NonPaletteComponentTypeId;
                return id;
            }
            return -1;
        }
        
        
        
        int32_t getSelectedComponentId ()
        {
              return selectedComponentId;
        }
        int32_t getSelectedComponentType ()
        {
              return selectedComponentType;
        }
        void *getSelectedComponent ()
        {
              return selectedComponent;
        }
};





#endif 


/*End of file*/

