//`include "../RTL/PLL/femtopll.v"

module Clockworks 
(
   input  CLK,   // clock pin of the board
   input  RESET, // reset pin of the board
   output clk,   // (optionally divided) clock for the design.
                 // divided if SLOW is different from zero.
   output resetn // (optionally timed) negative reset for the design
);               

//   generate
/*`ifdef CPU_FREQ	
        femtoPLL #(
          .freq(`CPU_FREQ)
        ) pll(
           .pclk(CLK),
           .clk(clk)
	);
`else*/
        assign clk=CLK;
//`endif

	reg [15:0] reset_cnt = 0;
	assign resetn = &reset_cnt;

/*`ifdef NEGATIVE_RESET
	 always @(posedge clk,negedge RESET) begin
	    if(!RESET) begin
	       reset_cnt <= 0;
	    end else begin
	       reset_cnt <= reset_cnt + !resetn;
	    end
	 end
`else   */
	 always @(posedge CLK,posedge RESET) begin
	    if(RESET) begin
	       reset_cnt <= 0;
	    end else begin
	       /* verilator lint_off WIDTH */
	       reset_cnt <= reset_cnt + !resetn;
	       /* verilator lint_on WIDTH */	       
	    end
	 end
//`endif   
//   endgenerate

endmodule
