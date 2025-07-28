package torv

import chisel3._
import chisel3.util._

class BranchPredictor(val size: Int) extends Module {

  val io = IO(new Bundle {
    val input_addr = Input(UInt(log2Ceil(size).W))

    val predict = Output(Bool())
    val isBranch = Input(Bool())
    val take_branch = Input(Bool())

  })

  val bht = SyncReadMem(size, UInt(2.W))

  val bht_data = bht.read(io.input_addr, true.B)

  def incdecSat(p: UInt, dir: Bool): UInt =
    Mux(dir, Mux(p === 3.U, 3.U, p + 1.U),
              Mux(p === 0.U, 0.U, p - 1.U))

  val f_bhtAddr = RegNext(io.input_addr)

  val d_predict = bht_data(1)
  io.predict := d_predict

  val e_bhtAddr = RegNext(f_bhtAddr)
  val e_bhtData = RegNext(bht_data)

  when (io.isBranch) {
    bht(e_bhtAddr) := incdecSat(e_bhtData, io.take_branch)
  }

}
