#ifndef CONTEXT_SWITCHING
#define CONTEXT_SWITCHING

#include <stdint.h>

extern "C"
void *StackSwitch (void *frame, int32_t);

extern "C"
void *StackSwitchPSV (void *frame, int32_t);
  
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
    uint32_t R11;
    uint32_t R10;
    uint32_t R9;
    uint32_t R8;
    uint32_t R7;
    uint32_t R6;
    uint32_t R5;
    uint32_t R4;
    uint32_t R0;
    uint32_t R1;
    uint32_t R2;
    uint32_t R3;
    uint32_t R12;
    uint32_t LR;
    uint32_t PC;
    uint32_t XPSR;
    //uint32_t CONTROL;
};    
  
    




#endif


/*End of file*/

