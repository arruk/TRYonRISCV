module mem (
        input             clk,

        input             imem_en,
        input      [15:0] imem_addr,
        output reg [31:0] imem_data,

        output reg [31:0] mem_data,
        input      [ 3:0] mem_wmask,
        input      [31:0] mem_addr,
        input      [31:0] mem_wdata
);
	
	parameter ROM_SIZE = 16384;
	parameter RAM_SIZE = 16384;

	reg [31:0]      ROM [0:ROM_SIZE-1];
	reg [ 3:0][7:0] RAM [0:RAM_SIZE-1];

	initial begin
                $readmemh("PROGROM.hex", ROM);
                $readmemh("DATARAM.hex", RAM);		
	end

	always@(posedge clk) begin
		if(mem_wmask[0]) RAM[mem_addr][0] <= mem_wdata[ 7:0 ];
		if(mem_wmask[1]) RAM[mem_addr][1] <= mem_wdata[15:8 ];
		if(mem_wmask[2]) RAM[mem_addr][2] <= mem_wdata[23:16];
		if(mem_wmask[3]) RAM[mem_addr][3] <= mem_wdata[31:24];
        	mem_data <= RAM[mem_addr];
	end

        always@(posedge clk) begin
                if(imem_en)
                        imem_data <= ROM[imem_addr[15:2]];
        end

endmodule 
