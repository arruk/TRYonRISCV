//`define STORE_IN_B
//`define LOAD_IN_B
`define CONFIG_RAS
//`define BTYPE_IN_B

`ifndef BTYPE_IN_B
	`ifdef LOAD_IN_B
		`define STORE_IN_B
	`endif
`else
	`define STORE_IN_B
	`define LOAD_IN_B
`endif
	
`ifndef BENCH
        `define SYN
`endif

module torv32(
	input         clk   ,
        input 	      resetn,

	output        a_imem_en  ,      
        output [31:0] a_imem_addr,  
        input  [31:0] a_imem_data,    

        input  [31:0] a_mem_data ,     
        output [ 3:0] a_mem_wmask,    
        output [31:0] a_mem_addr,     
        output [31:0] a_mem_wdata,    

	output        a_mem_cen,
	output        b_mem_cen,

	output        b_imem_en  ,      
        output [31:0] b_imem_addr,    
        input  [31:0] b_imem_data,    

        input  [31:0] b_mem_data ,     
        output [ 3:0] b_mem_wmask,    
        output [31:0] b_mem_addr,     
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


// START OF F STAGE WIRES //	
	wire [31:0] PC;
	wire [31:0] pc;
	wire [31:0] imemAddress;
	wire [31:0] a_fd_IR;
	wire [31:0] jumpAddress;
	wire jumpTaken;
	wire refetch;
	wire [31:0] b_fd_IR;

	reg [31:0] a_fd_PC;
        reg a_fd_NOP;
	reg [31:0] b_fd_PC;
	reg b_fd_NOP;
	reg [31:0] PCR;
// END OF F STAGE WIRES //


	reg [31:0] reg_file [0:31]; // REGISTER FILE


// START OF "A" D STAGE WIRES //
	wire a_d_predict;
	wire a_d_JoB_now;
	wire [31:0] a_d_JoB_ADDR;

	wire [4:0] a_d_rdID;
	wire [4:0] a_d_rs1ID;
	wire [4:0] a_d_rs2ID;

	wire a_d_isRRint;
	wire a_d_isRIint;
	wire a_d_isLoad;
	wire a_d_isStore;
	wire a_d_isSYSTEM;
	wire a_d_isJAL;
	wire a_d_isJALR;
	wire a_d_isLUI;
	wire a_d_isAUIPC;
	wire a_d_isBranch;
	wire a_d_isCSRRS;
        wire a_d_isEBREAK;

	wire a_d_isJALorJALR;
	wire a_d_isLUIorAUIPC; 
	wire a_d_isJALorJALRorLUIorAUIPC;

	wire a_d_reads_rs1;
	wire a_d_reads_rs2;
        wire a_d_wbEnable;
        wire a_d_writes_rd;
        
	wire [2:0] a_d_funct3;
        wire [7:0] a_d_funct3_is;
        wire a_d_funct7;
        wire [1:0] a_d_csrID;

	wire [31:0] a_d_Uimm;
	wire [31:0] a_d_Bimm;
	wire [31:0] a_d_Jimm;
	wire [31:0] a_d_IorSimm;
	wire [31:0] a_d_PCplus4orUimm;
	wire [31:0] a_d_PCplus4orBimm;

	wire a_d_aEaM_fwdrs1;
	wire a_d_aEaW_fwdrs1;
	wire a_d_aEbM_fwdrs1;
	wire a_d_aEbW_fwdrs1;
	wire [3:0] a_d_fwd1;

	wire a_d_aEaM_fwdrs2;
	wire a_d_aEaW_fwdrs2;
	wire a_d_aEbM_fwdrs2;
	wire a_d_aEbW_fwdrs2;
	wire [3:0] a_d_fwd2;

	`ifdef CONFIG_RAS
	reg [31:0] RAS_0;
	reg [31:0] RAS_1;
	reg [31:0] RAS_2;
	reg [31:0] RAS_3;  
	reg [31:0] a_de_predictRA;
	reg [31:0] b_de_predictRA;
	`endif

	reg a_de_nop;
	reg [31:0] a_de_PCplus4orUimm;
	reg [31:0] a_de_PCplus4orBimm;
	reg [4:0] a_de_rdID;
	reg [4:0] a_de_rs1ID;
	reg [4:0] a_de_rs2ID;
	reg [2:0] a_de_funct3;
	(* onehot *) reg [7:0] a_de_funct3_is;
	reg a_de_funct7;
	reg [1:0] a_de_csrID;
	reg a_de_isRRint;
	reg a_de_isRIint;
	reg a_de_isBranch;
	reg a_de_isJALR;
	reg a_de_isJAL;
	reg a_de_isAUIPC;
	reg a_de_isLUI;
	reg a_de_isLoad;
	reg a_de_isStore;
	reg a_de_isCSRRS;
	reg a_de_isEBREAK;
	reg a_de_wbEnable;
	reg [31:0] a_de_IorSimm;
	reg [3:0] a_de_fwd1;
	reg [3:0] a_de_fwd2;
	reg a_de_isJALorJALRorLUIorAUIPC;
// END OF "A" D STAGE WIRES //


// START OF "B" D STAGE WIRES //
        wire b_d_predict;
        wire b_d_JoB_now;
        wire [31:0] b_d_JoB_ADDR;

	wire [4:0] b_d_rdID;
	wire [4:0] b_d_rs1ID;
	wire [4:0] b_d_rs2ID;

	wire b_d_isRRint;
	wire b_d_isRIint;
	wire b_d_isLoad;
	wire b_d_isStore;
	wire b_d_isSYSTEM;
	wire b_d_isJAL;
	wire b_d_isJALR;
	wire b_d_isLUI;
	wire b_d_isAUIPC;
	wire b_d_isBranch;
	wire b_d_isCSRRS;
        wire b_d_isEBREAK;

	wire b_d_isJALorJALR;
	wire b_d_isLUIorAUIPC; 
	wire b_d_isJALorJALRorLUIorAUIPC;

	wire b_d_reads_rs1;
	wire b_d_reads_rs2;
        wire b_d_wbEnable;
        wire b_d_writes_rd;
        
	wire [2:0] b_d_funct3;
        wire [7:0] b_d_funct3_is;
        wire b_d_funct7;
        wire [1:0] b_d_csrID;

	wire [31:0] b_d_Uimm;
	wire [31:0] b_d_Bimm;
	wire [31:0] b_d_Jimm;
	wire [31:0] b_d_IorSimm;
	wire [31:0] b_d_PCplus4orUimm;
	wire [31:0] b_d_PCplus4orBimm;

	wire b_d_bEbM_fwdrs1;
	wire b_d_bEbW_fwdrs1;
	wire b_d_bEaM_fwdrs1;
	wire b_d_bEaW_fwdrs1;
	wire [3:0] b_d_fwd1;

	wire b_d_bEbM_fwdrs2;
	wire b_d_bEbW_fwdrs2;
	wire b_d_bEaM_fwdrs2;
	wire b_d_bEaW_fwdrs2;
	wire [3:0] b_d_fwd2;

	reg b_de_nop;
	reg [31:0] b_de_PCplus4orUimm;
	reg [31:0] b_de_PCplus4orBimm;
	reg [4:0] b_de_rdID;
	reg [4:0] b_de_rs1ID;
	reg [4:0] b_de_rs2ID;
	reg [2:0] b_de_funct3;
	reg [7:0] b_de_funct3_is;
	reg b_de_funct7;
	reg [1:0] b_de_csrID;
	reg b_de_isRRint;
	reg b_de_isRIint;
	reg b_de_isBranch;
	reg b_de_isJALR;
	reg b_de_isJAL;
	reg b_de_isAUIPC;
	reg b_de_isLUI;
	reg b_de_isLoad;
	reg b_de_isStore;
	reg b_de_isCSRRS;
	reg b_de_isEBREAK;
	reg b_de_wbEnable;
	reg [31:0] b_de_IorSimm;
	reg [3:0] b_de_fwd1;
	reg [3:0] b_de_fwd2;
	reg b_de_isJALorJALRorLUIorAUIPC;
// END OF "B" D STAGE WIRES //


// START OF "A" E STAGE WIRES //
	wire [31:0] a_e_rs1;
	wire [31:0] a_e_rs2;
	wire [31:0] a_e_rf_rs1;
	wire [31:0] a_e_rf_rs2;
	wire [31:0] a_e_ALUin1;
	wire [31:0] a_e_ALUin2;	
	wire [4:0] a_e_SHamt;
	wire a_e_minus;
	wire a_e_arith_shift;
	wire [31:0] a_e_ALUplus;
	wire [32:0] a_e_ALUminus;
        wire a_e_LT;
        wire a_e_LTU;
        wire a_e_EQ;
        wire [31:0] a_e_shifter_in;
        wire [31:0] a_e_shifter;
        wire [31:0] a_e_left_shift;
	wire [31:0] a_e_ALUout;
	wire a_e_take_branch;
        wire [31:0] a_e_jalrADDR;
        wire a_e_JoB;
        wire [31:0] a_e_JoB_ADDR;
        wire [31:0] a_e_result;
	wire [31:0] a_e_addr;

	wire [31:0] a_em_Mdata;

	reg a_em_nop;
	reg [4:0] a_em_rdID;
	reg [4:0] a_em_rs1ID;
	reg [4:0] a_em_rs2ID;
	reg [4:0] a_em_funct3;
	reg [3:0] a_em_csrID_is;
	reg [31:0] a_em_rs2;
	reg [31:0] a_em_result;
	reg [31:0] a_em_ADDR;
	reg a_em_isLoad;
	reg a_em_isStore;
	reg a_em_isCSRRS;
	reg a_em_isBranch;
	reg a_em_wbEnable;
	reg a_em_JoB_now;
	reg [31:0] a_em_JoB_ADDR;
// END OF "A" E STAGE WIRES //


// START OF "B" E STAGE WIRES //
	wire [31:0] b_e_rs1;
	wire [31:0] b_e_rs2;
	wire [31:0] b_e_rf_rs1;
	wire [31:0] b_e_rf_rs2;
	wire [31:0] b_e_ALUin1;
	wire [31:0] b_e_ALUin2;	
	wire [4:0] b_e_SHamt;
	wire b_e_minus;
	wire b_e_arith_shift;
	wire [31:0] b_e_ALUplus;
	wire [32:0] b_e_ALUminus;
        wire b_e_LT;
        wire b_e_LTU;
        wire b_e_EQ;
        wire [31:0] b_e_shifter_in;
        wire [31:0] b_e_shifter;
        wire [31:0] b_e_left_shift;
	wire [31:0] b_e_ALUout;
	wire b_e_take_branch;
        wire [31:0] b_e_jalrADDR;
        wire b_e_JoB;
        wire [31:0] b_e_JoB_ADDR;
        wire [31:0] b_e_result;
	wire [31:0] b_e_addr;

	reg b_em_nop;
	reg [4:0] b_em_rdID;
	reg [4:0] b_em_rs1ID;
	reg [4:0] b_em_rs2ID;
	reg [4:0] b_em_funct3;
	reg [3:0] b_em_csrID_is;
	reg [31:0] b_em_rs2;
	reg [31:0] b_em_result;
	reg [31:0] b_em_ADDR;
	reg b_em_isLoad;
	reg b_em_isStore;
	reg b_em_isBranch;
	reg b_em_isCSRRS;
	reg b_em_wbEnable;
	reg b_em_JoB_now;
	reg [31:0] b_em_JoB_ADDR;
// END OF "B" E STAGE WIRES //


// START OF "A" M STAGE WIRES //
	wire a_m_isB;
	wire a_m_isH;
	wire [31:0] a_m_store_DATA;
	wire [3:0] a_m_store_WMASK;
	wire [3:0] a_m_WMASK;
	wire a_m_isIO;
	wire a_m_isRAM;
	wire [31:0] a_mw_Mdata;
	wire a_m_isNotIOandLoad;
	wire [31:0] a_m_wb_DATA;
	wire [31:0] a_m_CSR_data;

	wire a_m_lb;
	wire a_m_lbu;
	wire a_m_lh;
	wire a_m_lhu;

	reg a_mw_nop;
	reg [4:0] a_mw_rdID;
	reg [31:0] a_mw_wb_DATA;
	reg a_mw_wbEnable;

	reg [4:0] a_mw_funct3;
	reg [31:0] a_mw_ADDR;
	reg a_mw_isNotIOandLoad;

	reg a_mw_lb;
	reg a_mw_lbu;
	reg a_mw_lh;
	reg a_mw_lhu;

// END OF "A" M STAGE WIRES //


// START OF "B" M STAGE WIRES //
	wire b_m_isB;
	wire b_m_isH;
	wire [31:0] b_m_store_DATA;
	wire [3:0] b_m_store_WMASK;
	wire [3:0] b_m_WMASK;
	wire b_m_isIO;
	wire b_m_isRAM;
	wire [31:0] b_mw_Mdata;
	wire b_m_isNotIOandLoad;
	wire [31:0] b_m_wb_DATA;

	wire b_m_lb;
	wire b_m_lbu;
	wire b_m_lh;
	wire b_m_lhu;

	wire store_addr_HAZ;
	wire a_store_b_load_HAZ;

	reg b_mw_nop;
	reg [4:0] b_mw_rdID;
	reg [31:0] b_mw_wb_DATA;
	reg b_mw_wbEnable;

`ifdef LOAD_IN_B
        reg [4:0] b_mw_funct3;
        reg [31:0] b_mw_ADDR;
        reg b_mw_isNotIOandLoad;	
	reg b_mw_ASBL;
	reg [31:0] b_mw_store;

	reg b_mw_lb;
	reg b_mw_lbu;
	reg b_mw_lh;
	reg b_mw_lhu;
`endif
// END  OF "B" M STAGE WIRES //


// START OF "A" W STAGE WIRES //
	wire a_w_isIO;
        wire [31:0] a_w_LB;
        wire [31:0] a_w_LBU;
        wire [31:0] a_w_LH;
        wire [31:0] a_w_LHU;
	wire [31:0] a_w_mem_RES;

	wire        a_wb_enable;
	wire [31:0] a_wb_DATA;
	wire [4:0]  a_wb_rdID;
// END  OF "A" W STAGE WIRES //


// START OF "B" W STAGE WIRES //
`ifdef LOAD_IN_B
	wire b_w_isIO;
        wire [31:0] b_w_LB;
        wire [31:0] b_w_LBU;
        wire [31:0] b_w_LH;
        wire [31:0] b_w_LHU;
	wire [31:0] b_w_mem_RES;
`endif

	wire        b_wb_enable;
	wire [31:0] b_wb_DATA;
	wire [4:0]  b_wb_rdID;
// END  OF "B" W STAGE WIRES //

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	wire a_rs1_HAZ  = a_d_reads_rs1 & (a_d_rs1ID == a_de_rdID);
	wire a_rs2_HAZ  = a_d_reads_rs2 & (a_d_rs2ID == a_de_rdID);

	wire ba_rs1_HAZ = b_d_reads_rs1 & (b_d_rs1ID == a_de_rdID);
	wire ba_rs2_HAZ = b_d_reads_rs2 & (b_d_rs2ID == a_de_rdID);

	wire a_data_HAZ   = !a_fd_NOP & (a_de_isLoad | a_de_isCSRRS) & ( a_rs1_HAZ | a_rs2_HAZ );
	wire ba_data_HAZ  = !b_fd_NOP & (a_de_isLoad | a_de_isCSRRS) & (ba_rs1_HAZ | ba_rs2_HAZ) & !control_HAZ;

`ifdef LOAD_IN_B
	wire b_rs1_HAZ  = b_d_reads_rs1 & (b_d_rs1ID == b_de_rdID);
        wire b_rs2_HAZ  = b_d_reads_rs2 & (b_d_rs2ID == b_de_rdID);

        wire ab_rs1_HAZ = a_d_reads_rs1 & (a_d_rs1ID == b_de_rdID);
        wire ab_rs2_HAZ = a_d_reads_rs2 & (a_d_rs2ID == b_de_rdID);

        wire b_data_HAZ   = !b_fd_NOP & b_de_isLoad & ( b_rs1_HAZ | b_rs2_HAZ) & !control_HAZ;
        wire ab_data_HAZ  = !a_fd_NOP & b_de_isLoad & (ab_rs1_HAZ | ab_rs2_HAZ);

        wire data_HAZ = a_data_HAZ | ba_data_HAZ | b_data_HAZ | ab_data_HAZ;
`else
	wire data_HAZ = a_data_HAZ | ba_data_HAZ;
`endif

	wire a_f_stall = halt | data_HAZ;
	wire a_d_stall = halt | data_HAZ;

	wire b_f_stall = halt | data_HAZ;
	wire b_d_stall = halt | data_HAZ;
	
`ifdef BTYPE_IN_B
	wire a_e_flush = a_e_JoB | b_e_JoB | data_HAZ;
	wire a_d_flush = a_e_JoB | b_e_JoB;

	wire b_e_flush = a_e_JoB | b_e_JoB | data_HAZ;
	wire b_d_flush = a_e_JoB | b_e_JoB;

	wire ba_fd_rs1_HAZ = !b_fd_NOP & b_ins_ALL & b_d_reads_rs1 & b_d_rs1ID!=0 & a_d_writes_rd & (b_d_rs1ID == a_d_rdID);
	wire ba_fd_rs2_HAZ = !b_fd_NOP & b_ins_ALL & b_d_reads_rs2 & b_d_rs2ID!=0 & a_d_writes_rd & (b_d_rs2ID == a_d_rdID);
	wire fd_data_HAZ = (ba_fd_rs1_HAZ | ba_fd_rs2_HAZ);
`else
	wire a_e_flush = a_e_JoB | data_HAZ;
	wire a_d_flush = a_e_JoB ;

	wire b_e_flush = a_e_JoB | data_HAZ;
	wire b_d_flush = a_e_JoB;

	wire ba_fd_rs1_HAZ = !b_fd_NOP & b_d_reads_rs1 & b_d_rs1ID!=0 & a_d_writes_rd & (b_d_rs1ID == a_d_rdID);
	wire ba_fd_rs2_HAZ = !b_fd_NOP & b_d_reads_rs2 & b_d_rs2ID!=0 & a_d_writes_rd & (b_d_rs2ID == a_d_rdID);
	wire fd_data_HAZ = (ba_fd_rs1_HAZ | ba_fd_rs2_HAZ);

`endif

`ifdef STORE_IN_B
`ifdef LOAD_IN_B
`ifdef BTYPE_IN_B
	wire b_ins_ALL = b_d_isRRint | b_d_isRIint | b_d_isAUIPC | b_d_isLUI | b_d_isStore | b_d_isLoad | b_d_isJAL | b_d_isJALR | b_d_isBranch;
`else
	wire b_ins_ALL = b_d_isRRint | b_d_isRIint | b_d_isAUIPC | b_d_isLUI | b_d_isStore | b_d_isLoad;
`endif
`else
	wire b_ins_ALL = b_d_isRRint | b_d_isRIint | b_d_isAUIPC | b_d_isLUI | b_d_isStore;
`endif
`else
	wire b_ins_ALL = b_d_isRRint | b_d_isRIint | b_d_isAUIPC | b_d_isLUI;
`endif

	wire control_HAZ = !b_ins_ALL | fd_data_HAZ;

	wire halt = resetn & a_de_isEBREAK;	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef BTYPE_IN_B
	assign jumpTaken = a_d_JoB_now | a_em_JoB_now | b_d_JoB_now | b_em_JoB_now;

	assign jumpAddress = a_em_JoB_now ? a_em_JoB_ADDR :
			     b_em_JoB_now ? b_em_JoB_ADDR :
			     a_d_JoB_now  ? a_d_JoB_ADDR  :
			   /*b_d_JoB_now*/  b_d_JoB_ADDR  ; 
	
	assign refetch = (control_HAZ & !a_fd_NOP & !(a_d_JoB_now|a_em_JoB_now) & !(b_d_JoB_now|b_em_JoB_now));
`else
	assign jumpTaken = a_d_JoB_now | a_em_JoB_now;

	assign jumpAddress = a_d_JoB_now  ? a_d_JoB_ADDR  :
			   /*a_em_JoB_now*/ a_em_JoB_ADDR ;
	
	assign refetch = (control_HAZ & !a_fd_NOP & !(a_d_JoB_now|a_em_JoB_now));
`endif
	
	assign PC = jumpTaken ? jumpAddress + 8 :
		    refetch   ? pc + 4		:
		  /*noretech*/  pc + 8          ;


	always@(posedge clk) begin
		if(!a_f_stall) begin
			a_fd_PC <= a_imem_addr;
			PCR     <= PC;
		end

		a_fd_NOP <= a_d_flush | !resetn;
		
		if(!b_f_stall) begin
			b_fd_PC <= b_imem_addr;
		end

		b_fd_NOP <= b_d_flush  | !resetn;
				
		if(!resetn) begin
			PCR <= 32'h00000;
		end
	       
	end

	assign pc = PCR;

	assign imemAddress = jumpTaken ? jumpAddress :
			     refetch   ? pc - 4      :
			 /*norefetch*/   pc          ;

	assign a_imem_en   = !a_f_stall;
	assign a_imem_addr = imemAddress;
	assign a_fd_IR     = a_imem_data;

	assign b_imem_en   = !b_f_stall;
	assign b_imem_addr = imemAddress + 4;
	assign b_fd_IR     = b_imem_data;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
`ifdef CONFIG_RAS
        assign a_d_JoB_now = !a_fd_NOP & (a_fd_IR[6:4] == 3'b110) & (a_fd_IR[2]);
        assign a_d_JoB_ADDR = a_fd_IR[3:2] == 2'b01 ? RAS_0 : (a_fd_PC + a_d_Jimm);
`else
        assign a_d_JoB_now = !a_fd_NOP & (a_d_isJAL);
        assign a_d_JoB_ADDR = a_fd_PC + a_d_Jimm;
`endif

	assign a_d_rdID  = a_fd_IR[11:7 ];
	assign a_d_rs1ID = a_fd_IR[19:15];
	assign a_d_rs2ID = a_fd_IR[24:20];

	assign a_d_isRRint  = a_fd_IR[6:2] == 5'b01100;
	assign a_d_isRIint  = a_fd_IR[6:2] == 5'b00100;
	assign a_d_isLoad   = a_fd_IR[6:2] == 5'b00000;
	assign a_d_isStore  = a_fd_IR[6:2] == 5'b01000;
	assign a_d_isSYSTEM = a_fd_IR[6:2] == 5'b11100;
	
	assign a_d_isJAL    = (a_fd_IR[6:2]==5'b11011);
	assign a_d_isJALR   = (a_fd_IR[6:2]==5'b11001);
	assign a_d_isAUIPC  = (a_fd_IR[6:2]==5'b00101); 
	assign a_d_isLUI    = (a_fd_IR[6:2]==5'b01101);
	assign a_d_isBranch = (a_fd_IR[6:2]==5'b11000); 

	assign a_d_isCSRRS  = a_d_isSYSTEM &&  a_fd_IR[13];
        assign a_d_isEBREAK = a_d_isSYSTEM && !a_fd_IR[13];
  
	assign a_d_isJALorJALR  = (a_fd_IR[2] & a_fd_IR[6]); 
	assign a_d_isLUIorAUIPC = (a_fd_IR[4] & a_fd_IR[6]); 

	assign a_d_reads_rs1 = !(a_d_isJAL | a_d_isLUIorAUIPC);
	assign a_d_reads_rs2 = a_fd_IR[5] & (a_fd_IR[3:2] == 2'b00);
        assign a_d_wbEnable = (a_fd_IR[5:2]  != 4'b1000) & (a_d_rdID != 5'b0);
	assign a_d_writes_rd = (a_fd_IR[5:2] != 4'b1000);

	assign a_d_Uimm = {a_fd_IR[31], a_fd_IR[30:12], {12{1'b0}}};
	assign a_d_Bimm = {{20{a_fd_IR[31]}}, a_fd_IR[7], a_fd_IR[30:25], a_fd_IR[11:8], 1'b0};
	assign a_d_Jimm = {{12{a_fd_IR[31]}}, a_fd_IR[19:12], a_fd_IR[20], a_fd_IR[30:21], 1'b0};
	assign a_d_IorSimm = {{21{a_fd_IR[31]}}, a_d_isStore ? {a_fd_IR[30:25],a_fd_IR[11:7]} : a_fd_IR[30:20]};
	
	assign a_d_aEaM_fwdrs1 = a_de_wbEnable & (a_de_rdID == a_d_rs1ID);
	assign a_d_aEaW_fwdrs1 = a_em_wbEnable & (a_em_rdID == a_d_rs1ID);
	assign a_d_aEbM_fwdrs1 = b_de_wbEnable & (b_de_rdID == a_d_rs1ID);
	assign a_d_aEbW_fwdrs1 = b_em_wbEnable & (b_em_rdID == a_d_rs1ID);
	assign a_d_fwd1 = {a_d_aEaM_fwdrs1, a_d_aEaW_fwdrs1, a_d_aEbM_fwdrs1, a_d_aEbW_fwdrs1};

	assign a_d_aEaM_fwdrs2 = a_de_wbEnable & (a_de_rdID == a_d_rs2ID);
	assign a_d_aEaW_fwdrs2 = a_em_wbEnable & (a_em_rdID == a_d_rs2ID);
	assign a_d_aEbM_fwdrs2 = b_de_wbEnable & (b_de_rdID == a_d_rs2ID);
	assign a_d_aEbW_fwdrs2 = b_em_wbEnable & (b_em_rdID == a_d_rs2ID);
	assign a_d_fwd2 = {a_d_aEaM_fwdrs2, a_d_aEaW_fwdrs2, a_d_aEbM_fwdrs2, a_d_aEbW_fwdrs2};

	assign a_d_funct3    = a_fd_IR[14:12];
	assign a_d_funct3_is = 8'b00000001 << a_fd_IR[14:12];
	assign a_d_funct7    = a_fd_IR[30];
	assign a_d_csrID     = {a_fd_IR[27],a_fd_IR[21]};

	assign a_d_PCplus4orUimm = ({32{a_fd_IR[6:5]!=2'b01}} & a_fd_PC) + (a_d_isJALorJALR ? 4 : a_d_Uimm);
	assign a_d_PCplus4orBimm = a_fd_PC + a_d_Bimm;
	assign a_d_isJALorJALRorLUIorAUIPC = a_fd_IR[2];
	
	always@(posedge clk) begin

		if(!a_d_stall) begin
			a_de_nop	   <= 1'b0;
			//a_de_predict       <= a_d_predict;
			a_de_PCplus4orUimm <= a_d_PCplus4orUimm;
			a_de_PCplus4orBimm <= a_d_PCplus4orBimm;
			a_de_rdID  	   <= a_d_rdID;
			a_de_rs1ID 	   <= a_d_rs1ID;
			a_de_rs2ID 	   <= a_d_rs2ID;
			a_de_funct3        <= a_d_funct3;
			a_de_funct3_is 	   <= a_d_funct3_is;
			a_de_funct7    	   <= a_d_funct7;
			a_de_csrID     	   <= a_d_csrID;
			a_de_isRRint  	   <= a_d_isRRint;
			a_de_isRIint  	   <= a_d_isRIint;
			a_de_isBranch 	   <= a_d_isBranch;
			a_de_isJALR   	   <= a_d_isJALR;
			a_de_isJAL    	   <= a_d_isJAL;
			a_de_isAUIPC  	   <= a_d_isAUIPC;
			a_de_isLUI    	   <= a_d_isLUI;
			a_de_isLoad   	   <= a_d_isLoad;
			a_de_isStore  	   <= a_d_isStore;
			a_de_isCSRRS  	   <= a_d_isCSRRS;
			a_de_isEBREAK 	   <= a_d_isEBREAK;
			a_de_wbEnable 	   <= a_d_wbEnable;
			a_de_IorSimm  	   <= a_d_IorSimm;
			a_de_fwd1          <= a_d_fwd1;   
			a_de_fwd2          <= a_d_fwd2;   
			a_de_isJALorJALRorLUIorAUIPC <= a_d_isJALorJALRorLUIorAUIPC;
			
			`ifdef CONFIG_RAS
			a_de_predictRA <= RAS_0;
			b_de_predictRA <= RAS_0;
                        if(!a_fd_NOP & !a_d_flush) begin
                                if(a_d_isJAL & a_d_rdID==1) begin
                                        RAS_3 <= RAS_2;
                                        RAS_2 <= RAS_1;
                                        RAS_1 <= RAS_0;
                                        RAS_0 <= a_fd_PC + 4;
                                end
                                if(a_d_isJALR & a_d_rdID==0 && (a_d_rs1ID == 1 | a_d_rs1ID==5)) begin
                                        RAS_0 <= RAS_1;
                                        RAS_1 <= RAS_2;
                                        RAS_2 <= RAS_3;
                                end
                        end else if(!b_fd_NOP & !b_d_flush) begin
                                if(b_d_isJAL & b_d_rdID==1) begin
                                        RAS_3 <= RAS_2;
                                        RAS_2 <= RAS_1;
                                        RAS_1 <= RAS_0;
                                        RAS_0 <= b_fd_PC + 4;
                                end
                                if(b_d_isJALR & b_d_rdID==0 && (b_d_rs1ID == 1 | b_d_rs1ID==5)) begin
                                        RAS_0 <= RAS_1;
                                        RAS_1 <= RAS_2;
                                        RAS_2 <= RAS_3;
                                end
                        end
			
			`endif
		end
		
		if(a_e_flush | a_fd_NOP) begin
			a_de_nop      <= 1'b1;
			a_de_isRRint  <= 1'b0;
			a_de_isRIint  <= 1'b0;
			a_de_isBranch <= 1'b0;
			a_de_isJALR   <= 1'b0;
			a_de_isJAL    <= 1'b0;
			a_de_isAUIPC  <= 1'b0;
			a_de_isLUI    <= 1'b0;
			a_de_isLoad   <= 1'b0;
			a_de_isStore  <= 1'b0;
			a_de_isCSRRS  <= 1'b0;
			a_de_isEBREAK <= 1'b0;
			a_de_wbEnable <= 1'b0;
			a_de_isJALorJALRorLUIorAUIPC <= 1'b0;			
		end

	end

`ifdef BTYPE_IN_B

	//assign b_d_predict = b_fd_IR[31];

`ifdef CONFIG_RAS
        assign b_d_JoB_now = !b_fd_NOP & !control_HAZ & (b_fd_IR[6:4] == 3'b110) & (b_fd_IR[2]);
        assign b_d_JoB_ADDR = b_fd_IR[3:2] == 2'b01 ? RAS_0 : (b_fd_PC + b_d_Jimm);
`else	
        assign b_d_JoB_now = !b_fd_NOP & !control_HAZ & (b_d_isJAL);
        assign b_d_JoB_ADDR = b_fd_PC + b_d_Jimm;
`endif

`endif
	assign b_d_rdID  = b_fd_IR[11:7 ];
	assign b_d_rs1ID = b_fd_IR[19:15];
	assign b_d_rs2ID = b_fd_IR[24:20];

	assign b_d_isRRint = b_fd_IR[6:2] == 5'b01100;
	assign b_d_isRIint = b_fd_IR[6:2] == 5'b00100;
	assign b_d_isLoad = b_fd_IR[6:2] == 5'b00000;
	assign b_d_isStore = b_fd_IR[6:2] == 5'b01000;
	assign b_d_isSYSTEM = b_fd_IR[6:2] == 5'b11100;

	assign b_d_isJAL    = (b_fd_IR[6:2]==5'b11011);
	assign b_d_isJALR   = (b_fd_IR[6:2]==5'b11001);
	assign b_d_isAUIPC  = (b_fd_IR[6:2]==5'b00101); 
	assign b_d_isLUI    = (b_fd_IR[6:2]==5'b01101);
	assign b_d_isBranch = (b_fd_IR[6:2]==5'b11000); 

	assign b_d_isCSRRS  = b_d_isSYSTEM &&  b_fd_IR[13];
        assign b_d_isEBREAK = b_d_isSYSTEM && !b_fd_IR[13];
  
	assign b_d_isJALorJALR  = (b_fd_IR[2] & b_fd_IR[6]); 
	assign b_d_isLUIorAUIPC = (b_fd_IR[4] & b_fd_IR[6]); 

	assign b_d_reads_rs1 = !(b_d_isJAL | b_d_isLUIorAUIPC);
	assign b_d_reads_rs2 = b_fd_IR[5] & (b_fd_IR[3:2] == 2'b00);
        assign b_d_wbEnable = (b_fd_IR[5:2]  != 4'b1000) & (b_d_rdID != 0);
	assign b_d_writes_rd = (b_fd_IR[5:2] != 4'b1000);

	assign b_d_Uimm = {b_fd_IR[31], b_fd_IR[30:12], {12{1'b0}}};
	assign b_d_Bimm = {{20{b_fd_IR[31]}}, b_fd_IR[7], b_fd_IR[30:25], b_fd_IR[11:8], 1'b0};
	assign b_d_Jimm = {{12{b_fd_IR[31]}}, b_fd_IR[19:12], b_fd_IR[20], b_fd_IR[30:21], 1'b0};
	assign b_d_IorSimm = {{21{b_fd_IR[31]}}, b_d_isStore ? {b_fd_IR[30:25],b_fd_IR[11:7]} : b_fd_IR[30:20]};
	
	assign b_d_bEbM_fwdrs1 = b_de_wbEnable & (b_de_rdID == b_d_rs1ID);
	assign b_d_bEbW_fwdrs1 = b_em_wbEnable & (b_em_rdID == b_d_rs1ID);
	assign b_d_bEaM_fwdrs1 = a_de_wbEnable & (a_de_rdID == b_d_rs1ID);
	assign b_d_bEaW_fwdrs1 = a_em_wbEnable & (a_em_rdID == b_d_rs1ID);
	assign b_d_fwd1 = {b_d_bEbM_fwdrs1, b_d_bEbW_fwdrs1, b_d_bEaM_fwdrs1, b_d_bEaW_fwdrs1};

	assign b_d_bEbM_fwdrs2 = b_de_wbEnable & (b_de_rdID == b_d_rs2ID);
	assign b_d_bEbW_fwdrs2 = b_em_wbEnable & (b_em_rdID == b_d_rs2ID);
	assign b_d_bEaM_fwdrs2 = a_de_wbEnable & (a_de_rdID == b_d_rs2ID); 
	assign b_d_bEaW_fwdrs2 = a_em_wbEnable & (a_em_rdID == b_d_rs2ID); 
	assign b_d_fwd2 = {b_d_bEbM_fwdrs2, b_d_bEbW_fwdrs2, b_d_bEaM_fwdrs2, b_d_bEaW_fwdrs2};

	assign b_d_funct3    = b_fd_IR[14:12];
	assign b_d_funct3_is = 8'b00000001 << b_fd_IR[14:12];
	assign b_d_funct7    = b_fd_IR[30];
	assign b_d_csrID     = {b_fd_IR[27],b_fd_IR[21]};

	assign b_d_PCplus4orUimm = ({32{b_fd_IR[6:5]!=2'b01}} & b_fd_PC) + (b_d_isJALorJALR ? 4 : b_d_Uimm);
	assign b_d_PCplus4orBimm = b_fd_PC + b_d_Bimm;
	assign b_d_isJALorJALRorLUIorAUIPC = b_fd_IR[2];

	always@(posedge clk) begin

		if(!b_d_stall) begin
                        b_de_nop                   <= 1'b0;
                        b_de_PCplus4orUimm <= b_d_PCplus4orUimm;
                        b_de_PCplus4orBimm <= b_d_PCplus4orBimm;
                        b_de_rdID          <= b_d_rdID;
                        b_de_rs1ID         <= b_d_rs1ID;
                        b_de_rs2ID         <= b_d_rs2ID;
                        b_de_funct3        <= b_d_funct3;
                        b_de_funct3_is     <= b_d_funct3_is;
                        b_de_funct7        <= b_d_funct7;
                        b_de_csrID         <= b_d_csrID;
                        b_de_isRRint       <= b_d_isRRint;
                        b_de_isRIint       <= b_d_isRIint;
                        b_de_isBranch      <= b_d_isBranch;
                        b_de_isJALR        <= b_d_isJALR;
                        b_de_isJAL         <= b_d_isJAL;
                        b_de_isAUIPC       <= b_d_isAUIPC;
                        b_de_isLUI         <= b_d_isLUI;
                        b_de_isLoad        <= b_d_isLoad;
                        b_de_isStore       <= b_d_isStore;
                        b_de_isCSRRS       <= b_d_isCSRRS;
                        b_de_isEBREAK      <= b_d_isEBREAK;
                        b_de_wbEnable      <= b_d_wbEnable;
                        b_de_IorSimm       <= b_d_IorSimm;
                        b_de_fwd1          <= b_d_fwd1;
                        b_de_fwd2          <= b_d_fwd2;
                        b_de_isJALorJALRorLUIorAUIPC <= b_d_isJALorJALRorLUIorAUIPC;

		`ifdef BTYPE_IN_B
                        //b_de_predict       <= b_d_predict;
		`endif			
		end 
			
		if(b_e_flush | b_fd_NOP | a_d_JoB_now | control_HAZ) begin
                        b_de_nop      <= 1'b1;
                        b_de_isRRint  <= 1'b0;
                        b_de_isRIint  <= 1'b0;
                        b_de_isBranch <= 1'b0;
                        b_de_isJALR   <= 1'b0;
                        b_de_isJAL    <= 1'b0;
                        b_de_isAUIPC  <= 1'b0;
                        b_de_isLUI    <= 1'b0;
                        b_de_isLoad   <= 1'b0;
                        b_de_isStore  <= 1'b0;
                        b_de_isCSRRS  <= 1'b0;
                        b_de_isEBREAK <= 1'b0;
                        b_de_wbEnable <= 1'b0;
                        b_de_isJALorJALRorLUIorAUIPC <= 1'b0;	
		end

	end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	assign a_e_rf_rs1 = reg_file[a_de_rs1ID];
	assign a_e_rf_rs2 = reg_file[a_de_rs2ID];

	assign a_e_rs1 = a_de_fwd1[1] ? b_em_result  : //
			 a_de_fwd1[3] ? a_em_result  : //
                         a_de_fwd1[0] ? b_wb_DATA : // A ORDEM IMPORTA!!
                         a_de_fwd1[2] ? a_wb_DATA : //
                                       a_e_rf_rs1 ; //

        assign a_e_rs2 = a_de_fwd2[1] ? b_em_result  : //
	  	         a_de_fwd2[3] ? a_em_result  : //
                         a_de_fwd2[0] ? b_wb_DATA : // A ORDEM IMPORTA!!
                         a_de_fwd2[2] ? a_wb_DATA : //
                                       a_e_rf_rs2 ; //

	assign a_e_ALUin1 = a_e_rs1;
	assign a_e_ALUin2 = (a_de_isRRint | a_de_isBranch) ? a_e_rs2 : a_de_IorSimm ;

	assign a_e_SHamt = a_de_isRRint ? a_e_rs2[4:0] : a_de_rs2ID;
	assign a_e_minus = a_de_funct7 & a_de_isRRint;

	assign a_e_ALUplus = a_e_ALUin1 + a_e_ALUin2;
	assign a_e_ALUminus = {1'b0, a_e_ALUin1} + {1'b1, ~a_e_ALUin2} + 33'b1;

	assign a_e_LT  = (a_e_ALUin1[31] ^ a_e_ALUin2[31]) ? a_e_ALUin1[31] : a_e_ALUminus[32];
	assign a_e_LTU = a_e_ALUminus[32];
	assign a_e_EQ  = (a_e_ALUin1 == a_e_ALUin2);

	assign a_e_shifter_in = (a_de_funct3 == 3'b001) ? flip32(a_e_ALUin1) : a_e_ALUin1;

        /* verilator lint_off WIDTH */
        assign a_e_shifter = $signed({a_e_arith_shift & a_e_ALUin1, a_e_shifter_in}) >>> a_e_ALUin2[4:0];
        /* verilator lint_off WIDTH */
	
	assign a_e_left_shift = flip32(a_e_shifter);

	assign a_e_ALUout = 
		(a_de_funct3_is[0] ? (a_e_minus ? a_e_ALUminus[31:0] : a_e_ALUplus) : 32'b0) |
		(a_de_funct3_is[1] ? a_e_left_shift                                 : 32'b0) |
		(a_de_funct3_is[2] ? {31'b0, a_e_LT }                               : 32'b0) |
		(a_de_funct3_is[3] ? {31'b0, a_e_LTU}                               : 32'b0) |
		(a_de_funct3_is[4] ? a_e_ALUin1 ^ a_e_ALUin2                        : 32'b0) |
		(a_de_funct3_is[5] ? a_e_shifter                                    : 32'b0) |
		(a_de_funct3_is[6] ? a_e_ALUin1 | a_e_ALUin2                        : 32'b0) |
		(a_de_funct3_is[7] ? a_e_ALUin1 & a_e_ALUin2                        : 32'b0) ;

	assign a_e_take_branch = 
		(a_de_funct3_is[0] &  a_e_EQ ) |
		(a_de_funct3_is[1] & !a_e_EQ ) |
		(a_de_funct3_is[4] &  a_e_LT ) |
		(a_de_funct3_is[5] & !a_e_LT ) |
		(a_de_funct3_is[6] &  a_e_LTU) |
		(a_de_funct3_is[7] & !a_e_LTU) ;	
	
	assign a_e_jalrADDR = {a_e_ALUplus[31:1],1'b0};

`ifdef CONFIG_RAS
        assign a_e_JoB =((a_de_isJALR   & (a_de_predictRA != a_e_jalrADDR)) |
			 (a_de_isBranch & a_e_take_branch));
`else
        assign a_e_JoB = a_de_isJALR | (a_de_isBranch & a_e_take_branch);
`endif	

	assign a_e_JoB_ADDR = a_de_isBranch ? a_de_PCplus4orBimm : a_e_jalrADDR;
	assign a_e_addr = a_e_rs1 + a_de_IorSimm;

	assign a_e_result = a_de_isJALorJALRorLUIorAUIPC ? a_de_PCplus4orUimm : a_e_ALUout;

	always@(posedge clk) begin
		a_em_result       <= a_e_result;
		a_em_ADDR         <= a_e_addr;
		a_em_nop          <= a_de_nop;
		a_em_rdID         <= a_de_rdID;
		a_em_rs1ID        <= a_de_rs1ID;
		a_em_rs2ID        <= a_de_rs2ID;
		a_em_funct3       <= a_de_funct3;
		a_em_csrID_is     <= 4'b0001 << a_de_csrID;
		a_em_rs2          <= a_e_rs2;
		a_em_isLoad       <= a_de_isLoad;
		a_em_isStore      <= a_de_isStore;
		a_em_isCSRRS      <= a_de_isCSRRS;
		a_em_isBranch     <= a_de_isBranch;
		a_em_wbEnable     <= a_de_wbEnable;
		a_em_JoB_now      <= a_e_JoB;
		a_em_JoB_ADDR     <= a_e_JoB_ADDR;
	end


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	assign b_e_rf_rs1 = reg_file[b_de_rs1ID];
	assign b_e_rf_rs2 = reg_file[b_de_rs2ID];

	assign b_e_rs1 = b_de_fwd1[3] ? b_em_result  : //
                         b_de_fwd1[1] ? a_em_result  : //
                         b_de_fwd1[2] ? b_wb_DATA : // A ORDEM IMPORTA!!
                         b_de_fwd1[0] ? a_wb_DATA : //
                                       b_e_rf_rs1 ; //

        assign b_e_rs2 = b_de_fwd2[3] ? b_em_result  : //
                         b_de_fwd2[1] ? a_em_result  : //
                         b_de_fwd2[2] ? b_wb_DATA : // A ORDEM IMPORTA!!
                         b_de_fwd2[0] ? a_wb_DATA : //
                                       b_e_rf_rs2 ; //

        assign b_e_ALUin1 = b_e_rs1;
        assign b_e_ALUin2 = (b_de_isRRint | b_de_isBranch) ? b_e_rs2 : b_de_IorSimm ;

        assign b_e_SHamt = b_de_isRRint ? b_e_rs2[4:0] : b_de_rs2ID;
        assign b_e_minus = b_de_funct7 & b_de_isRRint;

        assign b_e_ALUplus = b_e_ALUin1 + b_e_ALUin2;
        assign b_e_ALUminus = {1'b0, b_e_ALUin1} + {1'b1, ~b_e_ALUin2} + 33'b1;

        assign b_e_LT  = (b_e_ALUin1[31] ^ b_e_ALUin2[31]) ? b_e_ALUin1[31] : b_e_ALUminus[32];
        assign b_e_LTU = b_e_ALUminus[32];
        assign b_e_EQ  = (b_e_ALUin1 == b_e_ALUin2);

        assign b_e_shifter_in = (b_de_funct3 == 3'b001) ? flip32(b_e_ALUin1) : b_e_ALUin1;

        /* verilator lint_off WIDTH */
        assign b_e_shifter = $signed({b_e_arith_shift & b_e_ALUin1, b_e_shifter_in}) >>> b_e_ALUin2[4:0];
        /* verilator lint_off WIDTH */

        assign b_e_left_shift = flip32(b_e_shifter);

        assign b_e_ALUout =
                (b_de_funct3_is[0] ? (b_e_minus ? b_e_ALUminus[31:0] : b_e_ALUplus) : 32'b0) |
                (b_de_funct3_is[1] ? b_e_left_shift                                 : 32'b0) |
                (b_de_funct3_is[2] ? {31'b0, b_e_LT }                               : 32'b0) |
                (b_de_funct3_is[3] ? {31'b0, b_e_LTU}                               : 32'b0) |
                (b_de_funct3_is[4] ? b_e_ALUin1 ^ b_e_ALUin2                        : 32'b0) |
                (b_de_funct3_is[5] ? b_e_shifter                                    : 32'b0) |
                (b_de_funct3_is[6] ? b_e_ALUin1 | b_e_ALUin2                        : 32'b0) |
                (b_de_funct3_is[7] ? b_e_ALUin1 & b_e_ALUin2                        : 32'b0) ;

        assign b_e_take_branch =
                (b_de_funct3_is[0] &  b_e_EQ ) |
                (b_de_funct3_is[1] & !b_e_EQ ) |
                (b_de_funct3_is[4] &  b_e_LT ) |
                (b_de_funct3_is[5] & !b_e_LT ) |
                (b_de_funct3_is[6] &  b_e_LTU) |
                (b_de_funct3_is[7] & !b_e_LTU) ;

`ifdef BTYPE_IN_B

        assign b_e_jalrADDR = {b_e_ALUplus[31:1],1'b0};

`ifdef CONFIG_RAS
        assign b_e_JoB =((b_de_isJALR   & (b_de_predictRA != b_e_jalrADDR)) |
                         (b_de_isBranch & b_e_take_branch));
`else        
	assign b_e_JoB = b_de_isJALR | (b_de_isBranch & b_e_take_branch);
`endif
        
	assign b_e_JoB_ADDR = b_de_isBranch ? b_de_PCplus4orBimm : b_e_jalrADDR;
`endif
        assign b_e_addr = b_e_rs1 + b_de_IorSimm;

        assign b_e_result = b_de_isJALorJALRorLUIorAUIPC ? b_de_PCplus4orUimm : b_e_ALUout;

        always@(posedge clk) begin
		b_em_result       <= b_e_result;
                b_em_ADDR         <= b_e_addr;
                b_em_nop          <= b_de_nop & !a_e_JoB;
                b_em_rdID         <= b_de_rdID;
                b_em_rs1ID        <= b_de_rs1ID;
                b_em_rs2ID        <= b_de_rs2ID;
                b_em_funct3       <= b_de_funct3;
                b_em_csrID_is     <= 4'b0001 << b_de_csrID;
                b_em_rs2          <= b_e_rs2;
                b_em_isLoad       <= b_de_isLoad & !a_e_JoB;
                b_em_isStore      <= b_de_isStore & !a_e_JoB;
                b_em_isCSRRS      <= b_de_isCSRRS & !a_e_JoB;
                b_em_wbEnable     <= b_de_wbEnable & !a_e_JoB;

`ifdef BTYPE_IN_B		
                b_em_JoB_now      <= b_e_JoB;
                b_em_JoB_ADDR     <= b_e_JoB_ADDR;
`endif
        end
       	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	assign a_m_isIO  = a_em_ADDR[22];
	assign a_m_isRAM = !a_m_isIO;
	assign a_m_isB = (a_em_funct3[1:0] == 2'b00);
	assign a_m_isH = (a_em_funct3[1:0] == 2'b01);

	assign a_m_store_DATA[ 7:0 ] = a_em_rs2[7:0];
	assign a_m_store_DATA[15:8 ] = a_em_ADDR[0] ? a_em_rs2[7:0]  : a_em_rs2[15:8 ] ;
	assign a_m_store_DATA[23:16] = a_em_ADDR[1] ? a_em_rs2[7:0]  : a_em_rs2[23:16] ;
	assign a_m_store_DATA[31:24] = a_em_ADDR[0] ? a_em_rs2[7:0]  :
				       a_em_ADDR[1] ? a_em_rs2[15:8] : a_em_rs2[31:24] ;

	assign a_m_store_WMASK = a_m_isB ? (a_em_ADDR[1] ? (a_em_ADDR[0] ? 4'b1000 : 4'b0100)  :
							   (a_em_ADDR[0] ? 4'b0010 : 4'b0001)) :
				 a_m_isH ? (a_em_ADDR[1] ?                 4'b1100 : 4'b0011)  :
				                                                     4'b1111   ;

	assign a_m_WMASK = {4{a_em_isStore & a_m_isRAM}} & a_m_store_WMASK;

	assign a_m_CSR_data = (a_em_csrID_is[0] ? cycle  [31:0 ] : 32'b0) |
	 		      (a_em_csrID_is[2] ? cycle  [63:32] : 32'b0) |	       
			      (a_em_csrID_is[1] ? instret[31:0 ] : 32'b0) |
			      (a_em_csrID_is[3] ? instret[63:32] : 32'b0) ;

	assign a_m_wb_DATA = a_em_isLoad  ? a_IO_mem_rdata :
          		     a_em_isCSRRS ? a_m_CSR_data   :
          		     		    a_em_result    ;

	assign a_IO_mem_addr  = a_em_ADDR;
	assign a_IO_mem_wr    = a_em_isStore & a_m_isIO;
	assign a_IO_mem_wdata = a_em_rs2;

        assign a_mem_wmask = a_m_WMASK;
        assign a_mem_addr = {9'b0,a_em_ADDR[22:0]};
        assign a_mem_wdata  = a_m_store_DATA;
	assign a_mem_cen   = a_em_isLoad | a_em_isStore;
	assign a_mw_Mdata  = a_mem_data;

	assign a_m_isNotIOandLoad = a_em_isLoad & ! a_m_isIO;

        assign a_m_lb  = (a_em_funct3[2:0] == 3'b000);
        assign a_m_lbu = (a_em_funct3[2:0] == 3'b100);
        assign a_m_lh  = (a_em_funct3[2:0] == 3'b001);
        assign a_m_lhu = (a_em_funct3[2:0] == 3'b101);

	always@(posedge clk) begin
		a_mw_nop      <= a_em_nop;
		a_mw_rdID     <= a_em_rdID;
		a_mw_wb_DATA  <= a_m_wb_DATA;
		a_mw_wbEnable <= a_em_wbEnable;

		a_mw_funct3   <= a_em_funct3;
		a_mw_ADDR     <= a_em_ADDR;
		a_mw_isNotIOandLoad <= a_m_isNotIOandLoad;

		a_mw_lb     <= a_m_lb;
                a_mw_lbu    <= a_m_lbu;
                a_mw_lh     <= a_m_lh;
                a_mw_lhu    <= a_m_lhu;

	end

	always@(posedge clk) begin
		if(!resetn) begin
			instret <= 0;
		end else if(!a_mw_nop & !b_mw_nop) begin
			instret <= instret + 2;
		end else if(!a_mw_nop | !b_mw_nop) begin
			instret <= instret + 1;
		end
		cycle <= !resetn ? 0 : cycle + 1;
	end

	reg [63:0] cycle;
	reg [63:0] instret;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

`ifdef STORE_IN_B

	assign b_m_isIO  = b_em_ADDR[22];
	assign b_m_isRAM = !b_m_isIO;
	assign b_m_isB = (b_em_funct3[1:0] == 2'b00);
	assign b_m_isH = (b_em_funct3[1:0] == 2'b01);

	assign b_m_store_DATA[ 7:0 ] = b_em_rs2[7:0];
	assign b_m_store_DATA[15:8 ] = b_em_ADDR[0] ? b_em_rs2[7:0]  : b_em_rs2[15:8 ] ;
	assign b_m_store_DATA[23:16] = b_em_ADDR[1] ? b_em_rs2[7:0]  : b_em_rs2[23:16] ;
	assign b_m_store_DATA[31:24] = b_em_ADDR[0] ? b_em_rs2[7:0]  :
				       b_em_ADDR[1] ? b_em_rs2[15:8] : b_em_rs2[31:24] ;

	assign b_m_store_WMASK = b_m_isB ? (b_em_ADDR[1] ? (b_em_ADDR[0] ? 4'b1000 : 4'b0100)  :
							   (b_em_ADDR[0] ? 4'b0010 : 4'b0001)) :
				 b_m_isH ? (b_em_ADDR[1] ?                 4'b1100 : 4'b0011)  :
				                                                     4'b1111   ;

	assign b_m_WMASK = {4{b_em_isStore & b_m_isRAM}} & b_m_store_WMASK;

	assign b_m_wb_DATA = b_em_isLoad  ? b_IO_mem_rdata :
          		     		    b_em_result    ;

	assign b_IO_mem_addr  = b_em_ADDR;
	assign b_IO_mem_wr    = b_em_isStore & b_m_isIO;
	assign b_IO_mem_wdata = b_em_rs2;

        assign b_mem_wmask = b_m_WMASK & {4{!store_addr_HAZ}};
        assign b_mem_addr  = {9'b0,b_em_ADDR[22:0]};
        assign b_mem_wdata = b_m_store_DATA;
	assign b_mem_cen   = b_em_isLoad | b_em_isStore;

`ifdef LOAD_IN_B
	assign b_mw_Mdata  = b_mw_ASBL ? b_mw_store : b_mem_data;
	assign a_store_b_load_HAZ = a_em_isStore & (|a_mem_wmask) & b_em_isLoad & (a_mem_addr == b_mem_addr);

	assign b_m_lb  = (b_em_funct3[2:0] == 3'b000);
        assign b_m_lbu = (b_em_funct3[2:0] == 3'b100);
        assign b_m_lh  = (b_em_funct3[2:0] == 3'b001);
        assign b_m_lhu = (b_em_funct3[2:0] == 3'b101);
	
`else
	assign b_mw_Mdata  = b_mem_data;
        assign store_addr_HAZ = (b_mem_addr==a_mem_addr) & (|a_mem_wmask);	
`endif

	assign b_m_isNotIOandLoad = b_em_isLoad & ! b_m_isIO;

`else
	assign b_IO_mem_addr  = 0;
	assign b_IO_mem_wr    = 0;
	assign b_IO_mem_wdata = 0;
       	
	assign b_mem_wmask = 0;
        assign b_mem_addr  = 0;
        assign b_mem_wdata = 0;
        assign b_mem_cen   = 0;

	assign b_m_wb_DATA = b_em_result;
`endif

        always@(posedge clk) begin
		b_mw_nop      <= b_em_nop;
		b_mw_rdID     <= b_em_rdID;
		b_mw_wb_DATA  <= b_m_wb_DATA;
		b_mw_wbEnable <= b_em_wbEnable;

	`ifdef LOAD_IN_B
		b_mw_funct3   <= b_em_funct3;
		b_mw_ADDR     <= b_em_ADDR;
		b_mw_isNotIOandLoad <= b_m_isNotIOandLoad;
		b_mw_ASBL     <= a_store_b_load_HAZ;
                b_mw_store    <= a_m_store_DATA;

		b_mw_lb     <= b_m_lb;
                b_mw_lbu    <= b_m_lbu;
                b_mw_lh     <= b_m_lh;
                b_mw_lhu    <= b_m_lhu;
	`endif

        end
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	assign a_w_isIO   = a_mw_ADDR[22];

        assign a_w_LB = a_mw_ADDR[1:0] == 2'b00 ? {{24{a_mw_Mdata[7 ]}}, a_mw_Mdata[ 7:0 ]} :
                        a_mw_ADDR[1:0] == 2'b01 ? {{24{a_mw_Mdata[15]}}, a_mw_Mdata[15:8 ]} :
                        a_mw_ADDR[1:0] == 2'b10 ? {{24{a_mw_Mdata[23]}}, a_mw_Mdata[23:16]} :
                                                  {{24{a_mw_Mdata[31]}}, a_mw_Mdata[31:24]} ;

        assign a_w_LBU = a_mw_ADDR[1:0] == 2'b00 ? {24'b0, a_mw_Mdata[ 7:0 ]} :
                         a_mw_ADDR[1:0] == 2'b01 ? {24'b0, a_mw_Mdata[15:8 ]} :
                         a_mw_ADDR[1:0] == 2'b10 ? {24'b0, a_mw_Mdata[23:16]} :
                                                   {24'b0, a_mw_Mdata[31:24]} ;

        assign a_w_LH = a_mw_ADDR[1] == 1'b0 ? {{16{a_mw_Mdata[15]}}, a_mw_Mdata[15:0 ]} :
                                               {{16{a_mw_Mdata[31]}}, a_mw_Mdata[31:16]} ;

        assign a_w_LHU = a_mw_ADDR[1] == 1'b0 ? {16'b0, a_mw_Mdata[15:0 ]} :
                                                {16'b0, a_mw_Mdata[31:16]} ;

        assign a_w_mem_RES = a_mw_lb  ? a_w_LB  :
                             a_mw_lbu ? a_w_LBU :
                             a_mw_lh  ? a_w_LH  :
                             a_mw_lhu ? a_w_LHU :
                                     a_mw_Mdata ;

	assign a_wb_DATA   = a_mw_isNotIOandLoad ? a_w_mem_RES : a_mw_wb_DATA;
	assign a_wb_enable = a_mw_wbEnable;
	assign a_wb_rdID   = a_mw_rdID;

`ifdef LOAD_IN_B

        assign b_w_isIO   = b_mw_ADDR[22];

        assign b_w_LB = b_mw_ADDR[1:0] == 2'b00 ? {{24{b_mw_Mdata[7 ]}}, b_mw_Mdata[ 7:0 ]} :
                        b_mw_ADDR[1:0] == 2'b01 ? {{24{b_mw_Mdata[15]}}, b_mw_Mdata[15:8 ]} :
                        b_mw_ADDR[1:0] == 2'b10 ? {{24{b_mw_Mdata[23]}}, b_mw_Mdata[23:16]} :
                                                  {{24{b_mw_Mdata[31]}}, b_mw_Mdata[31:24]} ;

        assign b_w_LBU = b_mw_ADDR[1:0] == 2'b00 ? {24'b0, b_mw_Mdata[ 7:0 ]} :
                         b_mw_ADDR[1:0] == 2'b01 ? {24'b0, b_mw_Mdata[15:8 ]} :
                         b_mw_ADDR[1:0] == 2'b10 ? {24'b0, b_mw_Mdata[23:16]} :
                                                   {24'b0, b_mw_Mdata[31:24]} ;

        assign b_w_LH = b_mw_ADDR[1] == 1'b0 ? {{16{b_mw_Mdata[15]}}, b_mw_Mdata[15:0 ]} :
                                               {{16{b_mw_Mdata[31]}}, b_mw_Mdata[31:16]} ;

        assign b_w_LHU = b_mw_ADDR[1] == 1'b0 ? {16'b0, b_mw_Mdata[15:0 ]} :
                                                {16'b0, b_mw_Mdata[31:16]} ;

        assign b_w_mem_RES = b_mw_lb  ? b_w_LB  :
                             b_mw_lbu ? b_w_LBU :
                             b_mw_lh  ? b_w_LH  :
                             b_mw_lhu ? b_w_LHU :
                                     b_mw_Mdata ;

        assign b_wb_DATA   = b_mw_isNotIOandLoad ? b_w_mem_RES : b_mw_wb_DATA;
        assign b_wb_enable = b_mw_wbEnable;
        assign b_wb_rdID   = b_mw_rdID;

`else

	assign b_wb_DATA   = b_mw_wb_DATA;
	assign b_wb_enable = b_mw_wbEnable;
	assign b_wb_rdID   = b_mw_rdID;

`endif

	always@(posedge clk) begin
		if(a_wb_enable) begin
			reg_file[a_wb_rdID] <= a_wb_DATA;
		end
	
		if(b_wb_enable) begin
			reg_file[b_wb_rdID] <= b_wb_DATA;
		end
	end

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	function [31:0] flip32;
		input [31:0] x;
		flip32 = {x[ 0], x[ 1], x[ 2], x[ 3], x[ 4], x[ 5], x[ 6], x[ 7], 
			  x[ 8], x[ 9], x[10], x[11], x[12], x[13], x[14], x[15], 
			  x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
			  x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]};
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
        endfunction

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        `ifdef BENCH

                integer a_nbBranch = 0;
                integer a_nbPredictHit = 0;
                integer b_nbBranch = 0;
                integer b_nbPredictHit = 0;
		integer a_nbJAL  = 0;
                integer a_nbJALR = 0;
		integer b_nbJAL  = 0;
                integer b_nbJALR = 0;

                always @(posedge clk) begin
                        if(resetn) begin
                                if(a_de_isBranch) begin
                                        a_nbBranch <= a_nbBranch + 1;
                                        if(0) begin
                                                a_nbPredictHit <= a_nbPredictHit + 1;
                                        end
                                end

                                if(a_de_isJAL) begin
                                        a_nbJAL <= a_nbJAL + 1;
                                end
                                if(a_de_isJALR) begin
                                        a_nbJALR <= a_nbJALR + 1;
                                end

				if(b_de_isBranch) begin
                                        b_nbBranch <= b_nbBranch + 1;
                                        if(0) begin
                                                b_nbPredictHit <= b_nbPredictHit + 1;
                                        end
                                end

                                if(b_de_isJAL) begin
                                        b_nbJAL <= b_nbJAL + 1;
                                end
                                if(b_de_isJALR) begin
                                        b_nbJALR <= b_nbJALR + 1;
                                end

                        end
		end

                /* verilator lint_off WIDTH */
                always @(posedge clk) begin
                        if(halt) begin
                                $display("----------------------------");
                                $display("A Branch hits= %3.3f\%%", a_nbPredictHit*100.0/a_nbBranch);
                                $display("B Branch hits= %3.3f\%%", b_nbPredictHit*100.0/b_nbBranch);
                                $display("Numbers of = (Cycles: %d, Instret: %d)", cycle, instret);
                                $finish();
                        end
                end
                /* verilator lint_on WIDTH */
        `endif

endmodule
