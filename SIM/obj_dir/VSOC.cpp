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
            VL_FATAL_MT("core4.v", 305, "",
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
            VL_FATAL_MT("core4.v", 305, "",
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
    CData/*4:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0;
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
    IData/*31:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
    QData/*63:0*/ __Vdly__SOC__DOT__CPU__DOT__cycle;
    // Body
    __Vdly__SOC__DOT__CPU__DOT__cycle = vlTOPp->SOC__DOT__CPU__DOT__cycle;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3 = 0U;
    __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0 = 0U;
    if (VL_UNLIKELY(vlTOPp->SOC__DOT__CPU__DOT__halt)) {
        VL_FINISH_MT("core4.v", 299, "");
    }
    if (VL_UNLIKELY(((IData)(vlTOPp->SOC__DOT__IO_mem_wr) 
                     & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 3U)))) {
        VL_WRITEF("%c",8,(0xffU & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
        if (0x80000001U) { VL_FFLUSH_I(0x80000001U); }
    }
    vlTOPp->SOC__DOT__CPU__DOT__em_JoB_ADDR = vlTOPp->SOC__DOT__CPU__DOT__e_ADDR;
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
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_predict = (1U 
                                                  & (vlTOPp->SOC__DOT__CPU__DOT__fd_IR 
                                                     >> 0x1fU));
    }
    if ((1U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v0 = (0xffU 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA);
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v0 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v0 = 0U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v0 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((2U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v1 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 8U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v1 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v1 = 8U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v1 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((4U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v2 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 0x10U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v2 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v2 = 0x10U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v2 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((8U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__CPU__DOT__RAM__v3 = (0xffU 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                                                      >> 0x18U));
        __Vdlyvset__SOC__DOT__CPU__DOT__RAM__v3 = 1U;
        __Vdlyvlsb__SOC__DOT__CPU__DOT__RAM__v3 = 0x18U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__RAM__v3 = 
            (0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_stall)))) {
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
        [(0x3fffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                     >> 2U))];
    vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR = vlTOPp->SOC__DOT__CPU__DOT__em_ADDR;
    if (__Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0) {
        vlTOPp->SOC__DOT__CPU__DOT__reg_file[__Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0] 
            = __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
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
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__fd_PC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
    }
    vlTOPp->SOC__DOT__CPU__DOT__em_RES = vlTOPp->SOC__DOT__CPU__DOT__e_RES;
    vlTOPp->SOC__DOT__CPU__DOT__mw_IR = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->SOC__DOT__CPU__DOT__em_ADDR = vlTOPp->SOC__DOT__CPU__DOT__e_ADDR;
    vlTOPp->SOC__DOT__CPU__DOT__w_loadH = (0xffffU 
                                           & ((2U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                               ? (vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata 
                                                  >> 0x10U)
                                               : vlTOPp->SOC__DOT__CPU__DOT__mw_Mdata));
    vlTOPp->SOC__DOT__CPU__DOT__w_loadB = (0xffU & 
                                           ((1U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                             ? ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                >> 8U)
                                             : (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffff00U 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xffU 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__91__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__91__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__91__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__91__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__92__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__wb_rdID = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__90__Vfuncout;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__87__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__87__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__87__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__86__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__86__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__86__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__86__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__87__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__84__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__89__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__84__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__89__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__89__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__88__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__84__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__88__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__88__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__84__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__88__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__89__Vfuncout))));
    vlTOPp->SOC__DOT__CPU__DOT__wb_enable = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__84__Vfuncout) 
                                             & (0U 
                                                != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__85__Vfuncout)));
    vlTOPp->SOC__DOT__CPU__DOT__em_IR = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffff00ffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff00U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 8U)) 
                                                      << 8U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xff00ffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff0000U 
                                                   & (((2U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 0x10U)) 
                                                      << 0x10U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff000000U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       ((2U 
                                                         & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__83__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__83__Vfuncout 
        = ((0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__83__I)) 
           & (2U == (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__83__I 
                           >> 0xcU))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__82__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__82__Vfuncout 
        = (3U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__82__I));
    vlTOPp->SOC__DOT__CPU__DOT__wb_DATA = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__82__Vfuncout)
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
                                            : ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__83__Vfuncout)
                                                ? vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES
                                                : vlTOPp->SOC__DOT__CPU__DOT__mw_RES));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__80__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__80__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__80__I));
    vlTOPp->SOC__DOT__IO_mem_wr = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__80__Vfuncout) 
                                   & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                                      >> 0x16U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__81__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__81__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__81__I));
    vlTOPp->SOC__DOT__CPU__DOT__m_WMASK = ((- (IData)(
                                                      ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__81__Vfuncout) 
                                                       & (~ 
                                                          (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                                                           >> 0x16U))))) 
                                           & ((0U == 
                                               (3U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                   >> 0xcU)))
                                               ? ((2U 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                   ? 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 8U
                                                    : 4U)
                                                   : 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 2U
                                                    : 1U))
                                               : ((1U 
                                                   == 
                                                   (3U 
                                                    & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                       >> 0xcU)))
                                                   ? 
                                                  ((2U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 0xcU
                                                    : 3U)
                                                   : 0xfU)));
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_stall)))) {
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I 
                    >> 0x14U));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs2 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__49__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__49__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__49__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__51__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__51__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__51__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__50__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__50__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__50__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__50__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__51__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__47__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__53__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__47__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__53__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__53__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__52__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__47__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__52__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__52__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__47__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__52__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__53__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__55__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__55__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__55__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__54__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__54__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__54__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__54__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__55__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs2 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__46__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__47__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__48__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__49__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__59__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__59__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__59__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__61__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__61__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__61__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__60__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__60__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__60__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__60__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__61__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__57__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__63__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__57__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__63__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__63__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__62__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__57__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__62__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__62__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__57__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__62__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__63__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__65__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__65__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__65__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__64__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__64__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__64__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__64__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__65__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs2 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__56__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__57__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__58__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__59__Vfuncout)));
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__24__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__24__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__24__I 
                    >> 0xfU));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs1 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__24__Vfuncout];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__29__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__29__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__29__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__31__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__31__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__31__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__31__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__27__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__33__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__27__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__33__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__33__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__27__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__27__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__33__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__35__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__35__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__35__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__35__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_m_fwd_rs1 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__27__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__28__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__29__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__39__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__39__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__39__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__41__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__41__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__41__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__40__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__40__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__40__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__40__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__41__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__37__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__43__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__37__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__43__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__43__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__42__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__37__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__42__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__42__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__37__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__42__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__43__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__45__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__45__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__45__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__44__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__44__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__44__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__44__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__45__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__e_w_fwd_rs1 = (((0U 
                                                 != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__36__Vfuncout)) 
                                                & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__37__Vfuncout)) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__38__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__39__Vfuncout)));
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__20__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__20__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__20__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__19__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__19__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__19__I));
    vlTOPp->SOC__DOT__CPU__DOT__d_JoB_now = ((~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP)) 
                                             & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__19__Vfuncout) 
                                                | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__20__Vfuncout) 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__fd_IR 
                                                      >> 0x1fU))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__Vfuncout 
        = ((0xfffff000U & ((- (IData)((1U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__I 
                                             >> 0x1fU)))) 
                           << 0xcU)) | ((0x800U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__I 
                                                   << 4U)) 
                                        | ((0x7e0U 
                                            & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__I 
                                               >> 0x14U)) 
                                           | (0x1eU 
                                              & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__I 
                                                 >> 7U)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__Vfuncout 
        = ((0xfff00000U & ((- (IData)((1U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__I 
                                             >> 0x1fU)))) 
                           << 0x14U)) | ((0xff000U 
                                          & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__I) 
                                         | ((0x800U 
                                             & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__I 
                                                >> 9U)) 
                                            | (0x7feU 
                                               & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__I 
                                                  >> 0x14U)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__21__I 
        = vlTOPp->SOC__DOT__CPU__DOT__fd_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__21__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__21__I));
    vlTOPp->SOC__DOT__CPU__DOT__d_JoB_ADDR = (vlTOPp->SOC__DOT__CPU__DOT__fd_PC 
                                              + ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__21__Vfuncout)
                                                  ? vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Jimm__22__Vfuncout
                                                  : vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__Bimm__23__Vfuncout));
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDin2 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout) 
                                             & (IData)(vlTOPp->SOC__DOT__CPU__DOT__de_predict))
                                             ? 4U : vlTOPp->SOC__DOT__CPU__DOT__e_IMM);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__72__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__72__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__72__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__71__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__71__Vfuncout 
        = (0x13U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__71__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__70__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__70__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__70__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__69__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__69__Vfuncout 
        = (0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__69__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__69__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__70__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__e_rs2
                                             : (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__71__Vfuncout) 
                                                 | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__72__Vfuncout))
                                                 ? vlTOPp->SOC__DOT__CPU__DOT__e_IMM
                                                 : 4U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__75__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__75__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__75__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__74__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__74__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__74__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDin1 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__74__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__75__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__e_rs1);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__68__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__68__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__68__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__67__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__67__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__67__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__66__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__66__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__66__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 = ((((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__66__Vfuncout) 
                                              | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__67__Vfuncout)) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__68__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__e_rs1);
    vlTOPp->SOC__DOT__CPU__DOT__f_PC = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__d_JoB_now)
                                         ? vlTOPp->SOC__DOT__CPU__DOT__d_JoB_ADDR
                                         : ((0U != vlTOPp->SOC__DOT__CPU__DOT__em_JoB_now)
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__77__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__77__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__77__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDR = ((0xfffffffeU 
                                           & vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES) 
                                          | (1U & (vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES 
                                                   & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__77__Vfuncout)))));
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__73__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__73__Vfuncout 
        = (0x37U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__73__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_RES = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__73__Vfuncout)
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
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__79__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__79__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__79__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__78__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__78__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__78__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_JoB = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__78__Vfuncout) 
                                         | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__79__Vfuncout) 
                                            & (((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__i_take_b) 
                                                ^ (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                   >> 0xcU)) 
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
    vlTOPp->SOC__DOT__CPU__DOT__d_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
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
