


#include "main.h"
#include "device.h"
#include "extern.h"
#include "Font.h"
extern Device device;
extern Runtime runtime;

int timer0 (void *)
{
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
uint32_t systemHeap[10024];
int colorIndex = 0;
static ViewPort wp;
int SystemEventBurner3 (void *r)
{   
    vm::CleanUp cleanup;
    
    device.enableBackLight(true);
    for (;;) {
        colorIndex++;
        
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
    vm::init((uint32_t)systemHeap, 10000 * 4);
    
    vm::start();
	while (1) {
		device.fill(0xffff);
	}
	
	//return 0;
}


int SystemEventBurner2 (void *r);
int SystemEvent (void *v);

int touchAnyListener (void *t)
{
   auto adapter = (SensorAdapter *)t;
   Point<int32_t> p = adapter->getData().move;
   wp.move(p.x, p.y);
}
Point<int32_t> glo;
int touchClickListener (void *t)
{
   auto adapter = (SensorAdapter *)t;
   Point<int32_t> p = adapter->getData().coordinates;
   device.label1->setText(p.x);
   device.label1->apendText("    ");
   device.label1->apendText(p.y);
   glo.x = p.x + wp.x;
   glo.y = p.y - wp.y;
}

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
    vm::addSensorListener(touchClickListener, onClickHandler);
    vm::addSensorListener(touchAnyListener, onAnyActionHandler);
    Dimension<uint16_t> d(0, 0, 480, 320);
    wp(d);
    wp.set(0, 0);
    //int i = 0;
    for (;;) {
        
        HAL_Delay(5);
    }
    
    
    
}

int SystemEventBurner2 (void *r)
{
    vm::CleanUp cleanup;
    Graphic<ColorDepth> *g = device.contentPane->getGraphic();
    for (;;) {
        vm::pushEvent(SystemEvent);
        device.contentPane->fill(0x0000 + wp.x);
        device.clear();
        device.println("    ");
        device.print ((int32_t)wp.getX());
        device.println("    ");
        device.print ((int32_t)wp.getY());
        
        g->setText( device.getStream(), ColorWhite);
        g->DrawDda(0, 0, 200, 200, 0xee00 + wp.y);
        Box<MaxGuiRange> b = {120, 130, 100, 40};
        Dimension<int32_t> b1(50, 50, 10, 12);
        b1.setOrigins(glo);
        g->fill(b1, 0xa0a0);
        device.contentPane->repaint();
        device.fill<ColorDepth>(device.contentPane->getFrame(), wp, 0);
        vm::sleep(0);
    }
}



int SystemEvent (void *v)
{
    
    colorIndex += 0x8000;
    return 0;
}


/*End of file*/

