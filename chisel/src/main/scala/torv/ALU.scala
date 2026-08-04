package torv

import chisel3._
import chisel3.util._

import BitUtils._

class ALU extends Module {

  val io = IO(new Bundle{
    val inA = Input(UInt(32.W)) 
    val inB = Input(UInt(32.W)) 
  
    val deFlags = Input(new Flags)
  
    val Bimm = Input(UInt(32.W))
    val Uimm = Input(UInt(32.W))
    val IorSimm = Input(UInt(32.W))

    val rs2Id = Input(UInt(5.W))
    val funct3 = Input(UInt(3.W))
    val funct3_is = Input(UInt(8.W))
    val funct7 = Input(Bool())

    val take_branch = Output(Bool())

    val JoB = Output(Bool())
    val JoB_addr = Output(UInt(32.W))
    val result = Output(UInt(32.W))
    val addr = Output(UInt(32.W))
  })

  val e_ALUin1 = io.inA
  val e_ALUin2 = Mux(
    io.deFlags.rrInt | io.deFlags.branch,
    io.inB,
    io.IorSimm
  )

  val e_SHamt = Mux(
    io.deFlags.rrInt,
    io.inB(4,0),
    io.rs2Id
  )

  val e_minus = (io.funct7 & io.deFlags.rrInt).asBool
  val e_arith_shift = io.funct7

  val e_ALUplus = e_ALUin1 + e_ALUin2
  val e_ALUminus = Cat(0.U(1.W), e_ALUin1) + Cat(1.U(1.W), ~e_ALUin2) + 1.U(33.W)

  val e_LT = Mux(
    e_ALUin1(31) ^ e_ALUin2(31),
    e_ALUin1(31),
    e_ALUminus(32)
  )
  val e_LTU = e_ALUminus(32)
  val e_EQ  = (e_ALUin1 === e_ALUin2)

  val e_shifter_in = Mux(io.funct3 === "b001".U, flip32(e_ALUin1), e_ALUin1)

  val shifted = (Cat(Mux(e_arith_shift, e_ALUin1, 0.U), e_shifter_in)
                   .asSInt >> e_ALUin2(4,0)).asUInt

  val e_shifter = shifted(31,0)

  val e_left_shift = flip32(e_shifter)

  val e_ALUout = Mux1H(Seq(
    io.funct3_is(0) -> Mux(e_minus,
                         e_ALUminus(31,0),
                         e_ALUplus),
    io.funct3_is(1) -> e_left_shift,
    io.funct3_is(2) -> Cat(0.U(31.W),  e_LT),
    io.funct3_is(3) -> Cat(0.U(31.W),  e_LTU),
    io.funct3_is(4) -> (e_ALUin1 ^  e_ALUin2),
    io.funct3_is(5) ->  e_shifter,
    io.funct3_is(6) -> (e_ALUin1 |  e_ALUin2),
    io.funct3_is(7) -> (e_ALUin1 &  e_ALUin2)
  ))

  io.take_branch := Mux1H(Seq(
    io.funct3_is(0) ->  e_EQ ,
    io.funct3_is(1) -> !e_EQ ,
    io.funct3_is(4) ->  e_LT ,
    io.funct3_is(5) -> !e_LT ,
    io.funct3_is(6) ->  e_LTU,
    io.funct3_is(7) -> !e_LTU
  ))

  val e_jalrADDR = Cat(e_ALUplus(31,1),0.U(1.W))

  io.JoB := io.deFlags.jalr | (io.deFlags.branch & (io.take_branch =/= io.deFlags.predicted))
  io.JoB_addr := Mux(io.deFlags.branch, io.Bimm, e_jalrADDR)
  io.addr := io.inA + io.IorSimm
  io.result := Mux(io.deFlags.jjla, io.Uimm, e_ALUout)
  
}
