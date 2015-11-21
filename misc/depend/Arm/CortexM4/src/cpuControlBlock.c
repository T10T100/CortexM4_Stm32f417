
#include "cpuControlBlock.h"
/*                        R/W   Required    Reset
                                privilege   Value       -**-
*/

SCB_AdressSpace ScbAdressSpace = {
    0xE000E008,
    0xE000ED00,
    0xE000ED04,
    0xE000ED08,
    0xE000ED0C,
    0xE000ED10,
    0xE000ED14,
    0xE000ED18,
    0xE000ED1C,
    0xE000ED20,
    0xE000ED24,
    0xE000ED28,
    0xE000ED28,
    0xE000ED29,
    0xE000ED2A,
    0xE000ED2C,
    0xE000ED34,
    0xE000ED38,
    0xE000ED3C  
};


/*CPUID*/
SCB_CPUID readCpuId ()
{
    uint32_t id = *(uint32_t *)ScbAdressSpace.SCB_CPUID;
    SCB_CPUID s = {
        (id & Implementer) >> ImplementerBp,
        (id & Variant)     >> VariantGp,
        (id & Constant)    >> ConstantGp,
        (id & PartNo)      >> PartNoGp,
        (id & Revision)    >> RevisionGp
    };
    return s;
}


bool writeCpuId (SCB_CPUID id)
{
    return false;
}
/*CPUID*/


/*VTOR*/
SCB_VTOR readVtor ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.VTOR;
    SCB_VTOR v = {
        off & TBLOFF,
    };
    return v;
}

bool writeVtor (SCB_VTOR v)
{
    *(uint32_t *)ScbAdressSpace.VTOR = (v.Tbloff & TBLOFF) << TBLOFFgp;
     return true;           
}
/*VTOR*/



/*AIRCR*/
SCB_AIRCR readAirCr ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.AIRCR;
    SCB_AIRCR v = {
        off & VECTKEYSTAT,
        off & ENDIANNESS,
        off & PRIGROUP,
        off & SYSRESETREQ,
        off & VECTCLRACTIVE,
        off & VECTRESET,
    };
    return v;
}

bool writeAirCr (SCB_AIRCR v)
{
    *(uint32_t *)ScbAdressSpace.AIRCR = \
                        ((v.Endianness    & ENDIANNESS)    << ENDIANNESSgp) | \
                        ((v.Prigroup      & PRIGROUP)      << PRIGROUPgp) | \
                        ((v.SysResetReq   & SYSRESETREQ)   << SYSRESETREQgp) | \
                        ((v.VectCtlActive & VECTCLRACTIVE) << VECTCLRACTIVEgp) | \
                        ((v.VectKeyStat)  & VECTKEYSTAT)   << VECTKEYSTATgp | \
                        ((v.VectReset     & VECTRESET)     << VECTRESETgp);
    
    return true;
}
/*AIRCR*/





/*SCR*/
SCB_SCR readScr ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.SCR;
    SCB_SCR v = {
        off & SEVONPEND,
        off & SLEEPDEEP,
        off & SLEEPONEXIT,
    };
    return v;
}
bool writeScr (SCB_SCR v)
{
    *(uint32_t *)ScbAdressSpace.SCR = \
                        ((v.SevonPend      & SEVONPEND)      << SEVONPENDgp) | \
                        ((v.SleepDeep      & SLEEPDEEP)      << SLEEPDEEPgp) | \
                        ((v.SleepOnExit    & SLEEPONEXIT)    << SLEEPONEXITgp);
    
    return true;
}
/*SCR*/




/*CCR*/
SCB_CCR readCcr ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.CCR;
    SCB_CCR v = {
        off & STKALIGN,
        off & BFHFNMIGN,
        off & DIV_0_TRP,
        off & UNALIGN_TRP,
        off & USERSETMPEND,
        off & NONBASETHRDENA,
    };
    return v;
}

bool writeCcr (SCB_CCR v)
{
    *(uint32_t *)ScbAdressSpace.CCR = \
                        ((v.BFHFNMIGN        & BFHFNMIGN)        << BFHFNMIGNgp) | \
                        ((v.DIV_0_TRP        & DIV_0_TRP)        << DIV_0_TRPgp) | \
                        ((v.NONBASETHRDENA   & NONBASETHRDENA)   << NONBASETHRDENAgp) | \
                        ((v.StckAllign       & STKALIGN)         << STKALIGNgp) | \
                        ((v.UNALIGN_TRP      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.USERSETMPEND     & USERSETMPEND)     << USERSETMPENDgp);
    
    return true;
}
/*CCR*/





/*SHPR1*/
SCB_SHPR1 readShpr1 ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.SHPR1;
    SCB_SHPR1 v = {
        off & PRI_6,
        off & PRI_5,
        off & PRI_4,
    };
    return v;
}
bool writeShpr1 (SCB_SHPR1 v)
{
    *(uint32_t *)ScbAdressSpace.SHPR1 = \
                        ((v.PRI_4        & PRI_4)        << PRI_4gp) | \
                        ((v.PRI_5        & PRI_5)        <<PRI_5gp)  | \
                        ((v.PRI_6        & PRI_6)        << PRI_6gp);
    
    return true;
}

SCB_SHPR2 readShpr2 ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.SHPR2;
    SCB_SHPR2 v = {
        off & PRI_11,
    };
    return v;
}
bool writeShpr2 (SCB_SHPR2 v)
{
    *(uint32_t *)ScbAdressSpace.SHPR2 = \
                        ((v.PRI_11       & PRI_11)        << PRI_11gp);
    
    return true;
}

SCB_SHPR3 readShpr3 ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.SHPR3;
    SCB_SHPR3 v = {
        off & PRI_15,
        off & PRI_14,
    };
    return v;
}
bool writeShpr3 (SCB_SHPR3 v)
{
    *(uint32_t *)ScbAdressSpace.SHPR3 = \
                        ((v.PRI_14        & PRI_14)        << PRI_14gp) | \
                        ((v.PRI_15        & PRI_15)        <<PRI_15gp);
    
    return true;
}
/*SHPR1*/



/*SHCRS*/
SCB_SHCRS readShcrs ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.SHCRS;
    SCB_SHCRS v = {
        off & USGFAULTENA,
        off & BUSFAULTENA,
        off & MEMFAULTENA,
        off & BUSFAULTPENDED,
        off & MEMFAULTPENDED,
        off & USGFAULTPENDED,
        off & SYSTICKACT,
        off & PENDSVACT,
        off & Reserved,
        off & MONITORACT,
        off & SVCALLACT,
        off & BUSFAULTACT,
        off & MEMFAULTACT,
    };
    return v;

}
bool writeShcrs (SCB_SHCRS v)
{
    *(uint32_t *)ScbAdressSpace.SHCRS = \
                        ((v.BUSFAULTACT        & BFHFNMIGN)        << BFHFNMIGNgp) | \
                        ((v.BUSFAULTENA        & DIV_0_TRP)        << DIV_0_TRPgp) | \
                        ((v.BUSFAULTPENDED   & NONBASETHRDENA)   << NONBASETHRDENAgp) | \
                        ((v.MEMFAULTACT       & STKALIGN)         << STKALIGNgp) | \
                        ((v.MEMFAULTENA      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.MEMFAULTPENDED     & USERSETMPEND)     << USERSETMPENDgp) | \
                        ((v.MONITORACT      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.PENDSVACT      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.SVCALLACT      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.SVCALLPENDED      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.SYSTICKACT      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.USGFAULTENA      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.USGFAULTENA      & UNALIGN_TRP)      << UNALIGN_TRPgp) | \
                        ((v.USGFAULTPENDED      & UNALIGN_TRP)      << UNALIGN_TRPgp);
    
    return true;
}
/*SHCRS*/




/*CFSR*/
SCB_CFSR readCfsr ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.CFSR;
    SCB_CFSR v = {
        off & UFSR,
        off & BFSR,
        off & MMFSR,
    };
    return v;
}
bool writeCfsr (SCB_CFSR v)
{
    *(uint32_t *)ScbAdressSpace.CFSR = \
                        ((v.BFSR         & BFSR)          << BFSRgp) | \
                        ((v.MMFSR        & MMFSR)        << MMFSRgp) | \
                        ((v.UFSR         & UFSR)               << UFSRgp);
    
    return true;
}
/*CFSR*/





/*HFSR*/
SCB_HFSR readHfsr ()
{
    uint32_t off = *(uint32_t *)ScbAdressSpace.HFSR;
    SCB_HFSR v = {
        off & DEBUGEVT,
        off & FORCED,
        off & VECTTBL,
    };
    return v;
}
bool writeHfsr (SCB_HFSR v)
{
    *(uint32_t *)ScbAdressSpace.HFSR = \
                        ((v.DEBUGEVT        & DEBUGEVT)          << DEBUGEVTgp) | \
                        ((v.FORCED          & FORCED)            << FORCEDgp) | \
                        ((v.VECTTBL         & VECTTBL)           << VECTTBLgp);
    
    return true;
}
/*HFSR*/

/*

*/







