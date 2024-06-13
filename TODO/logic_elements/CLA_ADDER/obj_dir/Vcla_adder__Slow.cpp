// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcla_adder.h for the primary calling header

#include "Vcla_adder.h"
#include "Vcla_adder__Syms.h"

//==========

VL_CTOR_IMP(Vcla_adder) {
    Vcla_adder__Syms* __restrict vlSymsp = __VlSymsp = new Vcla_adder__Syms(this, name());
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vcla_adder::__Vconfigure(Vcla_adder__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-12);
    Verilated::timeprecision(-12);
}

Vcla_adder::~Vcla_adder() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vcla_adder::_eval_initial(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_eval_initial\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vcla_adder::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::final\n"); );
    // Variables
    Vcla_adder__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vcla_adder::_eval_settle(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_eval_settle\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
    vlTOPp->__Vm_traceActivity[0U] = 1U;
}

void Vcla_adder::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_ctor_var_reset\n"); );
    // Body
    a = VL_RAND_RESET_I(32);
    b = VL_RAND_RESET_I(32);
    cin = VL_RAND_RESET_I(1);
    s = VL_RAND_RESET_I(32);
    cout = VL_RAND_RESET_I(1);
    cla_adder32b__DOT__P = VL_RAND_RESET_I(4);
    cla_adder32b__DOT__G = VL_RAND_RESET_I(4);
    cla_adder32b__DOT__c = VL_RAND_RESET_I(4);
    cla_adder32b__DOT__a0__DOT__and_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a0__DOT__or_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a0__DOT__g = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a0__DOT__p = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a0__DOT__c = VL_RAND_RESET_I(9);
    cla_adder32b__DOT__a1__DOT__and_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a1__DOT__or_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a1__DOT__g = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a1__DOT__p = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a1__DOT__c = VL_RAND_RESET_I(9);
    cla_adder32b__DOT__a2__DOT__and_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a2__DOT__or_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a2__DOT__g = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a2__DOT__p = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a2__DOT__c = VL_RAND_RESET_I(9);
    cla_adder32b__DOT__a3__DOT__and_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a3__DOT__or_w = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a3__DOT__g = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a3__DOT__p = VL_RAND_RESET_I(8);
    cla_adder32b__DOT__a3__DOT__c = VL_RAND_RESET_I(9);
    __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__g = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__p = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__c = VL_RAND_RESET_I(9);
    __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__g = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__p = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__c = VL_RAND_RESET_I(9);
    __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__g = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__p = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__c = VL_RAND_RESET_I(9);
    __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__g = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__p = VL_RAND_RESET_I(8);
    __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__c = VL_RAND_RESET_I(9);
    { int __Vi0=0; for (; __Vi0<2; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
