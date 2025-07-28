package torv

import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFileInline

/*
class DMemToTL(implicit p: Parameters) extends LazyModule {
  val tlNode = TLClientNode(Seq(TLClientPortParameters(
      Seq(TLClientParameters("dmem", IdRange(0,1))), minLatency = 1)))

  lazy val module = new LazyModuleImp(this) {
    val io = IO(Flipped(new DMemPort))

    val (out, edge) = tlNode.out(0)      // canais A‑D
    // Canal A (Load/Store)
    out.a.valid := io.req
    out.a.bits  := TLBundleA(
      opcode = Mux(io.wen, TLMessages.PutFullData, TLMessages.Get),
      param  = 0.U,
      size   = (log2Ceil(io.wmask.getWidth/8)).U,
      source = 0.U,
      address= io.addr,
      mask   = io.wmask,
      data   = io.wdata,
      corrupt= false.B)

    io.reqReady := out.a.ready

    // Canal D (Resposta)
    io.rdata   := out.d.bits.data
    out.d.ready:= true.B
  }
}
*/

class ROM(depth: Int = 32, width: Int = 32) extends Module {
  val io = IO(new Bundle {
    val ren = Input(Bool())
    val raddr = Input(UInt(log2Ceil(depth).W))
    val rdata = Output(UInt(width.W))
  })

  val mem = SyncReadMem(depth, UInt(width.W))

  io.rdata := mem.read(io.raddr, io.ren)

  loadMemoryFromFileInline(mem, "PROGROM.hex")
}

class RAM(depth: Int = 32, width: Int = 32) extends Module {
  require(width % 8 == 0, "width deve ser múltiplo de 8 bits")

  private val nBytes = width / 8

  val io = IO(new Bundle {
    /*
    val wen   = Input(Bool())
    val wmask = Input(UInt(nBytes.W))
    val waddr = Input(UInt(log2Ceil(depth).W))
    val wdata = Input(UInt(width.W))
    val raddr = Input(UInt(log2Ceil(depth).W))
    val rdata = Output(UInt(width.W))
    */
   val dmem = Flipped(new DMemPort)
  })

  val mem = SyncReadMem(depth, Vec(nBytes, UInt(8.W)))

  when (io.dmem.wen) {
    val wVec = io.dmem.wdata.asTypeOf(Vec(nBytes, UInt(8.W)))
    mem.write(io.dmem.waddr, wVec, io.dmem.wmask.asBools)
  }
  
  io.dmem.rdata := mem.read(io.dmem.raddr, true.B).asUInt
} 
