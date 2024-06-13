// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcla_adder.h for the primary calling header

#include "Vcla_adder.h"
#include "Vcla_adder__Syms.h"

//==========

void Vcla_adder::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcla_adder::eval\n"); );
    Vcla_adder__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("cla_adder.v", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vcla_adder::_eval_initial_loop(Vcla_adder__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
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
            VL_FATAL_MT("cla_adder.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vcla_adder::_combo__TOP__1(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_combo__TOP__1\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->cla_adder32b__DOT__G = ((0xeU & (IData)(vlTOPp->cla_adder32b__DOT__G)) 
                                    | (1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__g) 
                                             >> 7U)));
    vlTOPp->cla_adder32b__DOT__P = ((0xeU & (IData)(vlTOPp->cla_adder32b__DOT__P)) 
                                    | (1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__p) 
                                             >> 7U)));
    vlTOPp->cla_adder32b__DOT__G = ((0xdU & (IData)(vlTOPp->cla_adder32b__DOT__G)) 
                                    | (2U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__g) 
                                             >> 6U)));
    vlTOPp->cla_adder32b__DOT__P = ((0xdU & (IData)(vlTOPp->cla_adder32b__DOT__P)) 
                                    | (2U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__p) 
                                             >> 6U)));
    vlTOPp->cla_adder32b__DOT__G = ((0xbU & (IData)(vlTOPp->cla_adder32b__DOT__G)) 
                                    | (4U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__g) 
                                             >> 5U)));
    vlTOPp->cla_adder32b__DOT__P = ((0xbU & (IData)(vlTOPp->cla_adder32b__DOT__P)) 
                                    | (4U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__p) 
                                             >> 5U)));
    vlTOPp->cla_adder32b__DOT__G = ((7U & (IData)(vlTOPp->cla_adder32b__DOT__G)) 
                                    | (8U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__g) 
                                             >> 4U)));
    vlTOPp->cla_adder32b__DOT__P = ((7U & (IData)(vlTOPp->cla_adder32b__DOT__P)) 
                                    | (8U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__p) 
                                             >> 4U)));
    vlTOPp->cla_adder32b__DOT__c = ((0xeU & (IData)(vlTOPp->cla_adder32b__DOT__c)) 
                                    | (1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c) 
                                             >> 8U)));
    vlTOPp->cla_adder32b__DOT__c = ((0xdU & (IData)(vlTOPp->cla_adder32b__DOT__c)) 
                                    | (2U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c) 
                                             >> 7U)));
    vlTOPp->cla_adder32b__DOT__c = ((0xbU & (IData)(vlTOPp->cla_adder32b__DOT__c)) 
                                    | (4U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c) 
                                             >> 6U)));
    vlTOPp->cla_adder32b__DOT__c = ((7U & (IData)(vlTOPp->cla_adder32b__DOT__c)) 
                                    | (8U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c) 
                                             >> 5U)));
    vlTOPp->cla_adder32b__DOT__a0__DOT__c = ((((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__g) 
                                               | ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__p) 
                                                  & (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c))) 
                                              << 1U) 
                                             | (IData)(vlTOPp->cin));
    vlTOPp->s = ((0xffffff00U & vlTOPp->s) | (0xffU 
                                              & ((vlTOPp->a 
                                                  ^ vlTOPp->b) 
                                                 ^ (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c))));
    vlTOPp->s = ((0xffff00ffU & vlTOPp->s) | (0xff00U 
                                              & ((0xffffff00U 
                                                  & (vlTOPp->a 
                                                     ^ vlTOPp->b)) 
                                                 ^ 
                                                 ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c) 
                                                  << 8U))));
    vlTOPp->s = ((0xff00ffffU & vlTOPp->s) | (0xff0000U 
                                              & ((0xffff0000U 
                                                  & (vlTOPp->a 
                                                     ^ vlTOPp->b)) 
                                                 ^ 
                                                 ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c) 
                                                  << 0x10U))));
    vlTOPp->s = ((0xffffffU & vlTOPp->s) | (0xff000000U 
                                            & ((0xff000000U 
                                                & (vlTOPp->a 
                                                   ^ vlTOPp->b)) 
                                               ^ ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c) 
                                                  << 0x18U))));
    vlTOPp->cla_adder32b__DOT__a0__DOT__and_w = (0xffU 
                                                 & (vlTOPp->a 
                                                    & vlTOPp->b));
    vlTOPp->cla_adder32b__DOT__a1__DOT__and_w = (0xffU 
                                                 & ((vlTOPp->a 
                                                     & vlTOPp->b) 
                                                    >> 8U));
    vlTOPp->cla_adder32b__DOT__a2__DOT__and_w = (0xffU 
                                                 & ((vlTOPp->a 
                                                     & vlTOPp->b) 
                                                    >> 0x10U));
    vlTOPp->cla_adder32b__DOT__a3__DOT__and_w = (0xffU 
                                                 & ((vlTOPp->a 
                                                     & vlTOPp->b) 
                                                    >> 0x18U));
    vlTOPp->cla_adder32b__DOT__a0__DOT__or_w = (0xffU 
                                                & (vlTOPp->a 
                                                   | vlTOPp->b));
    vlTOPp->cla_adder32b__DOT__a1__DOT__or_w = (0xffU 
                                                & ((vlTOPp->a 
                                                    | vlTOPp->b) 
                                                   >> 8U));
    vlTOPp->cla_adder32b__DOT__a2__DOT__or_w = (0xffU 
                                                & ((vlTOPp->a 
                                                    | vlTOPp->b) 
                                                   >> 0x10U));
    vlTOPp->cla_adder32b__DOT__a3__DOT__or_w = (0xffU 
                                                & ((vlTOPp->a 
                                                    | vlTOPp->b) 
                                                   >> 0x18U));
    vlTOPp->cout = (1U & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                          >> 3U));
    vlTOPp->cla_adder32b__DOT__a1__DOT__c = ((((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__g) 
                                               | ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__p) 
                                                  & (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c))) 
                                              << 1U) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__c)));
    vlTOPp->cla_adder32b__DOT__a2__DOT__c = ((((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__g) 
                                               | ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__p) 
                                                  & (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c))) 
                                              << 1U) 
                                             | (1U 
                                                & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                                   >> 1U)));
    vlTOPp->cla_adder32b__DOT__a3__DOT__c = ((((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__g) 
                                               | ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__p) 
                                                  & (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c))) 
                                              << 1U) 
                                             | (1U 
                                                & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                                   >> 2U)));
    vlTOPp->cla_adder32b__DOT__a0__DOT__p = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__or_w) 
                                                 & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__p) 
                                                    << 1U))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__or_w)));
    vlTOPp->cla_adder32b__DOT__a0__DOT__g = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__and_w) 
                                                 | (((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__g) 
                                                     << 1U) 
                                                    & (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__or_w)))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__and_w)));
    vlTOPp->cla_adder32b__DOT__a1__DOT__p = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__or_w) 
                                                 & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__p) 
                                                    << 1U))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__or_w)));
    vlTOPp->cla_adder32b__DOT__a1__DOT__g = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__and_w) 
                                                 | (((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__g) 
                                                     << 1U) 
                                                    & (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__or_w)))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__and_w)));
    vlTOPp->cla_adder32b__DOT__a2__DOT__p = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__or_w) 
                                                 & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__p) 
                                                    << 1U))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__or_w)));
    vlTOPp->cla_adder32b__DOT__a2__DOT__g = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__and_w) 
                                                 | (((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__g) 
                                                     << 1U) 
                                                    & (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__or_w)))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__and_w)));
    vlTOPp->cla_adder32b__DOT__a3__DOT__p = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__or_w) 
                                                 & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__p) 
                                                    << 1U))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__or_w)));
    vlTOPp->cla_adder32b__DOT__a3__DOT__g = ((0xfeU 
                                              & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__and_w) 
                                                 | (((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__g) 
                                                     << 1U) 
                                                    & (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__or_w)))) 
                                             | (1U 
                                                & (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__and_w)));
}

void Vcla_adder::_eval(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_eval\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
}

VL_INLINE_OPT QData Vcla_adder::_change_request(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_change_request\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vcla_adder::_change_request_1(Vcla_adder__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_change_request_1\n"); );
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->cla_adder32b__DOT__a0__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__g)
         | (vlTOPp->cla_adder32b__DOT__a0__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__p)
         | (vlTOPp->cla_adder32b__DOT__a0__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__c)
         | (vlTOPp->cla_adder32b__DOT__a1__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__g)
         | (vlTOPp->cla_adder32b__DOT__a1__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__p)
         | (vlTOPp->cla_adder32b__DOT__a1__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__c)
         | (vlTOPp->cla_adder32b__DOT__a2__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__g)
         | (vlTOPp->cla_adder32b__DOT__a2__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__p)
         | (vlTOPp->cla_adder32b__DOT__a2__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__c)
         | (vlTOPp->cla_adder32b__DOT__a3__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__g)
        || (vlTOPp->cla_adder32b__DOT__a3__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__p)
         | (vlTOPp->cla_adder32b__DOT__a3__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__c));
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a0__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__g))) VL_DBG_MSGF("        CHANGE: cla_adder.v:33: cla_adder32b.a0.g\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a0__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__p))) VL_DBG_MSGF("        CHANGE: cla_adder.v:34: cla_adder32b.a0.p\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a0__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__c))) VL_DBG_MSGF("        CHANGE: cla_adder.v:35: cla_adder32b.a0.c\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a1__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__g))) VL_DBG_MSGF("        CHANGE: cla_adder.v:33: cla_adder32b.a1.g\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a1__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__p))) VL_DBG_MSGF("        CHANGE: cla_adder.v:34: cla_adder32b.a1.p\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a1__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__c))) VL_DBG_MSGF("        CHANGE: cla_adder.v:35: cla_adder32b.a1.c\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a2__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__g))) VL_DBG_MSGF("        CHANGE: cla_adder.v:33: cla_adder32b.a2.g\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a2__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__p))) VL_DBG_MSGF("        CHANGE: cla_adder.v:34: cla_adder32b.a2.p\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a2__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__c))) VL_DBG_MSGF("        CHANGE: cla_adder.v:35: cla_adder32b.a2.c\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a3__DOT__g ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__g))) VL_DBG_MSGF("        CHANGE: cla_adder.v:33: cla_adder32b.a3.g\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a3__DOT__p ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__p))) VL_DBG_MSGF("        CHANGE: cla_adder.v:34: cla_adder32b.a3.p\n"); );
    VL_DEBUG_IF( if(__req && ((vlTOPp->cla_adder32b__DOT__a3__DOT__c ^ vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__c))) VL_DBG_MSGF("        CHANGE: cla_adder.v:35: cla_adder32b.a3.c\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__g 
        = vlTOPp->cla_adder32b__DOT__a0__DOT__g;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__p 
        = vlTOPp->cla_adder32b__DOT__a0__DOT__p;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a0__DOT__c 
        = vlTOPp->cla_adder32b__DOT__a0__DOT__c;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__g 
        = vlTOPp->cla_adder32b__DOT__a1__DOT__g;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__p 
        = vlTOPp->cla_adder32b__DOT__a1__DOT__p;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a1__DOT__c 
        = vlTOPp->cla_adder32b__DOT__a1__DOT__c;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__g 
        = vlTOPp->cla_adder32b__DOT__a2__DOT__g;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__p 
        = vlTOPp->cla_adder32b__DOT__a2__DOT__p;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a2__DOT__c 
        = vlTOPp->cla_adder32b__DOT__a2__DOT__c;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__g 
        = vlTOPp->cla_adder32b__DOT__a3__DOT__g;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__p 
        = vlTOPp->cla_adder32b__DOT__a3__DOT__p;
    vlTOPp->__Vchglast__TOP__cla_adder32b__DOT__a3__DOT__c 
        = vlTOPp->cla_adder32b__DOT__a3__DOT__c;
    return __req;
}

#ifdef VL_DEBUG
void Vcla_adder::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcla_adder::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((cin & 0xfeU))) {
        Verilated::overWidthError("cin");}
}
#endif  // VL_DEBUG
