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
            VL_FATAL_MT("soc.v", 1, "",
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
            VL_FATAL_MT("soc.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VSOC::_combo__TOP__2(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_combo__TOP__2\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid = 
        (((IData)(vlTOPp->pcpi_valid) & (0x33U == (0x7fU 
                                                   & vlTOPp->pcpi_insn))) 
         & (1U == (0x7fU & (vlTOPp->pcpi_insn >> 0x19U))));
}

VL_INLINE_OPT void VSOC::_sequent__TOP__4(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__4\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__SOC__DOT__MULT__DOT__active;
    // Body
    __Vdly__SOC__DOT__MULT__DOT__active = vlTOPp->SOC__DOT__MULT__DOT__active;
    vlTOPp->SOC__DOT__MULT__DOT__shift_out = ((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulh) 
                                              | ((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulhsu) 
                                                 | (IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulhu)));
    vlTOPp->SOC__DOT__MULT__DOT__rd = VL_MULS_QQQ(64,64,64, 
                                                  VL_EXTENDS_QQ(64,33, vlTOPp->SOC__DOT__MULT__DOT__rs1), 
                                                  VL_EXTENDS_QQ(64,33, vlTOPp->SOC__DOT__MULT__DOT__rs2));
    vlTOPp->pcpi_rd = (IData)(((IData)(vlTOPp->SOC__DOT__MULT__DOT__shift_out)
                                ? (vlTOPp->SOC__DOT__MULT__DOT__rd 
                                   >> 0x20U) : vlTOPp->SOC__DOT__MULT__DOT__rd));
    if ((((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mul) 
          | ((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulh) 
             | ((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulhsu) 
                | (IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulhu)))) 
         & (~ (IData)((0U != (3U & (IData)(vlTOPp->SOC__DOT__MULT__DOT__active))))))) {
        vlTOPp->SOC__DOT__MULT__DOT__rs1 = (0x1ffffffffULL 
                                            & (((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulh) 
                                                | (IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulhsu))
                                                ? VL_EXTENDS_QI(33,32, vlTOPp->pcpi_rs1)
                                                : (QData)((IData)(vlTOPp->pcpi_rs1))));
        vlTOPp->SOC__DOT__MULT__DOT__rs2 = (0x1ffffffffULL 
                                            & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__instr_mulh)
                                                ? VL_EXTENDS_QI(33,32, vlTOPp->pcpi_rs2)
                                                : (QData)((IData)(vlTOPp->pcpi_rs2))));
        __Vdly__SOC__DOT__MULT__DOT__active = (1U | (IData)(__Vdly__SOC__DOT__MULT__DOT__active));
    } else {
        __Vdly__SOC__DOT__MULT__DOT__active = (0xeU 
                                               & (IData)(__Vdly__SOC__DOT__MULT__DOT__active));
    }
    __Vdly__SOC__DOT__MULT__DOT__active = ((1U & (IData)(__Vdly__SOC__DOT__MULT__DOT__active)) 
                                           | (0xeU 
                                              & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__active) 
                                                 << 1U)));
    if ((1U & (~ (IData)(vlTOPp->RESETN)))) {
        __Vdly__SOC__DOT__MULT__DOT__active = 0U;
    }
    vlTOPp->SOC__DOT__MULT__DOT__active = __Vdly__SOC__DOT__MULT__DOT__active;
    vlTOPp->pcpi_wr = (1U & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__active) 
                             >> 1U));
    vlTOPp->pcpi_ready = (1U & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__active) 
                                >> 1U));
}

VL_INLINE_OPT void VSOC::_combo__TOP__5(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_combo__TOP__5\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__MULT__DOT__instr_mul = 0U;
    if (((IData)(vlTOPp->RESETN) & (IData)(vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid))) {
        if ((0U == (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
            vlTOPp->SOC__DOT__MULT__DOT__instr_mul = 1U;
        }
    }
    vlTOPp->SOC__DOT__MULT__DOT__instr_mulh = 0U;
    if (((IData)(vlTOPp->RESETN) & (IData)(vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
            if ((1U == (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
                vlTOPp->SOC__DOT__MULT__DOT__instr_mulh = 1U;
            }
        }
    }
    vlTOPp->SOC__DOT__MULT__DOT__instr_mulhsu = 0U;
    if (((IData)(vlTOPp->RESETN) & (IData)(vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
            if ((1U != (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
                if ((2U == (7U & (vlTOPp->pcpi_insn 
                                  >> 0xcU)))) {
                    vlTOPp->SOC__DOT__MULT__DOT__instr_mulhsu = 1U;
                }
            }
        }
    }
    vlTOPp->SOC__DOT__MULT__DOT__instr_mulhu = 0U;
    if (((IData)(vlTOPp->RESETN) & (IData)(vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
            if ((1U != (7U & (vlTOPp->pcpi_insn >> 0xcU)))) {
                if ((2U != (7U & (vlTOPp->pcpi_insn 
                                  >> 0xcU)))) {
                    if ((3U == (7U & (vlTOPp->pcpi_insn 
                                      >> 0xcU)))) {
                        vlTOPp->SOC__DOT__MULT__DOT__instr_mulhu = 1U;
                    }
                }
            }
        }
    }
}

void VSOC::_eval(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
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
    if (VL_UNLIKELY((RESETN & 0xfeU))) {
        Verilated::overWidthError("RESETN");}
    if (VL_UNLIKELY((pcpi_valid & 0xfeU))) {
        Verilated::overWidthError("pcpi_valid");}
}
#endif  // VL_DEBUG
