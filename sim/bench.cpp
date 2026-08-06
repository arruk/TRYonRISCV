#include <stdexcept>
#include <string>
#include <iostream>

#include "VSOC.h"
#include "verilated.h"

#include "bench_monitor.hpp"

static std::string getPlusArg(int argc, char** argv, const std::string& name)
{
	const std::string prefix = "+" + name + "=";

	for (int i = 1; i < argc; ++i) {
		const std::string argument = argv[i];

		if (argument.compare(0, prefix.size(), prefix) == 0)
			return argument.substr(prefix.size());
	}

	throw std::runtime_error("Argumento ausente: " + prefix + "<valor>");
}

int main(int argc, char** argv, char** env) {

	Verilated::commandArgs(argc, argv);
	VSOC top;
	
	const auto active     = static_cast<std::uint8_t>(std::stoul(getPlusArg(argc, argv, "ACTIVE_PIPELINES")));
	const auto prediction = static_cast<std::uint8_t>(std::stoul(getPlusArg(argc, argv, "PREDICTION_MASK")));
	BenchMonitor monitor(active, prediction);

	const std::string results   = getPlusArg(argc, argv, "RESULTS");
	const std::string core      = getPlusArg(argc, argv, "CORE");
	const std::string benchmark = getPlusArg(argc, argv, "BENCHMARK");
	const std::string defines   = getPlusArg(argc, argv, "DEFINES");
	const bool        save      = getPlusArg(argc, argv, "SAVE") == "1";	

	top.CLK = 0;

	top.eval();

	while(!Verilated::gotFinish()) {
		top.CLK = 1;

		top.eval();

		monitor.sample(
				top.bench_branch,
				top.bench_hit,
				top.bench_jal,
				top.bench_jalr
		);		

		if (top.bench_halt) {
			if(save) {
				monitor.write_csv(results, core, benchmark, top.bench_cycle, top.bench_instret, defines);
			}
			break;
		}

		top.CLK = 0;

		top.eval();
	}
	return 0;
}
