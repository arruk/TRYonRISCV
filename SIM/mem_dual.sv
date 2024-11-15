module mem(
        input             clk,

        input             a_imem_en,
        input      [31:0] a_imem_addr,
        output reg [31:0] a_imem_data,

	input             b_imem_en,
        input      [31:0] b_imem_addr,
        output reg [31:0] b_imem_data,

	output reg [31:0] a_mem_data,
        input      [ 3:0] a_mem_wmask,
        input      [31:0] a_mem_addr,
        input      [31:0] a_mem_wdata,

	output reg [31:0] b_mem_data,
        input      [ 3:0] b_mem_wmask,
        input      [31:0] b_mem_addr,
        input      [31:0] b_mem_wdata

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

	data_mem #(
		.DRAM_SIZE(RAM_SIZE)	
	) dmem (
		.clk        (clk),
		.a_mem_data (a_mem_data),
		.a_mem_wmask(a_mem_wmask),
		.a_mem_addr (a_mem_addr),
		.a_mem_wdata(a_mem_wdata),
		.b_mem_data (b_mem_data),
		.b_mem_wmask(b_mem_wmask),
		.b_mem_addr (b_mem_addr),
		.b_mem_wdata(b_mem_wdata)
	);



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
	//wire [15:0] b_imem_addr_seg = a_imem_addr[17:2];
	//wire [15:0] a_imem_addr_seg = b_imem_addr[17:2];
	//wire [14:0] a_imem_addr_seg = a_imem_addr[16:2];
	//wire [14:0] b_imem_addr_seg = b_imem_addr[16:2];
	wire [13:0] a_imem_addr_seg = a_imem_addr[15:2];
	wire [13:0] b_imem_addr_seg = b_imem_addr[15:2];


	parameter IROM_SIZE = 32768;

	reg [3:0][7:0] ROM [0:IROM_SIZE-1];  // 64kB of RAM

	initial begin
                $readmemh("PROGROM.hex", ROM);		
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

	output reg [31:0] b_mem_data,
        input      [ 3:0] b_mem_wmask,
        input      [31:0] b_mem_addr,
        input      [31:0] b_mem_wdata

);
	//wire [15:0] a_mem_addr_seg  = a_mem_addr [17:2];
	//wire [15:0] b_mem_addr_seg  = b_mem_addr [17:2];
	//wire [14:0] a_mem_addr_seg  = a_mem_addr [16:2];
	//wire [14:0] b_mem_addr_seg  = b_mem_addr [16:2];
	wire [13:0] a_mem_addr_seg  = a_mem_addr [15:2];
	wire [13:0] b_mem_addr_seg  = b_mem_addr [15:2];

	parameter DRAM_SIZE = 32768;

	reg [ 3:0][7:0] RAM [0:DRAM_SIZE-1];  // 64kB of RAM

	initial begin
                $readmemh("DATARAM.hex", RAM);		
	end
	
	always@(posedge clk) begin
		if(a_mem_wmask[0]) RAM[a_mem_addr_seg][0] <= a_mem_wdata[ 7:0 ];
		if(a_mem_wmask[1]) RAM[a_mem_addr_seg][1] <= a_mem_wdata[15:8 ];
		if(a_mem_wmask[2]) RAM[a_mem_addr_seg][2] <= a_mem_wdata[23:16];
		if(a_mem_wmask[3]) RAM[a_mem_addr_seg][3] <= a_mem_wdata[31:24];
        	a_mem_data <= RAM[a_mem_addr_seg];
	end

	always@(posedge clk) begin
		if(b_mem_wmask[0]) RAM[b_mem_addr_seg][0] <= b_mem_wdata[ 7:0 ];
		if(b_mem_wmask[1]) RAM[b_mem_addr_seg][1] <= b_mem_wdata[15:8 ];
		if(b_mem_wmask[2]) RAM[b_mem_addr_seg][2] <= b_mem_wdata[23:16];
		if(b_mem_wmask[3]) RAM[b_mem_addr_seg][3] <= b_mem_wdata[31:24];
        	b_mem_data <= RAM[b_mem_addr_seg];
	end

endmodule 
