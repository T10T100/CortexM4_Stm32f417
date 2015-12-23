


#include "main.h"
#include "device.h"
#include "extern.h"
#include "Font.h"


#include "krummWalk0.h"
#include "krumThrow0.h"
#include "KrummThrowAmmo0.h"



extern Device device;
extern Runtime runtime;

uint32_t systemHeap[12024];
int colorIndex = 0;
static ViewPort wp;


int timer0 (void *)
{
    colorIndex++;
    static int i = 0;
    i++;
    return i;
}

class TestClass {
    private :
        char c;
    public :
        TestClass (char c)
        {
            this->c = c;
        }
        char getChar ()
        {
            return this->c;
        }
};

ArrayList<TestClass> arrayList;

int SystemEventBurner3 (void *r)
{   
    vm::CleanUp cleanup;
    
    device.enableBackLight(true);
    for (;;) {
        
        vm::sleep(10);
    }
    return 0;
}

int event (void *)
{
    return 0;
}

int main ()
{
    vm::init((uint32_t)systemHeap + 32, 12000 * 4);
    
    vm::start();
	while (1) {
		device.fill(0xffff);
	}
	
	//return 0;
}


int SystemEventBurner2 (void *r);
int SystemEvent (void *v);


int SystemEventBurner (void *r)
{
    HAL_Init();
    SystemClock_Config();
    ClockEnable();
    HsramInit();
    DmaInit();
    SpiInit();
    TimInit();
    GpioInit();
    Heap(0x60000000, 0x7FFFF);
    
    device(Lcd_Rgb_Port, spiLcd);
    device.init();
    device.enableBackLight(true);
    vm::runtimeDispatchEvent(event);
    vm::create(SystemEventBurner3, "user");
    vm::create(SystemEventBurner2, "Renderer");
    vm::addTimer(timer0, 2);
    Dimension<int32_t> d(0, 0, 480, 320);
    wp(d);
    wp.set(0, 0);
    //int i = 0;
    for (;;) {
        
        HAL_Delay(5);
    }
    
    
    
}

int labelClickListener (TouchStruct arg)
{
    device.label1->setSelect();
    static int sw = 0;
    return 1;
}
int labelTouchListener (TouchStruct arg)
{
    static GLabel<ColorDepth> *l = (GLabel<ColorDepth> *)arg.object;
    l->setText(arg.local.x);
    l->apendText("    ");
    l->apendText(arg.local.y);
    return 1;
}
int PaneClickListener (TouchStruct arg)
{
    device.cursor->setOrigins(arg.local);
    device.cursor->remaind();
    return 1;
}

int SliderTouchListener (TouchStruct arg)
{
    device.slider1->setValue(arg.local.x);
    device.slider1->setSelect();
    
    device.label1->setText("SLIDER_1 : ");
    device.label1->apendText("    ");
    device.label1->apendText(device.slider1->getValue());
    return 1;
}
int Slider2TouchListener (TouchStruct arg)
{
    device.slider2->setValue(arg.local.x);
    device.slider2->setSelect();
    
    device.label1->setText("SLIDER_2 : ");
    device.label1->apendText("    ");
    device.label1->apendText(device.slider2->getValue());
    return 1;
}
int Slider3TouchListener (TouchStruct arg)
{
    device.slider3->setValue(arg.local.x);
    device.slider3->setSelect();
    
    device.label1->setText("SLIDER_3 : ");
    device.label1->apendText("    ");
    device.label1->apendText(device.slider3->getValue());
    return 1;
}
int Slider4TouchListener (TouchStruct arg)
{
    device.slider4->setValue(arg.local.x);
    device.slider4->setSelect();
    
    device.label1->setText("SLIDER_4 : ");
    device.label1->apendText("    ");
    device.label1->apendText(device.slider4->getValue());
    return 1;
}

int KeypadListener (TouchStruct arg)
{
    GButton<ColorDepth> *b = (GButton<ColorDepth> *)arg.object;
    if (b->getName()[0] == '*') {
        device.label1->setText(" ");
    } else {
        device.label1->apendText(b->getName());
    }
    b->setSelect();
}

int SystemEventBurner2 (void *r)
{
    vm::CleanUp cleanup;
    Graphic<ColorDepth> *g = device.contentPane->getGraphic();
    volatile const int backgroundColor = 0x0000;
    device.label1->addClickListener(labelClickListener);
    device.label1->addTouchListener(labelTouchListener);
    device.contentPane->addClickListener(PaneClickListener);
    device.slider1->addTouchListener(SliderTouchListener);
    device.slider2->addTouchListener(Slider2TouchListener);
    device.slider3->addTouchListener(Slider3TouchListener);
    device.slider4->addTouchListener(Slider4TouchListener);
    device.label1->setBackground(0xffff);
    device.contentPane->setBackground(0x140C);
    for (;;) {
        vm::pushEvent(SystemEvent);
        
        device.contentPane->fill();
        /*
        device.clear();
        device.println("    ");
        device.print (device.getViewPort().getTrueView().x);
        device.println("    ");
        device.print (device.getViewPort().getTrueView().y);
        */
        
        //vm::startCritical();
        //g->setText( device.getStream(), colorIndex );
        device.render();
        //vm::endCritical();
        vm::sleep(0);
    }
}



int SystemEvent (void *v)
{
    
    colorIndex += 0x8000;
    return 0;
}


/*End of file*/

