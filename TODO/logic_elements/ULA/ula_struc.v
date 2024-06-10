module ula(in_a, in_b, func7, func3, op, result, take_b);
	parameter n=32;

	input [n-1:0] in_a, in_b; 
	output [n-1:0] result; output take_b;
	
	input [6:0]func7; input [2:0]func3; input [6:0]op;
	wire [31:0] inst = {func7, 10'b0, func3, 5'b0, op};

	m2t1 #(.n(1)) m0 (t_LTU, in_a[31], (in_a[31] ^ in_b[31]), t_LT);

	wire minus         = (inst[6:0] == 7'b0110011) & (inst[30] | (~inst[14] &  inst[13]));
        wire t_inv         = inst[12] ;
        wire d_shifter     = (~inst[14]) & (~inst[13]) & (inst[12]);
        wire d_arith_shift = inst[30] & in_a[31];

	wire [1:0] d_take_b = inst[14:13];
       	wire  [2:0] d_result = inst[14:12];

	wire t_EQ = | r_add_sub;
	wire t_LTU, t_LT;

	wire [n-1:0] r_OR = in_a | in_b;
	wire [n-1:0] r_AND, r_XOR, r_add_sub;

	add_sub s0(in_a, in_b, minus, r_XOR, r_AND, r_add_sub, t_LTU);

	m4t1 #(.n(1)) m1 ((t_inv ^ t_EQ), 1'b0, (t_inv ^ t_LT), (t_inv ^ t_LTU), d_take_b, take_b);

	m8t1 #(.n(32)) m2 (r_add_sub, left_shift, {31'b0, t_LT}, {31'b0, t_LTU}, r_XOR, right_shift, r_OR, r_AND, d_result, result);

	m2t1 #(.n(32)) m3 (in_a, in_a_flipped, d_shifter, in_shifter);

	wire [n-1:0] in_shifter, right_shift, left_shift, in_a_flipped;
	flip32 fl0 (in_a, in_a_flipped);
	//shifter sh0 (in_shifter, in_b[4:0], d_arith_shift, right_shift);
	/* verilator lint_off WIDTH */
	assign right_shift = $signed({d_arith_shift ,in_shifter}) >>> in_b[4:0];
	/* verilator lint_off WIDTH */
	flip32 fl1 (right_shift, left_shift);


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

module shifter(in, amout, arith, out);
	input [31:0] in; input [4:0] amout; input arith;
	output [31:0] out;
	/* verilator lint_off WIDTH */
        assign out = $signed({arith, in}) >>> amout;
	/* verilator lint_on WIDTH */

endmodule

module m2t1(a,b,s,out);
	parameter n=32;
	input [n-1:0] a,b; input s;
	output [n-1:0] out;
	assign out = s ? b : a;
endmodule

module m4t1(a,b,c,d,s,out);
	parameter n=32;

	input [n-1:0] a,b,c,d; input [1:0]s;
	output reg [n-1:0] out;
	
	always@(*) begin
		case(s)
			2'b00: out = a;
			2'b01: out = b;
			2'b10: out = c;
			2'b11: out = d;
		endcase
	end
endmodule

module m8t1(a,b,c,d,e,f,g,h,s,out);
	parameter n=32;

	input [n-1:0] a,b,c,d,e,f,g,h; input [2:0]s;
	output reg [n-1:0] out;

	always@(*) begin
		case(s)
			3'b000: out = a;
			3'b001: out = b;
			3'b010: out = c;
			3'b011: out = d;
			3'b100: out = e;
			3'b101: out = f;
			3'b110: out = g;
			3'b111: out = h;
		endcase
	end
endmodule
