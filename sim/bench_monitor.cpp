#include "bench_monitor.hpp"

#include <filesystem>
#include <fstream>
#include <stdexcept>

BenchMonitor::BenchMonitor(
		std::uint8_t active_pipelines,
		std::uint8_t prediction_mask
) :
	active_pipelines_(active_pipelines),
	prediction_mask_(prediction_mask & active_pipelines)
{
	reset();
}

void BenchMonitor::reset()
{
	branches_.fill(0);
	prediction_hits_.fill(0);
	jals_.fill(0);
	jalrs_.fill(0);
}

void BenchMonitor::sample(
		std::uint8_t branch_mask,
		std::uint8_t prediction_hit_mask,
		std::uint8_t jal_mask,
		std::uint8_t jalr_mask
)
{
	for (std::size_t i = 0; i < PIPELINES; ++i) {
		const std::uint8_t bit = std::uint8_t{1} << i;

		if (!(active_pipelines_ & bit))
			continue;

		const bool branch = branch_mask & bit;

		if (branch)
			++branches_[i];

		if (branch &&
				(prediction_mask_ & bit) &&
				(prediction_hit_mask & bit))
			++prediction_hits_[i];

		if (jal_mask & bit)
			++jals_[i];

		if (jalr_mask & bit)
			++jalrs_[i];
	}
}

void BenchMonitor::write_csv(
		const std::string& path,
		const std::string& core,
		const std::string& benchmark,
		std::uint64_t cycles,
		std::uint64_t instret,
		const std::string& defines
) const
{
	const bool write_header = !std::filesystem::exists(path) || std::filesystem::file_size(path) == 0;	

	std::ofstream output(path, std::ios::app);

	if (write_header) {
		output << "core,benchmark,pipeline,branches,prediction_hits,jals,jalrs,cycles,instret,defines\n";
	}

	if (!output)
		throw std::runtime_error("Não foi possível abrir: " + path);

	for (std::size_t i = 0; i < PIPELINES; ++i) {
		const std::uint8_t bit = std::uint8_t{1} << i;

		if (!(active_pipelines_ & bit))
			continue;

		const char pipeline = i == 0 ? 'A' : 'B';

		output
			<< core << ','
			<< benchmark << ','
			<< pipeline << ','
			<< branches_[i] << ','
			<< prediction_hits_[i] << ','
			<< jals_[i] << ','
			<< jalrs_[i] << ','
			<< cycles << ','
			<< instret << ','
			<< defines << '\n';
	}
}	
