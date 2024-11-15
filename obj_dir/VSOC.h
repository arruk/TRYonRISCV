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
    VL_OUT8(LEDS,5,0);
    VL_OUT8(UART_TX,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ SOC__DOT__RESET;
        CData/*0:0*/ SOC__DOT__pcpi_valid;
        CData/*0:0*/ SOC__DOT__pcpi_div_wait;
        CData/*0:0*/ SOC__DOT__pcpi_div_ready;
        CData/*0:0*/ SOC__DOT__IO_mem_wr;
        CData/*0:0*/ SOC__DOT__uart_valid;
        CData/*0:0*/ SOC__DOT__uart_ready;
        CData/*0:0*/ SOC__DOT__resetn;
        CData/*0:0*/ SOC__DOT__CPU__DOT__rs1_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__rs2_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__mul_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__data_HAZ;
        CData/*0:0*/ SOC__DOT__CPU__DOT__f_stall;
        CData/*0:0*/ SOC__DOT__CPU__DOT__d_stall;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_flush;
        CData/*0:0*/ SOC__DOT__CPU__DOT__fd_NOP;
        CData/*0:0*/ SOC__DOT__CPU__DOT__wb_enable;
        CData/*4:0*/ SOC__DOT__CPU__DOT__wb_rdID;
        CData/*0:0*/ SOC__DOT__CPU__DOT__e_JoB;
        CData/*2:0*/ SOC__DOT__CPU__DOT__m_funct3;
        CData/*3:0*/ SOC__DOT__CPU__DOT__m_WMASK;
        CData/*2:0*/ SOC__DOT__CPU__DOT__w_funct3;
        CData/*7:0*/ SOC__DOT__CPU__DOT__w_loadB;
        CData/*0:0*/ SOC__DOT__CPU__DOT__w_load_sign;
        CData/*0:0*/ SOC__DOT__CPU__DOT__wb_csr_en;
        CData/*0:0*/ SOC__DOT__CPU__DOT__m0__DOT__Itype;
        CData/*0:0*/ SOC__DOT__CPU__DOT__m0__DOT__Utype;
        CData/*2:0*/ SOC__DOT__CPU__DOT__u0__DOT__d_result;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__t_LT;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__minus;
        CData/*0:0*/ SOC__DOT__CPU__DOT__u0__DOT__i_take_b;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__instr_mul;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__instr_mulh;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__instr_mulhsu;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__instr_mulhu;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__shift_out;
        CData/*3:0*/ SOC__DOT__pcpi_mul__DOT__active;
        CData/*0:0*/ SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__instr_div;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__instr_divu;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__instr_rem;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__instr_remu;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__pcpi_wait_q;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__start;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__running;
        CData/*0:0*/ SOC__DOT__pcpi_div__DOT__outsign;
        CData/*4:0*/ SOC__DOT__UART__DOT__cnt;
        SData/*15:0*/ SOC__DOT__CPU__DOT__w_loadH;
        SData/*9:0*/ SOC__DOT__UART__DOT__data;
        SData/*15:0*/ SOC__DOT__CW__DOT__reset_cnt;
        IData/*31:0*/ SOC__DOT__imem_data;
        IData/*31:0*/ SOC__DOT__mem_data;
        IData/*31:0*/ SOC__DOT__pcpi_div_rd;
        IData/*31:0*/ SOC__DOT__CPU__DOT__f_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__fd_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__wb_DATA;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_PC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_rs1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__de_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_IMM;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ALUin1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ALUin2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_RES;
    };
    struct {
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDin1;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDR_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__e_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__em_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__m_store_DATA;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_IR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_IO_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_ADDR;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_CSR_RES;
        IData/*31:0*/ SOC__DOT__CPU__DOT__mw_rs2;
        IData/*31:0*/ SOC__DOT__CPU__DOT__wb_csr;
        IData/*31:0*/ SOC__DOT__CPU__DOT__MEPC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__MTVEC;
        IData/*31:0*/ SOC__DOT__CPU__DOT__MCAUSE;
        IData/*31:0*/ SOC__DOT__CPU__DOT__MSTATUS;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__a_flipped;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__right_shift;
        IData/*31:0*/ SOC__DOT__CPU__DOT__u0__DOT__left_shift;
        IData/*31:0*/ SOC__DOT__pcpi_div__DOT__dividend;
        IData/*31:0*/ SOC__DOT__pcpi_div__DOT__quotient;
        IData/*31:0*/ SOC__DOT__pcpi_div__DOT__quotient_msk;
        QData/*63:0*/ SOC__DOT__CPU__DOT__cycle;
        QData/*63:0*/ SOC__DOT__CPU__DOT__instret;
        QData/*32:0*/ SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result;
        QData/*32:0*/ SOC__DOT__pcpi_mul__DOT__rs1;
        QData/*32:0*/ SOC__DOT__pcpi_mul__DOT__rs2;
        QData/*63:0*/ SOC__DOT__pcpi_mul__DOT__rd;
        QData/*62:0*/ SOC__DOT__pcpi_div__DOT__divisor;
        IData/*31:0*/ SOC__DOT__CPU__DOT__reg_file[32];
        IData/*31:0*/ SOC__DOT__DATA__DOT__RAM[65536];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__4__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__7__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__8__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__9__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__10__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__11__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__14__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__16__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__18__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__23__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__27__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__28__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__29__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__31__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__35__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__44__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__45__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__47__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__48__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRimm__49__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__52__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__54__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__56__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__57__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__58__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__59__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__Vfuncout;
        CData/*2:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__62__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout;
        CData/*2:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__65__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__66__Vfuncout;
    };
    struct {
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__70__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__71__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__72__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__73__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__74__Vfuncout;
        CData/*4:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__75__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__77__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__Vfuncout;
        CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__Vfuncout;
        CData/*7:0*/ __Vtableidx1;
        CData/*0:0*/ __VinpClk__TOP__SOC__DOT__RESET;
        CData/*0:0*/ __Vclklast__TOP__CLK;
        CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__SOC__DOT__RESET;
        CData/*0:0*/ __Vchglast__TOP__SOC__DOT__RESET;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__4__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__7__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__8__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__9__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__10__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__11__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__13__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__14__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__16__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__18__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__23__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__26__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__27__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__28__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__29__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__31__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__32__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__33__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__35__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__37__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__44__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__45__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRtype__47__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__48__I;
    };
    struct {
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isRimm__49__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLUI__52__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__54__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__56__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJAL__57__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isJALR__58__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__59__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__62__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__63__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__64__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__65__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isLoad__66__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__70__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__71__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__72__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__73__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__74__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__rdID__75__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isStype__77__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__I;
        IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__I;
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
