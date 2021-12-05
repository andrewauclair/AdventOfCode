#include "day_5.h"

#include <iostream>
#include <fstream>
#include <string>

void Day_5::run_part_1() const
{
	std::cout << "[Day 5] [Part 1]\n";

	std::fstream input{ "day_5.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_5.txt\n";
		return;
	}
}

void Day_5::run_part_2() const
{
	std::cout << "[Day 5] [Part 2]\n";

	std::fstream input{ "day_5.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_5.txt\n";
		return;
	}
}
