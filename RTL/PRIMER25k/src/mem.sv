`define TORVS
//`define DUALMEM

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
	//wire [15:0] mem_addr_seg  = mem_addr [17:2]; 
	//wire [15:0] imem_addr_seg = imem_addr[17:2];
	
	wire [13:0] mem_addr_seg  = mem_addr [15:2]; 
	wire [13:0] imem_addr_seg = imem_addr[15:2];
	
	parameter RAM_SIZE = 32768;

	//reg [ 3:0][7:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM
	//reg [ 3:0][7:0] ROM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [31:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [31:0] ROM [0:RAM_SIZE-1];  // 64kB of RAM

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
//		if(mem_wmask[0]) RAM[mem_addr_seg][0] <= mem_wdata[ 7:0 ];
//		if(mem_wmask[1]) RAM[mem_addr_seg][1] <= mem_wdata[15:8 ];
//		if(mem_wmask[2]) RAM[mem_addr_seg][2] <= mem_wdata[23:16];
//		if(mem_wmask[3]) RAM[mem_addr_seg][3] <= mem_wdata[31:24];
        if(mem_wmask[0]) RAM[mem_addr_seg][ 7:0 ] <= mem_wdata[ 7:0 ];
        if(mem_wmask[1]) RAM[mem_addr_seg][15:8 ] <= mem_wdata[15:8 ];
        if(mem_wmask[2]) RAM[mem_addr_seg][23:16] <= mem_wdata[23:16];
        if(mem_wmask[3]) RAM[mem_addr_seg][31:24] <= mem_wdata[31:24];
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

        input             a_imem_en,
        input      [31:0] a_imem_addr,
        output     [31:0] a_imem_data,

	input             b_imem_en,
        input      [31:0] b_imem_addr,
        output     [31:0] b_imem_data,

	output     [31:0] a_mem_data,
        input      [ 3:0] a_mem_wmask,
        input      [31:0] a_mem_addr,
        input      [31:0] a_mem_wdata,

	output     [31:0] b_mem_data,
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

	`ifndef SYN
	reg [3:0][7:0] ROM [0:IROM_SIZE-1];  // 64kB of RAM
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
	
	`ifndef SYN
	reg [3:0][7:0] RAM [0:DRAM_SIZE-1];  // 64kB of RAM
	`else
	reg [31:0] RAM [0:DRAM_SIZE-1];  // 64kB of RAM
	`endif

	initial begin
		`ifndef SYN
                $readmemh("HEX/DATARAM.hex", RAM);		
		`else
                $readmemh("DATARAM.hex", RAM);		
		`endif
	end
	
	always@(posedge clk) begin
		`ifndef SYN
		if(a_mem_wmask[0]) RAM[a_mem_addr_seg][0] <= a_mem_wdata[ 7:0 ];
		if(a_mem_wmask[1]) RAM[a_mem_addr_seg][1] <= a_mem_wdata[15:8 ];
		if(a_mem_wmask[2]) RAM[a_mem_addr_seg][2] <= a_mem_wdata[23:16];
		if(a_mem_wmask[3]) RAM[a_mem_addr_seg][3] <= a_mem_wdata[31:24];
		`else
		if(a_mem_wmask[0]) RAM[a_mem_addr_seg][ 7:0 ] <= a_mem_wdata[ 7:0 ];
		if(a_mem_wmask[1]) RAM[a_mem_addr_seg][15:8 ] <= a_mem_wdata[15:8 ];
		if(a_mem_wmask[2]) RAM[a_mem_addr_seg][23:16] <= a_mem_wdata[23:16];
		if(a_mem_wmask[3]) RAM[a_mem_addr_seg][31:24] <= a_mem_wdata[31:24];
		`endif
        	a_mem_data <= RAM[a_mem_addr_seg];
	end

	always@(posedge clk) begin
		`ifndef SYN
		if(b_mem_wmask[0]) RAM[b_mem_addr_seg][0] <= b_mem_wdata[ 7:0 ];
		if(b_mem_wmask[1]) RAM[b_mem_addr_seg][1] <= b_mem_wdata[15:8 ];
		if(b_mem_wmask[2]) RAM[b_mem_addr_seg][2] <= b_mem_wdata[23:16];
		if(b_mem_wmask[3]) RAM[b_mem_addr_seg][3] <= b_mem_wdata[31:24];
		`else
		if(b_mem_wmask[0]) RAM[b_mem_addr_seg][ 7:0 ] <= b_mem_wdata[ 7:0 ];
		if(b_mem_wmask[1]) RAM[b_mem_addr_seg][15:8 ] <= b_mem_wdata[15:8 ];
		if(b_mem_wmask[2]) RAM[b_mem_addr_seg][23:16] <= b_mem_wdata[23:16];
		if(b_mem_wmask[3]) RAM[b_mem_addr_seg][31:24] <= b_mem_wdata[31:24];
		`endif
        	b_mem_data <= RAM[b_mem_addr_seg];
	end

endmodule 

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
