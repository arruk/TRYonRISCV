`default_nettype none

`ifdef ALU
	`include "alu2.v"
`else
	`include "alu.v"
`endif

module torv32(
	input         clk,
        input 	      resetn,

        output [15:0] imem_addr,    // addres to fetch an instruction
        input  [31:0] imem_data,    // instruction fetched

        input  [31:0] mem_data,     // data read from memory
        output [ 3:0] mem_wmask,    // mask for write in memory
        output [31:0] mem_addr,     // address to write/read
        output [31:0] mem_wdata,    // data to write

	output [31:0] IO_mem_addr,  // IO mem address
	input  [31:0] IO_mem_rdata, // data read from IO
	output [31:0] IO_mem_wdata, // data written to IO
	output        IO_mem_wr    // IO write flag
);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	wire halt = resetn & isEBREAK(de_IR);	

        wire rs1_HAZ = reads_rs1(fd_IR) & (rs1ID(fd_IR) == rdID(de_IR));

        wire rs2_HAZ = reads_rs2(fd_IR) & (rs2ID(fd_IR) == rdID(de_IR));

	wire data_HAZ = !fd_NOP & (isLoad(de_IR) | isCSRRS(de_IR)) & ((writes_rd1(fd_IR)) | (rs1_HAZ | rs2_HAZ)); 
	
	wire f_stall = data_HAZ | halt;
	wire d_stall = data_HAZ | halt;

	wire e_flush = e_JoB | data_HAZ;
	wire d_flush = e_JoB;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	function [BHT_ADDR_BITS-1:0] BHT_index;
                input [31:0] PC;
                /* verilator lint_off WIDTH */
                BHT_index = PC[15:2] ^ BH;
                /* verilator lint_on WIDTH */
        endfunction

        //gshare with 14 bits of global branch hist and 14 bits of pc address
        localparam BP_HIST_BITS = 14;
        parameter BHT_ADDR_BITS = 16 ;
        localparam BHT_SIZE=1<<BHT_ADDR_BITS;

        reg [1:0] BHT [BHT_SIZE-1:0];
        reg [BP_HIST_BITS-1:0] BH;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg [31:0] PC;
        wire [31:0] f_PC = d_JoB_now  ? d_JoB_ADDR  :
                           em_JoB_now ? em_JoB_ADDR :
                                                 PC ;
	
	always@(posedge clk) begin
		if(!f_stall) begin
			fd_IR <= imem_data; 
			fd_PC <= f_PC;
			PC  <= f_PC+4;
		end

		fd_NOP <= d_flush | !resetn;

		if(!resetn) begin
			PC  <=0;
		end
	
	end

	wire JoB = e_JoB;
	wire [31:0] JoB_ADDR = e_JoB_ADDR;

	assign imem_addr = f_PC[15:0];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] fd_IR, fd_PC;
        reg fd_NOP;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	localparam NOP = 32'b0000000_00000_00000_000_00000_0110011;
	
	wire d_predict = BHT[BHT_index(fd_PC)][1];
        wire d_JoB_now = !fd_NOP & (isJAL(fd_IR) | (isBtype(fd_IR) & d_predict));
        wire [31:0] d_JoB_ADDR = fd_PC + (isJAL(fd_IR) ? Jimm(fd_IR) : Bimm(fd_IR));

	wire        wb_enable;
	wire [31:0] wb_DATA;
	wire [4:0]  wb_rdID;

	reg [31:0] reg_file [0:31];
	
	always@(posedge clk) begin
		if(!d_stall) begin
			de_IR <= (e_flush | fd_NOP) ? NOP : fd_IR;
			de_PC <= fd_PC;	
			de_predict  <= d_predict;
			de_BHTindex <= BHT_index(fd_PC);
		end	

		if(e_flush)
			de_IR <= NOP;
		
		if(wb_enable) begin
			reg_file[wb_rdID] <= wb_DATA;
		end

	end	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg de_predict;
	reg [BHT_ADDR_BITS-1:0] de_BHTindex;
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
	wire [31:0] e_ALUout;
	wire e_takeB;

	alu u0(
		.in_a(e_ALUin1),
	        .in_b(e_ALUin2),
	        .inst(de_IR),
	        .result(e_ALUout),
	        .take_b(e_takeB)
	);
	wire [31:0] e_RES = isLUI(de_IR) ? e_IMM : e_ALUout;

	wire [31:0] e_ADDin1 = (isJAL(de_IR) | isBtype(de_IR)) ? de_PC : de_rs1;
	wire [31:0] e_ADDin2 = (isBtype(de_IR) & de_predict)   ? 32'd4 : e_IMM;
	wire [31:0] e_ADDR_RES = e_ADDin1 + e_ADDin2;
	wire [31:0] e_ADDR = {e_ADDR_RES[31:1], e_ADDR_RES[0] & (~isJALR(de_IR))}; 

	wire e_JoB = isJALR(de_IR) | (isBtype(de_IR) & (e_takeB^de_predict));
	wire [31:0] e_JoB_ADDR = e_ADDR;

	always@(posedge clk) begin
		em_IR   <= de_IR;
		em_PC   <= de_PC;
		em_rs2  <= de_rs2;
		em_RES  <= e_RES;
		em_ADDR <= e_ADDR;
                em_JoB_now  <= e_JoB;
                em_JoB_ADDR <= e_JoB_ADDR;
		if(isBtype(de_IR)) begin
			BH <= {e_takeB, BH[BP_HIST_BITS-1:1]};
                        BHT[de_BHTindex] <= incdec_sat(BHT[de_BHTindex], e_takeB);
		end

		case(csrId(de_IR))
                        2'b00: em_CSR_RES <= cycle[31:0];
                        2'b10: em_CSR_RES <= cycle[63:32];
                        2'b01: em_CSR_RES <= instret[31:0];
                        2'b11: em_CSR_RES <= instret[63:32];
                endcase

                if(!resetn) begin
                        instret <= 0;
                end else if(em_IR != NOP) begin
                        instret <= instret + 1;
                end
                cycle <= !resetn ? 0 : cycle + 1;

	end
	
	reg [63:0] cycle;
	reg [63:0] instret;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg[31:0] em_IR, em_PC, em_rs2, em_RES, em_ADDR, em_CSR_RES, em_JoB_ADDR;
	reg em_JoB_now;

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

	assign IO_mem_addr  = em_ADDR;
	assign IO_mem_wr    = isStype(em_IR) & M_isIO;
	assign IO_mem_wdata = em_rs2;

        assign mem_wmask = m_WMASK;
        assign mem_addr = {11'b0,m_word_ADDR};
        assign mem_wdata = m_store_DATA;
       
        wire e_sign_e = !m_funct3[2];
        wire e_isIO   = em_ADDR[22];

        wire [15:0] e_loadH = em_ADDR[1] ? mem_data[31:16] : mem_data[15:0];
        wire [ 7:0] e_loadB = em_ADDR[0] ? e_loadH[15:8 ] : e_loadH[7: 0];
        wire e_load_sign    = e_sign_e & (m_isB ? e_loadB[7] : e_loadH[15]);

        wire [31:0] e_mem_RES = m_isB ? {{24{e_load_sign}}, e_loadB} :
                                m_isH ? {{16{e_load_sign}}, e_loadH} :
                                                            mem_data ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	assign wb_DATA = isLoad(em_IR)  ? (em_ADDR[22] ? IO_mem_rdata : e_mem_RES):
			 isCSRRS(em_IR) ? em_CSR_RES:
					       e_RES;

	assign wb_enable = ((isLoad(em_IR) | isCSRRS(em_IR)) & (rdID(em_IR)!=0)) | (writes_rd1(de_IR) & (rdID(de_IR)!=0));

	assign wb_rdID = (isLoad(em_IR) | isCSRRS(em_IR)) ? rdID(em_IR) : rdID(de_IR) ;

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

	function writes_rd;  input [31:0] I; writes_rd = !isStype(I) & !isBtype(I) ; endfunction
	function writes_rd1; input [31:0] I; writes_rd1 = !isStype(I) & !isBtype(I) & !isLoad(I) & !isCSRRS(I) ; endfunction
	function reads_rs1;  input [31:0] I; reads_rs1 = !(isJAL(I) | isAUIPC(I) | isLUI(I)) ; endfunction
	function reads_rs2;  input [31:0] I; reads_rs2 = isRtype(I) | isBtype(I) | isStype(I); endfunction

        function [31:0] Bimm; input [31:0] I; Bimm = {{20{I[31]}},I[7],I[30:25],I[11:8],1'b0};   endfunction
        function [31:0] Jimm; input [31:0] I; Jimm = {{12{I[31]}},I[19:12],I[20],I[30:21],1'b0}; endfunction

	function isEBREAK; input [31:0] I; isEBREAK = (isSYSTEM(I) && funct3(I) == 3'b000); endfunction
	function isCSRRS; input [31:0] I; isCSRRS = (isSYSTEM(I) && funct3(I) == 3'b010); endfunction

	function [1:0] incdec_sat;
                input [1:0] prev;
                input dir;
                incdec_sat =
                        {dir, prev} == 3'b000 ? 2'b00 :
                        {dir, prev} == 3'b001 ? 2'b00 :
                        {dir, prev} == 3'b010 ? 2'b01 :
                        {dir, prev} == 3'b011 ? 2'b10 :
                        {dir, prev} == 3'b100 ? 2'b01 :
                        {dir, prev} == 3'b101 ? 2'b10 :
                        {dir, prev} == 3'b110 ? 2'b11 :
                                                2'b11 ;
        endfunction;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*`ifdef BENCH
	   always @(posedge clk) begin
		   if(halt) $finish(); 
	   end
	`endif*/
        `ifdef BENCH

                /* verilator lint_off WIDTH */
                always @(posedge clk) begin
                        if(halt) begin
                                $display("Simulated processor's report");
                                $display("----------------------------");
                                $display("Numbers of = (Cycles: %d, Instret: %d)", cycle, instret);
                                $display("CPI = %f" , cycle/instret);
                                $finish();
                        end
                end
                /* verilator lint_on WIDTH */
        `endif

endmodule
