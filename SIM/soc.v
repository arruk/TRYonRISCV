`include "clockworks.v"
`include "uart_tx.v"
`include "mem.sv"

module SOC( input CLK, output [5:0] LEDS, output UART_TX);

        assign LEDS = IO_mem_wdata[5:0];

	wire 	    imem_en;
        wire [15:0] imem_addr;
	wire [31:0] imem_data;
        wire [31:0] mem_data;  // data read from memory
        wire [ 3:0] mem_wmask; // mask for write in memory
        wire [31:0] mem_addr;  // address to write/read
        wire [31:0] mem_wdata; // data to write

	parameter BHT = 5;
	parameter ADJ = 0;

        torv32 CPU (     
     		.clk          (clk),
                .resetn       (resetn),
		.imem_en      (imem_en),
                .imem_addr    (imem_addr),
                .imem_data    (imem_data),
                .mem_data     (mem_data),
                .mem_wmask    (mem_wmask),
                .mem_addr     (mem_addr),
                .mem_wdata    (mem_wdata),
                .IO_mem_addr  (IO_mem_addr),
                .IO_mem_rdata (IO_mem_rdata),
                .IO_mem_wdata (IO_mem_wdata),
                .IO_mem_wr    (IO_mem_wr)
        );

	mem #(
		.ROM_SIZE(im),
		.RAM_SIZE(dm)
	) DATA (
		.clk(clk),
		.imem_en   (imem_en),
		.imem_addr (imem_addr),
        	.imem_data (imem_data),
                .mem_data  (mem_data),
                .mem_wmask (mem_wmask),
		.mem_addr  (mem_addr),
                .mem_wdata (mem_wdata)
	);


        wire IO_mem_wr;
        wire [31:0] IO_mem_addr;
        wire [31:0] IO_mem_wdata;
        wire [31:0] IO_mem_rdata = IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        wire [13:0] IO_wordaddr  = IO_mem_addr[15:2];

        wire uart_valid = IO_mem_wr & IO_wordaddr[1];
        wire uart_ready;

	corescore_emitter_uart #(
		.clk_freq_hz (10000000),
		.baud_rate   (1000000)
	) UART(
		.i_clk     (clk),
		.i_rst     (!resetn),
		.i_data    (IO_mem_wdata[7:0]),
		.i_valid   (uart_valid),
		.o_ready   (uart_ready),
		.o_uart_tx (UART_TX)      			       
	);

        wire resetn, clk;
	reg RESET = 0;

        Clockworks CW(
                .CLK(CLK),
                .RESET(RESET),
                .clk(clk),
                .resetn(resetn)
        );

	`ifdef BENCH
                localparam dm=16384, im=16384;

                always@(posedge clk) begin
                        if(uart_valid) begin
                                $write("%c", IO_mem_wdata[7:0]);
                                $fflush(32'h8000_0001);
                        end
                end
        `else
                localparam dm=8192, im=8192;
        `endif

endmodule

/*module mem (
	input 	          clk,

	input         	  imem_en,
        input      [15:0] imem_addr,
        output reg [31:0] imem_data,
	
        output reg [31:0] mem_data,
        input      [ 3:0] mem_wmask,
        input      [31:0] mem_addr,
        input      [31:0] mem_wdata
);

        parameter ROM_SIZE = 16384;
	parameter RAM_SIZE = 16384;

        reg [31:0] ROM [0:ROM_SIZE-1];
	reg [31:0] RAM [0:RAM_SIZE-1];

        initial begin
                $readmemh("PROGROM.hex", ROM);
		$readmemh("DATARAM.hex", RAM);
        end
	always@(posedge clk) begin
		if(imem_en)
			imem_data <= ROM[imem_addr[15:2]];
	end

        always@(posedge clk) begin
		mem_data <= RAM[mem_addr];
                if(mem_wmask[0]) RAM[mem_addr][ 7:0 ] <= mem_wdata[ 7:0 ];
                if(mem_wmask[1]) RAM[mem_addr][15:8 ] <= mem_wdata[15:8 ];
                if(mem_wmask[2]) RAM[mem_addr][23:16] <= mem_wdata[23:16];
                if(mem_wmask[3]) RAM[mem_addr][31:24] <= mem_wdata[31:24];
        end


endmodule*/

`ifdef CORE2 
        `include "core2.v"
`elsif CORE3 
        `include "core3.v"
`elsif CORE4
        `include "core4.v"
`elsif CORE5
        `include "core5.v"
`elsif CORE6
        `include "core6.v"
`elsif CORE7
        `include "core7.v"
`elsif CORE8
        `include "core8.v"
`elsif TORV32
        `include "torv32.v"
`elsif NEWBYPASS
        `include "newbypass.v"
`elsif NEWBYPASS2
        `include "newbypass2.v"
`elsif NEWBYPASS3
        `include "newbypass3.v"
`elsif NEWBYPASS4
        `include "newbypass4.v"
`endif

