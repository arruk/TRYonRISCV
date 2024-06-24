module femtoPLL (
	input wire pclk,
	output wire clk
);
	
	wire clk_lock;

	rPLL pll(
        	.clkout(clk),     //output clkout
        	.clkin(pclk)      //input clkin
    	);



endmodule


