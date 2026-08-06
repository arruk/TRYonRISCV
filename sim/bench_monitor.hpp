#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

class BenchMonitor {
	public:
		static constexpr std::size_t PIPELINES = 2;

		explicit BenchMonitor(
				std::uint8_t active_pipelines = 0b11,
				std::uint8_t prediction_mask = 0b00
		);

		void reset();

		void sample(
				std::uint8_t branch_mask,
				std::uint8_t prediction_hit_mask,
				std::uint8_t jal_mask,
				std::uint8_t jalr_mask
		);

		void write_csv(
				const std::string& path,
				const std::string& core,
				const std::string& benchmark,
				std::uint64_t cycles,
				std::uint64_t instret,
				const std::string& defines
		) const;

	private:
		std::uint8_t active_pipelines_;
		std::uint8_t prediction_mask_;

		std::array<std::uint64_t, PIPELINES> branches_{};
		std::array<std::uint64_t, PIPELINES> prediction_hits_{};
		std::array<std::uint64_t, PIPELINES> jals_{};
		std::array<std::uint64_t, PIPELINES> jalrs_{};
};

