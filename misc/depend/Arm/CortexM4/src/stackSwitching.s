            PRESERVE8 
            EXPORT SysTick_Handler   
            EXPORT PendSV_Handler 
            EXPORT RuntimeStartup
                
            AREA    |.text|, CODE, READONLY
     IMPORT StackSwitch   
     IMPORT StackSwitchPSV   
     IMPORT RuntimeInit

RuntimeStartup   FUNCTION
                    ;MSR     MSP, R0
                    BL      RuntimeInit
                    MSR     PSP, R0 
                    MOV     R1, #1
                    BL      StackSwitch                  
                    MOV     R1, #6
                    MSR     CONTROL, R1
                    BX      R0
            ENDP
SysTick_Handler  FUNCTION 
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitch
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    POP     {PC}
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
SVC_Handler  FUNCTION      
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
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                