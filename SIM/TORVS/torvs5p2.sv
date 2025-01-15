`ifndef BENCH
        `define SYN
`endif

`ifndef SYN
        `include "AUX/alu.v"
`endif

module torv32(
	input         clk   ,
        input 	      resetn,

	output        a_imem_en  ,      
        output [31:0] a_imem_addr,  
        input  [31:0] a_imem_data,    

        input  [31:0] a_mem_data ,     
        output [ 3:0] a_mem_wmask,    
        output [31:0] a_mem_addr ,     
        output [31:0] a_mem_wdata,    

	output        a_mem_cen,
        output        b_mem_cen,

	output        b_imem_en  ,      
        output [31:0] b_imem_addr,    
        input  [31:0] b_imem_data,    

        input  [31:0] b_mem_data ,     
        output [ 3:0] b_mem_wmask,    
        output [31:0] b_mem_addr ,     
        output [31:0] b_mem_wdata,    

	output [31:0] a_IO_mem_addr ,  
	input  [31:0] a_IO_mem_rdata, 
	output [31:0] a_IO_mem_wdata, 
	output        a_IO_mem_wr,   

	output [31:0] b_IO_mem_addr ,  
	input  [31:0] b_IO_mem_rdata, 
	output [31:0] b_IO_mem_wdata, 
	output        b_IO_mem_wr    

);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	wire a_rs1_HAZ  = reads_rs1(a_fd_IR) & (rs1ID(a_fd_IR) == rdID(a_de_IR));
	wire a_rs2_HAZ  = reads_rs2(a_fd_IR) & (rs2ID(a_fd_IR) == rdID(a_de_IR));

	wire ba_rs1_HAZ = reads_rs1(b_fd_IR) & (rs1ID(b_fd_IR) == rdID(a_de_IR));
        wire ba_rs2_HAZ = reads_rs2(b_fd_IR) & (rs2ID(b_fd_IR) == rdID(a_de_IR));

        wire a_data_HAZ   = !a_fd_NOP & (isLoad(a_de_IR) | isCSRRS(a_de_IR)) & ( a_rs1_HAZ | a_rs2_HAZ );
        wire ba_data_HAZ  = !b_fd_NOP & (isLoad(a_de_IR) | isCSRRS(a_de_IR)) & (ba_rs1_HAZ | ba_rs2_HAZ) & !control_HAZ;

        wire data_HAZ = a_data_HAZ | ba_data_HAZ;

	wire a_f_stall = halt | data_HAZ;
	wire a_d_stall = halt | data_HAZ;

	wire a_e_flush = a_e_JoB | data_HAZ;
	wire a_d_flush = a_e_JoB ;

	wire b_f_stall = halt | data_HAZ;
	wire b_d_stall = halt | data_HAZ;

	wire b_e_flush = a_e_JoB | data_HAZ;
	wire b_d_flush = a_e_JoB;

	wire control_HAZ = !b_ins_ALL | b_LBC_HAZ | fd_data_HAZ;
	
	wire b_ins_ALL =isRtype(b_fd_IR) | isRimm(b_fd_IR) | isAUIPC(b_fd_IR) | isLUI(b_fd_IR) | isStype(b_fd_IR);
	wire b_LBC_HAZ = isBtype(a_fd_IR) | isJAL(a_fd_IR) | isJALR(a_fd_IR);
	wire ba_fd_rs1_HAZ = !b_fd_NOP & reads_rs1(b_fd_IR) & rs1ID(b_fd_IR)!=0 & (
			   (writes_rd(a_fd_IR) & (rs1ID(b_fd_IR) == rdID(a_fd_IR))));
	wire ba_fd_rs2_HAZ = !b_fd_NOP & reads_rs2(b_fd_IR) & rs2ID(b_fd_IR)!=0 & (
			   (writes_rd(a_fd_IR) & (rs2ID(b_fd_IR) == rdID(a_fd_IR))));
	wire fd_data_HAZ = (ba_fd_rs1_HAZ | ba_fd_rs2_HAZ);

	wire halt = resetn & isEBREAK(a_de_IR);	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] f_PC;
	wire [31:0] a_fd_IR = a_imem_data;
	wire [31:0] b_fd_IR = b_imem_data;

	always@(posedge clk) begin
		if(!a_f_stall) begin
			a_fd_PC <= a_imem_addr;

			f_PC <= (control_HAZ & !a_fd_NOP) ? f_PC + 4:
						            f_PC + 8;

		end

		if(a_e_JoB) begin
			f_PC <= a_e_JoB_ADDR;
		end 

		a_fd_NOP <= a_d_flush | !resetn;
		
		if(!b_f_stall) begin
			b_fd_PC <= b_imem_addr;
		end

		b_fd_NOP <= b_d_flush  | !resetn;
		
		
		if(!resetn) begin
			f_PC <= 32'h00000;
		end
	       
	end
	
	assign a_imem_en   = !a_f_stall;
	assign a_imem_addr = (control_HAZ & !a_fd_NOP) ? f_PC-4 : f_PC;

	assign b_imem_en   = !b_f_stall;
	assign b_imem_addr = (control_HAZ & !a_fd_NOP) ? f_PC :  f_PC+4 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] a_fd_PC, b_fd_PC;
        reg a_fd_NOP, b_fd_NOP, b_control_HAZ;
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	localparam NOP = 32'b0000000_00000_00000_000_00000_0110011;
	
	wire        a_wb_enable;
	wire [31:0] a_wb_DATA;
	wire [4:0]  a_wb_rdID;

	wire        b_wb_enable;
	wire [31:0] b_wb_DATA;
	wire [4:0]  b_wb_rdID;

	reg [31:0] reg_file [0:31];
	
	always@(posedge clk) begin

		if(!a_d_stall) begin
			a_de_IR <= (a_e_flush | a_fd_NOP) ? NOP : a_fd_IR;

			a_de_PC <= a_fd_PC;
		end
		
		if(a_e_flush) begin
			a_de_IR <= NOP;
		end

		if(!b_d_stall) begin
			b_de_IR <= (b_e_flush | b_fd_NOP | control_HAZ) ? NOP : b_fd_IR;

			b_de_PC <= b_fd_PC;
		end 
			
		if(b_e_flush) begin
			b_de_IR <= NOP;
		end

		if(a_wb_enable) begin
			reg_file[a_wb_rdID] <= a_wb_DATA;
		end
	
		if(b_wb_enable) begin
			reg_file[b_wb_rdID] <= b_wb_DATA;
		end

	end	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] a_de_IR, a_de_PC;
	reg [31:0] b_de_IR, b_de_PC;

	wire [31:0] a_de_rs1 = reg_file[rs1ID(a_de_IR)];
       	wire [31:0] a_de_rs2 = reg_file[rs2ID(a_de_IR)];

	wire [31:0] b_de_rs1 = reg_file[rs1ID(b_de_IR)];
       	wire [31:0] b_de_rs2 = reg_file[rs2ID(b_de_IR)];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire ae_am_fwd_rs1 = (rdID(a_em_IR)!=0) & (writes_rd(a_em_IR)) & (rdID(a_em_IR) == rs1ID(a_de_IR));
        wire ae_aw_fwd_rs1 = (rdID(a_mw_IR)!=0) & (writes_rd(a_mw_IR)) & (rdID(a_mw_IR) == rs1ID(a_de_IR));

	wire ae_bm_fwd_rs1 = (rdID(b_em_IR)!=0) & (writes_rd(b_em_IR)) & (rdID(b_em_IR) == rs1ID(a_de_IR));
        wire ae_bw_fwd_rs1 = (rdID(b_mw_IR)!=0) & (writes_rd(b_mw_IR)) & (rdID(b_mw_IR) == rs1ID(a_de_IR));

        wire ae_am_fwd_rs2 = (rdID(a_em_IR)!=0) & (writes_rd(a_em_IR)) & (rdID(a_em_IR) == rs2ID(a_de_IR));
        wire ae_aw_fwd_rs2 = (rdID(a_mw_IR)!=0) & (writes_rd(a_mw_IR)) & (rdID(a_mw_IR) == rs2ID(a_de_IR));

	wire ae_bm_fwd_rs2 = (rdID(b_em_IR)!=0) & (writes_rd(b_em_IR)) & (rdID(b_em_IR) == rs2ID(a_de_IR));
        wire ae_bw_fwd_rs2 = (rdID(b_mw_IR)!=0) & (writes_rd(b_mw_IR)) & (rdID(b_mw_IR) == rs2ID(a_de_IR));

        wire [31:0] a_e_rs1 = ae_bm_fwd_rs1 ? b_em_RES  : //
			      ae_am_fwd_rs1 ? a_em_RES  : //
                              ae_bw_fwd_rs1 ? b_wb_DATA : // A ORDEM IMPORTA!!
                              ae_aw_fwd_rs1 ? a_wb_DATA : //
                                              a_de_rs1  ; //

        wire [31:0] a_e_rs2 = ae_bm_fwd_rs2 ? b_em_RES  : //
			      ae_am_fwd_rs2 ? a_em_RES  : //
                              ae_bw_fwd_rs2 ? b_wb_DATA : // A ORDEM IMPORTA!!
                              ae_aw_fwd_rs2 ? a_wb_DATA : //
                                              a_de_rs2  ; //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [31:0] a_e_IMM;

	imm_mux m0(
		.instr(a_de_IR),
		.imm(a_e_IMM)
	);

	wire [31:0] a_e_ALUin1 = (isJAL(a_de_IR) | isJALR(a_de_IR) | isAUIPC(a_de_IR)) ? a_de_PC : a_e_rs1;
	wire [31:0] a_e_ALUin2 = (isRtype(a_de_IR) | isBtype(a_de_IR))? a_e_rs2 :
	       		         (isRimm(a_de_IR)  | isAUIPC(a_de_IR))? a_e_IMM  :
			       		                    		  32'd4  ;	
	wire [31:0] a_e_ALUout;
	wire a_e_takeB;

	alu u0(
		.in_a(a_e_ALUin1),
	        .in_b(a_e_ALUin2),
	        .inst(a_de_IR),
	        .result(a_e_ALUout),
	        .take_b(a_e_takeB)
	);
	wire [31:0] a_e_RES = isLUI(a_de_IR) ? a_e_IMM : a_e_ALUout;

	wire [31:0] a_e_ADDin1 = (isJAL(a_de_IR) | isBtype(a_de_IR)) ? a_de_PC : a_e_rs1;
	wire [31:0] a_e_ADDR_RES = a_e_ADDin1 + a_e_IMM;
	wire [31:0] a_e_ADDR = {a_e_ADDR_RES[31:1], a_e_ADDR_RES[0] & (~isJALR(a_de_IR))}; 

	wire a_e_JoB = isJAL(a_de_IR) | isJALR(a_de_IR) | (isBtype(a_de_IR) & a_e_takeB);
	wire [31:0] a_e_JoB_ADDR = a_e_ADDR;

	always@(posedge clk) begin
		a_em_IR   <= a_de_IR;
		a_em_PC   <= a_de_PC;
		a_em_rs2  <= a_e_rs2;
		a_em_RES  <= a_e_RES;
		a_em_ADDR <= a_e_ADDR;
	end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        wire b_e_bm_fwd_rs1 = (rdID(b_em_IR)!=0) & (writes_rd(b_em_IR)) & (rdID(b_em_IR) == rs1ID(b_de_IR));
        wire b_e_bw_fwd_rs1 = (rdID(b_mw_IR)!=0) & (writes_rd(b_mw_IR)) & (rdID(b_mw_IR) == rs1ID(b_de_IR));

        wire b_e_am_fwd_rs1 = (rdID(a_em_IR)!=0) & (writes_rd(a_em_IR)) & (rdID(a_em_IR) == rs1ID(b_de_IR));
        wire b_e_aw_fwd_rs1 = (rdID(a_mw_IR)!=0) & (writes_rd(a_mw_IR)) & (rdID(a_mw_IR) == rs1ID(b_de_IR));

        wire b_e_bm_fwd_rs2 = (rdID(b_em_IR)!=0) & (writes_rd(b_em_IR)) & (rdID(b_em_IR) == rs2ID(b_de_IR));
        wire b_e_bw_fwd_rs2 = (rdID(b_mw_IR)!=0) & (writes_rd(b_mw_IR)) & (rdID(b_mw_IR) == rs2ID(b_de_IR));

        wire b_e_am_fwd_rs2 = (rdID(a_em_IR)!=0) & (writes_rd(a_em_IR)) & (rdID(a_em_IR) == rs2ID(b_de_IR));
        wire b_e_aw_fwd_rs2 = (rdID(a_mw_IR)!=0) & (writes_rd(a_mw_IR)) & (rdID(a_mw_IR) == rs2ID(b_de_IR));

        wire [31:0] b_e_rs1 = b_e_bm_fwd_rs1 ? b_em_RES  : //
                              b_e_am_fwd_rs1 ? a_em_RES  : //
                              b_e_bw_fwd_rs1 ? b_wb_DATA : // A ORDEM IMPORTA!!
                              b_e_aw_fwd_rs1 ? a_wb_DATA : //
                                               b_de_rs1  ; //

        wire [31:0] b_e_rs2 = b_e_bm_fwd_rs2 ? b_em_RES  : //
                              b_e_am_fwd_rs2 ? a_em_RES  : //
                              b_e_bw_fwd_rs2 ? b_wb_DATA : // A ORDEM IMPORTA!!
                              b_e_aw_fwd_rs2 ? a_wb_DATA : //
                                               b_de_rs2  ; //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [31:0] b_e_IMM;

        imm_mux m1(
                .instr(b_de_IR),
                .imm(b_e_IMM)
        );

        wire [31:0] b_e_ALUin1 = (isJAL(b_de_IR) | isJALR(b_de_IR) | isAUIPC(b_de_IR)) ? b_de_PC : b_e_rs1;
        wire [31:0] b_e_ALUin2 = (isRtype(b_de_IR) | isBtype(b_de_IR))? b_e_rs2 :
                                 (isRimm(b_de_IR)  | isAUIPC(b_de_IR))? b_e_IMM :
                                                                          32'd4 ;
        wire [31:0] b_e_ALUout;
        wire b_e_takeB;

        alu u1(
                .in_a(b_e_ALUin1),
                .in_b(b_e_ALUin2),
                .inst(b_de_IR),
                .result(b_e_ALUout),
                .take_b(b_e_takeB)
        );

        wire [31:0] b_e_RES = isLUI(b_de_IR) ? b_e_IMM : b_e_ALUout;

        wire [31:0] b_e_ADDin1 = (isJAL(b_de_IR) | isBtype(b_de_IR)) ? b_de_PC : b_e_rs1;
        wire [31:0] b_e_ADDR_RES = b_e_ADDin1 + b_e_IMM;
        wire [31:0] b_e_ADDR = {b_e_ADDR_RES[31:1], b_e_ADDR_RES[0] & (~isJALR(b_de_IR))};

        always@(posedge clk) begin
                b_em_IR   <= b_de_IR;
                b_em_PC   <= b_de_PC;
                b_em_rs2  <= b_e_rs2;
                b_em_RES  <= b_e_RES;
                b_em_ADDR <= b_e_ADDR;
        end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	reg[31:0] a_em_IR, a_em_PC, a_em_rs2, a_em_RES, a_em_ADDR;
	reg[31:0] b_em_IR, b_em_PC, b_em_rs2, b_em_RES, b_em_ADDR;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire [2:0] a_m_funct3 = funct3(a_em_IR);
	wire a_m_isB = (a_m_funct3[1:0] == 2'b00);
	wire a_m_isH = (a_m_funct3[1:0] == 2'b01);


	wire [31:0] a_m_store_DATA;
	assign a_m_store_DATA[ 7:0 ] = a_em_rs2[7:0];
	assign a_m_store_DATA[15:8 ] = a_em_ADDR[0] ? a_em_rs2[7:0]  : a_em_rs2[15:8 ] ;
	assign a_m_store_DATA[23:16] = a_em_ADDR[1] ? a_em_rs2[7:0]  : a_em_rs2[23:16] ;
	assign a_m_store_DATA[31:24] = a_em_ADDR[0] ? a_em_rs2[7:0]  :
				     a_em_ADDR[1] ? a_em_rs2[15:8] : a_em_rs2[31:24] ;

	wire [3:0] a_m_store_WMASK = a_m_isB ? (a_em_ADDR[1] ? (a_em_ADDR[0] ? 4'b1000 : 4'b0100)  :
							       (a_em_ADDR[0] ? 4'b0010 : 4'b0001)) :
				     a_m_isH ? (a_em_ADDR[1] ?                 4'b1100 : 4'b0011)  :
				                                                         4'b1111   ;

	wire [3:0] a_m_WMASK = {4{isStype(a_em_IR) & a_M_isRAM}} & a_m_store_WMASK;
	wire [20:0] a_m_word_ADDR = a_em_ADDR[22:2]; 
	wire a_M_isIO  = a_em_ADDR[22];
	wire a_M_isRAM = !a_M_isIO;

	assign a_IO_mem_addr  = a_em_ADDR;
	assign a_IO_mem_wr    = isStype(a_em_IR) & a_M_isIO;
	assign a_IO_mem_wdata = a_em_rs2;

        assign a_mem_wmask = a_m_WMASK;
        assign a_mem_addr = {9'b0,a_em_ADDR[22:0]};
        //assign mem_addr = {11'b0,m_word_ADDR};
        assign a_mem_wdata = a_m_store_DATA;
        assign a_mem_cen = isLoad(a_em_IR) | isStype(a_em_IR);

	wire [31:0] a_mw_Mdata = a_mem_data;

	always@(posedge clk) begin
		a_mw_IR     <= a_em_IR;
		a_mw_PC     <= a_em_PC;
		a_mw_RES    <= a_em_RES;
		a_mw_IO_RES <= a_IO_mem_rdata;
		a_mw_ADDR   <= a_em_ADDR;

		case(csrId(a_em_IR)) 
			2'b00: a_mw_CSR_RES <= cycle[31:0];
			2'b10: a_mw_CSR_RES <= cycle[63:32];
			2'b01: a_mw_CSR_RES <= instret[31:0];
			2'b11: a_mw_CSR_RES <= instret[63:32];	 
		endcase 

		if(!resetn) begin
			instret <= 0;
		end else if(a_mw_IR != NOP & b_mw_IR != NOP) begin
			instret <= instret + 2;
		end else if(a_mw_IR != NOP | b_mw_IR != NOP) begin
			instret <= instret + 1;
		end


		cycle <= !resetn ? 0 : cycle + 1;
	end

	reg [63:0] cycle;
	reg [63:0] instret;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        wire [2:0] b_m_funct3 = funct3(b_em_IR);
        wire b_m_isB = (b_m_funct3[1:0] == 2'b00);
        wire b_m_isH = (b_m_funct3[1:0] == 2'b01);


        wire [31:0] b_m_store_DATA;
        assign b_m_store_DATA[ 7:0 ] = b_em_rs2[7:0];
        assign b_m_store_DATA[15:8 ] = b_em_ADDR[0] ? b_em_rs2[7:0]  : b_em_rs2[15:8 ] ;
        assign b_m_store_DATA[23:16] = b_em_ADDR[1] ? b_em_rs2[7:0]  : b_em_rs2[23:16] ;
        assign b_m_store_DATA[31:24] = b_em_ADDR[0] ? b_em_rs2[7:0]  :
                                       b_em_ADDR[1] ? b_em_rs2[15:8] : b_em_rs2[31:24] ;

        wire [3:0] b_m_store_WMASK = b_m_isB ? (b_em_ADDR[1] ? (b_em_ADDR[0] ? 4'b1000 : 4'b0100)  :
                                                               (b_em_ADDR[0] ? 4'b0010 : 4'b0001)) :
                                     b_m_isH ? (b_em_ADDR[1] ?                 4'b1100 : 4'b0011)  :
                                                                                         4'b1111   ;

        wire [3:0] b_m_WMASK = {4{isStype(b_em_IR) & b_M_isRAM}} & b_m_store_WMASK;
        wire [20:0] b_m_word_ADDR = b_em_ADDR[22:2];
        wire b_M_isIO  = b_em_ADDR[22];
        wire b_M_isRAM = !b_M_isIO;


        assign b_IO_mem_addr  = b_em_ADDR;
        assign b_IO_mem_wr    = isStype(b_em_IR) & b_M_isIO;
        assign b_IO_mem_wdata = b_em_rs2;

        assign b_mem_wmask = b_m_WMASK & {4{!addr_HAZ}};
        assign b_mem_addr =  {9'b0,b_em_ADDR[22:0]};
        assign b_mem_wdata = b_m_store_DATA;
        assign b_mem_cen = isLoad(b_em_IR) | isStype(b_em_IR);

        wire [31:0] b_mw_Mdata = b_mem_data;

        wire addr_HAZ = (b_mem_addr==a_mem_addr) & (|a_mem_wmask);

        always@(posedge clk) begin
                b_mw_IR     <= b_em_IR;
                b_mw_PC     <= b_em_PC;
                b_mw_RES    <= b_em_RES;
        end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	reg [31:0] a_mw_IR, a_mw_PC, a_mw_RES, a_mw_IO_RES, a_mw_ADDR, a_mw_CSR_RES;
	reg [31:0] b_mw_IR, b_mw_PC, b_mw_RES;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	wire [2:0] a_w_funct3 = funct3(a_mw_IR);

	wire a_w_isB = (a_w_funct3[1:0] == 2'b00);
	wire a_w_isH = (a_w_funct3[1:0] == 2'b01);
	wire a_w_sign_e = !a_w_funct3[2];
	wire a_W_isIO   = a_mw_ADDR[22];

	wire [15:0] a_w_loadH = a_mw_ADDR[1] ? a_mw_Mdata[31:16] : a_mw_Mdata[15:0];
	wire [ 7:0] a_w_loadB = a_mw_ADDR[0] ? a_w_loadH[15:8 ] : a_w_loadH[7: 0];
	wire a_w_load_sign    = a_w_sign_e & (a_w_isB ? a_w_loadB[7] : a_w_loadH[15]);

	wire [31:0] a_w_mem_RES = a_w_isB ? {{24{a_w_load_sign}}, a_w_loadB} :
				  a_w_isH ? {{16{a_w_load_sign}}, a_w_loadH} :
					                          a_mw_Mdata ;

	assign a_wb_DATA = isLoad(a_mw_IR) ? (a_W_isIO ? a_mw_IO_RES : a_w_mem_RES):
			   isCSRRS(a_mw_IR)?                           a_mw_CSR_RES:
					                                   a_mw_RES;

	assign a_wb_enable = writes_rd(a_mw_IR) & (rdID(a_mw_IR)!=0);

	assign a_wb_rdID = rdID(a_mw_IR);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	assign b_wb_DATA = b_mw_RES;
	
	assign b_wb_enable = writes_rd(b_mw_IR) & (rdID(b_mw_IR)!=0);

	assign b_wb_rdID = rdID(b_mw_IR);

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

	function writes_rd; input [31:0] I; writes_rd = !isStype(I) & !isBtype(I)           ; endfunction
	function reads_rs1; input [31:0] I; reads_rs1 = !(isJAL(I) | isAUIPC(I) | isLUI(I)) ; endfunction
	function reads_rs2; input [31:0] I; reads_rs2 = isRtype(I) | isBtype(I) | isStype(I); endfunction

	function isEBREAK; input [31:0] I; isEBREAK = (isSYSTEM(I) && funct3(I) == 3'b000); endfunction
	function isCSRRS; input [31:0] I; isCSRRS = (isSYSTEM(I) && funct3(I) == 3'b010); endfunction

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*	`ifdef BENCH
	   always @(posedge clk) begin
		   if(halt) $finish(); 
	   end
	`endif*/
        `ifdef BENCH

		/*
		integer n_fstall =0;

		always@(posedge clk) begin
			if(f_stall) begin
				n_fstall <= n_fstall + 1; 
			end
		end		
		*/

                /* verilator lint_off WIDTH */
                always @(posedge clk) begin
			//if(resetn)
			//	$display("%x", a_mw_IR);
			//if(b_wb_enable & a_wb_enable & (b_wb_rdID == a_wb_rdID))
			//	$display("ERRO! %d, %d, %x(pc %x), %x(pc %x)", a_wb_rdID, b_wb_rdID, a_mw_IR, a_mw_PC, b_mw_IR, b_mw_PC);
			//if(a_fd_IR == 32'h00f585b3 || b_fd_IR == 32'h00f585b3) begin
			//	$display("FD_HAZ: a=%x | b=%x | haz?%d",a_fd_IR, b_fd_IR, fd_data_HAZ );
			//end
                        if(halt) begin
                                /*$display("Simulated processor's report");
                                $display("----------------------------");
				//$display("Numbers of stalls in F stage: %d", n_fstall);
                                $display("Numbers of = (Cycles: %d, Instret: %d)", cycle, instret);
                                $display("CPI = %3.3f" , cycle/instret);*/
				$finish();
                        end
                end
                /* verilator lint_on WIDTH */
        `endif

endmodule
