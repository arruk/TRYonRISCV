`define DE10S
`ifndef BENCH
	`define SYN
`endif
`define DUALMEM
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

	`ifdef DE10S
	reg [ 3:0][7:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [ 3:0][7:0] ROM [0:RAM_SIZE-1];  // 64kB of RAM
	`else
	reg [31:0] RAM [0:RAM_SIZE-1];  // 64kB of RAM
	reg [31:0] ROM [0:RAM_SIZE-1];  // 64kB of RAM
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
