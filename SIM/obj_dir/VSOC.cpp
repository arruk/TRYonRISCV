// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========

void VSOC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSOC::eval\n"); );
    VSOC__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("core8.v", 392, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VSOC::_eval_initial_loop(VSOC__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("core8.v", 392, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VSOC::_sequent__TOP__1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*5:0*/ __Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__Vfuncout;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__82__Vfuncout;
    CData/*1:0*/ __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__Vfuncout;
    CData/*1:0*/ __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__97__Vfuncout;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__98__Vfuncout;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__99__Vfuncout;
    CData/*4:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0;
    CData/*2:0*/ __Vdly__SOC__DOT__CPU__DOT__BH;
    CData/*5:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__BHT__v0;
    CData/*1:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__BHT__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__BHT__v0;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v0;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v1;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v1;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v2;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v2;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v3;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v3;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v0;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v1;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v2;
    SData/*13:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v3;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__PC;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__82__I;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__97__I;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__98__I;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__99__I;
    IData/*31:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
    QData/*63:0*/ __Vdly__SOC__DOT__CPU__DOT__cycle;
    // Body
    __Vdly__SOC__DOT__CPU__DOT__cycle = vlTOPp->SOC__DOT__CPU__DOT__cycle;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0 = 0U;
    __Vdly__SOC__DOT__CPU__DOT__BH = vlTOPp->SOC__DOT__CPU__DOT__BH;
    __Vdlyvset__SOC__DOT__CPU__DOT__BHT__v0 = 0U;
    if (VL_UNLIKELY(vlTOPp->SOC__DOT__CPU__DOT__halt)) {
        VL_WRITEF("Simulated processor's report\n----------------------------\n");
        VL_WRITEF("Branch hits= %3.3f%%\n",64,((100.0 
                                                * VL_ITOR_D_I(vlTOPp->SOC__DOT__CPU__DOT__nbPredictHit)) 
                                               / VL_ITOR_D_I(vlTOPp->SOC__DOT__CPU__DOT__nbBranch)));
        VL_WRITEF("Numbers of = (Cycles: %20#, Instret: %20#)\n",
                  64,vlTOPp->SOC__DOT__CPU__DOT__cycle,
                  64,vlTOPp->SOC__DOT__CPU__DOT__instret);
        VL_WRITEF("Instr. mix = (Branch:%3.3f%% JAL:%3.3f%% JALR:%3.3f%%)\n",
                  64,((100.0 * VL_ITOR_D_I(vlTOPp->SOC__DOT__CPU__DOT__nbBranch)) 
                      / VL_ITOR_D_I((IData)(vlTOPp->SOC__DOT__CPU__DOT__instret))),
                  64,((100.0 * VL_ITOR_D_I(vlTOPp->SOC__DOT__CPU__DOT__nbJAL)) 
                      / VL_ITOR_D_I((IData)(vlTOPp->SOC__DOT__CPU__DOT__instret))),
                  64,((100.0 * VL_ITOR_D_I(vlTOPp->SOC__DOT__CPU__DOT__nbJALR)) 
                      / VL_ITOR_D_I((IData)(vlTOPp->SOC__DOT__CPU__DOT__instret))));
        VL_WRITEF("Numbers of = (Branch: %11d, JAL: %11d, JALR: %11d)\n",
                  32,vlTOPp->SOC__DOT__CPU__DOT__nbBranch,
                  32,vlTOPp->SOC__DOT__CPU__DOT__nbJAL,
                  32,vlTOPp->SOC__DOT__CPU__DOT__nbJALR);
        VL_WRITEF("Size of BHT =           6\nSize of BPH =           3\n");
        VL_FINISH_MT("core8.v", 380, "");
    }
    if (VL_UNLIKELY(((IData)(vlTOPp->SOC__DOT__IO_mem_wr) 
                     & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                        >> 3U)))) {
        VL_WRITEF("%c",8,(0xffU & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
        if (0x80000001U) { VL_FFLUSH_I(0x80000001U); }
    }
    vlTOPp->SOC__DOT__CPU__DOT__em_JoB_now = vlTOPp->SOC__DOT__CPU__DOT__e_JoB;
    __Vdly__SOC__DOT__CPU__DOT__cycle = ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))
                                          ? (1ULL + vlTOPp->SOC__DOT__CPU__DOT__cycle)
                                          : 0ULL);
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__PC = ((IData)(4U) 
                                          + vlTOPp->SOC__DOT__CPU__DOT__f_PC);
    }
    if ((1U & (~ (IData)((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt)))))) {
        vlTOPp->SOC__DOT__CPU__DOT__PC = 0U;
    }
    if ((1U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v0 = (0xffU 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA);
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v0 = 0U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v0 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                        >> 2U));
    }
    if ((2U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v1 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 8U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v1 = 8U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v1 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                        >> 2U));
    }
    if ((4U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v2 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 0x10U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v2 = 0x10U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v2 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                        >> 2U));
    }
    if ((8U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v3 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 0x18U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v3 = 0x18U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v3 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                        >> 2U));
    }
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_PC = vlTOPp->SOC__DOT__CPU__DOT__fd_PC;
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_IO_RES = vlTOPp->SOC__DOT__IO_mem_rdata;
    vlTOPp->SOC__DOT__CPU__DOT__mw_RES = vlTOPp->SOC__DOT__CPU__DOT__em_RES;
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_enable) {
        __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0 
            = vlTOPp->SOC__DOT__CPU__DOT__wb_DATA;
        __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0 = 1U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0 
            = vlTOPp->SOC__DOT__CPU__DOT__wb_rdID;
    }
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))) {
        __Vfunc_SOC__DOT__CPU__DOT__isJAL__98__I = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
        __Vfunc_SOC__DOT__CPU__DOT__isJAL__98__Vfuncout 
            = (0x6fU == (0x7fU & __Vfunc_SOC__DOT__CPU__DOT__isJAL__98__I));
        if (__Vfunc_SOC__DOT__CPU__DOT__isJAL__98__Vfuncout) {
            vlTOPp->SOC__DOT__CPU__DOT__nbJAL = ((IData)(1U) 
                                                 + vlTOPp->SOC__DOT__CPU__DOT__nbJAL);
        }
    }
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))) {
        __Vfunc_SOC__DOT__CPU__DOT__isJALR__99__I = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
        __Vfunc_SOC__DOT__CPU__DOT__isJALR__99__Vfuncout 
            = (0x67U == (0x7fU & __Vfunc_SOC__DOT__CPU__DOT__isJALR__99__I));
        if (__Vfunc_SOC__DOT__CPU__DOT__isJALR__99__Vfuncout) {
            vlTOPp->SOC__DOT__CPU__DOT__nbJALR = ((IData)(1U) 
                                                  + vlTOPp->SOC__DOT__CPU__DOT__nbJALR);
        }
    }
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))) {
        __Vfunc_SOC__DOT__CPU__DOT__isBtype__97__I 
            = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
        __Vfunc_SOC__DOT__CPU__DOT__isBtype__97__Vfuncout 
            = (0x63U == (0x7fU & __Vfunc_SOC__DOT__CPU__DOT__isBtype__97__I));
        if (__Vfunc_SOC__DOT__CPU__DOT__isBtype__97__Vfuncout) {
            vlTOPp->SOC__DOT__CPU__DOT__nbBranch = 
                ((IData)(1U) + vlTOPp->SOC__DOT__CPU__DOT__nbBranch);
            if (((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_takeB) 
                 == (IData)(vlTOPp->SOC__DOT__CPU__DOT__de_predict))) {
                vlTOPp->SOC__DOT__CPU__DOT__nbPredictHit 
                    = ((IData)(1U) + vlTOPp->SOC__DOT__CPU__DOT__nbPredictHit);
            }
        }
    }
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__82__I = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__82__Vfuncout 
        = (0x63U == (0x7fU & __Vfunc_SOC__DOT__CPU__DOT__isBtype__82__I));
    if (__Vfunc_SOC__DOT__CPU__DOT__isBtype__82__Vfuncout) {
        __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir 
            = vlTOPp->SOC__DOT__CPU__DOT__e_takeB;
        __Vdly__SOC__DOT__CPU__DOT__BH = (((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_takeB) 
                                           << 2U) | 
                                          (3U & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__BH) 
                                                 >> 1U)));
        __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev 
            = vlTOPp->SOC__DOT__CPU__DOT__BHT[vlTOPp->SOC__DOT__CPU__DOT__de_BHTindex];
        __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__Vfuncout 
            = ((0U == (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                        << 2U) | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                ? 0U : ((1U == (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                                 << 2U) | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                         ? 0U : ((2U == (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                                          << 2U) | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                                  ? 1U : ((3U == (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                                                   << 2U) 
                                                  | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                                           ? 2U : (
                                                   (4U 
                                                    == 
                                                    (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                                                      << 2U) 
                                                     | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                                                    ? 1U
                                                    : 
                                                   ((5U 
                                                     == 
                                                     (((IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__dir) 
                                                       << 2U) 
                                                      | (IData)(__Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__prev)))
                                                     ? 2U
                                                     : 3U))))));
        __Vdlyvval__SOC__DOT__CPU__DOT__BHT__v0 = __Vfunc_SOC__DOT__CPU__DOT__incdec_sat__83__Vfuncout;
        __Vdlyvset__SOC__DOT__CPU__DOT__BHT__v0 = 1U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__BHT__v0 = vlTOPp->SOC__DOT__CPU__DOT__de_BHTindex;
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES = ((0x8000000U 
                                               & vlTOPp->SOC__DOT__CPU__DOT__em_IR)
                                               ? ((0x200000U 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_IR)
                                                   ? (IData)(
                                                             (vlTOPp->SOC__DOT__CPU__DOT__instret 
                                                              >> 0x20U))
                                                   : (IData)(
                                                             (vlTOPp->SOC__DOT__CPU__DOT__cycle 
                                                              >> 0x20U)))
                                               : ((0x200000U 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_IR)
                                                   ? (IData)(vlTOPp->SOC__DOT__CPU__DOT__instret)
                                                   : (IData)(vlTOPp->SOC__DOT__CPU__DOT__cycle)));
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))) {
        if ((0x33U != vlTOPp->SOC__DOT__CPU__DOT__mw_IR)) {
            vlTOPp->SOC__DOT__CPU__DOT__instret = (1ULL 
                                                   + vlTOPp->SOC__DOT__CPU__DOT__instret);
        }
    } else {
        vlTOPp->SOC__DOT__CPU__DOT__instret = 0ULL;
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata = vlTOPp->SOC__DOT__CPU__DOT__RAM
        [(0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                     >> 2U))];
    vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR = vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR;
    if (__Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0) {
        vlTOPp->SOC__DOT__CPU__DOT__reg_file[__Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0] 
            = __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
    }
    if (__Vdlyvset__SOC__DOT__CPU__DOT__BHT__v0) {
        vlTOPp->SOC__DOT__CPU__DOT__BHT[__Vdlyvdim0__SOC__DOT__CPU__DOT__BHT__v0] 
            = __Vdlyvval__SOC__DOT__CPU__DOT__BHT__v0;
    }
    vlTOPp->SOC__DOT__CPU__DOT__cycle = __Vdly__SOC__DOT__CPU__DOT__cycle;
    if (__Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0) {
        vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v0))) 
                & vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v0]) 
               | ((IData)(__Vdlyvval__SOC__DOT__CPU__DOT__RAM__v0) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v0)));
    }
    if (__Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1) {
        vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v1))) 
                & vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v1]) 
               | ((IData)(__Vdlyvval__SOC__DOT__CPU__DOT__RAM__v1) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v1)));
    }
    if (__Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2) {
        vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v2))) 
                & vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v2]) 
               | ((IData)(__Vdlyvval__SOC__DOT__CPU__DOT__RAM__v2) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v2)));
    }
    if (__Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3) {
        vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v3))) 
                & vlTOPp->SOC__DOT__CPU__DOT__RAM[__Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v3]) 
               | ((IData)(__Vdlyvval__SOC__DOT__CPU__DOT__RAM__v3) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v3)));
    }
    vlTOPp->SOC__DOT__CPU__DOT__em_rs2 = vlTOPp->SOC__DOT__CPU__DOT__e_rs2;
    vlTOPp->SOC__DOT__CPU__DOT__em_RES = vlTOPp->SOC__DOT__CPU__DOT__e_RES;
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_predict = vlTOPp->SOC__DOT__CPU__DOT__d_predict;
    }
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        __Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__PC 
            = vlTOPp->SOC__DOT__CPU__DOT__fd_PC;
        __Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__Vfuncout 
            = (0x3fU & ((__Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__PC 
                         >> 2U) ^ ((IData)(vlTOPp->SOC__DOT__CPU__DOT__BH) 
                                   << 3U)));
        vlTOPp->SOC__DOT__CPU__DOT__de_BHTindex = __Vfunc_SOC__DOT__CPU__DOT__BHT_index__25__Vfuncout;
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_IR = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR = vlTOPp->SOC__DOT__CPU__DOT__e_ADDR;
    vlTOPp->SOC__DOT__CPU__DOT__w_loadH = (0xffffU 
                                           & ((2U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                               ? (vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata 
                                                  >> 0x10U)
                                               : vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata));
    vlTOPp->SOC__DOT__CPU__DOT__BH = __Vdly__SOC__DOT__CPU__DOT__BH;
    vlTOPp->SOC__DOT__CPU__DOT__w_loadB = (0xffU & 
                                           ((1U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                             ? ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                >> 8U)
                                             : (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH)));
    vlTOPp->LEDS = (0x3fU & vlTOPp->SOC__DOT__CPU__DOT__em_rs2);
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffff00U 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xffU 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__fd_PC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
    }
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__96__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__96__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__96__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__95__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__95__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__95__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__95__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__96__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__wb_rdID = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__94__Vfuncout;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__91__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__91__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__91__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__90__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__90__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__90__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__90__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__91__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__93__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__93__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__93__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__93__Vfuncout))));
    vlTOPp->SOC__DOT__CPU__DOT__wb_enable = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__Vfuncout) 
                                             & (0U 
                                                != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__89__Vfuncout)));
    vlTOPp->SOC__DOT__CPU__DOT__em_IR = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffff00ffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff00U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 8U)) 
                                                      << 8U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xff00ffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff0000U 
                                                   & (((2U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 0x10U)) 
                                                      << 0x10U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff000000U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       ((2U 
                                                         & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                         ? 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                         >> 8U)
                                                         : 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                         >> 0x18U))) 
                                                      << 0x18U)));
    vlTOPp->SOC__DOT__CPU__DOT__w_load_sign = (1U & 
                                               ((~ 
                                                 (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                  >> 0xeU)) 
                                                & ((0U 
                                                    == 
                                                    (3U 
                                                     & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                        >> 0xcU)))
                                                    ? 
                                                   ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadB) 
                                                    >> 7U)
                                                    : 
                                                   ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                    >> 0xfU))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__Vfuncout 
        = ((0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__I)) 
           & (2U == (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__I 
                           >> 0xcU))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__86__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__86__Vfuncout 
        = (3U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__86__I));
    vlTOPp->SOC__DOT__CPU__DOT__wb_DATA = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__86__Vfuncout)
                                            ? ((0x400000U 
                                                & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                                ? vlTOPp->SOC__DOT__CPU__DOT__mw_IO_RES
                                                : (
                                                   (0U 
                                                    == 
                                                    (3U 
                                                     & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                        >> 0xcU)))
                                                    ? 
                                                   ((0xffffff00U 
                                                     & ((- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_load_sign))) 
                                                        << 8U)) 
                                                    | (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadB))
                                                    : 
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                         >> 0xcU)))
                                                     ? 
                                                    ((0xffff0000U 
                                                      & ((- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_load_sign))) 
                                                         << 0x10U)) 
                                                     | (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH))
                                                     : vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata)))
                                            : ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__Vfuncout)
                                                ? vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES
                                                : vlTOPp->SOC__DOT__CPU__DOT__mw_RES));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__PC 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_PC;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__Vfuncout 
        = (0x3fU & ((vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__PC 
                     >> 2U) ^ ((IData)(vlTOPp->SOC__DOT__CPU__DOT__BH) 
                               << 3U)));
    vlTOPp->SOC__DOT__CPU__DOT__d_predict = (1U & (
                                                   vlTOPp->SOC__DOT__CPU__DOT__BHT
                                                   [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__Vfuncout] 
                                                   >> 1U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__84__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__84__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__84__I));
    vlTOPp->SOC__DOT__IO_mem_wr = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__84__Vfuncout) 
                                   & (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                                      >> 0x16U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__85__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__85__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__85__I));
    vlTOPp->SOC__DOT__CPU__DOT__m_WMASK = ((- (IData)(
                                                      ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__85__Vfuncout) 
                                                       & (~ 
                                                          (vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR 
                                                           >> 0x16U))))) 
                                           & ((0U == 
                                               (3U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                   >> 0xcU)))
                                               ? ((2U 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                   ? 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                    ? 8U
                                                    : 4U)
                                                   : 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                    ? 2U
                                                    : 1U))
                                               : ((1U 
                                                   == 
                                                   (3U 
                                                    & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                       >> 0xcU)))
                                                   ? 
                                                  ((2U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR)
                                                    ? 0xcU
                                                    : 3U)
                                                   : 0xfU)));
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_IR = (((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_flush) 
                                              | (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP))
                                              ? 0x33U
                                              : vlTOPp->SOC__DOT__CPU__DOT__fd_IR);
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__e_flush) {
        vlTOPp->SOC__DOT__CPU__DOT__de_IR = 0x33U;
    }
    vlTOPp->SOC__DOT__CPU__DOT__fd_NOP = (1U & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_JoB) 
                                                | (~ (IData)(
                                                             (0xffffU 
                                                              == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt))))));
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__fd_IR = vlTOPp->SOC__DOT__CPU__DOT__ROM
            [(0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__f_PC 
                         >> 2U))];
    }
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result = 
        (((0x6fU == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
          | (0x17U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
          ? 0U : (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                        >> 0xcU)));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus = ((
                                                   (0x33U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                   & ((vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                       >> 0x1eU) 
                                                      | ((~ 
                                                          (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                           >> 0xeU)) 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                            >> 0xdU)))) 
                                                  | (0x63U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__I 
                    >> 0x14U));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs2 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__Vfuncout];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__53__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__53__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__53__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__52__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__52__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__52__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__52__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__53__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__54__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__54__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__54__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__54__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__57__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__57__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__57__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__56__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__56__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__56__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__56__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__57__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs2 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__50__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__62__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__62__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__62__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__62__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__65__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__65__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__65__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__65__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__67__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__67__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__67__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__66__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__66__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__66__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__66__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__67__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs2 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__60__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__Vfuncout)));
    vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype = ((
                                                   (0x67U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                   | (3U 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
                                                  | (0x13U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype = ((0x37U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                  | (0x17U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__I 
                    >> 0xfU));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs1 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__Vfuncout];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__32__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__32__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__32__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__32__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__35__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__35__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__35__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__34__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__34__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__34__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__34__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__35__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs1 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__30__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__43__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__43__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__43__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__42__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__42__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__42__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__42__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__43__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__45__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__45__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__45__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__44__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__44__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__44__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__44__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__45__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__47__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__47__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__47__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__46__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__46__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__46__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__46__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__47__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs1 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__40__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__Vfuncout)));
    vlTOPp->SOC__DOT__CPU__DOT__e_rs2 = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs2)
                                          ? vlTOPp->SOC__DOT__CPU__DOT__em_RES
                                          : ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs2)
                                              ? vlTOPp->SOC__DOT__CPU__DOT__wb_DATA
                                              : vlTOPp->SOC__DOT__CPU__DOT__de_rs2));
    vlTOPp->SOC__DOT__CPU__DOT__e_IMM = ((0x80000000U 
                                          & vlTOPp->SOC__DOT__CPU__DOT__de_IR) 
                                         | ((0x7ff00000U 
                                             & (((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype)
                                                  ? 
                                                 (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                  >> 0x14U)
                                                  : 
                                                 (- (IData)(
                                                            (1U 
                                                             & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                >> 0x1fU))))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype) 
                                                     | (0x6fU 
                                                        == 
                                                        (0x7fU 
                                                         & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                     ? 
                                                    (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                     >> 0xcU)
                                                     : 
                                                    (- (IData)(
                                                               (1U 
                                                                & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                   >> 0x1fU))))) 
                                                   << 0xcU)) 
                                               | ((0x800U 
                                                   & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype) 
                                                        | (0x23U 
                                                           == 
                                                           (0x7fU 
                                                            & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                        ? 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                        >> 0x1fU)
                                                        : 
                                                       ((0x63U 
                                                         == 
                                                         (0x7fU 
                                                          & vlTOPp->SOC__DOT__CPU__DOT__de_IR))
                                                         ? 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                         >> 7U)
                                                         : 
                                                        ((0x6fU 
                                                          == 
                                                          (0x7fU 
                                                           & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                            >> 0x14U)))) 
                                                      << 0xbU)) 
                                                  | ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype)
                                                        ? 0U
                                                        : 
                                                       (0x3fU 
                                                        & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                           >> 0x19U))) 
                                                      << 5U) 
                                                     | ((0x1eU 
                                                         & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype) 
                                                              | (0x6fU 
                                                                 == 
                                                                 (0x7fU 
                                                                  & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                              ? 
                                                             (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                              >> 0x15U)
                                                              : 
                                                             (((0x23U 
                                                                == 
                                                                (0x7fU 
                                                                 & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                               | (0x63U 
                                                                  == 
                                                                  (0x7fU 
                                                                   & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                               ? 
                                                              (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                               >> 8U)
                                                               : 0U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype)
                                                               ? 
                                                              (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                               >> 0x14U)
                                                               : 
                                                              ((0x23U 
                                                                == 
                                                                (0x7fU 
                                                                 & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                  >> 7U))))))))));
    vlTOPp->SOC__DOT__CPU__DOT__e_rs1 = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs1)
                                          ? vlTOPp->SOC__DOT__CPU__DOT__em_RES
                                          : ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs1)
                                              ? vlTOPp->SOC__DOT__CPU__DOT__wb_DATA
                                              : vlTOPp->SOC__DOT__CPU__DOT__de_rs1));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__21__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__21__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__21__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__20__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__20__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__20__I));
    vlTOPp->SOC__DOT__CPU__DOT__d_JoB_now = ((~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP)) 
                                             & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__20__Vfuncout) 
                                                | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__21__Vfuncout) 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_predict))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__Vfuncout 
        = ((0xfffff000U & ((- (IData)((1U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I 
                                             >> 0x1fU)))) 
                           << 0xcU)) | ((0x800U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I 
                                                   << 4U)) 
                                        | ((0x7e0U 
                                            & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I 
                                               >> 0x14U)) 
                                           | (0x1eU 
                                              & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I 
                                                 >> 7U)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__Vfuncout 
        = ((0xfff00000U & ((- (IData)((1U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I 
                                             >> 0x1fU)))) 
                           << 0x14U)) | ((0xff000U 
                                          & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I) 
                                         | ((0x800U 
                                             & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I 
                                                >> 9U)) 
                                            | (0x7feU 
                                               & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I 
                                                  >> 0x14U)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__22__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__22__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__22__I));
    vlTOPp->SOC__DOT__CPU__DOT__d_JoB_ADDR = (vlTOPp->SOC__DOT__CPU__DOT__fd_PC 
                                              + ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__22__Vfuncout)
                                                  ? vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__23__Vfuncout
                                                  : vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__24__Vfuncout));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__5__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__5__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__5__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__4__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__4__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__4__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__4__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__5__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__8__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__8__Vfuncout 
        = (0x37U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__8__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__6__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__6__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__6__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__Vfuncout 
        = (1U & (~ (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__6__Vfuncout) 
                     | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__Vfuncout)) 
                    | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__8__Vfuncout))));
    vlTOPp->SOC__DOT__CPU__DOT__rs1_HAZ = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__Vfuncout) 
                                           & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__Vfuncout) 
                                              == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__3__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__16__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__16__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__16__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__14__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__14__Vfuncout 
        = (0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__14__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__14__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout)) 
           | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__16__Vfuncout));
    vlTOPp->SOC__DOT__CPU__DOT__rs2_HAZ = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__Vfuncout) 
                                           & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__Vfuncout) 
                                              == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__11__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__78__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__78__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__78__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDin2 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__78__Vfuncout) 
                                             & (IData)(vlTOPp->SOC__DOT__CPU__DOT__de_predict))
                                             ? 4U : vlTOPp->SOC__DOT__CPU__DOT__e_IMM);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__73__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__73__Vfuncout 
        = (0x13U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__73__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__72__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__72__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__72__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__71__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__71__Vfuncout 
        = (0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__71__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__71__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__72__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__e_rs2
                                             : (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__73__Vfuncout) 
                                                 | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__Vfuncout))
                                                 ? vlTOPp->SOC__DOT__CPU__DOT__e_IMM
                                                 : 4U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__77__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__77__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__77__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__76__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__76__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__76__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDin1 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__76__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__77__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__e_rs1);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__69__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__69__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__69__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__68__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__68__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__68__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 = ((((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__68__Vfuncout) 
                                              | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__69__Vfuncout)) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__e_rs1);
    vlTOPp->SOC__DOT__CPU__DOT__f_PC = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__d_JoB_now)
                                         ? vlTOPp->SOC__DOT__CPU__DOT__d_JoB_ADDR
                                         : ((IData)(vlTOPp->SOC__DOT__CPU__DOT__em_JoB_now)
                                             ? vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR
                                             : vlTOPp->SOC__DOT__CPU__DOT__PC));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__Vfuncout 
        = ((0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__I)) 
           & (2U == (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__I 
                           >> 0xcU))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__17__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__17__Vfuncout 
        = (3U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__17__I));
    vlTOPp->SOC__DOT__CPU__DOT__data_HAZ = (((~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP)) 
                                             & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__17__Vfuncout) 
                                                | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__Vfuncout))) 
                                            & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__rs1_HAZ) 
                                               | (IData)(vlTOPp->SOC__DOT__CPU__DOT__rs2_HAZ)));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES = (vlTOPp->SOC__DOT__CPU__DOT__e_ADDin1 
                                              + vlTOPp->SOC__DOT__CPU__DOT__e_ADDin2);
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__a_flipped 
        = ((0x80000000U & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                           << 0x1fU)) | ((0x40000000U 
                                          & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                             << 0x1dU)) 
                                         | ((0x20000000U 
                                             & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                << 0x1bU)) 
                                            | ((0x10000000U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                   << 0x19U)) 
                                               | ((0x8000000U 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                      << 0x17U)) 
                                                  | ((0x4000000U 
                                                      & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                         << 0x15U)) 
                                                     | ((0x2000000U 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                            << 0x13U)) 
                                                        | ((0x1000000U 
                                                            & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                               << 0x11U)) 
                                                           | ((0x800000U 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                  << 0xfU)) 
                                                              | ((0x400000U 
                                                                  & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                     << 0xdU)) 
                                                                 | ((0x200000U 
                                                                     & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                        << 0xbU)) 
                                                                    | ((0x100000U 
                                                                        & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                           << 9U)) 
                                                                       | ((0x80000U 
                                                                           & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                              << 7U)) 
                                                                          | ((0x40000U 
                                                                              & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 5U)) 
                                                                             | ((0x20000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 3U)) 
                                                                                | ((0x10000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 1U)) 
                                                                                | ((0x8000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 1U)) 
                                                                                | ((0x4000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 3U)) 
                                                                                | ((0x2000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 5U)) 
                                                                                | ((0x1000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 7U)) 
                                                                                | ((0x800U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 9U)) 
                                                                                | ((0x400U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xbU)) 
                                                                                | ((0x200U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xdU)) 
                                                                                | ((0x100U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xfU)) 
                                                                                | ((0x80U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x11U)) 
                                                                                | ((0x40U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x13U)) 
                                                                                | ((0x20U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x15U)) 
                                                                                | ((0x10U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x17U)) 
                                                                                | ((8U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x19U)) 
                                                                                | ((4U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1bU)) 
                                                                                | ((2U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1dU)) 
                                                                                | (1U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1fU)))))))))))))))))))))))))))))))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)) 
                              + (((QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus)) 
                                  << 0x20U) | (QData)((IData)(
                                                              (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 
                                                               ^ 
                                                               (- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus)))))))) 
                             + (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__79__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__79__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__79__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDR = ((0xfffffffeU 
                                           & vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES) 
                                          | (1U & (vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES 
                                                   & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__79__Vfuncout)))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
        = (IData)((0x1ffffffffULL & VL_SHIFTRS_QQI(33,33,5, 
                                                   (((QData)((IData)(
                                                                     (1U 
                                                                      & ((vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                          >> 0x1eU) 
                                                                         & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                            >> 0x1fU))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      ((1U 
                                                                        == 
                                                                        (7U 
                                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                            >> 0xcU)))
                                                                        ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__a_flipped
                                                                        : vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)))), 
                                                   (0x1fU 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT = (1U 
                                                 & ((0x80000000U 
                                                     & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                        ^ vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))
                                                     ? 
                                                    (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                     >> 0x1fU)
                                                     : (IData)(
                                                               (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                                >> 0x20U))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__left_shift 
        = ((0x80000000U & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                           << 0x1fU)) | ((0x40000000U 
                                          & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                             << 0x1dU)) 
                                         | ((0x20000000U 
                                             & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                << 0x1bU)) 
                                            | ((0x10000000U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                   << 0x19U)) 
                                               | ((0x8000000U 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                      << 0x17U)) 
                                                  | ((0x4000000U 
                                                      & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                         << 0x15U)) 
                                                     | ((0x2000000U 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                            << 0x13U)) 
                                                        | ((0x1000000U 
                                                            & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                               << 0x11U)) 
                                                           | ((0x800000U 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                  << 0xfU)) 
                                                              | ((0x400000U 
                                                                  & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                     << 0xdU)) 
                                                                 | ((0x200000U 
                                                                     & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                        << 0xbU)) 
                                                                    | ((0x100000U 
                                                                        & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                           << 9U)) 
                                                                       | ((0x80000U 
                                                                           & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                              << 7U)) 
                                                                          | ((0x40000U 
                                                                              & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 5U)) 
                                                                             | ((0x20000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 3U)) 
                                                                                | ((0x10000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 1U)) 
                                                                                | ((0x8000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 1U)) 
                                                                                | ((0x4000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 3U)) 
                                                                                | ((0x2000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 5U)) 
                                                                                | ((0x1000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 7U)) 
                                                                                | ((0x800U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 9U)) 
                                                                                | ((0x400U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xbU)) 
                                                                                | ((0x200U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xdU)) 
                                                                                | ((0x100U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xfU)) 
                                                                                | ((0x80U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x11U)) 
                                                                                | ((0x40U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x13U)) 
                                                                                | ((0x20U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x15U)) 
                                                                                | ((0x10U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x17U)) 
                                                                                | ((8U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x19U)) 
                                                                                | ((4U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1bU)) 
                                                                                | ((2U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1dU)) 
                                                                                | (1U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1fU)))))))))))))))))))))))))))))))));
    vlTOPp->__Vtableidx1 = ((0x80U & ((~ (IData)((0U 
                                                  != (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result)))) 
                                      << 7U)) | ((0x70U 
                                                  & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                     >> 8U)) 
                                                 | (((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT) 
                                                     << 3U) 
                                                    | ((4U 
                                                        & ((IData)(
                                                                   (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                                    >> 0x20U)) 
                                                           << 2U)) 
                                                       | (3U 
                                                          & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                             >> 0xdU))))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__i_take_b = 
        vlTOPp->__Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b
        [vlTOPp->__Vtableidx1];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__75__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__75__Vfuncout 
        = (0x37U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__75__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_RES = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__75__Vfuncout)
                                          ? vlTOPp->SOC__DOT__CPU__DOT__e_IMM
                                          : ((4U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                              ? ((2U 
                                                  & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? 
                                                  (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)
                                                   : 
                                                  (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                   | vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift
                                                   : 
                                                  (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                   ^ vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)))
                                              : ((2U 
                                                  & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? 
                                                  (1U 
                                                   & (IData)(
                                                             (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                              >> 0x20U)))
                                                   : (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__left_shift
                                                   : (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result)))));
    vlTOPp->SOC__DOT__CPU__DOT__e_takeB = (1U & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__i_take_b) 
                                                 ^ 
                                                 (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                  >> 0xcU)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__81__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__81__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__81__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__80__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__80__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__80__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_JoB = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__80__Vfuncout) 
                                         | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__81__Vfuncout) 
                                            & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_takeB) 
                                               ^ (IData)(vlTOPp->SOC__DOT__CPU__DOT__de_predict))));
    vlTOPp->SOC__DOT__CPU__DOT__e_flush = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_JoB) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ));
}

VL_INLINE_OPT void VSOC::_sequent__TOP__2(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__2\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt 
        = ((IData)(vlTOPp->RESET) ? 0U : (0xffffU & 
                                          ((IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt) 
                                           + (1U & 
                                              (~ (IData)(vlTOPp->SOC__DOT__resetn))))));
    vlTOPp->SOC__DOT__resetn = (0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__Vfuncout 
        = ((0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__I)) 
           & (0U == (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__I 
                           >> 0xcU))));
    vlTOPp->SOC__DOT__CPU__DOT__halt = ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt)) 
                                        & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__Vfuncout));
    vlTOPp->SOC__DOT__CPU__DOT__f_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__halt));
}

void VSOC::_eval(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    if ((((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK))) 
         | ((IData)(vlTOPp->RESET) & (~ (IData)(vlTOPp->__Vclklast__TOP__RESET))))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
    vlTOPp->__Vclklast__TOP__RESET = vlTOPp->RESET;
}

VL_INLINE_OPT QData VSOC::_change_request(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VSOC::_change_request_1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request_1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VSOC::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((CLK & 0xfeU))) {
        Verilated::overWidthError("CLK");}
    if (VL_UNLIKELY((RESET & 0xfeU))) {
        Verilated::overWidthError("RESET");}
}
#endif  // VL_DEBUG
