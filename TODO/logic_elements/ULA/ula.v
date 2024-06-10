module ula(
	input [31:0] in_a,
        input [31:0] in_b,
       	input 	     func7,
       	input [ 2:0] funct3,
       	input [ 6:0] op,
       	output reg [31:0] result,
       	output            take_b
);
	
	wire [31:0] inst = {1'b0, func7, 15'b0, funct3, 5'b0, op};

	wire [2:0] func3    = inst[14:12];
	wire [1:0] d_take_b = inst[14:13];
       	wire [2:0] d_result = inst[14:12];

	wire t_EQ = ~(|r_add_sub), t_LTU, t_LT;
	assign t_LT = (in_a[31] ^ in_b[31]) ? in_a[31] : t_LTU;

	wire [31:0] r_OR = in_a | in_b;
	wire [31:0] r_AND, r_XOR, r_add_sub;

	wire minus = ((inst[6:0] == 7'b0110011) & (inst[30] | (~inst[14] &  inst[13]))) | inst[6:0] == 7'b1100011;
	add_sub s0(in_a, in_b, minus, r_XOR, r_AND, r_add_sub, t_LTU);

	wire [31:0] a_flipped;
	flip32 fl0 (in_a, a_flipped);

	wire [31:0] in_shifter = (func3 == 3'b001) ? a_flipped : in_a ;

	/* verilator lint_off WIDTH */
	wire [31:0] right_shift = $signed({inst[30] & in_a[31] ,in_shifter}) >>> in_b[4:0];
	/* verilator lint_off WIDTH */

	wire [31:0] left_shift;
	flip32 fl1 (right_shift, left_shift);

	always@(*) begin
		case(d_result)
			3'b000: result = r_add_sub;
			3'b001: result = left_shift;
			3'b010: result = {31'b0, t_LT};
			3'b011: result = {31'b0, t_LTU};
			3'b100: result = r_XOR;
			3'b101: result = right_shift;
			3'b110: result = r_OR;
			3'b111: result = r_AND;
		endcase
	end

	reg i_take_b;
	always@(*) begin
		case(d_take_b)
			2'b00: i_take_b = t_EQ;
			2'b01: i_take_b = func3[0];
			2'b10: i_take_b = t_LT;
			2'b11: i_take_b = t_LTU;
		endcase
	end
	assign take_b = i_take_b ^ func3[0];

endmodule

/* verilator lint_off MULTITOP */
module add_sub(in_a, in_b, op, o_xor, o_and, res, cout);

	parameter n=32;
	
	input [n-1:0] in_a, in_b; input op;
	output [n-1:0] o_xor, o_and, res; output cout;

	/* verilator lint_off UNOPTFLAT */
	wire [n-1:0] in_b_op, cin, cout_in;
	/* verilator lint_on UNOPTFLAT */

	assign cin = {cout_in[n-2:0], op};
	assign in_b_op = in_b ^ {n{op}};

	genvar i;
	generate
		for(i=0; i<n; i=i+1)
			add_sub_u d0 (in_a[i], in_b_op[i], cin[i], o_and[i], o_xor[i], res[i], cout_in[i]);
	endgenerate

	assign cout = ~cout_in[n-1];

endmodule

module add_sub_u(a,b,cin,o_and,o_xor,s,cout);
	input a,b,cin;
	output o_and, o_xor, s, cout;

	assign o_and = a & b;
	assign o_xor = a ^ b;
	assign s = o_xor ^ cin;
	assign cout = o_and | (o_xor & cin);

endmodule

module flip32(x, out);
	input [31:0] x;
	output [31:0] out;
	assign out = {x[ 0], x[ 1], x[ 2], x[ 3], x[ 4], x[ 5], x[ 6], x[ 7], 
		      x[ 8], x[ 9], x[10], x[11], x[12], x[13], x[14], x[15], 
		      x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
                      x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]};
endmodule
