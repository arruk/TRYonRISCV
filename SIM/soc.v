`include "clockworks.v"
`include "uart_tx.v"
`include "pico_mul.v"
`include "pico_div.v"

`define TORVS
`ifdef TORVS
	`include "mem_dual.sv"
`else
	`include "mem.sv"
`endif

module SOC( input CLK, output [5:0] LEDS, output UART_TX);



	`ifdef MULDIV
	`endif


	parameter BHT = 10;
	parameter N   = 8;
	parameter M   = 0;

        torv32 
	/*#(
		.BP_HIST_BITS(9),
		.BHT_ADDR_BITS(BHT)	
	)*/ 
	CPU (     
     		.clk          (clk),
                .resetn       (resetn),

	`ifdef TORVS
                .a_imem_en  (a_imem_en  ), //
                .a_imem_addr(a_imem_addr),  //
                .a_imem_data(a_imem_data), // DUAL PORT INSTRUCTION
                .b_imem_en  (b_imem_en  ),  //       MEMORY
                .b_imem_addr(b_imem_addr), //
                .b_imem_data(b_imem_data),  //

                .a_mem_data (a_mem_data ),  //
                .a_mem_wmask(a_mem_wmask), //
                .a_mem_addr (a_mem_addr ),  //
                .a_mem_wdata(a_mem_wdata), // DUAL PORT DATA
                .b_mem_data (b_mem_data ),  //    MEMORY
                .b_mem_wmask(b_mem_wmask), //
                .b_mem_addr (b_mem_addr ),  //
                .b_mem_wdata(b_mem_wdata),  //
		
		.a_IO_mem_addr  (a_IO_mem_addr),
                .a_IO_mem_rdata (a_IO_mem_rdata),
                .a_IO_mem_wdata (a_IO_mem_wdata),
                .a_IO_mem_wr    (a_IO_mem_wr),

		.b_IO_mem_addr  (b_IO_mem_addr),
                .b_IO_mem_rdata (b_IO_mem_rdata),
                .b_IO_mem_wdata (b_IO_mem_wdata),
                .b_IO_mem_wr    (b_IO_mem_wr)

	
	`else		
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

	
	`endif


	`ifdef MULDIV
		,
                .pcpi_valid(pcpi_valid),
                .pcpi_insn(pcpi_insn),
                .pcpi_rs1(pcpi_rs1),
                .pcpi_rs2(pcpi_rs2),
                .pcpi_wr(pcpi_wr),
                .pcpi_rd(pcpi_rd),
                .pcpi_wait(pcpi_wait),
                .pcpi_ready(pcpi_ready)

	`endif
		
        );

	`ifdef MULDIV

	wire 	    pcpi_valid;
	wire [31:0] pcpi_insn ;
	wire [31:0] pcpi_rs1  ;
	wire [31:0] pcpi_rs2  ;

	wire 	    pcpi_wr   ;
	wire [31:0] pcpi_rd   ;
	wire 	    pcpi_wait ;
	wire 	    pcpi_ready;

	wire 	    pcpi_mul_wr   ;
	wire [31:0] pcpi_mul_rd   ;
	wire 	    pcpi_mul_wait ;
	wire 	    pcpi_mul_ready;

	wire 	    pcpi_div_wr   ;
	wire [31:0] pcpi_div_rd   ;
	wire 	    pcpi_div_wait ;
	wire 	    pcpi_div_ready;

        picorv32_pcpi_fast_mul pcpi_mul (
                .clk       (clk            ),
                .resetn    (resetn         ),
                .pcpi_valid(pcpi_valid     ),
                .pcpi_insn (pcpi_insn      ),
                .pcpi_rs1  (pcpi_rs1       ),
                .pcpi_rs2  (pcpi_rs2       ),
                .pcpi_wr   (pcpi_mul_wr    ),
                .pcpi_rd   (pcpi_mul_rd    ),
                .pcpi_wait (pcpi_mul_wait  ),
                .pcpi_ready(pcpi_mul_ready )
        );

	picorv32_pcpi_div pcpi_div (
		.clk       (clk            ),
		.resetn    (resetn         ),
		.pcpi_valid(pcpi_valid     ),
		.pcpi_insn (pcpi_insn      ),
		.pcpi_rs1  (pcpi_rs1       ),
		.pcpi_rs2  (pcpi_rs2       ),
		.pcpi_wr   (pcpi_div_wr    ),
		.pcpi_rd   (pcpi_div_rd    ),
		.pcpi_wait (pcpi_div_wait  ),
		.pcpi_ready(pcpi_div_ready )
	);

	assign pcpi_rd    = pcpi_insn[14] ? pcpi_div_rd :
					    pcpi_mul_rd ;
	assign pcpi_wr    = pcpi_insn[14] ? pcpi_div_wr :
					    pcpi_mul_wr ;
	assign pcpi_wait  = pcpi_insn[14] ? pcpi_div_wait :
					    pcpi_mul_wait ;
	assign pcpi_ready = pcpi_insn[14] ? pcpi_div_ready :
					    pcpi_mul_ready ;
	`endif


	`ifndef TORVS 

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
        wire [31:0] IO_mem_rdata = IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        wire [13:0] IO_wordaddr  = IO_mem_addr[15:2];

        wire uart_valid = IO_mem_wr & IO_wordaddr[1];
        wire uart_ready;

	wire halt = IO_mem_wr & IO_wordaddr[3];

        assign LEDS = IO_mem_wdata[5:0];
	
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

	`else

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

        wire [31:0] b_mem_data ;
        wire [ 3:0] b_mem_wmask;
        wire [31:0] b_mem_addr ;
        wire [31:0] b_mem_wdata;

	wire a_IO_mem_wr;
        wire [31:0] a_IO_mem_addr;
        wire [31:0] a_IO_mem_wdata;
        wire [31:0] a_IO_mem_rdata = a_IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        wire [13:0] a_IO_wordaddr  = a_IO_mem_addr[15:2];

	wire b_IO_mem_wr;
        wire [31:0] b_IO_mem_addr;
        wire [31:0] b_IO_mem_wdata;
        wire [31:0] b_IO_mem_rdata = b_IO_wordaddr[2] ? { 22'b0, !uart_ready, 9'b0} : 32'b0;
        wire [13:0] b_IO_wordaddr  = b_IO_mem_addr[15:2];

	wire a_uart_valid = a_IO_mem_wr & a_IO_wordaddr[1];
	wire b_uart_valid = b_IO_mem_wr & b_IO_wordaddr[1];
	
	wire uart_valid = a_uart_valid | b_uart_valid;
        wire uart_ready;
        
	wire [31:0] IO_mem_wdata = a_IO_mem_wdata;
	
	wire halt = a_IO_mem_wr & a_IO_wordaddr[3] | b_IO_mem_wr & b_IO_wordaddr[3];
        
	assign LEDS = a_IO_mem_wdata[5:0];
	
	mem #(
                .ROM_SIZE(im),
                .RAM_SIZE(dm)
        ) MI (
                .clk        (clk),

                .a_imem_en  (a_imem_en  ), //
                .a_imem_addr(a_imem_addr),  //
                .a_imem_data(a_imem_data), // DUAL PORT INSTRUCTION
                .b_imem_en  (b_imem_en  ),  //       MEMORY
                .b_imem_addr(b_imem_addr), //
                .b_imem_data(b_imem_data),  //

                .a_mem_data (a_mem_data ),  //
                .a_mem_wmask(a_mem_wmask), //
                .a_mem_addr (a_mem_addr ),  //
                .a_mem_wdata(a_mem_wdata), // DUAL PORT DATA
                .b_mem_data (b_mem_data ),  //    MEMORY
                .b_mem_wmask(b_mem_wmask), //
                .b_mem_addr (b_mem_addr ),  //
                .b_mem_wdata(b_mem_wdata)  //
        );

	`endif


	
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
                `ifdef TORVS
			//localparam dm=32768, im=32768;
			localparam dm=16384, im=16384;
			always@(posedge clk) begin
				if(a_uart_valid & !b_uart_valid) begin
					$write("%c", a_IO_mem_wdata[7:0]);
					$fflush(32'h8000_0001);
				end
				if(!a_uart_valid & b_uart_valid) begin
					$write("%c", b_IO_mem_wdata[7:0]);
					$fflush(32'h8000_0001);
				end
				if(a_uart_valid & b_uart_valid) begin
					$write("%c%c", a_IO_mem_wdata[7:0],b_IO_mem_wdata[7:0]);
					$fflush(32'h8000_0001);
				end

				if(halt) begin
				//	$finish();
				end

				/*if(~IO_mem_wr && (|mem_wmask)) begin
					$write("address: 0x%x\n", mem_addr);
				end*/
			end
		`else	
			localparam dm=65536, im=32768;
			always@(posedge clk) begin
				if(uart_valid) begin
					$write("%c", IO_mem_wdata[7:0]);
					$fflush(32'h8000_0001);
				end

				if(halt) begin
					$finish();
				end

				/*if(~IO_mem_wr && (|mem_wmask)) begin
					$write("address: 0x%x\n", mem_addr);
				end*/
			end

		`endif
        `else
		`ifdef TORVS
                	localparam dm=2*8192, im=2*8192;
		`else	
                	localparam dm=8192, im=8192;
		`endif

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

`ifdef CORE 
	`include "core.sv"
`elsif CORE2 
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

