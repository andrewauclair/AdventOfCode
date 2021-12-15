#pragma once

#include "../Day.h"

class Day_1 : public Day
{
protected:
	int day() const;

	std::string run_part_1() const override;
	std::string run_part_2() const override;
};
