#pragma once

#include "day.h"

#include <unordered_map>
#include <array>

class Day_14 : public Day
{
private:
	struct expand_pair
	{
		std::string one{ "  " };
		std::string two{ "  " };
	};
	void count_to_depth(const std::string& str, int depth, std::array<int64_t, 26>& counts, const std::unordered_map<std::string, expand_pair>& replacements) const;

public:
	void run_part_1() const override;
	std::string run_part_1(std::fstream& input) const;

	void run_part_2() const override;
	std::string run_part_2(std::fstream& input) const;
};
