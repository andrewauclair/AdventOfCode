#pragma once

#include "day.h"

class Day_7 : public Day
{
public:
	void run_part_1() const override;
	std::string run_part_1(std::fstream& input) const;

	void run_part_2() const override;
	std::string run_part_2(std::fstream& input) const;
};
