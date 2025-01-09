`define TORVS
//`define GOWIN
//`define DUALMEM
`define DE10S

`ifndef BENCH
	`define SYN
`endif


`ifdef DUALMEM
module mem (
        input             clk,

        input             imem_en,
        input      [31:0] imem_addr,
        output reg [31:0] imem_data,

        output reg [31:0] mem_data,
        input      [ 3:0] mem_wmask,
        input      [31:0] mem_addr,
        input      [31:0] mem_wdata

);
	
	wire [13:0] mem_addr_seg  = mem_addr [15:2]; 
	wire [13:0] imem_addr_seg = imem_addr[15:2];
	
	parameter RAM_SIZE = 32768;

	`ifdef DE10S
	reg [ 3:0][7:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [ 3:0][7:0] ROM [0:RAM_SIZE-1];  // 64kB of RAM
	`else
	reg [31:0]      RAM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [31:0]      ROM [0:RAM_SIZE-1];  // 64kB of RAM
	`endif

	`ifdef SYN	
	initial begin
                $readmemh("DATARAM.hex", RAM);		
                $readmemh("PROGROM.hex", ROM);		
	end
	`else
	initial begin
                $readmemh("HEX/DATARAM.hex", RAM);		
                $readmemh("HEX/PROGROM.hex", ROM);		
	end
	`endif

	always@(posedge clk) begin
		`ifdef DE10S
		if(mem_wmask[0]) RAM[mem_addr_seg][0] <= mem_wdata[ 7:0 ];
		if(mem_wmask[1]) RAM[mem_addr_seg][1] <= mem_wdata[15:8 ];
		if(mem_wmask[2]) RAM[mem_addr_seg][2] <= mem_wdata[23:16];
		if(mem_wmask[3]) RAM[mem_addr_seg][3] <= mem_wdata[31:24];
		`else
		if(mem_wmask[0]) RAM[mem_addr_seg][ 7:0 ] <= mem_wdata[ 7:0 ];
		if(mem_wmask[1]) RAM[mem_addr_seg][15:8 ] <= mem_wdata[15:8 ];
		if(mem_wmask[2]) RAM[mem_addr_seg][23:16] <= mem_wdata[23:16];
		if(mem_wmask[3]) RAM[mem_addr_seg][31:24] <= mem_wdata[31:24];
		`endif
		mem_data <= RAM[mem_addr_seg];
	end 

        always@(posedge clk) begin
                if(imem_en)
                        imem_data <= ROM[imem_addr_seg];
        end
endmodule

`elsif TORVS

module mem(
        input             clk,
	input 	  	  reset,

        input             a_imem_en,
        input      [31:0] a_imem_addr,
        output     [31:0] a_imem_data,

	input             b_imem_en,
        input      [31:0] b_imem_addr,
        output     [31:0] b_imem_data,

	`ifdef DE10S
	input		  a_mem_we,
	input		  b_mem_we,
	`endif

	output     [31:0] a_mem_data,
        input      [ 3:0] a_mem_wmask,
        input      [31:0] a_mem_addr,
        input      [31:0] a_mem_wdata,
        input      	  a_mem_cen,

	output     [31:0] b_mem_data,
        input      [ 3:0] b_mem_wmask,
        input      [31:0] b_mem_addr,
        input      [31:0] b_mem_wdata,
        input      	  b_mem_cen

);

	parameter ROM_SIZE = 32768;
	parameter RAM_SIZE = 32768;

	insn_mem #(
		.IROM_SIZE(ROM_SIZE)	
	) imem (
        	.clk        (clk),
        	.a_imem_en  (a_imem_en),
        	.a_imem_addr(a_imem_addr),
        	.a_imem_data(a_imem_data),
		.b_imem_en  (b_imem_en),
        	.b_imem_addr(b_imem_addr),
        	.b_imem_data(b_imem_data)
	);

	//`ifdef GOWIN	  

	wire wrea = |a_mem_wmask;
	wire wreb = |b_mem_wmask;	
	
	Gowin_DPB data_mem (
		.clka(clk),     //input clka
		.clkb(clk),     //input clkb

		.resetb(reset), //input resetb
		.reseta(reset), //input reseta

		.wrea(wrea), 	        // A WRITE ENABLE (0 - READ, 1 - WRITE)
		.cea(a_mem_cen),              // A CLOCK ENABLE
		.dina(a_mem_wdata),     // A DATA IN
		.byte_ena(a_mem_wmask), // A WRITE MASK
		.ada(a_mem_addr[15:2]),       // A DATA ADDRESS
		.douta(a_mem_data),     // A DATA OUT 

		.wreb(wreb), 	        // B WRITE ENABLE (0 - READ, 1 - WRITE)
		.ceb(b_mem_cen),              // B CLOCK ENABLE
		.dinb(b_mem_wdata),     // B DATA IN
		.byte_enb(b_mem_wmask), // B WRITE MASK
		.adb(b_mem_addr[15:2]),       // B DATA ADDRESS
		.doutb(b_mem_data),     // B DATA OUT

		.ocea(a_mem_cen), //input ocea INVALID
		.oceb(1'b1) //input oceb INVALID
	);

	//`else

	/*
	wire a_mem_we = |a_mem_wmask;
	wire b_mem_we = |b_mem_wmask;	
	
	data_mem #(
		.DRAM_SIZE(RAM_SIZE)	
	) dmem (
		.clk        (clk),
		.a_mem_data (a_mem_data),
		.a_mem_wmask(a_mem_wmask),
		.a_mem_addr (a_mem_addr),
		.a_mem_wdata(a_mem_wdata),
<<<<<<< HEAD
		.a_mem_we   (a_mem_we),
		.b_mem_data (b_mem_data),
		.b_mem_wmask(b_mem_wmask),
		.b_mem_addr (b_mem_addr),
		.b_mem_wdata(b_mem_wdata),
		.b_mem_we   (b_mem_we)
	);*/




=======
		`ifdef DE10S
	       	.a_mem_we   (a_mem_we), 
		.b_mem_we   (b_mem_we),
		`endif	
		.b_mem_data (b_mem_data),
		.b_mem_wmask(b_mem_wmask),
		.b_mem_addr (b_mem_addr),
		.b_mem_wdata(b_mem_wdata)
	);
	*/
	
>>>>>>> main
endmodule

module insn_mem(
        input             clk,

        input             a_imem_en,
        input      [31:0] a_imem_addr,
        output reg [31:0] a_imem_data,

	input             b_imem_en,
        input      [31:0] b_imem_addr,
        output reg [31:0] b_imem_data

);
	wire [13:0] a_imem_addr_seg = a_imem_addr[15:2];
	wire [13:0] b_imem_addr_seg = b_imem_addr[15:2];

	parameter IROM_SIZE = 32768;

	`ifdef DE10S
	logic [3:0][7:0] ROM [0:IROM_SIZE-1];  // 64kB of RAM
	`else	
	reg [31:0] ROM [0:IROM_SIZE-1];  // 64kB of RAM
	`endif

	initial begin
		`ifndef SYN
                $readmemh("HEX/PROGROM.hex", ROM);		
		`else
                $readmemh("PROGROM.hex", ROM);		
		`endif
	end

	always@(posedge clk) begin
                if(a_imem_en)
                        a_imem_data <= ROM[a_imem_addr_seg];
	end

        always@(posedge clk) begin
                if(b_imem_en)
                        b_imem_data <= ROM[b_imem_addr_seg];
        end

endmodule 


module data_mem(
        input             clk,

	output reg [31:0] a_mem_data,
        input      [ 3:0] a_mem_wmask,
        input      [31:0] a_mem_addr,
        input      [31:0] a_mem_wdata,
        input             a_mem_we,

	`ifdef DE10S
	input		  a_mem_we,
	input		  b_mem_we,
	`endif

	output reg [31:0] b_mem_data,
        input      [ 3:0] b_mem_wmask,
        input      [31:0] b_mem_addr,
        input      [31:0] b_mem_wdata,
        input             b_mem_we

);
	wire [13:0] a_mem_addr_seg  = a_mem_addr [15:2];
	wire [13:0] b_mem_addr_seg  = b_mem_addr [15:2];

	parameter DRAM_SIZE = 32768;
	
	`ifdef DE10S
	logic [3:0][7:0] RAM [0:DRAM_SIZE-1];  // 64kB of RAM
	`else
	reg [31:0] RAM [0:DRAM_SIZE-1];  // 64kB of RAM
	`endif

	initial begin
		`ifndef SYN
                $readmemh("HEX/GWDATARAM.hex", RAM);		
		`else
                $readmemh("DATARAM.hex", RAM);		
		`endif
	end
	
	always@(posedge clk) begin
<<<<<<< HEAD
		`ifndef SYN
=======
		`ifdef DE10S
>>>>>>> main
		if(a_mem_we) begin
			if(a_mem_wmask[0]) RAM[a_mem_addr_seg][0] <= a_mem_wdata[ 7:0 ];
			if(a_mem_wmask[1]) RAM[a_mem_addr_seg][1] <= a_mem_wdata[15:8 ];
			if(a_mem_wmask[2]) RAM[a_mem_addr_seg][2] <= a_mem_wdata[23:16];
			if(a_mem_wmask[3]) RAM[a_mem_addr_seg][3] <= a_mem_wdata[31:24];
<<<<<<< HEAD
		end else if(~a_mem_we)
	        	a_mem_data <= RAM[a_mem_addr_seg];
=======
		end
>>>>>>> main
		`else
		if(a_mem_we) begin
			if(a_mem_wmask[0]) RAM[a_mem_addr_seg][ 7:0 ] <= a_mem_wdata[ 7:0 ];
			if(a_mem_wmask[1]) RAM[a_mem_addr_seg][15:8 ] <= a_mem_wdata[15:8 ];
			if(a_mem_wmask[2]) RAM[a_mem_addr_seg][23:16] <= a_mem_wdata[23:16];
			if(a_mem_wmask[3]) RAM[a_mem_addr_seg][31:24] <= a_mem_wdata[31:24];
		end else if(~a_mem_we)
	        	a_mem_data <= RAM[a_mem_addr_seg];

		`endif
	end

	always@(posedge clk) begin
<<<<<<< HEAD
		`ifndef SYN
		if(b_mem_we) begin
=======
		`ifdef DE10S
		if(a_mem_we) begin
>>>>>>> main
			if(b_mem_wmask[0]) RAM[b_mem_addr_seg][0] <= b_mem_wdata[ 7:0 ];
			if(b_mem_wmask[1]) RAM[b_mem_addr_seg][1] <= b_mem_wdata[15:8 ];
			if(b_mem_wmask[2]) RAM[b_mem_addr_seg][2] <= b_mem_wdata[23:16];
			if(b_mem_wmask[3]) RAM[b_mem_addr_seg][3] <= b_mem_wdata[31:24];
<<<<<<< HEAD
		end else if(~b_mem_we)
	        	b_mem_data <= RAM[b_mem_addr_seg];

=======
		end
>>>>>>> main
		`else
		if(b_mem_we) begin
			if(b_mem_wmask[0]) RAM[b_mem_addr_seg][ 7:0 ] <= b_mem_wdata[ 7:0 ];
			if(b_mem_wmask[1]) RAM[b_mem_addr_seg][15:8 ] <= b_mem_wdata[15:8 ];
			if(b_mem_wmask[2]) RAM[b_mem_addr_seg][23:16] <= b_mem_wdata[23:16];
			if(b_mem_wmask[3]) RAM[b_mem_addr_seg][31:24] <= b_mem_wdata[31:24];
		end else if(~b_mem_we)
	        	b_mem_data <= RAM[b_mem_addr_seg];

		`endif
	end

endmodule 

// Quartus Prime SystemVerilog Template
//
// True Dual-Port RAM with different read/write addresses and single read/write clock
// and with a control for writing single bytes into the memory word; byte enable

// Read during write produces old data on ports A and B and old data on mixed ports
// For device families that do not support this mode (e.g. Stratix V) the ram is not inferred

/*module byte_enabled_true_dual_port_ram
	#(
		parameter int
		BYTE_WIDTH = 8,
		ADDRESS_WIDTH = 6,
		BYTES = 4,
		DATA_WIDTH_R = BYTE_WIDTH * BYTES
)
(
	input [ADDRESS_WIDTH-1:0] addr1,
	input [ADDRESS_WIDTH-1:0] addr2,
	input [BYTES-1:0] be1,
	input [BYTES-1:0] be2,
	input [BYTE_WIDTH-1:0] data_in1, 
	input [BYTE_WIDTH-1:0] data_in2, 
	input we1, we2, clk,
	output [DATA_WIDTH_R-1:0] data_out1,
	output [DATA_WIDTH_R-1:0] data_out2);
	localparam RAM_DEPTH = 1 << ADDRESS_WIDTH;

	// model the RAM with two dimensional packed array
	logic [BYTES-1:0][BYTE_WIDTH-1:0] ram[0:RAM_DEPTH-1];

	reg [DATA_WIDTH_R-1:0] data_reg1;
	reg [DATA_WIDTH_R-1:0] data_reg2;

	// port A
	always@(posedge clk)
	begin
		if(we1) begin
		// edit this code if using other than four bytes per word
			if(be1[0]) ram[addr1][0] <= data_in1;
			if(be1[1]) ram[addr1][1] <= data_in1;
			if(be1[2]) ram[addr1][2] <= data_in1;
			if(be1[3]) ram[addr1][3] <= data_in1;
		end
	data_reg1 <= ram[addr1];
	end

	assign data_out1 = data_reg1;
   
	// port B
	always@(posedge clk)
	begin
		if(we2) begin
		// edit this code if using other than four bytes per word
			if(be2[0]) ram[addr2][0] <= data_in2;
			if(be2[1]) ram[addr2][1] <= data_in2;
			if(be2[2]) ram[addr2][2] <= data_in2;
			if(be2[3]) ram[addr2][3] <= data_in2;
		end
	data_reg2 <= ram[addr2];
	end

	assign data_out2 = data_reg2;

endmodule : byte_enabled_true_dual_port_ram
*/
// Quartus Prime SystemVerilog Template
//
// True Dual-Port RAM with different read/write addresses and single read/write clock
// and with a control for writing single bytes into the memory word; byte enable

// Read during write produces old data on ports A and B and old data on mixed ports
// For device families that do not support this mode (e.g. Stratix V) the ram is not inferred

/*
module byte_enabled_true_dual_port_ram
	#(
		parameter int
		BYTE_WIDTH = 8,
		ADDRESS_WIDTH = 6,
		BYTES = 4,
		DATA_WIDTH_R = BYTE_WIDTH * BYTES
)
(
	input [ADDRESS_WIDTH-1:0] addr1,
	input [ADDRESS_WIDTH-1:0] addr2,
	input [BYTES-1:0] be1,
	input [BYTES-1:0] be2,
	input [BYTE_WIDTH -1:0] data_in1, 
	input [BYTE_WIDTH -1:0] data_in2, 
	input we1, we2, clk,
	output [DATA_WIDTH_R-1:0] data_out1,
	output [DATA_WIDTH_R-1:0] data_out2);
	localparam RAM_DEPTH = 1 << ADDRESS_WIDTH;

	//initial begin
	//	$readmemh("DATARAM.hex", ram);
	//end

	// model the RAM with two dimensional packed array
	logic [BYTES-1:0][BYTE_WIDTH-1:0] ram[0:RAM_DEPTH-1];

	reg [DATA_WIDTH_R-1:0] data_reg1;
	reg [DATA_WIDTH_R-1:0] data_reg2;

	// port A
	always@(posedge clk)
	begin
		if(we1) begin
		// edit this code if using other than four bytes per word
			if(be1[0]) ram[addr1][0] <= data_in1[ 7:0 ];
			if(be1[1]) ram[addr1][1] <= data_in1[15:8 ];
			if(be1[2]) ram[addr1][2] <= data_in1[23:16];
			if(be1[3]) ram[addr1][3] <= data_in1[31:24];			
			if(be1[0]) ram[addr1][0] <= data_in1;
			if(be1[1]) ram[addr1][1] <= data_in1;
			if(be1[2]) ram[addr1][2] <= data_in1;
			if(be1[3]) ram[addr1][3] <= data_in1;
		end
	end

	always@(posedge clk) begin
		data_reg1 <= ram[addr1];
	end

	assign data_out1 = data_reg1 & {32{1'b1}};
   
	// port B
	always@(posedge clk)
	begin
		if(we2) begin
		// edit this code if using other than four bytes per word
			/*if(be2[0]) ram[addr2][0] <= data_in2[ 7:0 ];
			if(be2[1]) ram[addr2][1] <= data_in2[15:8 ];
			if(be2[2]) ram[addr2][2] <= data_in2[23:16];
			if(be2[3]) ram[addr2][3] <= data_in2[31:24];

			if(be2[0]) ram[addr2][0] <= data_in2;
			if(be2[1]) ram[addr2][1] <= data_in2;
			if(be2[2]) ram[addr2][2] <= data_in2;
			if(be2[3]) ram[addr2][3] <= data_in2;
		end
	end

	always@(posedge clk) begin
		data_reg2 <= ram[addr2];
	end

	assign data_out2 = data_reg2 & {32{1'b1}};

endmodule : byte_enabled_true_dual_port_ram
*/

`else

module mem (
        input             clk,

        input             imem_en,
        input      [31:0] imem_addr,
        output reg [31:0] imem_data,

        output reg [31:0] mem_data,
        input      [ 3:0] mem_wmask,
        input      [31:0] mem_addr,
        input      [31:0] mem_wdata

);
	wire [15:0] mem_addr_seg  = mem_addr [17:2]; 
	wire [15:0] imem_addr_seg = imem_addr[17:2];
	
	parameter RAM_SIZE = 32768;

	reg [ 3:0][7:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM

	initial begin
                $readmemh("HEX/RAM.hex", RAM);		
	end
	
	always@(posedge clk) begin
		if(mem_wmask[0]) RAM[mem_addr_seg][0] <= mem_wdata[ 7:0 ];
		if(mem_wmask[1]) RAM[mem_addr_seg][1] <= mem_wdata[15:8 ];
		if(mem_wmask[2]) RAM[mem_addr_seg][2] <= mem_wdata[23:16];
		if(mem_wmask[3]) RAM[mem_addr_seg][3] <= mem_wdata[31:24];
        	mem_data <= RAM[mem_addr_seg];
	end

        always@(posedge clk) begin
                if(imem_en)
                        imem_data <= RAM[imem_addr_seg];
        end
endmodule 

`endif

