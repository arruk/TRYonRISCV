package torv

import chisel3._
import chisel3.util._

class Flags extends Bundle {
  val nop     = Bool()
  val rrInt   = Bool()
  val riInt   = Bool()
  val load    = Bool()
  val store   = Bool()
  val system  = Bool()
  val jal     = Bool()
  val jalr    = Bool()
  val auipc   = Bool()
  val lui     = Bool()
  val branch  = Bool()
  val csrrs   = Bool()
  val ebreak  = Bool()
  val jj      = Bool()
  val la      = Bool()
  val jjla    = Bool()
  val wb_en   = Bool()
  val r_rs1   = Bool()
  val r_rs2   = Bool()
  val w_rd    = Bool()
  val fwd_em_rs1 = Bool()
  val fwd_mw_rs1 = Bool()
  val fwd_em_rs2 = Bool()
  val fwd_mw_rs2 = Bool()
  val predicted  = Bool()
}

//class DMemPort(val addrW: Int, val dataW: Int = 32) extends Bundle {
class DMemPort extends Bundle {
  val wmask = Output(UInt(4.W))
  val waddr = Output(UInt(32.W))
  val wdata = Output(UInt(32.W))
  val wen   = Output(Bool())

  val raddr = Output(UInt(32.W))
  val rdata = Input(UInt(32.W))
}

class IOPort extends Bundle {
  val addr  = Output(UInt(32.W))
  val rdata = Input (UInt(32.W))
  val wdata = Output(UInt(32.W))
  val wr    = Output(Bool())
}

class Decoder extends Module {

  val io = IO(new Bundle{
    val instruction = Input(UInt(32.W))

    val de_wb_en = Input(Bool())
    val de_rdId = Input(UInt(5.W))
    
    val em_wb_en = Input(Bool())
    val em_rdId = Input(UInt(5.W))

    val rdId = Output(UInt(5.W))
    val rs1Id = Output(UInt(5.W))
    val rs2Id = Output(UInt(5.W))

    val funct3 = Output(UInt(3.W))
    val funct3_is = Output(UInt(8.W))
    val funct7 = Output(Bool()) 
    
    val csrId = Output(UInt(2.W))
    
    val Uimm = Output(UInt(32.W))
    val Bimm = Output(UInt(32.W))
    val Jimm = Output(UInt(32.W))
    val IorSimm = Output(UInt(32.W))
    
    val flags = Output(new Flags)

  })

  val decodeTable = Seq(
    "b01100".U -> "b000000000000001".U,  // isRRint - 0
    "b00100".U -> "b000000000000010".U,  // isRIint - 1
    "b00000".U -> "b000000000000100".U,  // isLoad  - 2
    "b01000".U -> "b000000000001000".U,  // isStore - 3
    "b11100".U -> "b000000000010000".U,  // isSYSTEM- 4
    //
    "b11011".U -> "b000000000100000".U,  // isJAL   - 5
    "b11001".U -> "b000000001000000".U,  // isJALR  - 6
    "b00101".U -> "b000000010000000".U,  // isAUIPC - 7
    "b01101".U -> "b000000100000000".U,  // isLUI   - 8
    "b11000".U -> "b000001000000000".U   // isBranch- 9
  )
  
  val decoded: UInt = MuxLookup(io.instruction(6,2), 0.U(15.W))( decodeTable)
  val flags = WireDefault(0.U.asTypeOf(new Flags))  
 
  flags.rrInt  := decoded(0)
  flags.riInt  := decoded(1)
  flags.load   := decoded(2)
  flags.store  := decoded(3)
  flags.system := decoded(4)
  flags.jal    := decoded(5)
  flags.jalr   := decoded(6)
  flags.auipc  := decoded(7)
  flags.lui    := decoded(8)
  flags.branch := decoded(9)
  
  io.rdId  := io.instruction(11,7 )
  io.rs1Id := io.instruction(19,15)
  io.rs2Id := io.instruction(24,20)

  io.Uimm := Cat(
     io.instruction(31),
     io.instruction(30,12),
     Fill(12, 0.U(1.W))
  )
  io.Bimm := Cat(
     Fill(20, io.instruction(31)),
     io.instruction(7),
     io.instruction(30,25),
     io.instruction(11,8),
     Fill(1, 0.U(1.W))
  )
  io.Jimm := Cat(
     Fill(12, io.instruction(31)),
     io.instruction(19,12),
     io.instruction(20),
     io.instruction(30,21),
     Fill(1, 0.U(1.W))
  )
  io.IorSimm := Cat(
     Fill(21, io.instruction(31)),
     Mux(flags.store,
       Cat(io.instruction(30,25), io.instruction(11,7)),
       io.instruction(30,20)
     )
  )

  io.funct3    := io.instruction(14,12)
  io.funct3_is := "b00000001".U << io.instruction(14,12)
  io.funct7    := io.instruction(30)

  io.csrId := Cat(
   io.instruction(27),
   io.instruction(21)
  )

 
  flags.csrrs := flags.system &&  io.instruction(13)
  flags.ebreak:= flags.system && !io.instruction(13)

  flags.jj   := flags.jal  || flags.jalr
  flags.la   := flags.lui  || flags.auipc
  flags.jjla := flags.jj   || flags.la
 
  flags.nop := false.B

  flags.wb_en := (io.instruction(5,2) =/= "b1000".U) & (io.rdId =/= "b00000".U)
  flags.r_rs1 := !(flags.jal | flags.la)
  flags.r_rs2 := io.instruction(5) & (io.instruction(3,2) === "b00".U)
  flags.w_rd := (io.instruction(5,2) =/= "b1000".U)

  flags.fwd_em_rs1 := io.de_wb_en & (io.de_rdId === io.rs1Id)
  flags.fwd_mw_rs1 := io.em_wb_en & (io.em_rdId === io.rs1Id)
  flags.fwd_em_rs2 := io.de_wb_en & (io.de_rdId === io.rs2Id)
  flags.fwd_mw_rs2 := io.em_wb_en & (io.em_rdId === io.rs2Id)

  io.flags := flags

}

class MemoryDEC extends Module {
  val io = IO(new Bundle {
    val result = Input(UInt(32.W))
    val addr = Input(UInt(32.W))
    val rs2 = Input(UInt(32.W))

    val funct3 = Input(UInt(3.W))
    val csrId_is = Input(UInt(4.W))
    val em_flags = Input(new Flags)

    val cycle   = Input(UInt(64.W))
    val instret = Input(UInt(64.W))

    val dmem = new DMemPort
    val iomem = new IOPort

    val notIOandLoad = Output(Bool())
    val wbData = Output(UInt(32.W))
    val mw_Mdata = Output(UInt(32.W))
  })

  val m_isIO  = io.addr(22)
  val m_isRAM = !m_isIO
  val m_isB   = (io.funct3(1,0) === "b00".U)
  val m_isH   = (io.funct3(1,0) === "b01".U)

  val store_bytes = Wire(Vec(4, UInt(8.W)))

  store_bytes(0) := io.rs2(7,0)
  store_bytes(1) := Mux(io.addr(0), io.rs2(7,0), io.rs2(15,8))
  store_bytes(2) := Mux(io.addr(1), io.rs2(7,0), io.rs2(23,16))
  store_bytes(3) := Mux(io.addr(0), io.rs2(7,0),
                    Mux(io.addr(1), io.rs2(15,8), io.rs2(31,24)))

  val m_store_DATA = store_bytes.asUInt

  val wmaskDefault = "b1111".U

  val m_store_WMASK = MuxCase(wmaskDefault, Seq(
    m_isB -> Mux(io.addr(1),
                 Mux(io.addr(0), "b1000".U, "b0100".U),
                 Mux(io.addr(0), "b0010".U, "b0001".U)),
    m_isH -> Mux(io.addr(1), "b1100".U, "b0011".U)
  ))

  //val m_WMASK = Fill(4, Cat(io.em_flags.store & m_isRAM)) & m_store_WMASK
  val m_WMASK = Fill(4, (io.em_flags.store && m_isRAM).asUInt) & m_store_WMASK

  val m_CSR_data = Mux1H(Seq(
    io.csrId_is(0) -> io.cycle(31,0),
    io.csrId_is(2) -> io.cycle(63,32),
    io.csrId_is(1) -> io.instret(31,0),
    io.csrId_is(3) -> io.instret(63,32)
  ))

  io.iomem.addr  := io.addr
  io.iomem.wr    := io.em_flags.store && m_isIO
  io.iomem.wdata := io.rs2
  val loadData = io.iomem.rdata

  io.wbData:= MuxCase(io.result, Seq(
    io.em_flags.load  -> loadData,
    io.em_flags.csrrs -> m_CSR_data
  ))

  val m_byteAddress = Cat(0.U(9.W), io.addr(22,0)) >> 2

  io.dmem.wmask := m_WMASK
  io.dmem.waddr := m_byteAddress
  io.dmem.wdata := m_store_DATA
  io.dmem.wen   := io.em_flags.load | (io.em_flags.store && m_isRAM)
  io.dmem.raddr := m_byteAddress
  io.mw_Mdata  := io.dmem.rdata

  io.notIOandLoad := io.em_flags.load & !m_isIO

  /*
  m_lb  := (em_funct3(2,0) === "b000".U)
  m_lbu := (em_funct3(2,0) === "b100".U)
  m_lh  := (em_funct3(2,0) === "b001".U)
  m_lhu := (em_funct3(2,0) === "b101".U)
  */

}

