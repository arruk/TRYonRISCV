// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VCLA_ADDER_H_
#define _VCLA_ADDER_H_  // guard

#include "verilated.h"

//==========

class Vcla_adder__Syms;
class Vcla_adder_VerilatedVcd;


//----------

VL_MODULE(Vcla_adder) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(cin,0,0);
    VL_OUT8(cout,0,0);
    VL_IN(a,31,0);
    VL_IN(b,31,0);
    VL_OUT(s,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*3:0*/ cla_adder32b__DOT__P;
    CData/*3:0*/ cla_adder32b__DOT__G;
    CData/*3:0*/ cla_adder32b__DOT__c;
    CData/*7:0*/ cla_adder32b__DOT__a0__DOT__and_w;
    CData/*7:0*/ cla_adder32b__DOT__a0__DOT__or_w;
    CData/*7:0*/ cla_adder32b__DOT__a0__DOT__g;
    CData/*7:0*/ cla_adder32b__DOT__a0__DOT__p;
    CData/*7:0*/ cla_adder32b__DOT__a1__DOT__and_w;
    CData/*7:0*/ cla_adder32b__DOT__a1__DOT__or_w;
    CData/*7:0*/ cla_adder32b__DOT__a1__DOT__g;
    CData/*7:0*/ cla_adder32b__DOT__a1__DOT__p;
    CData/*7:0*/ cla_adder32b__DOT__a2__DOT__and_w;
    CData/*7:0*/ cla_adder32b__DOT__a2__DOT__or_w;
    CData/*7:0*/ cla_adder32b__DOT__a2__DOT__g;
    CData/*7:0*/ cla_adder32b__DOT__a2__DOT__p;
    CData/*7:0*/ cla_adder32b__DOT__a3__DOT__and_w;
    CData/*7:0*/ cla_adder32b__DOT__a3__DOT__or_w;
    CData/*7:0*/ cla_adder32b__DOT__a3__DOT__g;
    CData/*7:0*/ cla_adder32b__DOT__a3__DOT__p;
    SData/*8:0*/ cla_adder32b__DOT__a0__DOT__c;
    SData/*8:0*/ cla_adder32b__DOT__a1__DOT__c;
    SData/*8:0*/ cla_adder32b__DOT__a2__DOT__c;
    SData/*8:0*/ cla_adder32b__DOT__a3__DOT__c;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__g;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__p;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__g;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__p;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__g;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__p;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__g;
    CData/*7:0*/ __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__p;
    SData/*8:0*/ __Vchglast__TOP__cla_adder32b__DOT__a0__DOT__c;
    SData/*8:0*/ __Vchglast__TOP__cla_adder32b__DOT__a1__DOT__c;
    SData/*8:0*/ __Vchglast__TOP__cla_adder32b__DOT__a2__DOT__c;
    SData/*8:0*/ __Vchglast__TOP__cla_adder32b__DOT__a3__DOT__c;
    CData/*0:0*/ __Vm_traceActivity[2];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vcla_adder__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vcla_adder);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vcla_adder(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vcla_adder();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vcla_adder__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vcla_adder__Syms* symsp, bool first);
  private:
    static QData _change_request(Vcla_adder__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vcla_adder__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vcla_adder__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vcla_adder__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vcla_adder__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vcla_adder__Syms* __restrict vlSymsp) VL_ATTR_COLD;
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
