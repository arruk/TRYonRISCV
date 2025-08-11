package torv

import chisel3._          
import chisel3.util._
import _root_.circt.stage.ChiselStage

import BitUtils._

class TorvChip extends Module {
  
  val DRAM = Module(new RAM(16384,32))
  val IROM = Module(new ROM(16384,32))
  
  val io = IO(new Bundle {
    val reset = Input(Bool())
    val halt = Output(Bool())

    val dram = Flipped(new DMemPort)
  })

  val torv = Module(new Torv)

  torv.io.reset := reset.asBool
  
  torv.io.iomem.rdata := Cat(0.U(22.W), 1.U(1.W), 0.U(9.W))
  io.halt := torv.io.cpu_halted

  val muxPort = Wire(new DMemPort)
  muxPort <> torv.io.dmem

  when (reset.asBool) {
    muxPort.wen   := io.dram.wen
    muxPort.wmask := io.dram.wmask
    muxPort.waddr := io.dram.waddr
    muxPort.wdata := io.dram.wdata
    muxPort.raddr := io.dram.raddr
  }

  DRAM.io.dmem <> muxPort

  io.dram.rdata   := muxPort.rdata
  torv.io.dmem.rdata := muxPort.rdata
  
  IROM.io.ren := torv.io.imem_en
  IROM.io.raddr := torv.io.imem_addr
  torv.io.imem_data := IROM.io.rdata 
  
  val uart_valid = Wire(Bool())
  uart_valid := torv.io.iomem.wr & torv.io.iomem.addr(3)
  when (uart_valid) {
    printf("%c", torv.io.iomem.wdata(7,0))
  }
}

class Torv extends Module {
  val io = IO(new Bundle {
    val reset  = Input(UInt(1.W))

    val imem_en = Output(Bool())
    val imem_addr = Output(UInt(32.W))
    val imem_data = Input(UInt(32.W))

    val dmem = new DMemPort
    val iomem = new IOPort

    val cpu_halted = Output(Bool())
  })
  
  val register_file = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  val rs1_HAZ = Wire(Bool())
  val rs2_HAZ = Wire(Bool()) 
  val halt = Wire(Bool())
  val data_HAZ = Wire(Bool())
  val f_stall = Wire(Bool())
  val d_stall = Wire(Bool())
  val e_flush = Wire(Bool())
  val d_flush = Wire(Bool())

  val PCR = RegInit(0.U(32.W))
  val fd_PC = RegInit(0.U(32.W))
  val fd_NOP = RegInit(true.B)

  val jumpTaken = Wire(Bool())
  val jumpAddress = Wire(UInt(32.W))
  val PC = Wire(UInt(32.W)) 
  val imemAddress = Wire(UInt(32.W)) 

  val fd_IR = Wire(UInt(32.W))
 
  val d_JoB_now = Wire(Bool()) 
  val d_JoB_ADDR = Wire(UInt(32.W))

  val DEC = Module(new Decoder)
  val d_PCplus4orUimm = Wire(UInt(32.W)) 
  val d_PCplus4orBimm = Wire(UInt(32.W)) 

  val de_flags = RegInit(0.U.asTypeOf(new Flags))

  val de_nop = Reg(Bool())
  val de_PCplus4orUimm = Reg(UInt(32.W))
  val de_PCplus4orBimm = Reg(UInt(32.W))
  val de_rdID = Reg(UInt(5.W))       
  val de_rs1ID = Reg(UInt(5.W))   
  val de_rs2ID = Reg(UInt(5.W))   
  val de_funct3 = Reg(UInt(3.W)) 
  val de_funct3_is = Reg(UInt(8.W)) 
  val de_funct7 = Reg(Bool())  
  val de_csrID = Reg(UInt(2.W))  
  val de_IorSimm = Reg(UInt(32.W)) 

  val e_JoB = WireDefault(false.B)
  val e_rs1 = Wire(UInt(32.W))
  val e_rs2 = Wire(UInt(32.W))
  val e_take_branch = Wire(Bool())
  val e_JoB_ADDR = Wire(UInt(32.W))
  val e_addr = Wire(UInt(32.W))
  val e_result  = Wire(UInt(32.W))

  val em_flags = RegInit(0.U.asTypeOf(new Flags))
  val em_result = Reg(UInt(32.W))
  val em_ADDR = Reg(UInt(32.W))
  val em_rdID = Reg(UInt(5.W))
  val em_rs1ID = Reg(UInt(5.W))
  val em_rs2ID = Reg(UInt(5.W))
  val em_funct3 = Reg(UInt(5.W))
  val em_csrID_is = Reg(UInt(4.W))
  val em_rs2 = Reg(UInt(32.W))
  val em_JoB_now = Reg(Bool())
  val em_JoB_ADDR = Reg(UInt(32.W))
 
  val cycle = RegInit(0.U(64.W))
  val instret = RegInit(0.U(64.W))

  val mw_nop = Reg(Bool())
  val mw_rdID = Reg(UInt(5.W))
  val mw_wb_DATA = Reg(UInt(32.W))
  val mw_wbEnable = Reg(Bool())
  val mw_funct3 = Reg(UInt(5.W))
  val mw_ADDR = Reg(UInt(32.W))
  val mw_isNotIOandLoad = Reg(Bool())
  
  val w_isIO = Wire(Bool())
  val w_LB = Wire(UInt(32.W))
  val w_LBU = Wire(UInt(32.W))
  val w_LH = Wire(UInt(32.W))
  val w_LHU = Wire(UInt(32.W))
  val w_mem_RES = Wire(UInt(32.W))

  val wb_enable = Wire(Bool())
  val wb_DATA = Wire(UInt(32.W))
  val wb_rdID = Wire(UInt(5.W))

//HAZARDS
  
  rs1_HAZ  := DEC.io.flags.r_rs1 && (DEC.io.rs1Id === de_rdID)
  rs2_HAZ  := DEC.io.flags.r_rs2 && (DEC.io.rs2Id === de_rdID)

  halt := (reset.asBool === false.B) & DEC.io.flags.ebreak

  io.cpu_halted := halt

  data_HAZ := !fd_NOP && ((de_flags.load || de_flags.csrrs) && (rs1_HAZ || rs2_HAZ))

  f_stall := data_HAZ | halt
  d_stall := data_HAZ | halt

  e_flush := e_JoB | data_HAZ
  d_flush := e_JoB


//FETCH

  fd_NOP := d_flush

  jumpTaken := d_JoB_now | em_JoB_now
  jumpAddress := Mux(d_JoB_now, d_JoB_ADDR, em_JoB_ADDR)
  PC := Mux(jumpTaken, jumpAddress + 4.U, PCR + 4.U)
  val wordAddr = Mux(jumpTaken, jumpAddress, PCR)
  
  imemAddress := wordAddr >> 2

  when (!f_stall) {
    fd_PC := wordAddr
    PCR   := PC
  }

  io.imem_en := !f_stall
  io.imem_addr := imemAddress
  fd_IR := io.imem_data

//DECODE

  val BP = Module(new BranchPredictor(1<<9))
  BP.io.input_addr := wordAddr(10,2)
  BP.io.isBranch := de_flags.branch
  BP.io.take_branch := e_take_branch
  val d_predict = BP.io.predict

  DEC.io.instruction := fd_IR
  DEC.io.de_wb_en := de_flags.wb_en
  DEC.io.de_rdId := de_rdID
  DEC.io.em_wb_en := em_flags.wb_en
  DEC.io.em_rdId := em_rdID

  d_JoB_now := !fd_NOP && (DEC.io.flags.jal || (DEC.io.flags.branch && d_predict))
  d_JoB_ADDR := fd_PC + Mux(DEC.io.flags.jal, DEC.io.Jimm, DEC.io.Bimm)
  
  d_PCplus4orUimm := (Fill(32, fd_IR(6,5)=/="b01".U) & fd_PC) + Mux(DEC.io.flags.jj, 4.U(32.W), DEC.io.Uimm)
  d_PCplus4orBimm := fd_PC + Mux(d_predict, 4.U, DEC.io.Bimm)

  when (!d_stall) {
    de_PCplus4orUimm := d_PCplus4orUimm
    de_PCplus4orBimm := d_PCplus4orBimm
    de_IorSimm       := DEC.io.IorSimm
    de_rdID := DEC.io.rdId
    de_rs1ID := DEC.io.rs1Id
    de_rs2ID := DEC.io.rs2Id
    de_funct3 := DEC.io.funct3
    de_funct3_is := DEC.io.funct3_is
    de_funct7 :=DEC.io.funct7
    de_csrID := DEC.io.csrId

    de_flags           := DEC.io.flags
    de_flags.predicted := d_predict
  } 

  when (e_flush | fd_NOP) {
    de_flags := 0.U.asTypeOf(new Flags)
    de_flags.nop := true.B
  }

//EXECUTE

  e_rs1 := MuxCase(register_file(de_rs1ID), Seq(
    (de_flags.fwd_em_rs1) -> em_result,
    (de_flags.fwd_mw_rs1) -> wb_DATA
  ))

  e_rs2 := MuxCase(register_file(de_rs2ID), Seq(
    (de_flags.fwd_em_rs2) -> em_result,
    (de_flags.fwd_mw_rs2) -> wb_DATA
  ))

  val alu = Module(new ALU)
  alu.io.inA := e_rs1
  alu.io.inB := e_rs2
  alu.io.deFlags := de_flags
  alu.io.Bimm := de_PCplus4orBimm
  alu.io.Uimm := de_PCplus4orUimm
  alu.io.IorSimm := de_IorSimm
  alu.io.rs2Id := de_rs2ID
  alu.io.funct3 := de_funct3
  alu.io.funct3_is := de_funct3_is
  alu.io.funct7 := de_funct7

  e_take_branch := alu.io.take_branch
  e_JoB := alu.io.JoB
  e_JoB_ADDR := alu.io.JoB_addr
  e_addr := alu.io.addr
  e_result := alu.io.result

  em_flags.nop   := de_flags.nop
  em_flags.load  := de_flags.load
  em_flags.store := de_flags.store
  em_flags.csrrs  := de_flags.csrrs
  em_flags.branch  := de_flags.branch
  em_flags.wb_en  := de_flags.wb_en

  em_result   := e_result
  em_ADDR     := e_addr
  em_JoB_now  := e_JoB
  em_JoB_ADDR := e_JoB_ADDR
  
  em_rdID     := de_rdID
  em_rs1ID    := de_rs1ID
  em_rs2ID    := de_rs2ID
  em_funct3   := de_funct3
  em_csrID_is := "b0001".U << de_csrID
  em_rs2      := e_rs2

//MEMORY

  val memDec = Module(new MemoryDEC)
  memDec.io.result := em_result
  memDec.io.addr := em_ADDR
  memDec.io.rs2 := em_rs2

  memDec.io.funct3 := em_funct3
  memDec.io.csrId_is := em_csrID_is
  memDec.io.em_flags := em_flags

  memDec.io.cycle   := cycle
  memDec.io.instret := instret

  io.dmem <> memDec.io.dmem
  io.iomem <> memDec.io.iomem

  mw_nop      := em_flags.nop
  mw_wbEnable := em_flags.wb_en
  mw_rdID     := em_rdID
  mw_funct3   := em_funct3
  mw_ADDR     := em_ADDR
  mw_wb_DATA        := memDec.io.wbData 
  mw_isNotIOandLoad := memDec.io.notIOandLoad

  cycle := cycle + 1.U
  when (!mw_nop) {
    instret := instret + 1.U
  }

//WRITE-BACK

  w_isIO := mw_ADDR(22)

  val w_lb_data = io.dmem.rdata.asTypeOf(Vec(4, UInt(8.W)))
  val w_lb_sel  = w_lb_data(mw_ADDR(1,0))
  w_LB  := Cat(Fill(24, w_lb_sel(7)), w_lb_sel)
  w_LBU := Cat(Fill(24, 0.U), w_lb_sel)

  val w_lh_data = io.dmem.rdata.asTypeOf(Vec(2, UInt(16.W)))
  val w_lh_sel  = w_lh_data(mw_ADDR(1))
  w_LH  := Cat(Fill(16, w_lh_sel(15)), w_lh_sel)
  w_LHU := Cat(Fill(16, 0.U), w_lh_sel)

  w_mem_RES := MuxCase(io.dmem.rdata, Seq(
    (mw_funct3(2,0) === "b000".U) -> w_LB,
    (mw_funct3(2,0) === "b100".U) -> w_LBU,
    (mw_funct3(2,0) === "b001".U) -> w_LH,
    (mw_funct3(2,0) === "b101".U) -> w_LHU
  ))

  wb_DATA   := Mux(mw_isNotIOandLoad, w_mem_RES, mw_wb_DATA)
  wb_enable := mw_wbEnable
  wb_rdID   := mw_rdID

  when (wb_enable) {
    register_file(wb_rdID) := wb_DATA
  }
 
// Results

  val branchs = RegInit(0.U(64.W))
  val predict_hits = RegInit(0.U(64.W))

  when (de_flags.branch) {
    branchs := branchs + 1.U
    when(e_take_branch === de_flags.predicted){
      predict_hits := predict_hits + 1.U
    }
  }

  val pct1000 = (predict_hits * 1000.U) / branchs
  val intPart = pct1000 / 10.U
  val fracPart = pct1000 % 10.U 

  when (halt) {
    chisel3.printf("Numbers of = (Cycles: %d, Instret: %d)\n", cycle, instret)
    printf(p"Numbers = (Branches: $branchs, Hits $predict_hits, % of Hits: ${intPart}.${fracPart})\n")
    stop()
  }

}

object TorvChip extends App {
  ChiselStage.emitSystemVerilogFile(
    new TorvChip,
    firtoolOpts = Array(
      "-disable-all-randomization",
      "-strip-debug-info"
    )
  )
}
