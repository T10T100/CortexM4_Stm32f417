            PRESERVE8 
            EXPORT SysTick_Handler   
            EXPORT PendSV_Handler 
            EXPORT SVC_Handler
            EXPORT RuntimeStartup
            EXPORT EnableFPU
            EXPORT SvcCall                              [WEAK]
                
            AREA    |.text|, CODE, READONLY
     IMPORT StackSwitch   
     IMPORT StackSwitchPSV   
     IMPORT RuntimeInit
     IMPORT CallSVC                                      [WEAK]                            
SvcCall       FUNCTION
                    SWI     0x02
                    BX      LR
                    ENDP
RuntimeStartup   FUNCTION
                    
                    CPSID   I
                    ;MSR     MSP, R1 
                    DSB
                    BL      RuntimeInit 
                    DMB
                    MOV     R1, #1
                    BL      StackSwitch  
                    DMB
                    MSR     PSP, R0                     
                    MOV     R1, #6
                    MSR     CONTROL, R1
                    CPSIE   I
                    POP     {PC}
            ENDP
SysTick_Handler  FUNCTION 
                    CPSID   I
                    DSB
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitch
                    DMB
                    DSB
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    CPSIE   I
                    POP     {PC}
            ENDP  
PendSV_Handler  FUNCTION  
                    CPSID   I
                    DSB
                    MRS     R0, PSP
                    STMDB   R0!, {R4-R11}
                    PUSH    {LR}  
                    MOV     R1, #0
                    BL      StackSwitchPSV
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    CPSIE   I
                    POP     {PC}
            ENDP  
SVC_Handler  FUNCTION      
                    CPSID   I
                    DSB
                    PUSH    {LR} 
                    MRS     R3, PSP
                    STMDB   R3!, {R4-R11}
                    BL      CallSVC
                    LDMIA   R0!, {R4-R11}
                    MSR     PSP, R0
                    CPSIE   I
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
                
                
                
                
                
                
                
                
                
                
                
                
                
                
                