// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========

VL_CTOR_IMP(VSOC) {
    VSOC__Syms* __restrict vlSymsp = __VlSymsp = new VSOC__Syms(this, name());
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VSOC::__Vconfigure(VSOC__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

VSOC::~VSOC() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void VSOC::_initial__TOP__1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_initial__TOP__1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->pcpi_wait = 0U;
}

void VSOC::_settle__TOP__3(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_settle__TOP__3\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__MULT__DOT__pcpi_insn_valid = 
        (((IData)(vlTOPp->pcpi_valid) & (0x33U == (0x7fU 
                                                   & vlTOPp->pcpi_insn))) 
         & (1U == (0x7fU & (vlTOPp->pcpi_insn >> 0x19U))));
    vlTOPp->pcpi_rd = (IData)(((IData)(vlTOPp->SOC__DOT__MULT__DOT__shift_out)
                                ? (vlTOPp->SOC__DOT__MULT__DOT__rd 
                                   >> 0x20U) : vlTOPp->SOC__DOT__MULT__DOT__rd));
    vlTOPp->pcpi_wr = (1U & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__active) 
                             >> 1U));
    vlTOPp->pcpi_ready = (1U & ((IData)(vlTOPp->SOC__DOT__MULT__DOT__active) 
                                >> 1U));
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

void VSOC::_eval_initial(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_initial\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
}

void VSOC::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::final\n"); );
    // Variables
    VSOC__Syms* __restrict vlSymsp = this->__VlSymsp;
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VSOC::_eval_settle(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_settle\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
}

void VSOC::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_ctor_var_reset\n"); );
    // Body
    CLK = VL_RAND_RESET_I(1);
    RESETN = VL_RAND_RESET_I(1);
    pcpi_valid = VL_RAND_RESET_I(1);
    pcpi_insn = VL_RAND_RESET_I(32);
    pcpi_rs1 = VL_RAND_RESET_I(32);
    pcpi_rs2 = VL_RAND_RESET_I(32);
    pcpi_wr = VL_RAND_RESET_I(1);
    pcpi_rd = VL_RAND_RESET_I(32);
    pcpi_wait = VL_RAND_RESET_I(1);
    pcpi_ready = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__instr_mul = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__instr_mulh = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__instr_mulhsu = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__instr_mulhu = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__shift_out = VL_RAND_RESET_I(1);
    SOC__DOT__MULT__DOT__active = VL_RAND_RESET_I(4);
    SOC__DOT__MULT__DOT__rs1 = VL_RAND_RESET_Q(33);
    SOC__DOT__MULT__DOT__rs2 = VL_RAND_RESET_Q(33);
    SOC__DOT__MULT__DOT__rd = VL_RAND_RESET_Q(64);
    SOC__DOT__MULT__DOT__pcpi_insn_valid = VL_RAND_RESET_I(1);
}
