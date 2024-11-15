// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========
CData/*0:0*/ VSOC::__Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[256];

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

void VSOC::_initial__TOP__3(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_initial__TOP__3\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__RESET = 0U;
    vlTOPp->SOC__DOT__CPU__DOT__MEPC = 0U;
    vlTOPp->SOC__DOT__UART__DOT__cnt = 0U;
    VL_READMEM_N(true, 32, 65536, 0, std::string("RAM.hex")
                 , vlTOPp->SOC__DOT__DATA__DOT__RAM
                 , 0, ~0ULL);
    vlTOPp->SOC__DOT__CW__DOT__reset_cnt = 0U;
}

void VSOC::_settle__TOP__4(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_settle__TOP__4\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->UART_TX = (1U & ((IData)(vlTOPp->SOC__DOT__UART__DOT__data) 
                             | (~ (IData)((0U != (IData)(vlTOPp->SOC__DOT__UART__DOT__data))))));
    vlTOPp->SOC__DOT__CPU__DOT__w_loadH = (0xffffU 
                                           & ((2U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                               ? (vlTOPp->SOC__DOT__mem_data 
                                                  >> 0x10U)
                                               : vlTOPp->SOC__DOT__mem_data));
    vlTOPp->LEDS = (0x3fU & vlTOPp->SOC__DOT__CPU__DOT__em_rs2);
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffff00U 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xffU 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffff00ffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff00U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 8U)) 
                                                      << 8U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xff00ffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff0000U 
                                                   & (((2U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                        >> 0x10U)) 
                                                      << 0x10U)));
    vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA = ((0xffffffU 
                                                 & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA) 
                                                | (0xff000000U 
                                                   & (((1U 
                                                        & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                        ? vlTOPp->SOC__DOT__CPU__DOT__em_rs2
                                                        : 
                                                       ((2U 
                                                         & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                         ? 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                         >> 8U)
                                                         : 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                         >> 0x18U))) 
                                                      << 0x18U)));
    vlTOPp->SOC__DOT__CPU__DOT__wb_csr = ((1U == (3U 
                                                  & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                     >> 0xcU)))
                                           ? vlTOPp->SOC__DOT__CPU__DOT__mw_rs2
                                           : ((2U == 
                                               (3U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                   >> 0xcU)))
                                               ? (vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES 
                                                  | vlTOPp->SOC__DOT__CPU__DOT__mw_rs2)
                                               : (vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES 
                                                  & (~ vlTOPp->SOC__DOT__CPU__DOT__mw_rs2))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__Vfuncout 
        = (0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__Vfuncout 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__Vfuncout;
    vlTOPp->SOC__DOT__CPU__DOT__wb_csr_en = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__Vfuncout) 
                                             & (((1U 
                                                  == 
                                                  (3U 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                      >> 0xcU))) 
                                                 | (2U 
                                                    == 
                                                    (3U 
                                                     & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                        >> 0xcU)))) 
                                                | (3U 
                                                   == 
                                                   (3U 
                                                    & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                                       >> 0xcU)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__77__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__77__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__77__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__77__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__I 
                             >> 7U)));
    vlTOPp->SOC__DOT__CPU__DOT__wb_rdID = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__75__Vfuncout;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__72__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__72__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__72__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__71__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__71__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__71__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__71__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__72__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__74__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__74__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__74__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__73__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__73__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__73__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__73__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__74__Vfuncout))));
    vlTOPp->SOC__DOT__CPU__DOT__wb_enable = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__Vfuncout) 
                                             & (0U 
                                                != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__70__Vfuncout)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__65__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__65__Vfuncout 
        = (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__65__I 
                 >> 0xcU));
    vlTOPp->SOC__DOT__CPU__DOT__w_funct3 = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__65__Vfuncout;
    vlTOPp->SOC__DOT__pcpi_div__DOT__start = ((IData)(vlTOPp->SOC__DOT__pcpi_div_wait) 
                                              & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__pcpi_wait_q)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__I));
    vlTOPp->SOC__DOT__IO_mem_wr = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout) 
                                   & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                                      >> 0x16U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__62__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__62__Vfuncout 
        = (7U & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__62__I 
                 >> 0xcU));
    vlTOPp->SOC__DOT__CPU__DOT__m_funct3 = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__funct3__62__Vfuncout;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__Vfuncout 
        = ((0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__I)) 
           & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__I 
              >> 0x19U));
    vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__Vfuncout) 
                                           & (~ ((0x4000U 
                                                  & vlTOPp->SOC__DOT__CPU__DOT__de_IR)
                                                  ? (IData)(vlTOPp->SOC__DOT__pcpi_div_ready)
                                                  : 
                                                 ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__active) 
                                                  >> 1U))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result = 
        (((0x6fU == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
          | (0x17U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
          ? 0U : (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                        >> 0xcU)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__Vfuncout 
        = ((0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__I)) 
           & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__I 
              >> 0x19U));
    vlTOPp->SOC__DOT__pcpi_valid = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__Vfuncout;
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus = ((
                                                   (0x33U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                   & ((vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                       >> 0x1eU) 
                                                      | ((~ 
                                                          (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                           >> 0xeU)) 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                            >> 0xdU)))) 
                                                  | (0x63U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__I 
                    >> 0x14U));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs2 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__Vfuncout];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__I 
                    >> 0xfU));
    vlTOPp->SOC__DOT__CPU__DOT__de_rs1 = vlTOPp->SOC__DOT__CPU__DOT__reg_file
        [vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__Vfuncout];
    vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype = ((
                                                   (0x67U 
                                                    == 
                                                    (0x7fU 
                                                     & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                   | (3U 
                                                      == 
                                                      (0x7fU 
                                                       & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
                                                  | (0x13U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype = ((0x37U 
                                                   == 
                                                   (0x7fU 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                  | (0x17U 
                                                     == 
                                                     (0x7fU 
                                                      & vlTOPp->SOC__DOT__CPU__DOT__de_IR)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__9__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__9__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__9__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__8__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__8__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__8__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__8__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__9__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__11__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__11__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__11__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__10__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__10__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__10__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__10__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__11__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__14__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__14__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__14__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__14__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__I 
                    >> 0xfU));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__18__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__18__Vfuncout 
        = (0x37U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__18__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__16__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__16__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__16__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__Vfuncout 
        = (1U & (~ (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__16__Vfuncout) 
                     | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__Vfuncout)) 
                    | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__18__Vfuncout))));
    vlTOPp->SOC__DOT__CPU__DOT__rs1_HAZ = ((((~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP)) 
                                             & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__Vfuncout)) 
                                            & (0U != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__Vfuncout))) 
                                           & (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__Vfuncout) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__4__Vfuncout))) 
                                              | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__Vfuncout) 
                                                 & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__Vfuncout) 
                                                    == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__7__Vfuncout)))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__28__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__28__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__28__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__27__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__27__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__27__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__27__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__28__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__29__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__29__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__29__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__29__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__31__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__31__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__31__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__31__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout))
            ? 0U : (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__I 
                             >> 7U)));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__Vfuncout 
        = (1U & ((~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout)) 
                 & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__Vfuncout 
        = (0x1fU & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__I 
                    >> 0x14U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I 
        = vlTOPp->SOC__DOT__imem_data;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__35__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__35__Vfuncout 
        = (0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__35__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__35__Vfuncout) 
            | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout)) 
           | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout));
    vlTOPp->SOC__DOT__CPU__DOT__rs2_HAZ = ((((~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP)) 
                                             & (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__Vfuncout)) 
                                            & (0U != (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__Vfuncout))) 
                                           & (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__Vfuncout) 
                                               & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__Vfuncout) 
                                                  == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__23__Vfuncout))) 
                                              | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__Vfuncout) 
                                                 & ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout) 
                                                    == (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout)))));
    vlTOPp->SOC__DOT__resetn = (0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt));
    vlTOPp->SOC__DOT__CPU__DOT__w_loadB = (0xffU & 
                                           ((1U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                             ? ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                >> 8U)
                                             : (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH)));
    vlTOPp->SOC__DOT__uart_valid = ((IData)(vlTOPp->SOC__DOT__IO_mem_wr) 
                                    & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                                       >> 3U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__I 
        = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout 
        = (0x23U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__I));
    vlTOPp->SOC__DOT__CPU__DOT__m_WMASK = ((- (IData)(
                                                      ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout) 
                                                       & (~ 
                                                          (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                                                           >> 0x16U))))) 
                                           & ((0U == 
                                               (3U 
                                                & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_funct3)))
                                               ? ((2U 
                                                   & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                   ? 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 8U
                                                    : 4U)
                                                   : 
                                                  ((1U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 2U
                                                    : 1U))
                                               : ((1U 
                                                   == 
                                                   (3U 
                                                    & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_funct3)))
                                                   ? 
                                                  ((2U 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                                    ? 0xcU
                                                    : 3U)
                                                   : 0xfU)));
    vlTOPp->SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid 
        = (((IData)(vlTOPp->SOC__DOT__pcpi_valid) & 
            (0x33U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
           & (1U == (0x7fU & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0x19U))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__Vfuncout 
        = (0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__Vfuncout 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__Vfuncout;
    vlTOPp->SOC__DOT__CPU__DOT__e_rs2 = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__Vfuncout)
                                          ? ((0x4000U 
                                              & vlTOPp->SOC__DOT__CPU__DOT__de_IR)
                                              ? (0x1fU 
                                                 & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                    >> 0xfU))
                                              : vlTOPp->SOC__DOT__CPU__DOT__de_rs1)
                                          : vlTOPp->SOC__DOT__CPU__DOT__de_rs2);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__54__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__54__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__54__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDin1 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__54__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__de_rs1);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__45__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__45__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__45__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__44__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__44__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__44__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 = ((((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__44__Vfuncout) 
                                              | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__45__Vfuncout)) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_PC
                                             : vlTOPp->SOC__DOT__CPU__DOT__de_rs1);
    vlTOPp->SOC__DOT__CPU__DOT__e_IMM = ((0x80000000U 
                                          & vlTOPp->SOC__DOT__CPU__DOT__de_IR) 
                                         | ((0x7ff00000U 
                                             & (((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype)
                                                  ? 
                                                 (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                  >> 0x14U)
                                                  : 
                                                 (- (IData)(
                                                            (1U 
                                                             & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                >> 0x1fU))))) 
                                                << 0x14U)) 
                                            | ((0xff000U 
                                                & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype) 
                                                     | (0x6fU 
                                                        == 
                                                        (0x7fU 
                                                         & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                     ? 
                                                    (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                     >> 0xcU)
                                                     : 
                                                    (- (IData)(
                                                               (1U 
                                                                & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                   >> 0x1fU))))) 
                                                   << 0xcU)) 
                                               | ((0x800U 
                                                   & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype) 
                                                        | (0x23U 
                                                           == 
                                                           (0x7fU 
                                                            & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                        ? 
                                                       (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                        >> 0x1fU)
                                                        : 
                                                       ((0x63U 
                                                         == 
                                                         (0x7fU 
                                                          & vlTOPp->SOC__DOT__CPU__DOT__de_IR))
                                                         ? 
                                                        (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                         >> 7U)
                                                         : 
                                                        ((0x6fU 
                                                          == 
                                                          (0x7fU 
                                                           & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                            >> 0x14U)))) 
                                                      << 0xbU)) 
                                                  | ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Utype)
                                                        ? 0U
                                                        : 
                                                       (0x3fU 
                                                        & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                           >> 0x19U))) 
                                                      << 5U) 
                                                     | ((0x1eU 
                                                         & ((((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype) 
                                                              | (0x6fU 
                                                                 == 
                                                                 (0x7fU 
                                                                  & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                              ? 
                                                             (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                              >> 0x15U)
                                                              : 
                                                             (((0x23U 
                                                                == 
                                                                (0x7fU 
                                                                 & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                               | (0x63U 
                                                                  == 
                                                                  (0x7fU 
                                                                   & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))
                                                               ? 
                                                              (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                               >> 8U)
                                                               : 0U)) 
                                                            << 1U)) 
                                                        | (1U 
                                                           & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__m0__DOT__Itype)
                                                               ? 
                                                              (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                               >> 0x14U)
                                                               : 
                                                              ((0x23U 
                                                                == 
                                                                (0x7fU 
                                                                 & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                  >> 7U))))))))));
    vlTOPp->SOC__DOT__CPU__DOT__data_HAZ = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__rs1_HAZ) 
                                            | (IData)(vlTOPp->SOC__DOT__CPU__DOT__rs2_HAZ));
    vlTOPp->SOC__DOT__CPU__DOT__w_load_sign = (1U & 
                                               ((~ 
                                                 ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_funct3) 
                                                  >> 2U)) 
                                                & ((0U 
                                                    == 
                                                    (3U 
                                                     & (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_funct3)))
                                                    ? 
                                                   ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadB) 
                                                    >> 7U)
                                                    : 
                                                   ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                    >> 0xfU))));
    vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mul = 0U;
    if (((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
         & (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid))) {
        if ((0U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mul = 1U;
        }
    }
    vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh = 0U;
    if (((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
         & (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((1U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh = 1U;
            }
        }
    }
    vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhsu = 0U;
    if (((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
         & (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((1U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                if ((2U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                  >> 0xcU)))) {
                    vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhsu = 1U;
                }
            }
        }
    }
    vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhu = 0U;
    if (((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
         & (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid))) {
        if ((0U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((1U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                if ((2U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                  >> 0xcU)))) {
                    if ((3U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                      >> 0xcU)))) {
                        vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhu = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__a_flipped 
        = ((0x80000000U & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                           << 0x1fU)) | ((0x40000000U 
                                          & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                             << 0x1dU)) 
                                         | ((0x20000000U 
                                             & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                << 0x1bU)) 
                                            | ((0x10000000U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                   << 0x19U)) 
                                               | ((0x8000000U 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                      << 0x17U)) 
                                                  | ((0x4000000U 
                                                      & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                         << 0x15U)) 
                                                     | ((0x2000000U 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                            << 0x13U)) 
                                                        | ((0x1000000U 
                                                            & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                               << 0x11U)) 
                                                           | ((0x800000U 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                  << 0xfU)) 
                                                              | ((0x400000U 
                                                                  & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                     << 0xdU)) 
                                                                 | ((0x200000U 
                                                                     & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                        << 0xbU)) 
                                                                    | ((0x100000U 
                                                                        & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                           << 9U)) 
                                                                       | ((0x80000U 
                                                                           & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                              << 7U)) 
                                                                          | ((0x40000U 
                                                                              & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 5U)) 
                                                                             | ((0x20000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 3U)) 
                                                                                | ((0x10000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                << 1U)) 
                                                                                | ((0x8000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 1U)) 
                                                                                | ((0x4000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 3U)) 
                                                                                | ((0x2000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 5U)) 
                                                                                | ((0x1000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 7U)) 
                                                                                | ((0x800U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 9U)) 
                                                                                | ((0x400U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xbU)) 
                                                                                | ((0x200U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xdU)) 
                                                                                | ((0x100U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0xfU)) 
                                                                                | ((0x80U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x11U)) 
                                                                                | ((0x40U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x13U)) 
                                                                                | ((0x20U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x15U)) 
                                                                                | ((0x10U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x17U)) 
                                                                                | ((8U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x19U)) 
                                                                                | ((4U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1bU)) 
                                                                                | ((2U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1dU)) 
                                                                                | (1U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                                >> 0x1fU)))))))))))))))))))))))))))))))));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES = (vlTOPp->SOC__DOT__CPU__DOT__e_ADDin1 
                                              + vlTOPp->SOC__DOT__CPU__DOT__e_IMM);
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__Vfuncout 
        = (0x17U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__49__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__49__Vfuncout 
        = (0x13U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__49__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__48__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__48__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__48__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__47__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__47__Vfuncout 
        = (0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__47__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRtype__47__Vfuncout) 
                                             | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__48__Vfuncout))
                                             ? vlTOPp->SOC__DOT__CPU__DOT__de_rs2
                                             : (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isRimm__49__Vfuncout) 
                                                 | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__Vfuncout))
                                                 ? vlTOPp->SOC__DOT__CPU__DOT__e_IMM
                                                 : 4U));
    vlTOPp->SOC__DOT__CPU__DOT__f_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ));
    vlTOPp->SOC__DOT__CPU__DOT__d_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__I 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__I;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__Vfuncout 
        = (0x73U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__Vfuncout 
        = vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__Vfuncout;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__66__I 
        = vlTOPp->SOC__DOT__CPU__DOT__mw_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__66__Vfuncout 
        = (3U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__66__I));
    vlTOPp->SOC__DOT__CPU__DOT__wb_DATA = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLoad__66__Vfuncout)
                                            ? ((0x400000U 
                                                & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                                ? vlTOPp->SOC__DOT__CPU__DOT__mw_IO_RES
                                                : (
                                                   (0U 
                                                    == 
                                                    (3U 
                                                     & (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_funct3)))
                                                    ? 
                                                   ((0xffffff00U 
                                                     & ((- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_load_sign))) 
                                                        << 8U)) 
                                                    | (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadB))
                                                    : 
                                                   ((1U 
                                                     == 
                                                     (3U 
                                                      & (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_funct3)))
                                                     ? 
                                                    ((0xffff0000U 
                                                      & ((- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_load_sign))) 
                                                         << 0x10U)) 
                                                     | (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH))
                                                     : vlTOPp->SOC__DOT__mem_data)))
                                            : ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__Vfuncout)
                                                ? vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES
                                                : vlTOPp->SOC__DOT__CPU__DOT__mw_RES));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__56__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__56__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__56__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_ADDR = ((0xfffffffeU 
                                           & vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES) 
                                          | (1U & (vlTOPp->SOC__DOT__CPU__DOT__e_ADDR_RES 
                                                   & (~ (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__56__Vfuncout)))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
        = (IData)((0x1ffffffffULL & VL_SHIFTRS_QQI(33,33,5, 
                                                   (((QData)((IData)(
                                                                     (1U 
                                                                      & ((vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                          >> 0x1eU) 
                                                                         & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                                            >> 0x1fU))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      ((1U 
                                                                        == 
                                                                        (7U 
                                                                         & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                                            >> 0xcU)))
                                                                        ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__a_flipped
                                                                        : vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)))), 
                                                   (0x1fU 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
        = (0x1ffffffffULL & (((QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)) 
                              + (((QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus)) 
                                  << 0x20U) | (QData)((IData)(
                                                              (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 
                                                               ^ 
                                                               (- (IData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus)))))))) 
                             + (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__minus))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__left_shift 
        = ((0x80000000U & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                           << 0x1fU)) | ((0x40000000U 
                                          & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                             << 0x1dU)) 
                                         | ((0x20000000U 
                                             & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                << 0x1bU)) 
                                            | ((0x10000000U 
                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                   << 0x19U)) 
                                               | ((0x8000000U 
                                                   & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                      << 0x17U)) 
                                                  | ((0x4000000U 
                                                      & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                         << 0x15U)) 
                                                     | ((0x2000000U 
                                                         & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                            << 0x13U)) 
                                                        | ((0x1000000U 
                                                            & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                               << 0x11U)) 
                                                           | ((0x800000U 
                                                               & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                  << 0xfU)) 
                                                              | ((0x400000U 
                                                                  & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                     << 0xdU)) 
                                                                 | ((0x200000U 
                                                                     & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                        << 0xbU)) 
                                                                    | ((0x100000U 
                                                                        & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                           << 9U)) 
                                                                       | ((0x80000U 
                                                                           & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                              << 7U)) 
                                                                          | ((0x40000U 
                                                                              & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 5U)) 
                                                                             | ((0x20000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 3U)) 
                                                                                | ((0x10000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                << 1U)) 
                                                                                | ((0x8000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 1U)) 
                                                                                | ((0x4000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 3U)) 
                                                                                | ((0x2000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 5U)) 
                                                                                | ((0x1000U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 7U)) 
                                                                                | ((0x800U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 9U)) 
                                                                                | ((0x400U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xbU)) 
                                                                                | ((0x200U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xdU)) 
                                                                                | ((0x100U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0xfU)) 
                                                                                | ((0x80U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x11U)) 
                                                                                | ((0x40U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x13U)) 
                                                                                | ((0x20U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x15U)) 
                                                                                | ((0x10U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x17U)) 
                                                                                | ((8U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x19U)) 
                                                                                | ((4U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1bU)) 
                                                                                | ((2U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1dU)) 
                                                                                | (1U 
                                                                                & (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift 
                                                                                >> 0x1fU)))))))))))))))))))))))))))))))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT = (1U 
                                                 & ((0x80000000U 
                                                     & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                        ^ vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))
                                                     ? 
                                                    (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                     >> 0x1fU)
                                                     : (IData)(
                                                               (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                                >> 0x20U))));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__Vfuncout 
        = ((0x33U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__I)) 
           & (vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__I 
              >> 0x19U));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__52__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__52__Vfuncout 
        = (0x37U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__52__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_RES = ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isLUI__52__Vfuncout)
                                          ? vlTOPp->SOC__DOT__CPU__DOT__e_IMM
                                          : ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__Vfuncout)
                                              ? ((0x4000U 
                                                  & vlTOPp->SOC__DOT__CPU__DOT__de_IR)
                                                  ? vlTOPp->SOC__DOT__pcpi_div_rd
                                                  : (IData)(
                                                            ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__shift_out)
                                                              ? 
                                                             (vlTOPp->SOC__DOT__pcpi_mul__DOT__rd 
                                                              >> 0x20U)
                                                              : vlTOPp->SOC__DOT__pcpi_mul__DOT__rd)))
                                              : ((4U 
                                                  & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                  ? 
                                                 ((2U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                    ? 
                                                   (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                    & vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)
                                                    : 
                                                   (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                    | vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))
                                                   : 
                                                  ((1U 
                                                    & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                    ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__right_shift
                                                    : 
                                                   (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                                                    ^ vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)))
                                                  : 
                                                 ((2U 
                                                   & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                    ? 
                                                   (1U 
                                                    & (IData)(
                                                              (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                               >> 0x20U)))
                                                    : (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT))
                                                   : 
                                                  ((1U 
                                                    & (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__d_result))
                                                    ? vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__left_shift
                                                    : (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result))))));
    vlTOPp->__Vtableidx1 = ((0x80U & ((~ (IData)((0U 
                                                  != (IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result)))) 
                                      << 7U)) | ((0x70U 
                                                  & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                     >> 8U)) 
                                                 | (((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__t_LT) 
                                                     << 3U) 
                                                    | ((4U 
                                                        & ((IData)(
                                                                   (vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result 
                                                                    >> 0x20U)) 
                                                           << 2U)) 
                                                       | (3U 
                                                          & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                             >> 0xdU))))));
    vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__i_take_b = 
        vlTOPp->__Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b
        [vlTOPp->__Vtableidx1];
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__59__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__59__Vfuncout 
        = (0x63U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__59__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__58__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__58__Vfuncout 
        = (0x67U == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__58__I));
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__57__I 
        = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
    vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__57__Vfuncout 
        = (0x6fU == (0x7fU & vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__57__I));
    vlTOPp->SOC__DOT__CPU__DOT__e_JoB = (((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJAL__57__Vfuncout) 
                                          | (IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isJALR__58__Vfuncout)) 
                                         | ((IData)(vlTOPp->__Vfunc_SOC__DOT__CPU__DOT__isBtype__59__Vfuncout) 
                                            & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__u0__DOT__i_take_b) 
                                               ^ (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                                  >> 0xcU))));
    vlTOPp->SOC__DOT__CPU__DOT__e_flush = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_JoB) 
                                           | ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                              & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ))));
}

void VSOC::_eval_initial(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_initial\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__SOC__DOT__RESET 
        = vlTOPp->__VinpClk__TOP__SOC__DOT__RESET;
    vlTOPp->_initial__TOP__3(vlSymsp);
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
    vlTOPp->_settle__TOP__4(vlSymsp);
}

void VSOC::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_ctor_var_reset\n"); );
    // Body
    CLK = VL_RAND_RESET_I(1);
    LEDS = VL_RAND_RESET_I(6);
    UART_TX = VL_RAND_RESET_I(1);
    SOC__DOT__imem_data = VL_RAND_RESET_I(32);
    SOC__DOT__mem_data = VL_RAND_RESET_I(32);
    SOC__DOT__pcpi_valid = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div_rd = VL_RAND_RESET_I(32);
    SOC__DOT__pcpi_div_wait = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div_ready = VL_RAND_RESET_I(1);
    SOC__DOT__IO_mem_wr = VL_RAND_RESET_I(1);
    SOC__DOT__uart_valid = VL_RAND_RESET_I(1);
    SOC__DOT__uart_ready = VL_RAND_RESET_I(1);
    SOC__DOT__resetn = VL_RAND_RESET_I(1);
    SOC__DOT__RESET = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__rs1_HAZ = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__rs2_HAZ = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__mul_HAZ = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__data_HAZ = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__f_stall = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__d_stall = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__e_flush = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__f_PC = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__fd_PC = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__fd_NOP = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__wb_enable = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__wb_DATA = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__wb_rdID = VL_RAND_RESET_I(5);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            SOC__DOT__CPU__DOT__reg_file[__Vi0] = VL_RAND_RESET_I(32);
    }}
    SOC__DOT__CPU__DOT__de_IR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__de_PC = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__de_rs1 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__de_rs2 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_IMM = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_ALUin1 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_ALUin2 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_ADDin1 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_ADDR_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_ADDR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__e_JoB = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__e_rs2 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__em_IR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__em_rs2 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__em_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__em_ADDR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__m_funct3 = VL_RAND_RESET_I(3);
    SOC__DOT__CPU__DOT__m_store_DATA = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__m_WMASK = VL_RAND_RESET_I(4);
    SOC__DOT__CPU__DOT__cycle = VL_RAND_RESET_Q(64);
    SOC__DOT__CPU__DOT__instret = VL_RAND_RESET_Q(64);
    SOC__DOT__CPU__DOT__mw_IR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__mw_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__mw_IO_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__mw_ADDR = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__mw_CSR_RES = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__mw_rs2 = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__w_funct3 = VL_RAND_RESET_I(3);
    SOC__DOT__CPU__DOT__w_loadH = VL_RAND_RESET_I(16);
    SOC__DOT__CPU__DOT__w_loadB = VL_RAND_RESET_I(8);
    SOC__DOT__CPU__DOT__w_load_sign = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__wb_csr = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__wb_csr_en = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__MEPC = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__MTVEC = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__MCAUSE = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__MSTATUS = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__m0__DOT__Itype = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__m0__DOT__Utype = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__u0__DOT__d_result = VL_RAND_RESET_I(3);
    SOC__DOT__CPU__DOT__u0__DOT__t_LT = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__u0__DOT__minus = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__u0__DOT__a_flipped = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__u0__DOT__right_shift = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__u0__DOT__left_shift = VL_RAND_RESET_I(32);
    SOC__DOT__CPU__DOT__u0__DOT__i_take_b = VL_RAND_RESET_I(1);
    SOC__DOT__CPU__DOT__u0__DOT__s0__DOT__result = VL_RAND_RESET_Q(33);
    SOC__DOT__pcpi_mul__DOT__instr_mul = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_mul__DOT__instr_mulh = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_mul__DOT__instr_mulhsu = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_mul__DOT__instr_mulhu = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_mul__DOT__shift_out = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_mul__DOT__active = VL_RAND_RESET_I(4);
    SOC__DOT__pcpi_mul__DOT__rs1 = VL_RAND_RESET_Q(33);
    SOC__DOT__pcpi_mul__DOT__rs2 = VL_RAND_RESET_Q(33);
    SOC__DOT__pcpi_mul__DOT__rd = VL_RAND_RESET_Q(64);
    SOC__DOT__pcpi_mul__DOT__pcpi_insn_valid = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__instr_div = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__instr_divu = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__instr_rem = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__instr_remu = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__pcpi_wait_q = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__start = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__dividend = VL_RAND_RESET_I(32);
    SOC__DOT__pcpi_div__DOT__divisor = VL_RAND_RESET_Q(63);
    SOC__DOT__pcpi_div__DOT__quotient = VL_RAND_RESET_I(32);
    SOC__DOT__pcpi_div__DOT__quotient_msk = VL_RAND_RESET_I(32);
    SOC__DOT__pcpi_div__DOT__running = VL_RAND_RESET_I(1);
    SOC__DOT__pcpi_div__DOT__outsign = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<65536; ++__Vi0) {
            SOC__DOT__DATA__DOT__RAM[__Vi0] = VL_RAND_RESET_I(32);
    }}
    SOC__DOT__UART__DOT__cnt = VL_RAND_RESET_I(5);
    SOC__DOT__UART__DOT__data = VL_RAND_RESET_I(10);
    SOC__DOT__CW__DOT__reset_cnt = VL_RAND_RESET_I(16);
    __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__reads_rs1__0__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__1__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__2__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__3__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__4__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__4__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__5__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__6__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__7__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__7__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__8__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__8__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__9__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__9__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__10__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__10__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__11__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__11__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__12__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__13__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__13__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__14__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__14__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__15__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__16__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__16__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__17__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isLUI__18__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isLUI__18__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__reads_rs2__19__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__20__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__21__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__22__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__23__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__23__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__24__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__25__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__26__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__26__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__27__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__27__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__28__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__28__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__29__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__29__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__30__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__30__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__31__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__31__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__32__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__32__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__33__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__33__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__34__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__34__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isRtype__35__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isRtype__35__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__36__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__37__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__37__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__38__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs1ID__42__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rs2ID__43__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__44__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__44__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__45__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__45__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__46__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isRtype__47__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isRtype__47__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__48__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__48__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isRimm__49__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isRimm__49__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isAUIPC__50__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__51__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isLUI__52__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isLUI__52__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isMulDiv__53__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__54__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__54__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__55__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__56__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__56__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__57__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJAL__57__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__58__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isJALR__58__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__59__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__59__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__60__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__61__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__funct3__62__Vfuncout = VL_RAND_RESET_I(3);
    __Vfunc_SOC__DOT__CPU__DOT__funct3__62__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__63__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__63__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__64__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__64__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__funct3__65__Vfuncout = VL_RAND_RESET_I(3);
    __Vfunc_SOC__DOT__CPU__DOT__funct3__65__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isLoad__66__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isLoad__66__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__67__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__68__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__writes_rd__69__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__70__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__70__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__71__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__71__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__72__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__72__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__73__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__73__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__74__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__74__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__75__Vfuncout = VL_RAND_RESET_I(5);
    __Vfunc_SOC__DOT__CPU__DOT__rdID__75__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__76__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isBtype__76__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__77__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isStype__77__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isCSRRS__78__I = VL_RAND_RESET_I(32);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__Vfuncout = VL_RAND_RESET_I(1);
    __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__79__I = VL_RAND_RESET_I(32);
    __Vtableidx1 = 0;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[0] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[1] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[2] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[3] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[4] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[5] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[6] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[7] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[8] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[9] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[10] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[11] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[12] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[13] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[14] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[15] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[16] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[17] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[18] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[19] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[20] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[21] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[22] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[23] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[24] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[25] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[26] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[27] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[28] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[29] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[30] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[31] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[32] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[33] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[34] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[35] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[36] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[37] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[38] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[39] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[40] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[41] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[42] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[43] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[44] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[45] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[46] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[47] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[48] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[49] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[50] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[51] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[52] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[53] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[54] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[55] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[56] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[57] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[58] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[59] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[60] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[61] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[62] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[63] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[64] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[65] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[66] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[67] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[68] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[69] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[70] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[71] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[72] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[73] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[74] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[75] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[76] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[77] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[78] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[79] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[80] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[81] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[82] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[83] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[84] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[85] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[86] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[87] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[88] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[89] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[90] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[91] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[92] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[93] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[94] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[95] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[96] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[97] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[98] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[99] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[100] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[101] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[102] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[103] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[104] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[105] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[106] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[107] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[108] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[109] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[110] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[111] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[112] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[113] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[114] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[115] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[116] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[117] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[118] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[119] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[120] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[121] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[122] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[123] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[124] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[125] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[126] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[127] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[128] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[129] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[130] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[131] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[132] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[133] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[134] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[135] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[136] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[137] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[138] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[139] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[140] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[141] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[142] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[143] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[144] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[145] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[146] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[147] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[148] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[149] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[150] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[151] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[152] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[153] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[154] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[155] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[156] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[157] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[158] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[159] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[160] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[161] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[162] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[163] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[164] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[165] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[166] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[167] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[168] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[169] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[170] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[171] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[172] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[173] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[174] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[175] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[176] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[177] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[178] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[179] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[180] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[181] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[182] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[183] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[184] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[185] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[186] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[187] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[188] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[189] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[190] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[191] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[192] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[193] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[194] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[195] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[196] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[197] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[198] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[199] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[200] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[201] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[202] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[203] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[204] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[205] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[206] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[207] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[208] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[209] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[210] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[211] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[212] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[213] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[214] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[215] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[216] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[217] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[218] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[219] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[220] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[221] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[222] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[223] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[224] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[225] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[226] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[227] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[228] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[229] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[230] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[231] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[232] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[233] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[234] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[235] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[236] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[237] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[238] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[239] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[240] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[241] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[242] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[243] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[244] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[245] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[246] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[247] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[248] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[249] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[250] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[251] = 0U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[252] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[253] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[254] = 1U;
    __Vtable1_SOC__DOT__CPU__DOT__u0__DOT__i_take_b[255] = 1U;
    __VinpClk__TOP__SOC__DOT__RESET = VL_RAND_RESET_I(1);
    __Vchglast__TOP__SOC__DOT__RESET = VL_RAND_RESET_I(1);
}
