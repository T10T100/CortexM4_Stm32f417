


#ifndef DEVICE_H
#define DEVICE_H


#include "stdint.h"
#include "init.h"
#include "gpio_ex.h"
#include "memory_alloc.h"
#include "memory_template.h"
#include "ArrayListStatic.h"
#include "ArrayList.h"
#include "Queue.h"
#include "String.h"
#include "deviceEventObject.h"

#include "screen_driver.h"
#include "graphicFrameClass.h"
#include "VM.h"
#include "vmapi.h"
#include "graphic.h"
#include "contentPane.h"
#include "extern.h"
#include "touchScreenAdapter.h"


class Device : public ILI9488<GPIO_TypeDef, SpiSoftTypeDef>,
               public ScreenDriver<ILI9488<GPIO_TypeDef, SpiSoftTypeDef>, GraphicFrame<uint16_t,  uint16_t> > {
private:
        
    GraphicFrameFactory<uint16_t, uint16_t> frameFactory;
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
    GContentPane<ColorDepth> *contentPane;
    Device () : ILI9488<GPIO_TypeDef, SpiSoftTypeDef>()
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
        this->ScreenDriver::init((char *)"ili9486");
        Dimension<MaxGuiRange> d(0, 0, 480, 320);
        GraphicFrame<uint16_t, uint16_t> *f = frameFactory.newFrame(d);
        contentPane = (GContentPane<ColorDepth> *) new GContentPane<ColorDepth>(f);
        contentPane->getGraphic()->setFont(Font);
        contentPane->fill(0xaaaa);
        this->fill(contentPane->getFrame());
    }
    
    String *toString ()
    {
        return (String *) new String("device");
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

