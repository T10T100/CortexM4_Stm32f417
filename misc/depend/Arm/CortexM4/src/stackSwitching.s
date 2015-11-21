            PRESERVE8 
            EXPORT SysTick_Handler   
            EXPORT PendSV_Handler 
            EXPORT RuntimeStartup
            EXPORT EnableFPU
                
            AREA    |.text|, CODE, READONLY
     IMPORT StackSwitch   
     IMPORT StackSwitchPSV   
     IMPORT RuntimeInit

RuntimeStartup   FUNCTION
                    
                    CPSID   I
                    ;MSR     MSP, R1 
                    BL      RuntimeInit 
                    MOV     R1, #1
                    BL      StackSwitch  
                    MSR     PSP, R0                     
                    MOV     R1, #6
                    MSR     CONTROL, R1
                    CPSIE   I
                    POP     {PC}
            ENDP
SysTick_Handler  FUNCTION 
                    CPSID   I
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitch
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    CPSIE   I
                    POP     {PC}
            ENDP  
PendSV_Handler  FUNCTION      
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitchPSV
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    POP     {PC}
            ENDP  
SVC_Handler  FUNCTION      
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitchPSV
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    POP     {PC}
            ENDP 

                
EnableFPU   FUNCTION
                    ; CPACR is located at address 0xE000ED88
                    LDR R0, =0xE000ED88
                    ; Read CPACR
                    LDR R1, [R0]
                    ; Set bits 20-23 to enable CP10 and CP11 coprocessors
                    ORR R1, R1, #(0xF << 20)
                    ; Write back the modified value to the CPACR
                    STR R1, [R0]; wait for store to complete
                    DSB
                    ;reset pipeline now the FPU is enabled
                    ISB
            ENDP
            END
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                