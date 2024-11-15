// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSOC_H_
#define _VSOC_H_  // guard

#include "verilated.h"

//==========

class VSOC__Syms;

//----------

VL_MODULE(VSOC) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(CLK,0,0);
    VL_IN8(RESETN,0,0);
    VL_IN8(pcpi_valid,0,0);
    VL_OUT8(pcpi_wr,0,0);
    VL_OUT8(pcpi_wait,0,0);
    VL_OUT8(pcpi_ready,0,0);
    VL_IN(pcpi_insn,31,0);
    VL_IN(pcpi_rs1,31,0);
    VL_IN(pcpi_rs2,31,0);
    VL_OUT(pcpi_rd,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ SOC__DOT__MULT__DOT__instr_mul;
    CData/*0:0*/ SOC__DOT__MULT__DOT__instr_mulh;
    CData/*0:0*/ SOC__DOT__MULT__DOT__instr_mulhsu;
    CData/*0:0*/ SOC__DOT__MULT__DOT__instr_mulhu;
    CData/*0:0*/ SOC__DOT__MULT__DOT__shift_out;
    CData/*3:0*/ SOC__DOT__MULT__DOT__active;
    CData/*0:0*/ SOC__DOT__MULT__DOT__pcpi_insn_valid;
    QData/*32:0*/ SOC__DOT__MULT__DOT__rs1;
    QData/*32:0*/ SOC__DOT__MULT__DOT__rs2;
    QData/*63:0*/ SOC__DOT__MULT__DOT__rd;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__CLK;
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VSOC__Syms* __VlSymsp;  // Symbol table
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(VSOC);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    VSOC(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VSOC();
    
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
    static void _eval_initial_loop(VSOC__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VSOC__Syms* symsp, bool first);
  private:
    static QData _change_request(VSOC__Syms* __restrict vlSymsp);
    static QData _change_request_1(VSOC__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(VSOC__Syms* __restrict vlSymsp);
    static void _combo__TOP__5(VSOC__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(VSOC__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(VSOC__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
