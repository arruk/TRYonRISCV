package torv

import scala.util.Random
import scala.io.Source
import scala.util.Using

import chisel3._
import chiseltest._
import chiseltest.simulator.{VerilatorBackendAnnotation,VerilatorCFlags, VerilatorFlags}
import chiseltest.experimental.expose
import org.scalatest.flatspec.AnyFlatSpec

class LearnSpec extends AnyFlatSpec with ChiselScalatestTester {
  behavior of "SoC"

  it should "testbench" in {
    test(new TorvChip)
      .withAnnotations(Seq(VerilatorBackendAnnotation,
        VerilatorCFlags(Seq("-Wno-error=type-limits"))))
      { dut =>
      dut.clock.setTimeout(0)

      dut.reset.poke(true.B) 
      val dram = dut.io.dram

      val words = Using(Source.fromFile("DATARAM.hex")) { src =>
        src.getLines().flatMap(_.trim.split("\\s+")).filter(_.nonEmpty).toVector
      }.get

      words.zipWithIndex.foreach { case (hex, idx) =>
        val value = BigInt(hex, 16).U(32.W)
        dram.wen  .poke(true.B)
        dram.wmask.poke("b1111".U)
        dram.waddr.poke(idx.U)
        dram.wdata.poke(value)
        dut.clock.step()
      }

      dram.wen.poke(false.B)
      dut.clock.step()
      dut.reset.poke(false.B)

      val maxCycles = 600000000

      var cycle = 0
      //while (cycle < maxCycles) {
      while (cycle < maxCycles && !dut.io.halt.peekBoolean()) {
        dut.clock.step()
        cycle += 1
      }
      assert(cycle < maxCycles, "Timeout – CPU não gerou halt")
    }
  }
}
