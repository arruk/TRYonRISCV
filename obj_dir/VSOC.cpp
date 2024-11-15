// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSOC.h for the primary calling header

#include "VSOC.h"
#include "VSOC__Syms.h"

//==========

void VSOC::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VSOC::eval\n"); );
    VSOC__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("soc.v", 7, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void VSOC::_eval_initial_loop(VSOC__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
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
            VL_FATAL_MT("soc.v", 7, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void VSOC::_sequent__TOP__1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__Vfuncout;
    CData/*0:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__Vfuncout;
    CData/*2:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__41__Vfuncout;
    CData/*4:0*/ __Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0;
    CData/*3:0*/ __Vdly__SOC__DOT__pcpi_mul__DOT__active;
    CData/*0:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__instr_div;
    CData/*0:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__instr_divu;
    CData/*0:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__instr_rem;
    CData/*0:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__running;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v0;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v0;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v0;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v1;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v1;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v1;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v2;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v2;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v2;
    CData/*4:0*/ __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v3;
    CData/*7:0*/ __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v3;
    CData/*0:0*/ __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v3;
    CData/*0:0*/ __Vdly__SOC__DOT__uart_ready;
    CData/*4:0*/ __Vdly__SOC__DOT__UART__DOT__cnt;
    SData/*15:0*/ __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v0;
    SData/*15:0*/ __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v1;
    SData/*15:0*/ __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v2;
    SData/*15:0*/ __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v3;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__I;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__I;
    IData/*31:0*/ __Vfunc_SOC__DOT__CPU__DOT__funct3__41__I;
    IData/*31:0*/ __Vdly__SOC__DOT__CPU__DOT__f_PC;
    IData/*31:0*/ __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
    IData/*31:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__dividend;
    IData/*31:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__quotient;
    IData/*31:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__quotient_msk;
    IData/*31:0*/ __Vtemp2;
    QData/*62:0*/ __Vdly__SOC__DOT__pcpi_div__DOT__divisor;
    // Body
    __Vdly__SOC__DOT__uart_ready = vlTOPp->SOC__DOT__uart_ready;
    __Vdly__SOC__DOT__UART__DOT__cnt = vlTOPp->SOC__DOT__UART__DOT__cnt;
    __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v0 = 0U;
    __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v1 = 0U;
    __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v2 = 0U;
    __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v3 = 0U;
    __Vdly__SOC__DOT__pcpi_mul__DOT__active = vlTOPp->SOC__DOT__pcpi_mul__DOT__active;
    __Vdly__SOC__DOT__pcpi_div__DOT__quotient_msk = vlTOPp->SOC__DOT__pcpi_div__DOT__quotient_msk;
    __Vdly__SOC__DOT__pcpi_div__DOT__quotient = vlTOPp->SOC__DOT__pcpi_div__DOT__quotient;
    __Vdly__SOC__DOT__pcpi_div__DOT__divisor = vlTOPp->SOC__DOT__pcpi_div__DOT__divisor;
    __Vdly__SOC__DOT__pcpi_div__DOT__dividend = vlTOPp->SOC__DOT__pcpi_div__DOT__dividend;
    __Vdly__SOC__DOT__pcpi_div__DOT__running = vlTOPp->SOC__DOT__pcpi_div__DOT__running;
    __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0 = 0U;
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_rem = vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem;
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_divu = vlTOPp->SOC__DOT__pcpi_div__DOT__instr_divu;
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_div = vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div;
    __Vdly__SOC__DOT__CPU__DOT__f_PC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
    if (VL_UNLIKELY(vlTOPp->SOC__DOT__uart_valid)) {
        VL_WRITEF("%c",8,(0xffU & vlTOPp->SOC__DOT__CPU__DOT__em_rs2));
        if (0x80000001U) { VL_FFLUSH_I(0x80000001U); }
    }
    if (VL_UNLIKELY(((IData)(vlTOPp->SOC__DOT__IO_mem_wr) 
                     & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 5U)))) {
        VL_FINISH_MT("soc.v", 175, "");
    }
    vlTOPp->SOC__DOT__pcpi_mul__DOT__shift_out = ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh) 
                                                  | ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhsu) 
                                                     | (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhu)));
    vlTOPp->SOC__DOT__CPU__DOT__mw_RES = vlTOPp->SOC__DOT__CPU__DOT__em_RES;
    vlTOPp->SOC__DOT__CPU__DOT__mw_rs2 = vlTOPp->SOC__DOT__CPU__DOT__em_rs2;
    if ((1U & (((IData)(vlTOPp->SOC__DOT__UART__DOT__cnt) 
                >> 4U) & (~ (IData)((0U != (IData)(vlTOPp->SOC__DOT__UART__DOT__data))))))) {
        __Vdly__SOC__DOT__uart_ready = 1U;
    } else {
        if (((IData)(vlTOPp->SOC__DOT__uart_valid) 
             & (IData)(vlTOPp->SOC__DOT__uart_ready))) {
            __Vdly__SOC__DOT__uart_ready = 0U;
        }
    }
    __Vdly__SOC__DOT__UART__DOT__cnt = ((1U & ((IData)(vlTOPp->SOC__DOT__uart_ready) 
                                               | ((IData)(vlTOPp->SOC__DOT__UART__DOT__cnt) 
                                                  >> 4U)))
                                         ? 0xaU : (0x1fU 
                                                   & ((IData)(vlTOPp->SOC__DOT__UART__DOT__cnt) 
                                                      - (IData)(1U))));
    if ((0x10U & (IData)(vlTOPp->SOC__DOT__UART__DOT__cnt))) {
        vlTOPp->SOC__DOT__UART__DOT__data = (0x1ffU 
                                             & ((IData)(vlTOPp->SOC__DOT__UART__DOT__data) 
                                                >> 1U));
    } else {
        if (((IData)(vlTOPp->SOC__DOT__uart_valid) 
             & (IData)(vlTOPp->SOC__DOT__uart_ready))) {
            vlTOPp->SOC__DOT__UART__DOT__data = (0x200U 
                                                 | (0x1feU 
                                                    & (vlTOPp->SOC__DOT__CPU__DOT__em_rs2 
                                                       << 1U)));
        }
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_IO_RES = ((0x10U 
                                              & vlTOPp->SOC__DOT__CPU__DOT__em_ADDR)
                                              ? (0x200U 
                                                 & ((~ (IData)(vlTOPp->SOC__DOT__uart_ready)) 
                                                    << 9U))
                                              : 0U);
    if ((1U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v0 = 
            (0xffU & vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA);
        __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v0 = 1U;
        __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v0 = 0U;
        __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v0 = 
            (0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((2U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v1 = 
            (0xffU & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                      >> 8U));
        __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v1 = 1U;
        __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v1 = 8U;
        __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v1 = 
            (0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((4U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v2 = 
            (0xffU & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                      >> 0x10U));
        __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v2 = 1U;
        __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v2 = 0x10U;
        __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v2 = 
            (0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    if ((8U & (IData)(vlTOPp->SOC__DOT__CPU__DOT__m_WMASK))) {
        __Vdlyvval__SOC__DOT__DATA__DOT__RAM__v3 = 
            (0xffU & (vlTOPp->SOC__DOT__CPU__DOT__m_store_DATA 
                      >> 0x18U));
        __Vdlyvset__SOC__DOT__DATA__DOT__RAM__v3 = 1U;
        __Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v3 = 0x18U;
        __Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v3 = 
            (0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                        >> 2U));
    }
    vlTOPp->SOC__DOT__mem_data = vlTOPp->SOC__DOT__DATA__DOT__RAM
        [(0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__em_ADDR 
                     >> 2U))];
    vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR = vlTOPp->SOC__DOT__CPU__DOT__em_ADDR;
    vlTOPp->SOC__DOT__pcpi_mul__DOT__rd = VL_MULS_QQQ(64,64,64, 
                                                      VL_EXTENDS_QQ(64,33, vlTOPp->SOC__DOT__pcpi_mul__DOT__rs1), 
                                                      VL_EXTENDS_QQ(64,33, vlTOPp->SOC__DOT__pcpi_mul__DOT__rs2));
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_enable) {
        __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0 
            = vlTOPp->SOC__DOT__CPU__DOT__wb_DATA;
        __Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0 = 1U;
        __Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0 
            = vlTOPp->SOC__DOT__CPU__DOT__wb_rdID;
    }
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_rem = 0U;
    if ((((((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
            & (IData)(vlTOPp->SOC__DOT__pcpi_valid)) 
           & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div_ready))) 
          & (0x33U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
         & (1U == (0x7fU & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                            >> 0x19U))))) {
        if ((4U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((5U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                if ((6U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                  >> 0xcU)))) {
                    __Vdly__SOC__DOT__pcpi_div__DOT__instr_rem = 1U;
                }
            }
        }
    }
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_divu = 0U;
    if ((((((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
            & (IData)(vlTOPp->SOC__DOT__pcpi_valid)) 
           & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div_ready))) 
          & (0x33U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
         & (1U == (0x7fU & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                            >> 0x19U))))) {
        if ((4U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((5U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                __Vdly__SOC__DOT__pcpi_div__DOT__instr_divu = 1U;
            }
        }
    }
    __Vdly__SOC__DOT__pcpi_div__DOT__instr_div = 0U;
    if ((((((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
            & (IData)(vlTOPp->SOC__DOT__pcpi_valid)) 
           & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div_ready))) 
          & (0x33U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
         & (1U == (0x7fU & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                            >> 0x19U))))) {
        if ((4U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            __Vdly__SOC__DOT__pcpi_div__DOT__instr_div = 1U;
        }
    }
    vlTOPp->SOC__DOT__pcpi_div__DOT__pcpi_wait_q = 
        ((IData)(vlTOPp->SOC__DOT__pcpi_div_wait) & 
         (0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)));
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_PC = vlTOPp->SOC__DOT__CPU__DOT__fd_PC;
    }
    __Vtemp2 = (((((((((0xc00U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                             >> 0x14U))) 
                       | (0xc02U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                               >> 0x14U)))) 
                      | (0xc80U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                              >> 0x14U)))) 
                     | (0xc82U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                             >> 0x14U)))) 
                    | (0x300U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                            >> 0x14U)))) 
                   | (0x305U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                           >> 0x14U)))) 
                  | (0x341U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                          >> 0x14U)))) 
                 | (0x342U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                         >> 0x14U))))
                 ? ((0xc00U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                          >> 0x14U)))
                     ? (IData)(vlTOPp->SOC__DOT__CPU__DOT__cycle)
                     : ((0xc02U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                              >> 0x14U)))
                         ? (IData)(vlTOPp->SOC__DOT__CPU__DOT__instret)
                         : ((0xc80U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                  >> 0x14U)))
                             ? (IData)((vlTOPp->SOC__DOT__CPU__DOT__cycle 
                                        >> 0x20U)) : 
                            ((0xc82U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                   >> 0x14U)))
                              ? (IData)((vlTOPp->SOC__DOT__CPU__DOT__instret 
                                         >> 0x20U))
                              : ((0x300U == (0xfffU 
                                             & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                >> 0x14U)))
                                  ? vlTOPp->SOC__DOT__CPU__DOT__MSTATUS
                                  : ((0x305U == (0xfffU 
                                                 & (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                                    >> 0x14U)))
                                      ? vlTOPp->SOC__DOT__CPU__DOT__MTVEC
                                      : ((0x341U == 
                                          (0xfffU & 
                                           (vlTOPp->SOC__DOT__CPU__DOT__em_IR 
                                            >> 0x14U)))
                                          ? vlTOPp->SOC__DOT__CPU__DOT__MEPC
                                          : vlTOPp->SOC__DOT__CPU__DOT__MCAUSE)))))))
                 : vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES);
    vlTOPp->SOC__DOT__CPU__DOT__mw_CSR_RES = __Vtemp2;
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt))) {
        if ((0x33U != vlTOPp->SOC__DOT__CPU__DOT__mw_IR)) {
            vlTOPp->SOC__DOT__CPU__DOT__instret = (1ULL 
                                                   + vlTOPp->SOC__DOT__CPU__DOT__instret);
        }
    } else {
        vlTOPp->SOC__DOT__CPU__DOT__instret = 0ULL;
    }
    vlTOPp->SOC__DOT__CPU__DOT__cycle = ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt))
                                          ? (1ULL + vlTOPp->SOC__DOT__CPU__DOT__cycle)
                                          : 0ULL);
    vlTOPp->SOC__DOT__UART__DOT__cnt = __Vdly__SOC__DOT__UART__DOT__cnt;
    vlTOPp->SOC__DOT__uart_ready = __Vdly__SOC__DOT__uart_ready;
    if (__Vdlyvset__SOC__DOT__CPU__DOT__reg_file__v0) {
        vlTOPp->SOC__DOT__CPU__DOT__reg_file[__Vdlyvdim0__SOC__DOT__CPU__DOT__reg_file__v0] 
            = __Vdlyvval__SOC__DOT__CPU__DOT__reg_file__v0;
    }
    vlTOPp->SOC__DOT__CPU__DOT__em_RES = vlTOPp->SOC__DOT__CPU__DOT__e_RES;
    vlTOPp->UART_TX = (1U & ((IData)(vlTOPp->SOC__DOT__UART__DOT__data) 
                             | (~ (IData)((0U != (IData)(vlTOPp->SOC__DOT__UART__DOT__data))))));
    vlTOPp->SOC__DOT__CPU__DOT__em_rs2 = vlTOPp->SOC__DOT__CPU__DOT__e_rs2;
    vlTOPp->SOC__DOT__CPU__DOT__em_ADDR = vlTOPp->SOC__DOT__CPU__DOT__e_ADDR;
    vlTOPp->SOC__DOT__CPU__DOT__w_loadH = (0xffffU 
                                           & ((2U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                               ? (vlTOPp->SOC__DOT__mem_data 
                                                  >> 0x10U)
                                               : vlTOPp->SOC__DOT__mem_data));
    if ((((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mul) 
          | ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh) 
             | ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhsu) 
                | (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhu)))) 
         & (~ (IData)((0U != (3U & (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__active))))))) {
        vlTOPp->SOC__DOT__pcpi_mul__DOT__rs1 = (0x1ffffffffULL 
                                                & (((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh) 
                                                    | (IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulhsu))
                                                    ? 
                                                   VL_EXTENDS_QI(33,32, vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)
                                                    : (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1))));
        vlTOPp->SOC__DOT__pcpi_mul__DOT__rs2 = (0x1ffffffffULL 
                                                & ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__instr_mulh)
                                                    ? 
                                                   VL_EXTENDS_QI(33,32, vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)
                                                    : (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))));
        __Vdly__SOC__DOT__pcpi_mul__DOT__active = (1U 
                                                   | (IData)(__Vdly__SOC__DOT__pcpi_mul__DOT__active));
    } else {
        __Vdly__SOC__DOT__pcpi_mul__DOT__active = (0xeU 
                                                   & (IData)(__Vdly__SOC__DOT__pcpi_mul__DOT__active));
    }
    __Vdly__SOC__DOT__pcpi_mul__DOT__active = ((1U 
                                                & (IData)(__Vdly__SOC__DOT__pcpi_mul__DOT__active)) 
                                               | (0xeU 
                                                  & ((IData)(vlTOPp->SOC__DOT__pcpi_mul__DOT__active) 
                                                     << 1U)));
    if ((1U & (~ (IData)((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)))))) {
        __Vdly__SOC__DOT__pcpi_mul__DOT__active = 0U;
    }
    vlTOPp->SOC__DOT__pcpi_div_wait = (((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div) 
                                        | ((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_divu) 
                                           | ((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem) 
                                              | (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_remu)))) 
                                       & (0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)));
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_csr_en) {
        if ((0x300U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                  >> 0x14U)))) {
            vlTOPp->SOC__DOT__CPU__DOT__MSTATUS = vlTOPp->SOC__DOT__CPU__DOT__wb_csr;
        }
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_csr_en) {
        if ((0x300U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                  >> 0x14U)))) {
            if ((0x305U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                      >> 0x14U)))) {
                if ((0x341U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                          >> 0x14U)))) {
                    if ((0x342U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                              >> 0x14U)))) {
                        vlTOPp->SOC__DOT__CPU__DOT__MCAUSE 
                            = vlTOPp->SOC__DOT__CPU__DOT__wb_csr;
                    }
                }
            }
        }
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_csr_en) {
        if ((0x300U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                  >> 0x14U)))) {
            if ((0x305U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                      >> 0x14U)))) {
                if ((0x341U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                          >> 0x14U)))) {
                    vlTOPp->SOC__DOT__CPU__DOT__MEPC 
                        = vlTOPp->SOC__DOT__CPU__DOT__wb_csr;
                }
            }
        }
    }
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        if ((0U != (3U & vlTOPp->SOC__DOT__CPU__DOT__f_PC))) {
            vlTOPp->SOC__DOT__CPU__DOT__MCAUSE = 1U;
            vlTOPp->SOC__DOT__CPU__DOT__MEPC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
            __Vdly__SOC__DOT__CPU__DOT__f_PC = vlTOPp->SOC__DOT__CPU__DOT__MTVEC;
        } else {
            vlTOPp->SOC__DOT__CPU__DOT__fd_PC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
            __Vdly__SOC__DOT__CPU__DOT__f_PC = ((IData)(4U) 
                                                + vlTOPp->SOC__DOT__CPU__DOT__f_PC);
        }
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__e_JoB) {
        __Vdly__SOC__DOT__CPU__DOT__f_PC = vlTOPp->SOC__DOT__CPU__DOT__e_ADDR;
    }
    if ((1U & (~ (IData)((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)))))) {
        __Vdly__SOC__DOT__CPU__DOT__f_PC = 0x20000U;
    }
    if ((((((((((((0x13U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)) 
                  & (0x33U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
                 & (3U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
                & (0x23U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
               & (0x63U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
              & (0x67U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
             & (0x6fU != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
            & (0x17U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
           & (0x37U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
          & (0xfU != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
         & (0x73U != (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR)))) {
        vlTOPp->SOC__DOT__CPU__DOT__MCAUSE = 2U;
        vlTOPp->SOC__DOT__CPU__DOT__MEPC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
        __Vdly__SOC__DOT__CPU__DOT__f_PC = vlTOPp->SOC__DOT__CPU__DOT__MTVEC;
    } else {
        __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__I 
            = vlTOPp->SOC__DOT__CPU__DOT__de_IR;
        __Vfunc_SOC__DOT__CPU__DOT__funct3__41__I = __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__I;
        __Vfunc_SOC__DOT__CPU__DOT__funct3__41__Vfuncout 
            = (7U & (__Vfunc_SOC__DOT__CPU__DOT__funct3__41__I 
                     >> 0xcU));
        __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__I 
            = __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__I;
        __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__Vfuncout 
            = (0x73U == (0x7fU & __Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__I));
        __Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__Vfuncout 
            = ((IData)(__Vfunc_SOC__DOT__CPU__DOT__isSYSTEM__40__Vfuncout) 
               & (0U == (IData)(__Vfunc_SOC__DOT__CPU__DOT__funct3__41__Vfuncout)));
        if (__Vfunc_SOC__DOT__CPU__DOT__isEBREAK__39__Vfuncout) {
            vlTOPp->SOC__DOT__CPU__DOT__MCAUSE = 3U;
            vlTOPp->SOC__DOT__CPU__DOT__MEPC = vlTOPp->SOC__DOT__CPU__DOT__f_PC;
            __Vdly__SOC__DOT__CPU__DOT__f_PC = vlTOPp->SOC__DOT__CPU__DOT__MTVEC;
        }
    }
    vlTOPp->SOC__DOT__CPU__DOT__w_loadB = (0xffU & 
                                           ((1U & vlTOPp->SOC__DOT__CPU__DOT__mw_ADDR)
                                             ? ((IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH) 
                                                >> 8U)
                                             : (IData)(vlTOPp->SOC__DOT__CPU__DOT__w_loadH)));
    vlTOPp->SOC__DOT__pcpi_mul__DOT__active = __Vdly__SOC__DOT__pcpi_mul__DOT__active;
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
    vlTOPp->SOC__DOT__pcpi_div__DOT__instr_remu = 0U;
    if ((((((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt)) 
            & (IData)(vlTOPp->SOC__DOT__pcpi_valid)) 
           & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div_ready))) 
          & (0x33U == (0x7fU & vlTOPp->SOC__DOT__CPU__DOT__de_IR))) 
         & (1U == (0x7fU & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                            >> 0x19U))))) {
        if ((4U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                          >> 0xcU)))) {
            if ((5U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                              >> 0xcU)))) {
                if ((6U != (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                  >> 0xcU)))) {
                    if ((7U == (7U & (vlTOPp->SOC__DOT__CPU__DOT__de_IR 
                                      >> 0xcU)))) {
                        vlTOPp->SOC__DOT__pcpi_div__DOT__instr_remu = 1U;
                    }
                }
            }
        }
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__wb_csr_en) {
        if ((0x300U != (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                  >> 0x14U)))) {
            if ((0x305U == (0xfffU & (vlTOPp->SOC__DOT__CPU__DOT__mw_IR 
                                      >> 0x14U)))) {
                vlTOPp->SOC__DOT__CPU__DOT__MTVEC = vlTOPp->SOC__DOT__CPU__DOT__wb_csr;
            }
        }
    }
    vlTOPp->SOC__DOT__pcpi_div_ready = 0U;
    vlTOPp->SOC__DOT__pcpi_div_rd = 0U;
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt))) {
        if (vlTOPp->SOC__DOT__pcpi_div__DOT__start) {
            __Vdly__SOC__DOT__pcpi_div__DOT__running = 1U;
            __Vdly__SOC__DOT__pcpi_div__DOT__dividend 
                = ((((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div) 
                     | (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem)) 
                    & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                       >> 0x1fU)) ? (- vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1)
                    : vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1);
            __Vdly__SOC__DOT__pcpi_div__DOT__divisor 
                = (0x7fffffffffffffffULL & (((((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div) 
                                               | (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem)) 
                                              & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 
                                                 >> 0x1fU))
                                              ? (- (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)))
                                              : (QData)((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2))) 
                                            << 0x1fU));
            __Vdly__SOC__DOT__pcpi_div__DOT__quotient = 0U;
            __Vdly__SOC__DOT__pcpi_div__DOT__quotient_msk = 0x80000000U;
        } else {
            if (((~ (IData)((0U != vlTOPp->SOC__DOT__pcpi_div__DOT__quotient_msk))) 
                 & (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__running))) {
                __Vdly__SOC__DOT__pcpi_div__DOT__running = 0U;
                vlTOPp->SOC__DOT__pcpi_div_ready = 1U;
                vlTOPp->SOC__DOT__pcpi_div_rd = (((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div) 
                                                  | (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_divu))
                                                  ? 
                                                 ((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__outsign)
                                                   ? 
                                                  (- vlTOPp->SOC__DOT__pcpi_div__DOT__quotient)
                                                   : vlTOPp->SOC__DOT__pcpi_div__DOT__quotient)
                                                  : 
                                                 ((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__outsign)
                                                   ? 
                                                  (- vlTOPp->SOC__DOT__pcpi_div__DOT__dividend)
                                                   : vlTOPp->SOC__DOT__pcpi_div__DOT__dividend));
            } else {
                if ((vlTOPp->SOC__DOT__pcpi_div__DOT__divisor 
                     <= (QData)((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__dividend)))) {
                    __Vdly__SOC__DOT__pcpi_div__DOT__dividend 
                        = (vlTOPp->SOC__DOT__pcpi_div__DOT__dividend 
                           - (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__divisor));
                    __Vdly__SOC__DOT__pcpi_div__DOT__quotient 
                        = (vlTOPp->SOC__DOT__pcpi_div__DOT__quotient 
                           | vlTOPp->SOC__DOT__pcpi_div__DOT__quotient_msk);
                }
                __Vdly__SOC__DOT__pcpi_div__DOT__divisor 
                    = (0x7fffffffffffffffULL & (vlTOPp->SOC__DOT__pcpi_div__DOT__divisor 
                                                >> 1U));
                __Vdly__SOC__DOT__pcpi_div__DOT__quotient_msk 
                    = (vlTOPp->SOC__DOT__pcpi_div__DOT__quotient_msk 
                       >> 1U);
            }
        }
    } else {
        __Vdly__SOC__DOT__pcpi_div__DOT__running = 0U;
    }
    vlTOPp->SOC__DOT__CPU__DOT__mw_IR = vlTOPp->SOC__DOT__CPU__DOT__em_IR;
    vlTOPp->SOC__DOT__pcpi_div__DOT__running = __Vdly__SOC__DOT__pcpi_div__DOT__running;
    vlTOPp->SOC__DOT__pcpi_div__DOT__dividend = __Vdly__SOC__DOT__pcpi_div__DOT__dividend;
    vlTOPp->SOC__DOT__pcpi_div__DOT__divisor = __Vdly__SOC__DOT__pcpi_div__DOT__divisor;
    vlTOPp->SOC__DOT__pcpi_div__DOT__quotient = __Vdly__SOC__DOT__pcpi_div__DOT__quotient;
    vlTOPp->SOC__DOT__pcpi_div__DOT__quotient_msk = __Vdly__SOC__DOT__pcpi_div__DOT__quotient_msk;
    vlTOPp->SOC__DOT__pcpi_div__DOT__instr_divu = __Vdly__SOC__DOT__pcpi_div__DOT__instr_divu;
    if ((0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt))) {
        if (vlTOPp->SOC__DOT__pcpi_div__DOT__start) {
            vlTOPp->SOC__DOT__pcpi_div__DOT__outsign 
                = ((((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div) 
                     & ((1U & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                               >> 0x1fU)) != (1U & 
                                              (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2 
                                               >> 0x1fU)))) 
                    & (0U != vlTOPp->SOC__DOT__CPU__DOT__e_ALUin2)) 
                   | ((IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem) 
                      & (vlTOPp->SOC__DOT__CPU__DOT__e_ALUin1 
                         >> 0x1fU)));
        }
    }
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
    vlTOPp->SOC__DOT__CPU__DOT__em_IR = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ)
                                          ? 0x33U : vlTOPp->SOC__DOT__CPU__DOT__de_IR);
    vlTOPp->SOC__DOT__pcpi_div__DOT__instr_div = __Vdly__SOC__DOT__pcpi_div__DOT__instr_div;
    vlTOPp->SOC__DOT__pcpi_div__DOT__instr_rem = __Vdly__SOC__DOT__pcpi_div__DOT__instr_rem;
    vlTOPp->SOC__DOT__pcpi_div__DOT__start = ((IData)(vlTOPp->SOC__DOT__pcpi_div_wait) 
                                              & (~ (IData)(vlTOPp->SOC__DOT__pcpi_div__DOT__pcpi_wait_q)));
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
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__d_stall)))) {
        vlTOPp->SOC__DOT__CPU__DOT__de_IR = (((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_flush) 
                                              | (IData)(vlTOPp->SOC__DOT__CPU__DOT__fd_NOP))
                                              ? 0x33U
                                              : vlTOPp->SOC__DOT__imem_data);
    }
    if (vlTOPp->SOC__DOT__CPU__DOT__e_flush) {
        vlTOPp->SOC__DOT__CPU__DOT__de_IR = 0x33U;
    }
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
    if ((1U & (~ (IData)(vlTOPp->SOC__DOT__CPU__DOT__f_stall)))) {
        vlTOPp->SOC__DOT__imem_data = vlTOPp->SOC__DOT__DATA__DOT__RAM
            [(0xffffU & (vlTOPp->SOC__DOT__CPU__DOT__f_PC 
                         >> 2U))];
    }
    vlTOPp->SOC__DOT__CPU__DOT__fd_NOP = (1U & ((IData)(vlTOPp->SOC__DOT__CPU__DOT__e_JoB) 
                                                | (~ (IData)(
                                                             (0xffffU 
                                                              == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt))))));
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
    vlTOPp->SOC__DOT__CPU__DOT__f_PC = __Vdly__SOC__DOT__CPU__DOT__f_PC;
    if (__Vdlyvset__SOC__DOT__DATA__DOT__RAM__v0) {
        vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v0))) 
                & vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v0]) 
               | ((IData)(__Vdlyvval__SOC__DOT__DATA__DOT__RAM__v0) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v0)));
    }
    if (__Vdlyvset__SOC__DOT__DATA__DOT__RAM__v1) {
        vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v1))) 
                & vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v1]) 
               | ((IData)(__Vdlyvval__SOC__DOT__DATA__DOT__RAM__v1) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v1)));
    }
    if (__Vdlyvset__SOC__DOT__DATA__DOT__RAM__v2) {
        vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v2))) 
                & vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v2]) 
               | ((IData)(__Vdlyvval__SOC__DOT__DATA__DOT__RAM__v2) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v2)));
    }
    if (__Vdlyvset__SOC__DOT__DATA__DOT__RAM__v3) {
        vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v3))) 
                & vlTOPp->SOC__DOT__DATA__DOT__RAM[__Vdlyvdim0__SOC__DOT__DATA__DOT__RAM__v3]) 
               | ((IData)(__Vdlyvval__SOC__DOT__DATA__DOT__RAM__v3) 
                  << (IData)(__Vdlyvlsb__SOC__DOT__DATA__DOT__RAM__v3)));
    }
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
    vlTOPp->SOC__DOT__CPU__DOT__data_HAZ = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__rs1_HAZ) 
                                            | (IData)(vlTOPp->SOC__DOT__CPU__DOT__rs2_HAZ));
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
    vlTOPp->SOC__DOT__CPU__DOT__f_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ));
    vlTOPp->SOC__DOT__CPU__DOT__d_stall = ((IData)(vlTOPp->SOC__DOT__CPU__DOT__data_HAZ) 
                                           | (IData)(vlTOPp->SOC__DOT__CPU__DOT__mul_HAZ));
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

VL_INLINE_OPT void VSOC::_sequent__TOP__2(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_sequent__TOP__2\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->SOC__DOT__CW__DOT__reset_cnt = ((IData)(vlTOPp->SOC__DOT__RESET)
                                             ? 0U : 
                                            (0xffffU 
                                             & ((IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt) 
                                                + (1U 
                                                   & (~ (IData)(vlTOPp->SOC__DOT__resetn))))));
    vlTOPp->SOC__DOT__resetn = (0xffffU == (IData)(vlTOPp->SOC__DOT__CW__DOT__reset_cnt));
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
}

void VSOC::_eval(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    if ((((IData)(vlTOPp->CLK) & (~ (IData)(vlTOPp->__Vclklast__TOP__CLK))) 
         | ((IData)(vlTOPp->__VinpClk__TOP__SOC__DOT__RESET) 
            & (~ (IData)(vlTOPp->__Vclklast__TOP____VinpClk__TOP__SOC__DOT__RESET))))) {
        vlTOPp->_sequent__TOP__2(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__CLK = vlTOPp->CLK;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__SOC__DOT__RESET 
        = vlTOPp->__VinpClk__TOP__SOC__DOT__RESET;
    vlTOPp->__VinpClk__TOP__SOC__DOT__RESET = vlTOPp->SOC__DOT__RESET;
}

VL_INLINE_OPT QData VSOC::_change_request(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData VSOC::_change_request_1(VSOC__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_change_request_1\n"); );
    VSOC* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    __req |= ((vlTOPp->SOC__DOT__RESET ^ vlTOPp->__Vchglast__TOP__SOC__DOT__RESET));
    VL_DEBUG_IF( if(__req && ((vlTOPp->SOC__DOT__RESET ^ vlTOPp->__Vchglast__TOP__SOC__DOT__RESET))) VL_DBG_MSGF("        CHANGE: soc.v:155: SOC.RESET\n"); );
    // Final
    vlTOPp->__Vchglast__TOP__SOC__DOT__RESET = vlTOPp->SOC__DOT__RESET;
    return __req;
}

#ifdef VL_DEBUG
void VSOC::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSOC::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((CLK & 0xfeU))) {
        Verilated::overWidthError("CLK");}
}
#endif  // VL_DEBUG
