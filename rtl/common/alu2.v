module alu(
	input [31:0] in_a,
        input [31:0] in_b,
       	input [31:0] inst,
	output reg [31:0] result,
       	output           take_b
);
	
	wire [2:0] func3    = inst[14:12];
	wire [1:0] d_take_b = inst[14:13];
       	wire [2:0] d_result = (inst[6:0] == 7'b1101111 | inst[6:0] == 7'b0010111) ? 3'b000 : inst[14:12];

	wire t_EQ = ~(|r_add_sub);
	wire t_LTU;// = (in_a < in_b);
	wire t_LT = (in_a[31] ^ in_b[31]) ? in_a[31] : t_LTU;

	wire [31:0] r_OR = in_a | in_b;
	wire [31:0] r_AND= in_a & in_b;
        wire [31:0] r_XOR= in_a & in_b;
	wire [31:0] r_add_sub;

	wire minus = ((inst[6:0] == 7'b0110011) & (inst[30] | (~inst[14] &  inst[13]))) | inst[6:0] == 7'b1100011;
	cla_adder32b s0(
		.a(in_a),
	        .b(in_b),
	        .cin(minus),
	        .s(r_add_sub),
	        .cout(t_LTU)
	);
        //wire te_LTU;
        /*add_sub s0(
                .in_a(in_a),
                .in_b(in_b),
                .op(minus),
                .res(r_add_sub),
                .cout(te_LTU)
        );*/


	wire [31:0] a_flipped;
	flip32 fl0 (in_a, a_flipped);

	wire [31:0] in_shifter = (func3 == 3'b001) ? a_flipped : in_a ;

	/* verilator lint_off WIDTH */
	wire [31:0] right_shift = $signed({inst[30] & in_a[31] ,in_shifter}) >>> in_b[4:0];
	/* verilator lint_on WIDTH */

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

module cla_adder32b(
        input [31:0] a,
        input [31:0] b,
        input cin,
        output [31:0] s,
        output cout
);
        wire [3:0] P, G, c;

	wire [31:0] B = b ^ {32{cin}};

	adder8b a0 (a[0+: 8], B[0+: 8], cin , P[0], G[0], s[0+: 8], c[0]);
        adder8b a1 (a[8+: 8], B[8+: 8], c[0], P[1], G[1], s[8+: 8], c[1]);
        adder8b a2 (a[16+:8], B[16+:8], c[1], P[2], G[2], s[16+:8], c[2]);
        adder8b a3 (a[24+:8], B[24+:8], c[2], P[3], G[3], s[24+:8], c[3]);

        assign cout = ~c[3];
endmodule

module adder8b(
        input [7:0] a,
        input [7:0] b,
        input    cin,
        output P,
        output G,
        output [7:0] s,
        output cout
);

        wire [7:0] xor_w = a^b;
        wire [7:0] and_w = a&b;
        wire [7:0] or_w  = a|b;

        /* verilator lint_off UNOPTFLAT */
        wire [7:0] g = {and_w[7:1] | (g[6:0] & or_w[7:1]) , and_w[0]};
        wire [7:0] p = {or_w [7:1] & p[6:0]               , or_w[0] };
        wire [8:0] c = {g[7:0] | (p[7:0] & c[7:0]), cin};
        /* verilator lint_off UNOPTFLAT */

        assign s = xor_w ^ c[7:0];
        assign P = p[7];
        assign G = g[7];
        assign cout = c[8];
endmodule



module flip32(x, out);
	input [31:0] x;
	output [31:0] out;
	assign out = {x[ 0], x[ 1], x[ 2], x[ 3], x[ 4], x[ 5], x[ 6], x[ 7], 
		      x[ 8], x[ 9], x[10], x[11], x[12], x[13], x[14], x[15], 
		      x[16], x[17], x[18], x[19], x[20], x[21], x[22], x[23],
                      x[24], x[25], x[26], x[27], x[28], x[29], x[30], x[31]};
endmodule

module imm_mux(
	input [31:0] instr,
	output [31:0] imm
);
	
	wire Itype = (instr[6:0] == 7'b1100111 | instr[6:0] == 7'b0000011 | instr[6:0] == 7'b0010011);
	wire Stype = (instr[6:0] == 7'b0100011);
	wire Btype = (instr[6:0] == 7'b1100011);
	wire Utype = (instr[6:0] == 7'b0110111 | instr[6:0] == 7'b0010111);
	wire Jtype = (instr[6:0] == 7'b1101111);

	wire imm_0 = Itype ? instr[20] :
		     Stype ? instr[ 7] :
		                  1'b0 ;

	wire [3:0] imm_1 = (Itype | Jtype) ? instr[24:21] : 
	       	           (Stype | Btype) ? instr[11:8 ] :
	     	                                     4'b0 ;

	wire [5:0] imm_2 = (Utype) ? 6'b0 : instr[30:25] ;

	wire imm_3 =  (Itype | Stype) ? instr[31] :
		      (Btype)         ? instr[ 7] :
		      (Jtype)         ? instr[20] :
		      		             1'b0 ;

	wire [7:0] imm_4 = (Utype | Jtype) ? instr[19:12] : {8{instr[31]}} ;

	wire [10:0] imm_5 = (Utype) ? instr[30:20] : {11{instr[31]}};

	assign imm = {instr[31], imm_5, imm_4, imm_3, imm_2, imm_1, imm_0};

endmodule

