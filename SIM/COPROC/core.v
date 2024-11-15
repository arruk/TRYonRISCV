`default_nettype none

`ifdef ALU
	`include "alu2.v"
`else
	`include "alu.v"
`endif

module torv32(
	input         clk,
        input 	      resetn,

	output        imem_en,      // enable to fetch an instruction
        output [31:0] imem_addr,    // addres to fetch an instruction
        input  [31:0] imem_data,    // instruction fetched

        input  [31:0] mem_data,     // data read from memory
        output [ 3:0] mem_wmask,    // mask for write in memory
        output [31:0] mem_addr,     // address to write/read
        output [31:0] mem_wdata,    // data to write

	output [31:0] IO_mem_addr,  // IO mem address
	input  [31:0] IO_mem_rdata, // data read from IO
	output [31:0] IO_mem_wdata, // data written to IO
	output        IO_mem_wr,    // IO write flag
	
	output        pcpi_valid,
	output [31:0] pcpi_insn,
	output [31:0] pcpi_rs1,
	output [31:0] pcpi_rs2,
	input         pcpi_wr,
	input  [31:0] pcpi_rd,
	input         pcpi_wait,
	input         pcpi_ready

);


	localparam IMMEDIATE_OPS = 7'b0010011;
	localparam REGISTER_OPS  = 7'b0110011;
	localparam STORE_OPS     = 7'b0100011;
	localparam LOAD_OPS      = 7'b0000011;
	localparam BRANCH_OPS    = 7'b1100011;
	localparam JALR          = 7'b1100111;
	localparam JAL           = 7'b1101111;
	localparam AUIPC         = 7'b0010111;
	localparam LUI           = 7'b0110111;
	localparam FENCE         = 7'b0001111;
       	localparam CALL_BREAK    = 7'b1110011;
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire rs1_HAZ = !fd_NOP & reads_rs1(fd_IR) & rs1ID(fd_IR)!=0 &      (
		       	(writes_rd(de_IR) & (rs1ID(fd_IR) == rdID(de_IR))) |
		        (writes_rd(em_IR) & (rs1ID(fd_IR) == rdID(em_IR))) );
	
	wire rs2_HAZ = !fd_NOP & reads_rs2(fd_IR) & rs2ID(fd_IR)!=0 &      (
		       	(writes_rd(de_IR) & (rs2ID(fd_IR) == rdID(de_IR))) |
		        (writes_rd(em_IR) & (rs2ID(fd_IR) == rdID(em_IR))) );

	wire mul_HAZ = isMulDiv(de_IR) & ~pcpi_ready;
	
	wire halt = 0;//resetn & isEBREAK(de_IR);	

	wire data_HAZ = rs1_HAZ | rs2_HAZ;

	wire f_stall = data_HAZ | mul_HAZ | halt;
	wire d_stall = data_HAZ | mul_HAZ | halt;

	wire m_flush = mul_HAZ;
	wire e_flush = e_JoB | (data_HAZ & !mul_HAZ);
	wire d_flush = e_JoB;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg [31:0] f_PC;
	wire [31:0] fd_IR = imem_data;

	// INSTRUCTION SEGMENT
	// 0x00000 - 0x10000

	always@(posedge clk) begin
		if(!f_stall) begin
			if(|f_PC[1:0]) begin
				MCAUSE <= {1'b0, 20'b0, 11'd1};
				MEPC   <= f_PC;
				f_PC   <= MTVEC;
			end else begin
				fd_PC <= f_PC;
				f_PC  <= f_PC+4;
			end
		end

		if(JoB) 
			f_PC <= JoB_ADDR;

		fd_NOP <= d_flush | !resetn ;

		if(!resetn) begin
			//f_PC  <=32'h20000;
			f_PC <= 32'h30000;
		end
	
	end
	
	assign imem_en   = !f_stall;
	assign imem_addr = f_PC;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] fd_PC;
        reg fd_NOP;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	localparam NOP = 32'b0000000_00000_00000_000_00000_0110011;
	
	wire        wb_enable;
	wire [31:0] wb_DATA;
	wire [4:0]  wb_rdID;

	reg [31:0] reg_file [0:31];
	
	always@(posedge clk) begin
		if(!d_stall) begin
			de_IR <= (e_flush | fd_NOP) ? NOP : fd_IR;
			de_PC <= fd_PC;
		end	

		if(e_flush)
			de_IR <= NOP;
		
		if(wb_enable) begin
			reg_file[wb_rdID] <= wb_DATA;
		end

	end	

	always@(posedge clk) begin

		if((de_IR[6:0]!=IMMEDIATE_OPS) & (de_IR[6:0]!=REGISTER_OPS) &
		   (de_IR[6:0]!=LOAD_OPS)      & (de_IR[6:0]!=STORE_OPS)    & 
		   (de_IR[6:0]!=BRANCH_OPS)    & (de_IR[6:0]!=JALR)         & 
		   (de_IR[6:0]!=JAL)           & (de_IR[6:0]!=AUIPC)        & 
		   (de_IR[6:0]!=LUI)           & (de_IR[6:0]!=FENCE)        & 
		   (de_IR[6:0]!=CALL_BREAK)) begin

			MCAUSE <= {1'b0, 20'b0, 11'd2};
			MEPC   <= f_PC;
			f_PC   <= MTVEC;

		end else if (isEBREAK(de_IR)) begin
                        MCAUSE <= {1'b0, 20'b0, 11'd3};
                        MEPC   <= f_PC;
                        f_PC   <= MTVEC;

		end

	end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] de_IR, de_PC;
	wire [31:0] de_rs1 = reg_file[rs1ID(de_IR)];
       	wire [31:0] de_rs2 = reg_file[rs2ID(de_IR)];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [31:0] e_IMM;

	imm_mux m0(
		.instr(de_IR),
		.imm(e_IMM)
	);

	wire [31:0] e_ALUin1 = (isJAL(de_IR) | isJALR(de_IR) | isAUIPC(de_IR)) ? de_PC : de_rs1;
	wire [31:0] e_ALUin2 = (isRtype(de_IR) | isBtype(de_IR))? de_rs2 :
	       		       (isRimm(de_IR)  | isAUIPC(de_IR))? e_IMM  :
			       					  32'd4  ;

	assign pcpi_insn  = de_IR;
	assign pcpi_rs1   = e_ALUin1;
	assign pcpi_rs2   = e_ALUin2;
	assign pcpi_valid = isMulDiv(de_IR);
	
	always@(posedge clk) begin
		if(pcpi_valid) begin
			//$display("is mul/div in de_IR %1d ? PC = %x | pcpi_ready = %1x", isMulDiv(de_IR), de_PC, pcpi_ready);
		end
	end

	wire [31:0] e_ALUout;
	wire e_takeB;

	alu u0(
		.in_a(e_ALUin1),
	        .in_b(e_ALUin2),
	        .inst(de_IR),
	        .result(e_ALUout),
	        .take_b(e_takeB)
	);
	wire [31:0] e_RES = isLUI(de_IR)    ? e_IMM  :
			    isMulDiv(de_IR) ? pcpi_rd:
			    	            e_ALUout ;

	wire [31:0] e_ADDin1 = (isJAL(de_IR) | isBtype(de_IR)) ? de_PC : de_rs1;
	wire [31:0] e_ADDR_RES = e_ADDin1 + e_IMM;
	wire [31:0] e_ADDR = {e_ADDR_RES[31:1], e_ADDR_RES[0] & (~isJALR(de_IR))}; 

	wire e_JoB = isJAL(de_IR) | isJALR(de_IR) | (isBtype(de_IR) & e_takeB);
	wire [31:0] e_JoB_ADDR = e_ADDR;

	wire [31:0] e_rs2 = (isCSRRS(de_IR)) ? ( de_IR[14] ? {27'b0, de_IR[19:15]} : de_rs1 ):
					     					       de_rs2;

	always@(posedge clk) begin
		if(m_flush)
			em_IR <= NOP;
		else
			em_IR   <= de_IR;
		em_PC   <= de_PC;
		em_rs2  <= e_rs2;
		em_RES  <= e_RES;
		em_ADDR <= e_ADDR;
	end
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg[31:0] em_IR, em_PC, em_rs2, em_RES, em_ADDR;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [2:0] m_funct3 = funct3(em_IR);
	wire m_isB = (m_funct3[1:0] == 2'b00);
	wire m_isH = (m_funct3[1:0] == 2'b01);


	wire [31:0] m_store_DATA;
		assign m_store_DATA[ 7:0 ] = em_rs2[7:0];
	assign m_store_DATA[15:8 ] = em_ADDR[0] ? em_rs2[7:0]  : em_rs2[15:8 ] ;
	assign m_store_DATA[23:16] = em_ADDR[1] ? em_rs2[7:0]  : em_rs2[23:16] ;
	assign m_store_DATA[31:24] = em_ADDR[0] ? em_rs2[7:0]  :
				     em_ADDR[1] ? em_rs2[15:8] : em_rs2[31:24] ;

	wire [3:0] m_store_WMASK = m_isB ? (em_ADDR[1] ? (em_ADDR[0] ? 4'b1000 : 4'b0100)  :
							 (em_ADDR[0] ? 4'b0010 : 4'b0001)) :
				   m_isH ? (em_ADDR[1] ? 4'b1100 : 4'b0011)                :
				   4'b1111;

	wire [3:0] m_WMASK = {4{isStype(em_IR) & M_isRAM}} & m_store_WMASK;
	wire [20:0] m_word_ADDR = em_ADDR[22:2]; 
	wire M_isIO  = em_ADDR[22];
	wire M_isRAM = !M_isIO;
	wire [31:0] mw_Mdata = mem_data;

	assign IO_mem_addr  = em_ADDR;
	assign IO_mem_wr    = isStype(em_IR) & M_isIO;
	assign IO_mem_wdata = em_rs2;

        assign mem_wmask = m_WMASK;
        assign mem_addr = {9'b0,em_ADDR[22:0]};
        assign mem_wdata = m_store_DATA;
	
	/*
	wire [31:0] csr_write = (em_IR[13:12]==2'b01) ?               em_rs2 :
	*			(em_IR[13:12]==2'b10) ? mw_CSR_RES |  em_rs2 :
	*						mw_CSR_RES & ~em_rs2 ;
	*/

	always@(posedge clk) begin
		mw_IR     <= em_IR;
		mw_PC     <= em_PC;
		mw_RES    <= em_RES;
		mw_IO_RES <= IO_mem_rdata;
		mw_ADDR   <= em_ADDR;
		mw_rs2    <= em_rs2;
	end


	always@(posedge clk) begin

		case(em_IR[31:20])
			12'hC00: mw_CSR_RES <= cycle  [31:0 ];
			12'hC02: mw_CSR_RES <= instret[31:0 ];
			12'hC80: mw_CSR_RES <= cycle  [63:32];
			12'hC82: mw_CSR_RES <= instret[63:32];
			
			12'h300: mw_CSR_RES <= MSTATUS;
			12'h305: mw_CSR_RES <=   MTVEC;
			12'h341: mw_CSR_RES <=    MEPC;
			12'h342: mw_CSR_RES <=  MCAUSE;
		
			default: mw_CSR_RES <= mw_CSR_RES;
		endcase


		if(!resetn) begin
			instret <= 0;
		end else if(mw_IR != NOP) begin
			instret <= instret + 1;
		end
		cycle <= !resetn ? 0 : cycle + 1;
	end

	reg [63:0] cycle;
	reg [63:0] instret;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] mw_IR, mw_PC, mw_RES, mw_IO_RES, mw_ADDR, mw_CSR_RES, mw_rs2;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	wire [2:0] w_funct3 = funct3(mw_IR);

	wire w_isB = (w_funct3[1:0] == 2'b00);
	wire w_isH = (w_funct3[1:0] == 2'b01);
	wire w_sign_e = !w_funct3[2];
	wire W_isIO   = mw_ADDR[22];

	wire [15:0] w_loadH = mw_ADDR[1] ? mw_Mdata[31:16] : mw_Mdata[15:0];
	wire [ 7:0] w_loadB = mw_ADDR[0] ? w_loadH[15:8 ] : w_loadH[7: 0];
	wire w_load_sign    = w_sign_e & (w_isB ? w_loadB[7] : w_loadH[15]);

	wire [31:0] w_mem_RES = w_isB ? {{24{w_load_sign}}, w_loadB} :
				w_isH ? {{16{w_load_sign}}, w_loadH} :
							    mw_Mdata ;

	assign wb_DATA = isLoad(mw_IR) ? (W_isIO ? mw_IO_RES : w_mem_RES):
			 isCSRRS(mw_IR)? mw_CSR_RES:
					 mw_RES    ;

	assign wb_enable = writes_rd(mw_IR) & (rdID(mw_IR)!=0);

	assign wb_rdID = rdID(mw_IR);

	wire [31:0] wb_csr = (mw_IR[13:12]==2'b01) ?               mw_rs2 :
                             (mw_IR[13:12]==2'b10) ? mw_CSR_RES |  mw_rs2 :
                                                     mw_CSR_RES & ~mw_rs2 ;

	wire wb_csr_en = isCSRRS(mw_IR) & (mw_IR[13:12]==2'b01 | mw_IR[13:12]==2'b10 | mw_IR[13:12]==2'b11);

	wire [11:0] wb_csr_addr = mw_IR[31:20];

	wire JoB = e_JoB;
	wire [31:0] JoB_ADDR = e_JoB_ADDR;

	always@(posedge clk) begin

		if(wb_csr_en) begin
			case(wb_csr_addr)
				12'h300: MSTATUS <= wb_csr;
				12'h305: MTVEC   <= wb_csr;
				12'h341: MEPC    <= wb_csr;
				12'h342: MCAUSE  <= wb_csr;
				default: un<=un;
			endcase
		end
	end

	reg un=0;
	reg [31:0] MEPC=0, MTVEC, MCAUSE, MSTATUS;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	function [6:0] opcode; input [31:0] I; opcode = I[6:0  ]; endfunction
	function [2:0] funct3; input [31:0] I; funct3 = I[14:12]; endfunction
	function [6:0] funct7; input [31:0] I; funct7 = I[31:25]; endfunction
	function [4:0] rs1ID ; input [31:0] I; rs1ID  = I[19:15]; endfunction
	function [4:0] rs2ID ; input [31:0] I; rs2ID  = I[24:20]; endfunction
	function [4:0] rdID  ; input [31:0] I; rdID   = (isBtype(I) | isStype(I)) ? 0 : I[11:7]; endfunction
	function [4:0] shamt ; input [31:0] I; shamt  = I[24:20]; endfunction
	function [1:0] csrId ; input [31:0] I; csrId = {I[27],I[21]};endfunction

	function isRtype ; input [31:0] I; isRtype  =(I[6:0]==7'b0110011); endfunction	
	function isLoad  ; input [31:0] I; isLoad   =(I[6:0]==7'b0000011); endfunction
	function isRimm  ; input [31:0] I; isRimm   =(I[6:0]==7'b0010011); endfunction 
	function isStype ; input [31:0] I; isStype  =(I[6:0]==7'b0100011); endfunction
	function isBtype ; input [31:0] I; isBtype  =(I[6:0]==7'b1100011); endfunction
	function isLUI   ; input [31:0] I; isLUI    =(I[6:0]==7'b0110111); endfunction
	function isAUIPC ; input [31:0] I; isAUIPC  =(I[6:0]==7'b0010111); endfunction
	function isJAL   ; input [31:0] I; isJAL    =(I[6:0]==7'b1101111); endfunction
	function isJALR  ; input [31:0] I; isJALR   =(I[6:0]==7'b1100111); endfunction
	function isSYSTEM; input [31:0] I; isSYSTEM =(I[6:0]==7'b1110011); endfunction

	function isMulDiv; input [31:0] I; isMulDiv =(I[6:0]==7'b0110011 && I[25]); endfunction

	function writes_rd; input [31:0] I; writes_rd = !isStype(I) & !isBtype(I)           ; endfunction
	function reads_rs1; input [31:0] I; reads_rs1 = !(isJAL(I) | isAUIPC(I) | isLUI(I)) ; endfunction
	function reads_rs2; input [31:0] I; reads_rs2 = isRtype(I) | isBtype(I) | isStype(I); endfunction

	function isEBREAK; input [31:0] I; isEBREAK = (isSYSTEM(I) && funct3(I) == 3'b000); endfunction
	function isCSRRS;  input [31:0] I; isCSRRS = (isSYSTEM(I)); endfunction

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        `ifdef BENCH
                /* verilator lint_off WIDTH */
                always @(posedge clk) begin
                        if(halt) begin
				/*$display("Simulated processor's report");
				$display("----------------------------");
				$display("Numbers of = (Cycles: %d, Instret: %d)", cycle, instret);
				$display("CPI = %f" , cycle/instret);*/
				//$display("MEPC 0x%04x\nMSTATUS 0x%04x\nMTVEC 0x%04x\nMCAUSE 0x%04x\n", MEPC, MSTATUS, MTVEC, MCAUSE);
				$finish();
                        end
                end
                /* verilator lint_on WIDTH */
        `endif

endmodule
