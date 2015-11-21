#ifndef CONTEXT_SWITCHING
#define CONTEXT_SWITCHING

#include <stdint.h>

typedef uint32_t Word;
typedef uint16_t HWord;
typedef uint8_t byte;

#pragma import StackSwitch   
#pragma import StackSwitchPSV   
#pragma import RuntimeInit
#pragma import CallSVC
  
class RuntimeFrame {
    private :
    
    public :
    RuntimeFrame ()
    {
        
    }
    void operator () (RuntimeFrame *runtime)
    {
        (*this) = runtime;
    }
    void operator = (void *r)
    {
        (*this) = (RuntimeFrame *)r;
    }
    void operator = (RuntimeFrame *runtime)
    {
        this->R0 = runtime->R0;
        this->R1 = runtime->R1;
        this->R2 = runtime->R2;
        this->R3 = runtime->R3;
        this->R4 = runtime->R4;
        this->R5 = runtime->R5;
        this->R6 = runtime->R6;
        this->R7 = runtime->R7;
        this->R8 = runtime->R8;
        this->R9 = runtime->R9;
        this->R10 = runtime->R10;
        this->R11 = runtime->R11;
        this->R12 = runtime->R12;
        this->LR = runtime->LR;
        //this->RL = runtime->RL;
        this->PC = runtime->PC;
        this->XPSR = runtime->XPSR;
        //this->CONTROL = runtime->CONTROL;
    }
    Word R11;
    Word R10;
    Word R9;
    Word R8;
    Word R7;
    Word R6;
    Word R5;
    Word R4;
    Word R0;
    Word R1;
    Word R2;
    Word R3;
    Word R12;
    Word LR;
    Word PC;
    Word XPSR;
    //uint32_t CONTROL;
};    
  
    
typedef struct {
   Word a0;
   Word a1;
   Word a2;
   Word a3; /*Access to this parameter is denied !!! dont write in it representation address in any case !*/
} SVC_arg;



#endif


/*End of file*/

