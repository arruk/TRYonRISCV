// src/main/scala/learn/BitUtils.scala
package torv

import chisel3._
import chisel3.util._

object BitUtils { 
  def flip32(x: UInt): UInt = {
    require(x.getWidth == 32, "flip32 espera UInt(32.W)")
    Cat((0 until 32).map(i => x(i)))
  }

  /*
  def incdecSat(prev: UInt, dir: Bool): UInt = {
    require(prev.getWidth == 2,  "prev must be 2‑bit")
    val satInc = Mux(prev === 3.U, 3.U, prev + 1.U)
    val satDec = Mux(prev === 0.U, 0.U, prev - 1.U)
    Mux(dir, satInc, satDec)
  }  */
}
