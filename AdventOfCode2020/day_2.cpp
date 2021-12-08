#include "day_2.h"

#include <iostream>
#include <fstream>
#include <string>

void Day_2::run_part_1() const
{
	std::cout << "[Day 2] [Part 1]\n";

	std::fstream input{ "day_2.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_2.txt\n";
		return;
	}

	int horizontal_position{};
	int depth_position{};

	std::string command{};
	int units{};

	while (input >> command)
	{
		input >> units;

		if (command.compare("forward") == 0)
		{
			horizontal_position += units;
		}
		else if (command.compare("down") == 0)
		{
			depth_position += units;
		}
		else if (command.compare("up") == 0)
		{
			depth_position -= units;
		}
	}

	std::cout << std::to_string(horizontal_position * depth_position) << "\n\n";
}

void Day_2::run_part_2() const
{
	std::cout << "[Day 2] [Part 2]\n";

	std::fstream input{ "day_2.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_2.txt\n";
		return;
	}

	int horizontal_position{};
	int depth_position{};
	int aim_position{};

	std::string command{};
	int units{};

	while (input >> command)
	{
		input >> units;

		if (command.compare("forward") == 0)
		{
			horizontal_position += units;

			depth_position += aim_position * units;
		}
		else if (command.compare("down") == 0)
		{
			aim_position += units;
		}
		else if (command.compare("up") == 0)
		{
			aim_position -= units;
		}
	}

	std::cout << std::to_string(horizontal_position * depth_position) << "\n\n";
}
