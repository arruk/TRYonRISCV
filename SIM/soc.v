//`define TORVS
//`define COPROC
//`define DE10S
//`define PRIMER20K
//`define GOWIN

`ifndef BENCH
	`define SYN
`endif

module SOC( 
	input CLK,
       	input RESET,
    	output [7:0] LEDS, 
	output UART_TX, 
	output UART_CTS
);

        wire resetn, clk;
	
	assign UART_CTS = 1;

	`ifdef TORVS 

        wire        a_imem_en  ;
        wire [31:0] a_imem_addr;
        wire [31:0] a_imem_data;

        wire        b_imem_en  ;
        wire [31:0] b_imem_addr;
        wire [31:0] b_imem_data;

        wire [31:0] a_mem_data ;
        wire [ 3:0] a_mem_wmask;
        wire [31:0] a_mem_addr ;
        wire [31:0] a_mem_wdata;
	wire        a_mem_cen  ;

        wire [31:0] b_mem_data ;
        wire [ 3:0] b_mem_wmask;
        wire [31:0] b_mem_addr ;
        wire [31:0] b_mem_wdata;
	wire        b_mem_cen  ;

	wire a_IO_mem_wr;
        wire [31:0] a_IO_mem_addr;
        wire [31:0] a_IO_mem_wdata;
        wire [13:0] a_IO_wordaddr  = a_IO_mem_addr[15:2];

	wire b_IO_mem_wr;
        wire [31:0] b_IO_mem_addr;
        wire [31:0] b_IO_mem_wdata;
        wire [13:0] b_IO_wordaddr  = b_IO_mem_addr[15:2];
	
	`ifdef FIFO
        wire [31:0] a_IO_mem_rdata = a_IO_wordaddr[2] ? { 22'b0,   fifo_full, 9'b0} : 32'b0;
        wire [31:0] b_IO_mem_rdata = b_IO_wordaddr[2] ? { 22'b0,   fifo_full, 9'b0} : 32'b0;
	`elsif BENCH
        wire [31:0] a_IO_mem_rdata = a_IO_wordaddr[2] ? { 22'b0,        1'b0, 9'b0} : 32'b0;
        wire [31:0] b_IO_mem_rdata = b_IO_wordaddr[2] ? { 22'b0,        1'b0, 9'b0} : 32'b0;
        `else
        wire [31:0] a_IO_mem_rdata = a_IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        wire [31:0] b_IO_mem_rdata = b_IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        `endif

	wire a_uart_valid = a_IO_mem_wr & a_IO_wordaddr[1];
	wire b_uart_valid = b_IO_mem_wr & b_IO_wordaddr[1];
	
	wire uart_valid = a_uart_valid | b_uart_valid;
        wire uart_ready;
        
	wire [31:0] IO_mem_wdata = a_uart_valid ? a_IO_mem_wdata :
				   		  b_IO_mem_wdata ;
	
	wire halt = a_IO_mem_wr & a_IO_wordaddr[3] | b_IO_mem_wr & b_IO_wordaddr[3];
        
	assign LEDS = a_IO_mem_wdata[7:0];
	
	`else

	wire 	    imem_en  ;
        wire [31:0] imem_addr;
	wire [31:0] imem_data;

        wire [31:0] mem_data ;  
        wire [ 3:0] mem_wmask; 
	wire [31:0] mem_addr ;  
        wire [31:0] mem_wdata;

	wire        IO_mem_wr;
        wire [31:0] IO_mem_addr;
        wire [31:0] IO_mem_wdata;
        wire [13:0] IO_wordaddr  = IO_mem_addr[15:2];
	
	`ifdef FIFO 
        wire [31:0] IO_mem_rdata = IO_wordaddr[2] ? { 22'b0,   fifo_full, 9'b0} : 32'b0;
	`elsif BENCH
        wire [31:0] IO_mem_rdata = IO_wordaddr[2] ? { 22'b0,        1'b0, 9'b0} : 32'b0;
	`else
        wire [31:0] IO_mem_rdata = IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
	`endif

        wire uart_ready;
	wire uart_valid = IO_mem_wr & IO_wordaddr[1];
	wire halt = IO_mem_wr & IO_wordaddr[3];

        assign LEDS = IO_mem_wdata[7:0];

	`endif

	`ifdef TORVS

        torv32 CPU (     
     		.clk          (clk),
                .resetn       (resetn),

                .a_imem_en  (a_imem_en  ), //
                .a_imem_addr(a_imem_addr),  //
                .a_imem_data(a_imem_data), // DUAL PORT INSTRUCTION
                .b_imem_en  (b_imem_en  ),  //       MEMORY
                .b_imem_addr(b_imem_addr), //
                .b_imem_data(b_imem_data),  //

		.a_mem_cen  (a_mem_cen  ),  //
                .a_mem_data (a_mem_data ), //
                .a_mem_wmask(a_mem_wmask),  //
                .a_mem_addr (a_mem_addr ), //
                .a_mem_wdata(a_mem_wdata),  //
	       	.b_mem_cen  (b_mem_cen  ), // DUAL PORT DATA
                .b_mem_data (b_mem_data ),  //    MEMORY
                .b_mem_wmask(b_mem_wmask), //
                .b_mem_addr (b_mem_addr ),  //
                .b_mem_wdata(b_mem_wdata), //
		
		.a_IO_mem_addr  (a_IO_mem_addr),
                .a_IO_mem_rdata (a_IO_mem_rdata),
                .a_IO_mem_wdata (a_IO_mem_wdata),
                .a_IO_mem_wr    (a_IO_mem_wr),

		.b_IO_mem_addr  (b_IO_mem_addr),
                .b_IO_mem_rdata (b_IO_mem_rdata),
                .b_IO_mem_wdata (b_IO_mem_wdata),
                .b_IO_mem_wr    (b_IO_mem_wr)
        );

	`else

	
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

	`endif
	
	`ifdef TORVS
	
	mem #(
                .ROM_SIZE(im),
                .RAM_SIZE(dm)
        ) MI (
                .clk        (clk),
		.reset	    (~resetn),

                .a_imem_en  (a_imem_en  ), //
                .a_imem_addr(a_imem_addr),  //
                .a_imem_data(a_imem_data), // DUAL PORT INSTRUCTION
                .b_imem_en  (b_imem_en  ),  //       MEMORY
                .b_imem_addr(b_imem_addr), //
                .b_imem_data(b_imem_data),  //

		.a_mem_cen  (a_mem_cen  ), //
                .a_mem_data (a_mem_data ),  //
                .a_mem_wmask(a_mem_wmask), //
                .a_mem_addr (a_mem_addr ),  //
                .a_mem_wdata(a_mem_wdata), //
	       	.b_mem_cen  (b_mem_cen  ),  // DUAL PORT DATA
                .b_mem_data (b_mem_data ), //    MEMORY
                .b_mem_wmask(b_mem_wmask),  //
                .b_mem_addr (b_mem_addr ), //
                .b_mem_wdata(b_mem_wdata)   //
        );

	`else

	mem #(
		.RAM_SIZE(dm)
	) DATA (
		.clk(clk),
		.imem_en   (imem_en  ),
		.imem_addr (imem_addr),
        	.imem_data (imem_data),
                .mem_data  (mem_data ),
                .mem_wmask (mem_wmask),
		.mem_addr  (mem_addr ),
                .mem_wdata (mem_wdata)
	);

	`endif

	
	`ifdef FIFO
	
	wire [7:0] output_fifo;
	wire fifo_full, fifo_empty;

	fifo_sc_top fifo_tx(
		.Data (IO_mem_wdata[7:0]),
		.Clk  (clk),    
		.WrEn (uart_valid&!fifo_full ),
		.RdEn (uart_ready&!fifo_empty),
		.Reset(!resetn),             
		.Q    (output_fifo),          
		.Empty(fifo_empty),            
		.Full (fifo_full)               
	);

	corescore_emitter_uart #(
		.clk_freq_hz (50000000),
		.baud_rate   (115200)    
	) UART(
		.i_clk     (clk),
		.i_rst     (!resetn),
		.i_data    (output_fifo),
		.i_valid   (!fifo_empty),
		.o_ready   (uart_ready),
		.o_uart_tx (UART_TX)      			       
	);

	`else

	corescore_emitter_uart #(
		.clk_freq_hz (50000000),
		.baud_rate   (115200)    
	) UART(
		.i_clk     (clk),
		.i_rst     (!resetn),
		.i_data    (IO_mem_wdata[7:0]),
		.i_valid   (uart_valid),
		.o_ready   (uart_ready),
		.o_uart_tx (UART_TX)      			       
	);

	`endif

        Clockworks CW(
                .CLK(CLK),
                `ifdef DE10S               
                .RESET(~RESET),
                `else
                .RESET(RESET),
                `endif
                .clk(clk),
                .resetn(resetn)
        );

	localparam dm=16384, im=16384;
	`ifdef BENCH
		always@(posedge clk) begin
			if(uart_valid) begin
				$write("%c", IO_mem_wdata[7:0]);
				$fflush(32'h8000_0001);
			end
		end
        `endif

endmodule

`ifndef SYN

	`include "AUX/clockworks.v"
	`include "AUX/uart_tx.v"

	`include "mem.sv"

	`ifdef TORV1 
		`include "torv1.v"
	`elsif TORV2
		`include "torv2.v"
	`elsif TORV3
		`include "torv3.v"
	`elsif TORV4
		`include "torv4.v"
	`elsif TORV5
		`include "torv5.v"
	`elsif TORVS1
		`include "torvs1.sv"
	`elsif TORVS6P1
		`include "torvs6p1.sv"
	`elsif TORVS9P4
		`include "torvs9p4.sv"
	`elsif TORVS1P4
		`include "torvs1p4.sv"
	`elsif TORVS9P5
		`include "torvs9p5.sv"
	`elsif TORVS9P1
		`include "torvs9p1.sv"
	`elsif TORVS9P2
		`include "torvs9p2.sv"
	`elsif TORVS9P3
		`include "torvs9p3.sv"
	`elsif TORVS1P1
		`include "torvs1p1.sv"
	`elsif TORVS1P2
		`include "torvs1p2.sv"
	`elsif TORVS1P3
		`include "torvs1p3.sv"
	`elsif TORVS1P4
		`include "torvs1p4.sv"
	`elsif TORVS1P5
		`include "torvs1p5.sv"
	`elsif TORVS8P1
		`include "torvs8p1.sv"
	`elsif TORVS8P2
		`include "torvs8p2.sv"
	`elsif TORVS8P3
		`include "torvs8p3.sv"
	`elsif TORVS8P4
		`include "torvs8p4.sv"
	`elsif TORVS8P5
		`include "torvs8p5.sv"
	`elsif TORVS7P1
		`include "torvs7p1.sv"
	`elsif TORVS7P2
		`include "torvs7p2.sv"
	`elsif TORVS7P3
		`include "torvs7p3.sv"
	`elsif TORVS7P4
		`include "torvs7p4.sv"
	`elsif TORVS7P5
		`include "torvs7p5.sv"
	`elsif TORVS6
		`include "torvs6.sv"
	`elsif TORVS6P1
		`include "torvs6p1.sv"
	`elsif TORVS6P2
		`include "torvs6p2.sv"
	`elsif TORVS6P3
		`include "torvs6p3.sv"
	`elsif TORVS6P4
		`include "torvs6p4.sv"
	`elsif TORVS6P5
		`include "torvs6p5.sv"
	`elsif TORVS5P1
		`include "torvs5p1.sv"
	`elsif TORVS5P2
		`include "torvs5p2.sv"
	`elsif TORVS5P3
		`include "torvs5p3.sv"
	`elsif TORVS5P4
		`include "torvs5p4.sv"
	`elsif TORVS5P5
		`include "torvs5p5.sv"
	`endif

`endif

