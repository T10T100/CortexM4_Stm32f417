


#include "main.h"
#include "device.h"
#include "extern.h"
extern Device device;
extern Runtime runtime;

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

uint32_t systemHeap[20000];



int main ()
{
  HAL_Init();
  HAL_Delay(500);
  SystemClock_Config();
  ClockEnable();
  HsramInit();
  DmaInit();
  //SpiInit();
  GpioInit();
    Heap(0x60000000, 0x7FFFF);
    
    device(Lcd_Rgb_Port, spiLcd);
    device.init();
    device.enableBackLight(true);
    runtime((uint32_t)systemHeap, 20000);
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
	while (1) {
        if (iterator->hasNext() == false) {
            iterator = arrayList.iterator();
        } else {
            iterator->next();
        }
		device.fill(0xffff);
	}
	
	return 0;
}

