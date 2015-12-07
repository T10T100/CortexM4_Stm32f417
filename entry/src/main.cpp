


#include "main.h"
#include "device.h"
#include "extern.h"
#include "Font.h"
extern Device device;
extern Runtime runtime;

int timer0 (void *)
{
    //runtime.TouchSensorIT();
    vm::invokeServer(TouchSensorDriverID);
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
int SystemEventBurner3 (void *r)
{   
    vm::CleanUp cleanup;
    
    device.enableBackLight(true);
    for (;;) {
        colorIndex++;
        
        vm::sleep(10);
        //device.fill(0x12bc);
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
    /*
    String str0("need");
    String str1("java");
    str0 + str1;
    str1 + 1237765;
    str0 + device;
    arrayList.addFirst((TestClass *) new TestClass('h'));
    arrayList.addFirst((TestClass *) new TestClass('e'));
    arrayList.addFirst((TestClass *) new TestClass('l'));
    arrayList.addFirst((TestClass *) new TestClass('l'));
    arrayList.addFirst((TestClass *) new TestClass('o'));
    Iterator<ArrayList<TestClass>, TestClass> *iterator = arrayList.iterator(); 
    */
    
	while (1) {
		device.fill(0xffff);
	}
	
	//return 0;
}


int SystemEventBurner2 (void *r);
int SystemEvent (void *v);
Point<int16_t> glo;
int touchAnyListener (void *t)
{
   auto adapter = (SensorAdapter *)t;
   
   glo.x = adapter->getData().coordinates.x;
   glo.y = adapter->getData().coordinates.y;
   return 0;
}

int SystemEventBurner (void *r)
{
    HAL_Init();
    SystemClock_Config();
    ClockEnable();
    HsramInit();
    DmaInit();
    SpiInit();
    GpioInit();
    Heap(0x60000000, 0x7FFFF);
    
    device(Lcd_Rgb_Port, spiLcd);
    device.init();
    device.enableBackLight(true);
    vm::runtimeDispatchEvent(event);
    vm::create(SystemEventBurner3, 0);
    vm::create(SystemEventBurner2, 0);
    vm::addTimer(timer0, 10);
    vm::addSensorListener(touchAnyListener, onAnyActionHandler);
    Dimension<uint16_t> d(0, 0, 480, 320);
    ViewPort wp(d);
    //int i = 0;
    for (;;) {
        device.contentPane->fill(0x1aee);
        device.contentPane->getGraphic()->setText("\n\n\n This text is allow only on screen\nit has no presentation in ram yet\nThis text is allow only on screen\nit has no presentation in ram yet\n", colorIndex );
        device.fill<ColorDepth>(device.contentPane->getFrame(), wp);
        wp.set(glo.x % 300, glo.y % 300);  
        //glo = Read();
        HAL_Delay(5);
    }
    
    
    
}

int SystemEventBurner2 (void *r)
{
    vm::CleanUp cleanup;
    for (;;) {
        //device.fill(0x4400);
        vm::pushEvent(SystemEvent);
        vm::sleep(3);
        //colorIndex += 0x8000;
    }
}



int SystemEvent (void *v)
{
    
    colorIndex += 0x8000;
    return 0;
}


/*End of file*/

