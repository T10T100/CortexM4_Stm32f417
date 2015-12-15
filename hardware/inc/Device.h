


#ifndef DEVICE_H
#define DEVICE_H

#include "cursors.h"
#include "stdint.h"
#include "init.h"
#include "gpio_ex.h"
#include "memory_alloc.h"


#include "VM.h"
#include "vmapi.h"
#include "GuiEngine.h"
#include "screen_driver.h"
#include "extern.h"
#include "touchScreenAdapter.h"
#include "vmStdOut.h"



class Device : public ILI9488<GPIO_TypeDef, SpiSoftTypeDef>,
               public ScreenDriver<ILI9488<GPIO_TypeDef, SpiSoftTypeDef>, GraphicFrame<ColorDepth,  MaxGuiRange> >,
               public VmOut<char> {
private:
    char outputCharBuffer[296];
    GraphicFrameFactory frameFactory;
    GuiEngine guiEngine;
/*
    ArrayList<DeviceListener<Device> > listenerList;
    void fireEvents ()
    {
        Iterator<ArrayList<DeviceListener<Device> >, DeviceListener<Device> > *iterator = listenerList.iterator();
        DeviceEventObject<Device> event(*this);
        while (iterator->hasNext() == true) {
            //iterator->getNext()->actionPerformed(event);
        }
    }
*/
    
public:
    GLabel<ColorDepth> *label1;
    GSlide<ColorDepth> *slider1;
    GSlide<ColorDepth> *slider2;
    GSlide<ColorDepth> *slider3;
    GSlide<ColorDepth> *slider4;
    GTextField<ColorDepth> *textField;
    GButton<ColorDepth> **keyPad;
    int keyCount;
    gwt::DefaultCursor<ColorDepth> *cursor;
    GContentPane<ColorDepth> *contentPane;
    GContentPane<ColorDepth> *serviceContentPane;
    Device () : ILI9488<GPIO_TypeDef, SpiSoftTypeDef>(),
                VmOut<char>(outputCharBuffer, 296),
                guiEngine()
    {
       // this->addListener(((DeviceListener<Device> *) new DeviceListener<Device>()));
        
        
    }
    void enableBackLight (bool value)
    {
        this->backLight((int)value);
    }
    void operator () (GPIO_TypeDef *port, SpiSoftTypeDef &spiPort) 
    {
        this->ILI9488::operator()(port, spiPort, 0x0000);
        this->ScreenDriver::operator()(*this);
    }
    void init ()
    {
        guiEngine.init();
        this->ScreenDriver::init((char *)"ili9486");
        GraphicFrame<ColorDepth,  MaxGuiRange> *mainFrame = guiEngine.newFrame(0, 0, 550, 400);
        contentPane = guiEngine.newContentPane( mainFrame );
        label1 = contentPane->createComponent<GLabel<ColorDepth> >(100, 100, 200, 40);
        cursor = contentPane->createComponent<gwt::DefaultCursor<ColorDepth> >(100, 100, 10, 10);
        slider1 = contentPane->createComponent<GSlide<ColorDepth> >(0, 50, 180, 40);
        slider2 = contentPane->createComponent<GSlide<ColorDepth> >(0, 100, 180, 40);
        slider3 = contentPane->createComponent<GSlide<ColorDepth> >(0, 150, 180, 40);
        slider4 = contentPane->createComponent<GSlide<ColorDepth> >(0, 200, 180, 40);
        textField = contentPane->createComponent<GTextField<ColorDepth> >(0, 250, 180, 40);
        slider1->setTop(slider1->getWidth());
        slider2->setTop(slider2->getWidth());
        slider3->setTop(slider3->getWidth());
        slider4->setTop(slider4->getWidth());

        label1->setTopCenter( contentPane->getTopCenter() );
        
        contentPane->addSlider(slider1);
        contentPane->addSlider(slider2);
        contentPane->addSlider(slider3);
        contentPane->addSlider(slider4);
        contentPane->addLabel(label1);
        contentPane->addTextFied(textField);
        //contentPane->addCursor(cursor);
        contentPane->setVisible(true);
        contentPane->setEnable(true);
        
        serviceContentPane = guiEngine.newContentPane( mainFrame );
        serviceContentPane->setBackground(0x0000);
        int w = 0;
        int h = 0;
        keyCount = 0;
        keyPad = (GButton<ColorDepth> **) new GButton<ColorDepth> *[72];
        char *kpdNames[] = {"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","J","I","K","L","M","N","O","P","R","S","T","U","V","W","X","Y","Z"," ","_","%","*","#","!","@","$","^","&","*","(",")","-","+","=","<",">","?","/",",",".","\"","\'","{","}","[","]","Clr","Ret","Exe"};
        for (int i = 0; i < 72; i++, keyCount++) {
            keyPad[i] = serviceContentPane->createComponent<GButton<ColorDepth> >(190 + w, 50 + h, 40, 30);
            w += 45;
            if (w > 260) {
                w = 0;
                h += 35;
                if (h > 310) {
                    break;
                }
            }
            keyPad[i]->setName( kpdNames[i] );
            serviceContentPane->addButton(keyPad[i]);
        }
    }
    
    String *toString ()
    {
        return (String *) new String("device");
    }
    
    void render (ViewPort w, ColorDepth color = 0)
    {
        cursor->setOrigins( w.getTrueView() );
        serviceContentPane->repaint(w);
        contentPane->repaint(w);
        fill<ColorDepth>(contentPane->getFrame(), w, color);
    }
    
    void render (ColorDepth color = 0)
    {
        cursor->setOrigins( guiEngine.getViewPort().getTrueView() );
        contentPane->repaint( guiEngine.getViewPort() );
        serviceContentPane->repaint( guiEngine.getViewPort() );
        fill<ColorDepth>(contentPane->getFrame(), guiEngine.getViewPort(), color);
    }
    
    ViewPort &getViewPort ()
    {
        return guiEngine.getViewPort();
    }
    void setViewPort ()
    {
        
    }
    
};



template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::backLight (uint8_t value)
    {
        if (value) {
            DEV_Pin_Set(Lcd_light_Port, lcd_led_pin ); 
        } else {
            DEV_Pin_Clr(Lcd_light_Port, lcd_led_pin ); 
        }
    }
    
template <typename GPIO_TypeDef, typename SpiSoftTypeDef> template <typename  Color>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::rgbOut (Color color)
    {
        DEV_fPort_Out (this->rgbPort, color);
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::setVs (bool value)
    {
        if (value == true) {
            DEV_Pin_Set(Lcd_Vsync_Port, LCD_Vsync_Pin); 
        } else {
            DEV_Pin_Clr(Lcd_Vsync_Port, LCD_Vsync_Pin); 
        }
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::setHs (bool value)
    {
        if (value == true) {
            DEV_Pin_Set(Lcd_Hsync_Port, LCD_Hsync_Pin);
        } else {
            DEV_Pin_Clr(Lcd_Hsync_Port, LCD_Hsync_Pin);
        }
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::setDot (bool value)
    {
        if (value == true) {
            DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
        } else {
            DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);
        }        
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::toggleDot ()
    {       
        DEV_Pin_Set(Lcd_Clk_Port, LCD_Clk_Pin);
        DEV_Pin_Clr(Lcd_Clk_Port, LCD_Clk_Pin);
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::setDen (bool value)
    {
        if (value == true) {
            DEV_Pin_Set(Lcd_Den_Port, LCD_Den_Pin); 
        } else {
            DEV_Pin_Clr(Lcd_Den_Port, LCD_Den_Pin);  
        }
    }

template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::resetForce (bool value)
    {
        if (value == true) {
            DEV_Pin_Set(Lcd_Reset_Port, LCD_Reset_Pin); 
        } else {
            DEV_Pin_Clr(Lcd_Reset_Port, LCD_Reset_Pin);
        }
    }
template <typename GPIO_TypeDef, typename SpiSoftTypeDef>
void Device::ILI9488<GPIO_TypeDef, SpiSoftTypeDef>::delay (uint32_t msec)
    {
        HAL_Delay(msec);
    } 
    
    
    

#endif /*DEVICE_H*/

