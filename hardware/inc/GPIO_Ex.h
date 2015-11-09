






#ifndef __GPIO_EX
#define __GPIO_EX
#include <stdint.h>
#include "main.h"


static GPIO_InitTypeDef  GPIO_InitStruct;

int32_t DEV_Gpio_Init (GPIO_TypeDef *port, int pin_bm, uint32_t mode, uint32_t pupd);
int32_t DEV_AltGpio_Init (GPIO_TypeDef *port, int pin_bm, uint32_t mode, uint32_t alt);

/*
void DEV_Pin_Set  (GPIO_TypeDef *port, uint32_t pin_bm);
void DEV_Pin_Clr  (GPIO_TypeDef *port, uint32_t pin_bm);
void DEV_Pin_Tog  (GPIO_TypeDef *port, uint32_t pin_bm);
void DEV_Pin_Put  (GPIO_TypeDef *port, uint32_t pin_bm, bool val);
void DEV_Port_Out (GPIO_TypeDef *port, uint32_t val, uint32_t mask);
bool DEV_Pin_Read (GPIO_TypeDef *port, uint32_t pin_bm);
*/
#define  DEV_Pin_Set(p, v)  do {\
	                                p->BSRR = v;\
                            } while (0)

#define  DEV_Pin_Clr(p, v)  do {\
	                                p->BSRR = v << 16;\
                            } while (0)

#define  DEV_Pin_Tog(p, v)  do {\
	                                p->ODR ^= v;\
                            } while (0)

#define  DEV_Pin_Put(p, bm, v)  do {\
	                                if (v) DEV_Pin_Set (p, bm);\
	                                else DEV_Pin_Clr(p, bm);\
                            } while (0)

#define  DEV_Port_Out(p, v, m)  do {\
	                                p->BSRR = m;\
	                                p->BSRR = v;\
                            } while (0)

#define  DEV_fPort_Out(p, v)  do {\
	                                p->ODR = v;\
                            } while (0)

#define  DEV_Pin_Read(p, v)  (p->IDR & v)														



class SpiSoftTypeDef {
	protected:
        void dummyWait (uint32_t _us);
	public:
		void init (void);
		void select (void);
		void deSelect (void);
		void dummyClock (void);
        void send_9bit_Data (bool _nine, uint8_t data);
		uint8_t read_8bit_Data (void);
};

#endif
