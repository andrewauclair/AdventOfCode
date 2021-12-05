#include "day_1.h"

#include <fstream>
#include <iostream>
#include <string>

#include <array>

void Day_1::run_part_1() const
{
	std::cout << "[Day 1] [Part 1]\n";

	std::fstream input{ "day_1.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_1.txt\n";
		return;
	}

	int last_depth{};
	int depth{};

	input >> last_depth;

	int depth_increases{};

	while (input >> depth)
	{
		if (depth > last_depth)
		{
			depth_increases++;
		}
		last_depth = depth;
	}

	std::cout << std::to_string(depth_increases) << "\n\n";
}

void Day_1::run_part_2() const
{
	std::cout << "[Day 1] [Part 2]\n";

	std::fstream input{ "day_1.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_1.txt\n";
		return;
	}

	std::array<int, 3> window{};

	input >> window[0];
	input >> window[1];
	input >> window[2];

	int sum{ window[0] + window[1] + window[2] };

	int depth{};

	int depth_increases{};
	
	while (input >> depth)
	{
		int previous_sum{ sum };

		window[0] = window[1];
		window[1] = window[2];
		window[2] = depth;

		sum = window[0] + window[1] + window[2];

		if (sum > previous_sum)
		{
			depth_increases++;
		}
	}

	std::cout << std::to_string(depth_increases) << "\n\n";
}
