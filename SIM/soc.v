`include "clockworks.v"
`include "uart_tx.v"
`include "torv32.v"

module SOC( input CLK, input RESET, output [5:0] LEDS, output UART_TX);

        parameter sz=5;

        wire resetn, clk;

        wire [31:0] IO_mem_addr, IO_mem_rdata, IO_mem_wdata;
        wire IO_mem_wr;

        `ifdef BENCH
                localparam dm=16384, im=16384;
        `else
                localparam dm=8192, im=8192;
        `endif
        wire [15:0] pc;
	wire [31:0] mem_inst;
        wire [31:0] mem_data;     // data read from memory
        wire [ 3:0] mem_wmask;      // mask for write in memory
        wire [31:0] mem_addr;  // address to write/read
        wire [31:0] mem_wdata; // data to write

        torv32 #(
		.BYPASS(1),
		.BRANCH_PRED(4'd0),
		.BHT_ADDR_BITS(16)
	) CPU (     
     		.clk(clk),
                .resetn(resetn),
                .pc(pc),
                .mem_inst(mem_inst),
                .mem_data(mem_data),
                .mem_wmask(mem_wmask),
                .mem_addr(mem_addr),
                .mem_wdata(mem_wdata),
                .IO_mem_addr(IO_mem_addr),
                .IO_mem_rdata(IO_mem_rdata),
                .IO_mem_wdata(IO_mem_wdata),
                .IO_mem_wr(IO_mem_wr)
        );

	mem #(
		.ROM_SIZE(im),
		.RAM_SIZE(dm)
	) DATA (
		.clk(clk),
		.pc(pc),
        	.mem_inst(mem_inst),
                .mem_data(mem_data),
                .mem_wmask(mem_wmask),
                .mem_addr(mem_addr),
                .mem_wdata(mem_wdata)
	);

        assign LEDS = IO_mem_wdata[5:0];

        wire [13:0] IO_wordaddr = IO_mem_addr[15:2];
        wire uart_valid = IO_mem_wr & IO_wordaddr[1];
        wire uart_ready;

	corescore_emitter_uart #(
		.clk_freq_hz(10000000),
		.baud_rate(1000000)
	) UART(
		.i_clk(clk),
		.i_rst(!resetn),
		.i_data(IO_mem_wdata[7:0]),
		.i_valid(uart_valid),
		.o_ready(uart_ready),
		.o_uart_tx(UART_TX)      			       
	);
        assign IO_mem_rdata = IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;

        `ifdef BENCH
		reg ch;
                always@(posedge clk) begin
                        if(uart_valid) begin
                                $write("%c", IO_mem_wdata[7:0]);
                                $fflush(32'h8000_0001);
                        end
                end
        `endif

        Clockworks CW(
                .CLK(CLK),
                .RESET(RESET),
                .clk(clk),
                .resetn(resetn)
        );

endmodule

module mem (
	input 	          clk,

        input  [15:0] pc,
        output [31:0] mem_inst,
	
        output [31:0] mem_data,     // data read from memory
        input  [ 3:0] mem_wmask,      // mask for write in memory
        input  [31:0] mem_addr,  // address to write/read
        input  [31:0] mem_wdata // data to write
);

        parameter ROM_SIZE = 16384;
	parameter RAM_SIZE = 16384;

        reg [31:0] ROM [0:ROM_SIZE-1];
	reg [31:0] RAM [0:RAM_SIZE-1];

        initial begin
                $readmemh("PROGROM.hex", ROM);
		$readmemh("DATARAM.hex", RAM);
        end
	
	assign mem_inst = ROM[pc[15:2]];

        always@(posedge clk) begin
                if(mem_wmask[0]) RAM[mem_addr][ 7:0 ] <= mem_wdata[ 7:0 ];
                if(mem_wmask[1]) RAM[mem_addr][15:8 ] <= mem_wdata[15:8 ];
                if(mem_wmask[2]) RAM[mem_addr][23:16] <= mem_wdata[23:16];
                if(mem_wmask[3]) RAM[mem_addr][31:24] <= mem_wdata[31:24];
        end

	assign mem_data = RAM[mem_addr];

endmodule

