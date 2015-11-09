            PRESERVE8 
            EXPORT SysTick_Handler   
            EXPORT PendSV_Handler 
                
            AREA    |.text|, CODE, READONLY
     IMPORT StackSwitch   
     IMPORT StackSwitchPSV         
SysTick_Handler  FUNCTION 
                    PUSH    {R4}
                    PUSH    {R5}
                    PUSH    {R6}
                    PUSH    {R7}
                    PUSH    {R8}
                    PUSH    {R9}
                    PUSH    {R10}
                    PUSH    {R11}
                    PUSH    {LR}  
                    MRS     R0, MSP
                    BL StackSwitch
                    MSR     MSP, R0 
                    POP     {LR}
                    POP     {R11}
                    POP     {R10}
                    POP     {R9}
                    POP     {R8}
                    POP     {R7}
                    POP     {R6}
                    POP     {R5}
                    POP     {R4}     
                    BX      LR
            ENDP  
PendSV_Handler  FUNCTION      
                    PUSH    {R4}
                    PUSH    {R5}
                    PUSH    {R6}
                    PUSH    {R7}
                    PUSH    {R8}
                    PUSH    {R9}
                    PUSH    {R10}
                    PUSH    {R11}
                    PUSH    {LR}  
                    MRS     R0, MSP
                    BL StackSwitchPSV
                    MSR     MSP, R0 
                    POP     {LR}
                    POP     {R11}
                    POP     {R10}
                    POP     {R9}
                    POP     {R8}
                    POP     {R7}
                    POP     {R6}
                    POP     {R5}
                    POP     {R4}     
                    BX      LR
            ENDP  
            END
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                