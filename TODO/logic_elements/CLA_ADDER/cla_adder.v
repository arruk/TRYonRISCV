module cla_adder32b(
	input [31:0] a,
	input [31:0] b,
	input cin,
	output [31:0] s,
	output cout
);
	wire [3:0] P, G, c;

	adder8b a0 (a[0+: 8], b[0+: 8], cin , P[0], G[0], s[0+: 8], c[0]);
	adder8b a1 (a[8+: 8], b[8+: 8], c[0], P[1], G[1], s[8+: 8], c[1]);
	adder8b a2 (a[16+:8], b[16+:8], c[1], P[2], G[2], s[16+:8], c[2]);
	adder8b a3 (a[24+:8], b[24+:8], c[2], P[3], G[3], s[24+:8], c[3]);

	assign cout = c[3];
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


