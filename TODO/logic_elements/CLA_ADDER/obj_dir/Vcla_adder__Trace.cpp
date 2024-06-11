// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcla_adder__Syms.h"


void Vcla_adder::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vcla_adder::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgCData(oldp+0,(vlTOPp->cla_adder32b__DOT__P),4);
            tracep->chgCData(oldp+1,(vlTOPp->cla_adder32b__DOT__G),4);
            tracep->chgCData(oldp+2,(vlTOPp->cla_adder32b__DOT__c),4);
            tracep->chgBit(oldp+3,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__p) 
                                          >> 7U))));
            tracep->chgBit(oldp+4,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__g) 
                                          >> 7U))));
            tracep->chgBit(oldp+5,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c) 
                                          >> 8U))));
            tracep->chgCData(oldp+6,(vlTOPp->cla_adder32b__DOT__a0__DOT__and_w),8);
            tracep->chgCData(oldp+7,(vlTOPp->cla_adder32b__DOT__a0__DOT__or_w),8);
            tracep->chgCData(oldp+8,(vlTOPp->cla_adder32b__DOT__a0__DOT__g),8);
            tracep->chgCData(oldp+9,(vlTOPp->cla_adder32b__DOT__a0__DOT__p),8);
            tracep->chgSData(oldp+10,(vlTOPp->cla_adder32b__DOT__a0__DOT__c),9);
            tracep->chgBit(oldp+11,((1U & (IData)(vlTOPp->cla_adder32b__DOT__c))));
            tracep->chgBit(oldp+12,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__p) 
                                           >> 7U))));
            tracep->chgBit(oldp+13,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__g) 
                                           >> 7U))));
            tracep->chgBit(oldp+14,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c) 
                                           >> 8U))));
            tracep->chgCData(oldp+15,(vlTOPp->cla_adder32b__DOT__a1__DOT__and_w),8);
            tracep->chgCData(oldp+16,(vlTOPp->cla_adder32b__DOT__a1__DOT__or_w),8);
            tracep->chgCData(oldp+17,(vlTOPp->cla_adder32b__DOT__a1__DOT__g),8);
            tracep->chgCData(oldp+18,(vlTOPp->cla_adder32b__DOT__a1__DOT__p),8);
            tracep->chgSData(oldp+19,(vlTOPp->cla_adder32b__DOT__a1__DOT__c),9);
            tracep->chgBit(oldp+20,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                           >> 1U))));
            tracep->chgBit(oldp+21,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__p) 
                                           >> 7U))));
            tracep->chgBit(oldp+22,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__g) 
                                           >> 7U))));
            tracep->chgBit(oldp+23,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c) 
                                           >> 8U))));
            tracep->chgCData(oldp+24,(vlTOPp->cla_adder32b__DOT__a2__DOT__and_w),8);
            tracep->chgCData(oldp+25,(vlTOPp->cla_adder32b__DOT__a2__DOT__or_w),8);
            tracep->chgCData(oldp+26,(vlTOPp->cla_adder32b__DOT__a2__DOT__g),8);
            tracep->chgCData(oldp+27,(vlTOPp->cla_adder32b__DOT__a2__DOT__p),8);
            tracep->chgSData(oldp+28,(vlTOPp->cla_adder32b__DOT__a2__DOT__c),9);
            tracep->chgBit(oldp+29,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                           >> 2U))));
            tracep->chgBit(oldp+30,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__p) 
                                           >> 7U))));
            tracep->chgBit(oldp+31,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__g) 
                                           >> 7U))));
            tracep->chgBit(oldp+32,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c) 
                                           >> 8U))));
            tracep->chgCData(oldp+33,(vlTOPp->cla_adder32b__DOT__a3__DOT__and_w),8);
            tracep->chgCData(oldp+34,(vlTOPp->cla_adder32b__DOT__a3__DOT__or_w),8);
            tracep->chgCData(oldp+35,(vlTOPp->cla_adder32b__DOT__a3__DOT__g),8);
            tracep->chgCData(oldp+36,(vlTOPp->cla_adder32b__DOT__a3__DOT__p),8);
            tracep->chgSData(oldp+37,(vlTOPp->cla_adder32b__DOT__a3__DOT__c),9);
        }
        tracep->chgIData(oldp+38,(vlTOPp->a),32);
        tracep->chgIData(oldp+39,(vlTOPp->b),32);
        tracep->chgBit(oldp+40,(vlTOPp->cin));
        tracep->chgIData(oldp+41,(vlTOPp->s),32);
        tracep->chgBit(oldp+42,(vlTOPp->cout));
        tracep->chgCData(oldp+43,((0xffU & vlTOPp->a)),8);
        tracep->chgCData(oldp+44,((0xffU & vlTOPp->b)),8);
        tracep->chgCData(oldp+45,((0xffU & ((vlTOPp->a 
                                             ^ vlTOPp->b) 
                                            ^ (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c)))),8);
        tracep->chgCData(oldp+46,((0xffU & (vlTOPp->a 
                                            ^ vlTOPp->b))),8);
        tracep->chgCData(oldp+47,((0xffU & (vlTOPp->a 
                                            >> 8U))),8);
        tracep->chgCData(oldp+48,((0xffU & (vlTOPp->b 
                                            >> 8U))),8);
        tracep->chgCData(oldp+49,((0xffU & (((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 8U) 
                                            ^ (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c)))),8);
        tracep->chgCData(oldp+50,((0xffU & ((vlTOPp->a 
                                             ^ vlTOPp->b) 
                                            >> 8U))),8);
        tracep->chgCData(oldp+51,((0xffU & (vlTOPp->a 
                                            >> 0x10U))),8);
        tracep->chgCData(oldp+52,((0xffU & (vlTOPp->b 
                                            >> 0x10U))),8);
        tracep->chgCData(oldp+53,((0xffU & (((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 0x10U) 
                                            ^ (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c)))),8);
        tracep->chgCData(oldp+54,((0xffU & ((vlTOPp->a 
                                             ^ vlTOPp->b) 
                                            >> 0x10U))),8);
        tracep->chgCData(oldp+55,((0xffU & (vlTOPp->a 
                                            >> 0x18U))),8);
        tracep->chgCData(oldp+56,((0xffU & (vlTOPp->b 
                                            >> 0x18U))),8);
        tracep->chgCData(oldp+57,((0xffU & (((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 0x18U) 
                                            ^ (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c)))),8);
        tracep->chgCData(oldp+58,((0xffU & ((vlTOPp->a 
                                             ^ vlTOPp->b) 
                                            >> 0x18U))),8);
    }
}

void Vcla_adder::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}
