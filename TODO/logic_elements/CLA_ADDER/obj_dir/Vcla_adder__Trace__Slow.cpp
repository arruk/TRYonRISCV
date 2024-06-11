// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vcla_adder__Syms.h"


//======================

void Vcla_adder::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vcla_adder::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vcla_adder::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vcla_adder::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vcla_adder::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBus(c+39,"a", false,-1, 31,0);
        tracep->declBus(c+40,"b", false,-1, 31,0);
        tracep->declBit(c+41,"cin", false,-1);
        tracep->declBus(c+42,"s", false,-1, 31,0);
        tracep->declBit(c+43,"cout", false,-1);
        tracep->declBus(c+39,"cla_adder32b a", false,-1, 31,0);
        tracep->declBus(c+40,"cla_adder32b b", false,-1, 31,0);
        tracep->declBit(c+41,"cla_adder32b cin", false,-1);
        tracep->declBus(c+42,"cla_adder32b s", false,-1, 31,0);
        tracep->declBit(c+43,"cla_adder32b cout", false,-1);
        tracep->declBus(c+1,"cla_adder32b P", false,-1, 3,0);
        tracep->declBus(c+2,"cla_adder32b G", false,-1, 3,0);
        tracep->declBus(c+3,"cla_adder32b c", false,-1, 3,0);
        tracep->declBus(c+44,"cla_adder32b a0 a", false,-1, 7,0);
        tracep->declBus(c+45,"cla_adder32b a0 b", false,-1, 7,0);
        tracep->declBit(c+41,"cla_adder32b a0 cin", false,-1);
        tracep->declBit(c+4,"cla_adder32b a0 P", false,-1);
        tracep->declBit(c+5,"cla_adder32b a0 G", false,-1);
        tracep->declBus(c+46,"cla_adder32b a0 s", false,-1, 7,0);
        tracep->declBit(c+6,"cla_adder32b a0 cout", false,-1);
        tracep->declBus(c+47,"cla_adder32b a0 xor_w", false,-1, 7,0);
        tracep->declBus(c+7,"cla_adder32b a0 and_w", false,-1, 7,0);
        tracep->declBus(c+8,"cla_adder32b a0 or_w", false,-1, 7,0);
        tracep->declBus(c+9,"cla_adder32b a0 g", false,-1, 7,0);
        tracep->declBus(c+10,"cla_adder32b a0 p", false,-1, 7,0);
        tracep->declBus(c+11,"cla_adder32b a0 c", false,-1, 8,0);
        tracep->declBus(c+48,"cla_adder32b a1 a", false,-1, 7,0);
        tracep->declBus(c+49,"cla_adder32b a1 b", false,-1, 7,0);
        tracep->declBit(c+12,"cla_adder32b a1 cin", false,-1);
        tracep->declBit(c+13,"cla_adder32b a1 P", false,-1);
        tracep->declBit(c+14,"cla_adder32b a1 G", false,-1);
        tracep->declBus(c+50,"cla_adder32b a1 s", false,-1, 7,0);
        tracep->declBit(c+15,"cla_adder32b a1 cout", false,-1);
        tracep->declBus(c+51,"cla_adder32b a1 xor_w", false,-1, 7,0);
        tracep->declBus(c+16,"cla_adder32b a1 and_w", false,-1, 7,0);
        tracep->declBus(c+17,"cla_adder32b a1 or_w", false,-1, 7,0);
        tracep->declBus(c+18,"cla_adder32b a1 g", false,-1, 7,0);
        tracep->declBus(c+19,"cla_adder32b a1 p", false,-1, 7,0);
        tracep->declBus(c+20,"cla_adder32b a1 c", false,-1, 8,0);
        tracep->declBus(c+52,"cla_adder32b a2 a", false,-1, 7,0);
        tracep->declBus(c+53,"cla_adder32b a2 b", false,-1, 7,0);
        tracep->declBit(c+21,"cla_adder32b a2 cin", false,-1);
        tracep->declBit(c+22,"cla_adder32b a2 P", false,-1);
        tracep->declBit(c+23,"cla_adder32b a2 G", false,-1);
        tracep->declBus(c+54,"cla_adder32b a2 s", false,-1, 7,0);
        tracep->declBit(c+24,"cla_adder32b a2 cout", false,-1);
        tracep->declBus(c+55,"cla_adder32b a2 xor_w", false,-1, 7,0);
        tracep->declBus(c+25,"cla_adder32b a2 and_w", false,-1, 7,0);
        tracep->declBus(c+26,"cla_adder32b a2 or_w", false,-1, 7,0);
        tracep->declBus(c+27,"cla_adder32b a2 g", false,-1, 7,0);
        tracep->declBus(c+28,"cla_adder32b a2 p", false,-1, 7,0);
        tracep->declBus(c+29,"cla_adder32b a2 c", false,-1, 8,0);
        tracep->declBus(c+56,"cla_adder32b a3 a", false,-1, 7,0);
        tracep->declBus(c+57,"cla_adder32b a3 b", false,-1, 7,0);
        tracep->declBit(c+30,"cla_adder32b a3 cin", false,-1);
        tracep->declBit(c+31,"cla_adder32b a3 P", false,-1);
        tracep->declBit(c+32,"cla_adder32b a3 G", false,-1);
        tracep->declBus(c+58,"cla_adder32b a3 s", false,-1, 7,0);
        tracep->declBit(c+33,"cla_adder32b a3 cout", false,-1);
        tracep->declBus(c+59,"cla_adder32b a3 xor_w", false,-1, 7,0);
        tracep->declBus(c+34,"cla_adder32b a3 and_w", false,-1, 7,0);
        tracep->declBus(c+35,"cla_adder32b a3 or_w", false,-1, 7,0);
        tracep->declBus(c+36,"cla_adder32b a3 g", false,-1, 7,0);
        tracep->declBus(c+37,"cla_adder32b a3 p", false,-1, 7,0);
        tracep->declBus(c+38,"cla_adder32b a3 c", false,-1, 8,0);
    }
}

void Vcla_adder::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vcla_adder::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vcla_adder::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vcla_adder__Syms* __restrict vlSymsp = static_cast<Vcla_adder__Syms*>(userp);
    Vcla_adder* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullCData(oldp+1,(vlTOPp->cla_adder32b__DOT__P),4);
        tracep->fullCData(oldp+2,(vlTOPp->cla_adder32b__DOT__G),4);
        tracep->fullCData(oldp+3,(vlTOPp->cla_adder32b__DOT__c),4);
        tracep->fullBit(oldp+4,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__p) 
                                       >> 7U))));
        tracep->fullBit(oldp+5,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__g) 
                                       >> 7U))));
        tracep->fullBit(oldp+6,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c) 
                                       >> 8U))));
        tracep->fullCData(oldp+7,(vlTOPp->cla_adder32b__DOT__a0__DOT__and_w),8);
        tracep->fullCData(oldp+8,(vlTOPp->cla_adder32b__DOT__a0__DOT__or_w),8);
        tracep->fullCData(oldp+9,(vlTOPp->cla_adder32b__DOT__a0__DOT__g),8);
        tracep->fullCData(oldp+10,(vlTOPp->cla_adder32b__DOT__a0__DOT__p),8);
        tracep->fullSData(oldp+11,(vlTOPp->cla_adder32b__DOT__a0__DOT__c),9);
        tracep->fullBit(oldp+12,((1U & (IData)(vlTOPp->cla_adder32b__DOT__c))));
        tracep->fullBit(oldp+13,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__p) 
                                        >> 7U))));
        tracep->fullBit(oldp+14,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__g) 
                                        >> 7U))));
        tracep->fullBit(oldp+15,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c) 
                                        >> 8U))));
        tracep->fullCData(oldp+16,(vlTOPp->cla_adder32b__DOT__a1__DOT__and_w),8);
        tracep->fullCData(oldp+17,(vlTOPp->cla_adder32b__DOT__a1__DOT__or_w),8);
        tracep->fullCData(oldp+18,(vlTOPp->cla_adder32b__DOT__a1__DOT__g),8);
        tracep->fullCData(oldp+19,(vlTOPp->cla_adder32b__DOT__a1__DOT__p),8);
        tracep->fullSData(oldp+20,(vlTOPp->cla_adder32b__DOT__a1__DOT__c),9);
        tracep->fullBit(oldp+21,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                        >> 1U))));
        tracep->fullBit(oldp+22,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__p) 
                                        >> 7U))));
        tracep->fullBit(oldp+23,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__g) 
                                        >> 7U))));
        tracep->fullBit(oldp+24,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c) 
                                        >> 8U))));
        tracep->fullCData(oldp+25,(vlTOPp->cla_adder32b__DOT__a2__DOT__and_w),8);
        tracep->fullCData(oldp+26,(vlTOPp->cla_adder32b__DOT__a2__DOT__or_w),8);
        tracep->fullCData(oldp+27,(vlTOPp->cla_adder32b__DOT__a2__DOT__g),8);
        tracep->fullCData(oldp+28,(vlTOPp->cla_adder32b__DOT__a2__DOT__p),8);
        tracep->fullSData(oldp+29,(vlTOPp->cla_adder32b__DOT__a2__DOT__c),9);
        tracep->fullBit(oldp+30,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__c) 
                                        >> 2U))));
        tracep->fullBit(oldp+31,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__p) 
                                        >> 7U))));
        tracep->fullBit(oldp+32,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__g) 
                                        >> 7U))));
        tracep->fullBit(oldp+33,((1U & ((IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c) 
                                        >> 8U))));
        tracep->fullCData(oldp+34,(vlTOPp->cla_adder32b__DOT__a3__DOT__and_w),8);
        tracep->fullCData(oldp+35,(vlTOPp->cla_adder32b__DOT__a3__DOT__or_w),8);
        tracep->fullCData(oldp+36,(vlTOPp->cla_adder32b__DOT__a3__DOT__g),8);
        tracep->fullCData(oldp+37,(vlTOPp->cla_adder32b__DOT__a3__DOT__p),8);
        tracep->fullSData(oldp+38,(vlTOPp->cla_adder32b__DOT__a3__DOT__c),9);
        tracep->fullIData(oldp+39,(vlTOPp->a),32);
        tracep->fullIData(oldp+40,(vlTOPp->b),32);
        tracep->fullBit(oldp+41,(vlTOPp->cin));
        tracep->fullIData(oldp+42,(vlTOPp->s),32);
        tracep->fullBit(oldp+43,(vlTOPp->cout));
        tracep->fullCData(oldp+44,((0xffU & vlTOPp->a)),8);
        tracep->fullCData(oldp+45,((0xffU & vlTOPp->b)),8);
        tracep->fullCData(oldp+46,((0xffU & ((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             ^ (IData)(vlTOPp->cla_adder32b__DOT__a0__DOT__c)))),8);
        tracep->fullCData(oldp+47,((0xffU & (vlTOPp->a 
                                             ^ vlTOPp->b))),8);
        tracep->fullCData(oldp+48,((0xffU & (vlTOPp->a 
                                             >> 8U))),8);
        tracep->fullCData(oldp+49,((0xffU & (vlTOPp->b 
                                             >> 8U))),8);
        tracep->fullCData(oldp+50,((0xffU & (((vlTOPp->a 
                                               ^ vlTOPp->b) 
                                              >> 8U) 
                                             ^ (IData)(vlTOPp->cla_adder32b__DOT__a1__DOT__c)))),8);
        tracep->fullCData(oldp+51,((0xffU & ((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 8U))),8);
        tracep->fullCData(oldp+52,((0xffU & (vlTOPp->a 
                                             >> 0x10U))),8);
        tracep->fullCData(oldp+53,((0xffU & (vlTOPp->b 
                                             >> 0x10U))),8);
        tracep->fullCData(oldp+54,((0xffU & (((vlTOPp->a 
                                               ^ vlTOPp->b) 
                                              >> 0x10U) 
                                             ^ (IData)(vlTOPp->cla_adder32b__DOT__a2__DOT__c)))),8);
        tracep->fullCData(oldp+55,((0xffU & ((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 0x10U))),8);
        tracep->fullCData(oldp+56,((0xffU & (vlTOPp->a 
                                             >> 0x18U))),8);
        tracep->fullCData(oldp+57,((0xffU & (vlTOPp->b 
                                             >> 0x18U))),8);
        tracep->fullCData(oldp+58,((0xffU & (((vlTOPp->a 
                                               ^ vlTOPp->b) 
                                              >> 0x18U) 
                                             ^ (IData)(vlTOPp->cla_adder32b__DOT__a3__DOT__c)))),8);
        tracep->fullCData(oldp+59,((0xffU & ((vlTOPp->a 
                                              ^ vlTOPp->b) 
                                             >> 0x18U))),8);
    }
}
