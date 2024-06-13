// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSOC_H_
#define _VSOC_H_  // guard

#include "verilated_heavy.h"

//==========

class VSOC__Syms;

//----------

VL_MODULE(VSOC) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(CLK,0,0);
    VL_IN8(RESET,0,0);
    VL_OUT8(LEDS,5,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ SOC__DOT__resetn;
        CData/*0:0*/ SOC__DOT__IO_mem_wr;
        CData/*0:0*/ SOC__DOT__CPU__DOT__halt;
        CData/*0:0*/ SOC__DOT__CPU__DOT__rs1_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__rs2_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__data_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__f_stall;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_flush;
        CData/*2:0*/ SOC__DOT__CPU__DOT__BH;
        CData/*0:0*/ SOC__DOT__CPU__DOT__fd_NOP;
        CData/*0:0*/ SOC__DOT__CPU__DOT__d_predict;
        CData/*0:0*/ SOC__DOT__CPU__DOT__d_JoB_now;
        CData/*0:0*/ SOC__DOT__CPU__DOT__wb_enable;
        CData/*4:0*/ SOC__DOT__CPU__DOT__wb_rdID;
        CData/*0:0*/ SOC__DOT__CPU__DOT__de_predict;
        CData/*5:0*/ SOC__DOT__CPU__DOT__de_BHTindex;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_m_fwd_rs1;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_w_fwd_rs1;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_m_fwd_rs2;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_w_fwd_rs2;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_takeB;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_JoB;
        CData/*0:0*/ SOC__DOT__CPU__DOT__em_JoB_now;
        CData/*3:0*/ SOC__DOT__CPU__DOT__m_WMASK;
        CData/*7:0*/ SOC__DOT__CPU__DOT__w_loadB;
        CData/*0:0*/ SOC__DOT__CPU__DOT__w_load_sign;
        CData/*0:0*/ SOC__DOT__CPU__DOT__m0__DOT__Itype;
        CData/*0:0*/ SOC__DOT__CPU__DOT__m0__DOT__Utype;
        CData/*2:0*/ SOC__DOT__CPU__DOT__u0__DOT__d_result;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__t_LT;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__minus;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__i_take_b;
        SData/*15:0*/ SOC__DOT__CPU__DOT__w_loadH;
        SData/*15:0*/ SOC__DOT__CW__DOT__genblk2__DOT__reset_cnt;
        IData/*31:0*/ SOC__DOT__IO_mem_rdata;
        IData/*31:0*/ SOC__DOT__CPU__DOT__PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__f_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__fd_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__fd_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__d_JoB_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__wb_DATA;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_rs1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_rs1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_IMM;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ALUin1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ALUin2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDin1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDin2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDR_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_JoB_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__m_store_DATA;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_IO_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_ADDR;
    };
    struct {
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_Mdata;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_CSR_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__nbBranch;
        IData/*31:0*/ SOC__DOT__CPU__DOT__nbPredictHit;
        IData/*31:0*/ SOC__DOT__CPU__DOT__nbJAL;
        IData/*31:0*/ SOC__DOT__CPU__DOT__nbJALR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__a_flipped;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__right_shift;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__left_shift;
        QData/*63:0*/ SOC__DOT__CPU__DOT__cycle;
        QData/*63:0*/ SOC__DOT__CPU__DOT__instret;
        QData/*32:0*/ SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result;
        IData/*31:0*/ SOC__DOT__CPU__DOT__RAM[16384];
        IData/*31:0*/ SOC__DOT__CPU__DOT__ROM[16384];
        CData/*1:0*/ SOC__DOT__CPU__DOT__BHT[64];
        IData/*31:0*/ SOC__DOT__CPU__DOT__reg_file[32];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__3__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__4__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__5__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__6__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__8__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__11__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__14__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__16__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__17__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__Vfuncout;
        CData/*5:0*/ __Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__20__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__21__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__22__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__28__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__30__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__32__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__34__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__35__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__38__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__40__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__42__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__43__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__44__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__45__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__46__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__47__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__48__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__50__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__52__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__53__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__54__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__56__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__57__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__58__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__60__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__62__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__65__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__66__Vfuncout;
    };
    struct {
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__67__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__68__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__69__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__71__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__72__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRimm__73__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__75__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__76__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__77__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__78__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__79__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__80__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__81__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__84__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__85__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__86__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__89__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__90__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__91__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__92__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__93__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__94__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__95__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__96__Vfuncout;
        CData/*7:0*/ __Vtableidx1;
        CData/*0:0*/ __Vclklast__TOP__CLK;
        CData/*0:0*/ __Vclklast__TOP__RESET;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__0__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__1__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__2__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__3__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__4__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__5__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__6__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__7__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__8__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__9__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__10__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__11__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__13__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__14__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__16__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__17__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__18__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__BHT_index__19__PC;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__20__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__21__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__22__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__Jimm__23__Vfuncout;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__Jimm__23__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__Bimm__24__Vfuncout;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__Bimm__24__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__26__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__27__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__28__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__29__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__30__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__31__I;
    };
    struct {
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__32__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__33__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__34__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__35__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__37__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__38__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__39__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__40__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__41__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__42__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__43__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__44__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__45__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__46__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__47__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__48__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__49__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__50__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__51__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__52__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__53__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__54__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__56__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__57__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__58__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__59__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__60__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__61__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__62__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__63__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__64__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__65__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__66__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__67__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__68__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__69__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__70__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__71__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__72__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRimm__73__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__74__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__75__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__76__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__77__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__78__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__79__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__80__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__81__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__84__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__85__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__86__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__87__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__88__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__89__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__90__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__91__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__92__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__93__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__94__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__95__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__96__I;
    };
    static CData/*0:0*/ __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[256];
    
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
    static void _initial__TOP__3(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__1(VSOC__Syms* __restrict vlSymsp);
    static void _sequent__TOP__2(VSOC__Syms* __restrict vlSymsp);
    static void _settle__TOP__4(VSOC__Syms* __restrict vlSymsp) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
