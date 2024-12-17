`ifdef ALU
	`include "alu2.v"
`else
	`include "alu.v"
`endif

module torv32 #(

	parameter       BYPASS        = 0,
	parameter [3:0] BRANCH_PRED   = 4'b0,
        parameter       BHT_ADDR_BITS = 4

)(
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
	output        IO_mem_wr     // IO write flag
);

	wire rs1_HAZ;
        wire rs2_HAZ;
        wire data_HAZ;
	wire e_m_fwd_rs1;
        wire e_w_fwd_rs1;
        wire e_m_fwd_rs2;
        wire e_w_fwd_rs2;
        wire [31:0] e_rs1;
        wire [31:0] e_rs2;

	generate 
		if(BYPASS) begin
		
			assign rs1_HAZ = reads_rs1(fd_IR) & (rs1ID(fd_IR) == rdID(de_IR));

			assign rs2_HAZ = reads_rs2(fd_IR) & (rs2ID(fd_IR) == rdID(de_IR));

			assign data_HAZ = !fd_NOP & (isLoad(de_IR) | isCSRRS(de_IR)) & (rs1_HAZ | rs2_HAZ);
		
			assign e_m_fwd_rs1 = (rdID(em_IR)!=0) & (writes_rd(em_IR)) & (rdID(em_IR) == rs1ID(de_IR));
			assign e_w_fwd_rs1 = (rdID(mw_IR)!=0) & (writes_rd(mw_IR)) & (rdID(mw_IR) == rs1ID(de_IR));
		
			assign e_m_fwd_rs2 = (rdID(em_IR)!=0) & (writes_rd(em_IR)) & (rdID(em_IR) == rs2ID(de_IR));
			assign e_w_fwd_rs2 = (rdID(mw_IR)!=0) & (writes_rd(mw_IR)) & (rdID(mw_IR) == rs2ID(de_IR));
			
			assign e_rs1 = e_m_fwd_rs1 ? em_RES  :
						    e_w_fwd_rs1 ? wb_DATA :
								  de_rs1  ;

			assign e_rs2 = e_m_fwd_rs2 ? em_RES  :
					    e_w_fwd_rs2 ? wb_DATA :
								  de_rs2  ;
					
		end else begin
		
			assign rs1_HAZ = !fd_NOP & reads_rs1(fd_IR) & rs1ID(fd_IR)!=0 &    (
					(writes_rd(de_IR) & (rs1ID(fd_IR) == rdID(de_IR))) |
					(writes_rd(em_IR) & (rs1ID(fd_IR) == rdID(em_IR))) );

			assign rs2_HAZ = !fd_NOP & reads_rs2(fd_IR) & rs2ID(fd_IR)!=0 &    (
					(writes_rd(de_IR) & (rs2ID(fd_IR) == rdID(de_IR))) |
					(writes_rd(em_IR) & (rs2ID(fd_IR) == rdID(em_IR))) );

			assign data_HAZ = rs1_HAZ | rs2_HAZ;

			assign e_rs1 = de_rs1;
			assign e_rs2 = de_rs2;

		end 
	endgenerate

	localparam BP_HIST_BITS  = (BRANCH_PRED == 4'd3) ? 7 : 14;
        localparam BHT_SIZE=1<<BHT_ADDR_BITS;

        reg [1:0]               BHT [BHT_SIZE-1:0]; // BRANCH HISTORY TALBE
	reg [BP_HIST_BITS-1 :0] BH;                 // BRANCH HISTORY
	reg [BHT_ADDR_BITS-1:0] de_BHT_index;
	reg                     de_predict;	
	wire                    d_predict;
	wire                    d_JoB_now;
	wire [31:0]             d_JoB_ADDR;
	wire [31:0]             f_PC;
	wire                    e_JoB;
	wire [31:0]             e_ADDin2;	

	generate 
		if(BRANCH_PRED == 4'b0000) begin
			assign f_PC = em_JoB ? em_JoB_ADDR : PC;

        	        assign e_JoB = isJAL(de_IR) | isJALR(de_IR) | (isBtype(de_IR) & e_takeB);
	                assign e_ADDin2 = e_IMM;

                end else if(BRANCH_PRED == 4'b0001) begin
		
        		assign f_PC = d_JoB_now  ? d_JoB_ADDR  :
                                      em_JoB     ? em_JoB_ADDR :
                                                            PC ;

			assign d_predict  = fd_IR[31];
			assign d_JoB_now  = !fd_NOP & (isJAL(fd_IR) | (isBtype(fd_IR) & d_predict));
			assign d_JoB_ADDR = fd_PC + (isJAL(fd_IR) ? Jimm(fd_IR) : Bimm(fd_IR));
			always@(posedge clk)
				if(!d_stall) de_predict <= d_predict;
	
			assign e_JoB = isJALR(de_IR) | (isBtype(de_IR) & (e_takeB^de_predict));
	                assign e_ADDin2 = (isBtype(de_IR) & de_predict)   ? 32'd4 : e_IMM;

		end else if(BRANCH_PRED == 4'b0010) begin 
		
			assign f_PC = d_JoB_now  ? d_JoB_ADDR  :
                                      em_JoB     ? em_JoB_ADDR :
                                                            PC ;

			assign d_predict  = BHT[BHT_index(fd_PC)][1];
			assign d_JoB_now  = !fd_NOP & (isJAL(fd_IR) | (isBtype(fd_IR) & d_predict));
			assign d_JoB_ADDR = fd_PC + (isJAL(fd_IR) ? Jimm(fd_IR) : Bimm(fd_IR));
			always@(posedge clk)
				if(!d_stall) begin
					de_predict   <= d_predict;
					de_BHT_index <= BHT_index(fd_PC);
				end
        	
			assign e_JoB = isJALR(de_IR) | (isBtype(de_IR) & (e_takeB^de_predict));
	                assign e_ADDin2 = (isBtype(de_IR) & de_predict)   ? 32'd4 : e_IMM;

                	always@(posedge clk) begin
                	        if(isBtype(de_IR))
        	                        BHT[de_BHT_index] <= incdec_sat(BHT[de_BHT_index], e_takeB);
	                end


		end else if(BRANCH_PRED == 4'b0011) begin

			assign f_PC = d_JoB_now  ? d_JoB_ADDR  :
                                      em_JoB     ? em_JoB_ADDR :
                                                            PC ;

			assign d_predict  = BHT[BHT_index_gselect(fd_PC)][1];
			assign d_JoB_now  = !fd_NOP & (isJAL(fd_IR) | (isBtype(fd_IR) & d_predict));
			assign d_JoB_ADDR = fd_PC + (isJAL(fd_IR) ? Jimm(fd_IR) : Bimm(fd_IR));
			always@(posedge clk)
				if(!d_stall) begin
					de_predict   <= d_predict;
					de_BHT_index <= BHT_index_gselect(fd_PC);
				end
			
			assign e_JoB = isJALR(de_IR) | (isBtype(de_IR) & (e_takeB^de_predict));
			assign e_ADDin2 = (isBtype(de_IR) & de_predict)   ? 32'd4 : e_IMM;

			always@(posedge clk) begin
				if(isBtype(de_IR)) begin
					BH <= {e_takeB, BH[BP_HIST_BITS-1:1]};
					BHT[de_BHT_index] <= incdec_sat(BHT[de_BHT_index], e_takeB);
				end
			end

		end else if(BRANCH_PRED == 4'b0100) begin

			assign f_PC = d_JoB_now  ? d_JoB_ADDR  :
                                      em_JoB     ? em_JoB_ADDR :
                                                            PC ;

			assign d_predict  = BHT[BHT_index_gshare(fd_PC)][1];
			assign d_JoB_now  = !fd_NOP & (isJAL(fd_IR) | (isBtype(fd_IR) & d_predict));
			assign d_JoB_ADDR = fd_PC + (isJAL(fd_IR) ? Jimm(fd_IR) : Bimm(fd_IR));
			always@(posedge clk)
				if(!d_stall) begin
					de_predict   <= d_predict;
					de_BHT_index <= BHT_index_gshare(fd_PC);
				end
			
			assign e_JoB = isJALR(de_IR) | (isBtype(de_IR) & (e_takeB^de_predict));
			assign e_ADDin2 = (isBtype(de_IR) & de_predict)   ? 32'd4 : e_IMM;

			always@(posedge clk) begin
				if(isBtype(de_IR)) begin
					BH <= {e_takeB, BH[BP_HIST_BITS-1:1]};
					BHT[de_BHT_index] <= incdec_sat(BHT[de_BHT_index], e_takeB);
				end
			end

		end  
	endgenerate

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire halt = resetn & isEBREAK(de_IR);	

	wire f_stall = data_HAZ | halt;
	wire d_stall = data_HAZ | halt;

	wire e_flush = e_JoB | data_HAZ;
	wire d_flush = e_JoB;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg [31:0] PC;
	assign imem_addr = f_PC[15:0];

	always@(posedge clk) begin
		if(!f_stall) begin
			fd_IR <= imem_data;
			fd_PC <= f_PC;
			PC    <= f_PC +4;
		end

		fd_NOP <= d_flush | !resetn;

		if(!resetn)
			PC <=0;
	end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] fd_IR, fd_PC;
        reg fd_NOP;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	localparam NOP = 32'b0000000_00000_00000_000_00000_0110011;
	
	wire        wb_enable;
	wire [31:0] wb_DATA;
	wire [4:0]  wb_rdID;

	reg [31:0] reg_file[0:31];
	
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] de_IR, de_PC;
	wire [31:0] de_rs1 = reg_file[de_IR[19:15]];
       	wire [31:0] de_rs2 = reg_file[de_IR[24:20]];


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [31:0] e_IMM;

	imm_mux m0(
		.instr(de_IR),
		.imm(e_IMM)
	);

	wire [31:0] e_ALUin1 = (isJAL(de_IR) | isJALR(de_IR) | isAUIPC(de_IR)) ? de_PC : e_rs1;
	wire [31:0] e_ALUin2 = (isRtype(de_IR) | isBtype(de_IR))? e_rs2 :
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

	wire [31:0] e_ADDin1 = (isJAL(de_IR) | isBtype(de_IR)) ? de_PC : e_rs1;
	wire [31:0] e_ADDR_RES = e_ADDin1 + e_ADDin2;
	wire [31:0] e_ADDR = {e_ADDR_RES[31:1], e_ADDR_RES[0] & (~isJALR(de_IR))}; 

	wire [31:0] e_JoB_ADDR = e_ADDR;

	always@(posedge clk) begin
		em_IR  <= de_IR;
		em_PC  <= de_PC;
		em_rs2 <= e_rs2;
		em_RES <= e_RES;
		em_ADDR <= e_ADDR;
		em_JoB  <= e_JoB;
		em_JoB_ADDR <= e_JoB_ADDR;
	end
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg[31:0] em_IR, em_PC, em_rs2, em_RES, em_ADDR, em_JoB_ADDR;
	reg em_JoB;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [2:0] m_funct3 = em_IR[14:12];
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

	wire M_isIO  = em_ADDR[22];
	wire M_isRAM = !M_isIO;
	wire [3:0] m_WMASK = {4{isStype(em_IR) & M_isRAM}} & m_store_WMASK;
	wire [20:0] m_word_ADDR = em_ADDR[22:2];

	assign IO_mem_addr  = em_ADDR;
	assign IO_mem_wr    = isStype(em_IR) & M_isIO;
	assign IO_mem_wdata = em_rs2;

	assign mem_wmask = m_WMASK;
	assign mem_addr = {11'b0,m_word_ADDR};
	assign mem_wdata = m_store_DATA;

	always@(posedge clk) begin
		mw_IR     <= em_IR;
		mw_PC     <= em_PC;
		mw_RES    <= em_RES;
		mw_IO_RES <= IO_mem_rdata;
		mw_ADDR   <= em_ADDR;
		mw_Mdata  <= mem_data;

		case({em_IR[27], em_IR[21]}) // CSR ID
			2'b00: mw_CSR_RES <= cycle[31:0];
			2'b10: mw_CSR_RES <= cycle[63:32];
			2'b01: mw_CSR_RES <= instret[31:0];
			2'b11: mw_CSR_RES <= instret[63:32];	 
		endcase 

		cycle <= !resetn ? 0 : cycle + 1;
		if(!resetn) begin
			instret <= 0;
		end else if(mw_IR != NOP) begin
			instret <= instret + 1;
		end
	end

	reg [63:0] cycle;
	reg [63:0] instret;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] mw_IR, mw_PC, mw_RES, mw_IO_RES, mw_ADDR, mw_Mdata, mw_CSR_RES;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	wire [2:0] w_funct3 = mw_IR[14:12];

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

	wire JoB = e_JoB;
	wire [31:0] JoB_ADDR = e_JoB_ADDR;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        function [4:0] rs1ID ; input [31:0] I; rs1ID  = I[19:15]; endfunction
        function [4:0] rs2ID ; input [31:0] I; rs2ID  = I[24:20]; endfunction
	function [4:0] rdID  ; input [31:0] I; rdID   = (isBtype(I) | isStype(I)) ? 0 : I[11:7]; endfunction

	function isRtype ; input [31:0] I; isRtype  =(I[6:0]==7'b0110011); endfunction	
	function isLoad  ; input [31:0] I; isLoad   =(I[6:0]==7'b0000011); endfunction
	function isRimm  ; input [31:0] I; isRimm   =(I[6:0]==7'b0010011); endfunction 
	function isStype ; input [31:0] I; isStype  =(I[6:0]==7'b0100011); endfunction
	function isBtype ; input [31:0] I; isBtype  =(I[6:0]==7'b1100011); endfunction
	function isLUI   ; input [31:0] I; isLUI    =(I[6:0]==7'b0110111); endfunction
	function isAUIPC ; input [31:0] I; isAUIPC  =(I[6:0]==7'b0010111); endfunction
	function isJAL   ; input [31:0] I; isJAL    =(I[6:0]==7'b1101111); endfunction
	function isJALR  ; input [31:0] I; isJALR   =(I[6:0]==7'b1100111); endfunction
	function isEBREAK; input [31:0] I; isEBREAK =((I[6:0]==7'b1110011) && I[14:12] == 3'b000); endfunction
	function isCSRRS ; input [31:0] I; isCSRRS  =((I[6:0]==7'b1110011) && I[14:12] == 3'b010); endfunction

	function [31:0] Bimm; input [31:0] I; Bimm = {{20{I[31]}},I[7],I[30:25],I[11:8],1'b0};   endfunction
        function [31:0] Jimm; input [31:0] I; Jimm = {{12{I[31]}},I[19:12],I[20],I[30:21],1'b0}; endfunction

	function writes_rd; input [31:0] I; writes_rd = !isStype(I) & !isBtype(I)           ; endfunction
	function reads_rs1; input [31:0] I; reads_rs1 = !(isJAL(I) | isAUIPC(I) | isLUI(I)) ; endfunction
	function reads_rs2; input [31:0] I; reads_rs2 = isRtype(I) | isBtype(I) | isStype(I); endfunction
        
	function [BHT_ADDR_BITS-1:0] BHT_index;
                input [31:0] PC;
                BHT_index = PC[BHT_ADDR_BITS+1:2];
        endfunction

        function [BHT_ADDR_BITS-1:0] BHT_index_gselect;
                input [31:0] PC;
                BHT_index_gselect = {PC[BHT_ADDR_BITS+1:2], BH[BP_HIST_BITS-1:0]};
        endfunction

        function [BHT_ADDR_BITS-1:0] BHT_index_gshare;
                input [31:0] PC;
                /* verilator lint_off WIDTH */
                BHT_index_gshare = PC[15:2] ^ BH;
                /* verilator lint_on WIDTH */
        endfunction

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

	`ifdef BENCH
	   always @(posedge clk) begin
		   if(halt) $finish(); 
	   end
	`endif
        `ifdef BENC

                integer nbBranch = 0;
                integer nbPredictHit = 0;
                integer nbJAL  = 0;
                integer nbJALR = 0;

                always @(posedge clk) begin
                        if(resetn) begin
                                if(isBtype(de_IR)) begin
                                        nbBranch <= nbBranch + 1;
                                        if(e_takeB == de_predict) begin
                                                nbPredictHit <= nbPredictHit + 1;
                                        end
                                end
                                if(isJAL(de_IR)) begin
                                        nbJAL <= nbJAL + 1;
                                end
                                if(isJALR(de_IR)) begin
                                        nbJALR <= nbJALR + 1;
                                end
                        end
                end
                /* verilator lint_off WIDTH */
                always @(posedge clk) begin
                        if(halt) begin
                                $display("Simulated processor's report");
                                $display("----------------------------");
                                $display("Branch hits= %3.3f\%%", nbPredictHit*100.0/nbBranch);
                                $display("Numbers of = (Cycles: %d, Instret: %d)", cycle, instret);
                                $display("Instr. mix = (Branch:%3.3f\%% JAL:%3.3f\%% JALR:%3.3f\%%)",
                                          nbBranch*100.0/instret,
                                             nbJAL*100.0/instret,
                                            nbJALR*100.0/instret);
                                $display("Numbers of = (Branch: %d, JAL: %d, JALR: %d)", nbBranch, nbJAL, nbJALR);
                                $display("Size of BHT = %d", BHT_ADDR_BITS);
                                $display("Size of BPH = %d" , BP_HIST_BITS);
                                $finish();
                        end
                end
                /* verilator lint_on WIDTH */
        `endif

endmodule

