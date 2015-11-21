#ifndef CPU_CONTROL_PRESENT
#define CPU_CONTROL_PRESENT
#include <stdint.h>
#include "contextSwitching.h"


typedef struct SCB_AdressSpace__ {
    uint32_t SCB_ACTLR; /*RW	Privileged	0x00000000	Auxiliary Control Register*/
    uint32_t SCB_CPUID; /*RO	Privileged	0x410FC240  CPUID Base Register*/
    uint32_t ICSR;      /*RW    Privileged	0x00000000	Interrupt Control and State Register*/
    uint32_t VTOR;      /*RW	Privileged	0x00000000	Vector Table Offset Register*/
    uint32_t AIRCR;     /*RW 	Privileged	0xFA050000  Application Interrupt and Reset Control Register*/
    uint32_t SCR;       /*RW	Privileged	0x00000000	System Control Register*/
    uint32_t CCR;       /*RW	Privileged	0x00000200	Configuration and Control Register*/
    uint32_t SHPR1;     /*RW	Privileged	0x00000000	System Handler Priority Register 1*/
    uint32_t SHPR2;     /*RW	Privileged	0x00000000	System Handler Priority Register 2*/
    uint32_t SHPR3;     /*RW	Privileged	0x00000000	System Handler Priority Register 3*/
    uint32_t SHCRS;     /*RW	Privileged	0x00000000	System Handler Control and State Register*/
    uint32_t CFSR;      /*RW	Privileged	0x00000000	Configurable Fault Status Register*/
    uint32_t MMSR;      /*RW	Privileged	0x00	    MemManage Fault Status Register*/
    uint32_t BFSR;      /*RW	Privileged	0x00	    BusFault Status Register*/
    uint32_t UFSR;      /*RW	Privileged	0x0000	    UsageFault Status Register*/
    uint32_t HFSR;      /*RW	Privileged	0x00000000	HardFault Status Register*/
    uint32_t MMAR;      /*RW	Privileged	Unknown	    MemManage Fault Address Register*/
    uint32_t BFAR;      /*RW	Privileged	Unknown	    BusFault Address Register*/
    uint32_t AFSR;      /*RW	Privileged	0x00000000	Auxiliary Fault Status Register*/
} SCB_AdressSpace;



/**/
enum SCB_CPUID_bm {
    Implementer  = (0xFF << 23),
    Variant      = (0xF << 19),
    Constant     = (0xF << 15), 
    PartNo       = (0xFFF << 3),
    Revision     = (0xF << 0),
    ImplementerBp  = (24),
    VariantGp      = (20),
    ConstantGp     = (16), 
    PartNoGp       = (4),
    RevisionGp     = (0)
};
typedef struct {
    uint32_t Implementer; 
    uint32_t Variant;
    uint32_t Constant;
    uint32_t PartNo;
    uint32_t Revision;
} SCB_CPUID;
/**/


/**/
enum SCB_VTOR_bm {
    TBLOFF  = ((0xFFFFFF | (1 << 7)) << 7),
    TBLOFFgp   = (7),
    ReservedGp = 20,
};
typedef struct {
    uint32_t Tbloff; 
    uint32_t Reserved;
} SCB_VTOR;
/**/

/**/
enum SCB_AIRCR_bm {
    VECTKEYSTAT   = (0xFFFF  << 15),
    ENDIANNESS    = (1 << 15),
    PRIGROUP      = (3 << 7),
    SYSRESETREQ   = (1 << 2),
    VECTCLRACTIVE = (1 << 1),
    VECTRESET     = (1 << 0),
    VECTKEYSTATgp   = (15),
    ENDIANNESSgp    = (15),
    PRIGROUPgp      = (8),
    SYSRESETREQgp   = (2),
    VECTCLRACTIVEgp = (11),
    VECTRESETgp     = (0),
};
typedef struct {
    uint32_t VectKeyStat; 
    uint32_t Endianness; 
    uint32_t Prigroup; 
    uint32_t SysResetReq; 
    uint32_t VectCtlActive; 
    uint32_t VectReset; 
} SCB_AIRCR;
/**/



/**/
enum SCB_SCR_bm {
    SEVONPEND    = (1 << 4),
    SLEEPDEEP    = (1 << 2),
    SLEEPONEXIT  = (1 << 1),
    SEVONPENDgp    = (4),
    SLEEPDEEPgp    = (2),
    SLEEPONEXITgp  = (1),
};
typedef struct {
    uint32_t SevonPend; 
    uint32_t SleepDeep; 
    uint32_t SleepOnExit; 
} SCB_SCR;
/**/



/**/
enum SCB_CCR_bm {
    STKALIGN       = (1 << 9),
    BFHFNMIGN      = (1 << 8),
    DIV_0_TRP      = (1 << 4),
    UNALIGN_TRP    = (1 << 3),
    USERSETMPEND   = (1 << 1),
    NONBASETHRDENA = (1 << 0),
    STKALIGNgp       = (9),
    BFHFNMIGNgp      = (8),
    DIV_0_TRPgp      = (4),
    UNALIGN_TRPgp    = (3),
    USERSETMPENDgp   = (1),
    NONBASETHRDENAgp = (0),
};
typedef struct {
    uint32_t StckAllign; 
    uint32_t BFHFNMIGN; 
    uint32_t DIV_0_TRP; 
    uint32_t UNALIGN_TRP; 
    uint32_t USERSETMPEND; 
    uint32_t NONBASETHRDENA; 
} SCB_CCR;
/**/



/**/
enum SCB_SHPR1_bm {
    PRI_6       = (0xFF << 15),
    PRI_5       = (0xFF << 7),
    PRI_4       = (0xFF << 0),
    PRI_6gp       = (16),
    PRI_5gp       = (8),
    PRI_4gp       = (0),
};
typedef struct {
    uint32_t PRI_6; 
    uint32_t PRI_5; 
    uint32_t PRI_4; 
} SCB_SHPR1;
/**/



/**/
enum SCB_SHPR2_bm {
    PRI_11       = (0xFF << 23),
    PRI_11gp       = (24),
};
typedef struct {
    uint32_t PRI_11; 
} SCB_SHPR2;
/**/



/**/
enum SCB_SHPR3_bm {
    PRI_15       = (0xFF << 23),
    PRI_14       = (0xFF << 15),
    PRI_15gp       = (23),
    PRI_14gp       = (15),
};
typedef struct {
    uint32_t PRI_15; 
    uint32_t PRI_14; 
} SCB_SHPR3;
/**/


/**/
enum SCB_SHCRS_bm {
    USGFAULTENA = (1 << 18),
    BUSFAULTENA = (1 << 17),
    MEMFAULTENA = (1 << 16),
    SVCALLPENDED = (1 << 15),
    BUSFAULTPENDED = (1 << 14),
    MEMFAULTPENDED = (1 << 13),
    USGFAULTPENDED = (1 << 12),
    SYSTICKACT = (1 << 11),
    PENDSVACT = (1 << 10),
    /*Reserved = (1 << 9),*/
    MONITORACT = (1 << 8),
    SVCALLACT = (1 << 7),
    USGFAULTACT = (1 << 3),
    BUSFAULTACT = (1 << 1),
    MEMFAULTACT = (1 << 0),
    USGFAULTENAgp = (18),
    BUSFAULTENAgp = (17),
    MEMFAULTENAgp = (16),
    SVCALLPENDEDgp = (15),
    BUSFAULTPENDEDgp = (14),
    MEMFAULTPENDEDgp = (13),
    USGFAULTPENDEDgp = (12),
    SYSTICKACTgp = (11),
    PENDSVACTgp = (10),
    Reserved = (1 << 9),
    MONITORACTgp =  (8),
    SVCALLACTgp = (7),
    USGFAULTACTgp = (3),
    BUSFAULTACTgp = (1),
    MEMFAULTACTgp = (0),
};

typedef struct {
    int32_t USGFAULTENA;
    int32_t BUSFAULTENA;
    int32_t MEMFAULTENA;
    int32_t SVCALLPENDED;
    int32_t BUSFAULTPENDED;
    int32_t MEMFAULTPENDED;
    int32_t USGFAULTPENDED;
    int32_t SYSTICKACT;
    int32_t PENDSVACT;
    int32_t Reserved;
    int32_t MONITORACT;
    int32_t SVCALLACT;
    int32_t BUSFAULTACT;
    int32_t MEMFAULTACT;
} SCB_SHCRS;
/**/




/**/
enum SCB_CFSR_bm {
    UFSR       = (0xFFFF << 15),
    BFSR      = (0xFF << 7),
    MMFSR      = (0xFF << 0),
    UFSRgp       = (16),
    BFSRgp      = (8),
    MMFSRgp      = (0),
};
typedef struct {
    uint32_t UFSR; 
    uint32_t BFSR; 
    uint32_t MMFSR; 
} SCB_CFSR;
/**/


/**/
enum SCB_HFSR_bm {
    DEBUGEVT       = (1 << 31),
    FORCED      = (1 << 30),
    VECTTBL      = (1 << 1),
    DEBUGEVTgp       = (31),
    FORCEDgp      = (30),
    VECTTBLgp      = (1),
};
typedef struct {
    uint32_t DEBUGEVT; 
    uint32_t FORCED; 
    uint32_t VECTTBL; 
} SCB_HFSR;
/**/


/**/
enum SCB_ICSR_bm {
    NMIPENDSET  = (1 << 31),
    PENDSVSET   = (1 << 28),
    PENDSVCLR   = (1 << 27),
    PENDSTSET   = (1 << 26),
    PENDSTCLR   = (1 << 25),
    ISRPENDING  = (1 << 22),
    VECTPENDING = (0x3F << 11),
    RETTOBASE   = (1 << 1),
    VECTACTIVE  = (0xFF << 0),
    NMIPENDSETgp  = (31),
    PENDSVSETgp   = (28),
    PENDSVCLRgp   = (27),
    PENDSTSETgp   = (26),
    PENDSTCLRgp   = (25),
    ISRPENDINGgp  = (22),
    VECTPENDINGgp = (12),
    RETTOBASEgp   = (1),
    VECTACTIVEgp  = (0)
};
typedef struct {
    uint32_t NMIPENDSET;
    uint32_t PENDSVSET;
    uint32_t PENDSVCLR;
    uint32_t PENDSTSET;
    uint32_t PENDSTCLR;
    uint32_t ISRPENDING;
    uint32_t VECTPENDING;
    uint32_t RETTOBASE;
    uint32_t VECTACTIVE;
} SCB_ICSR;
/**/
#endif


/*End of file*/

