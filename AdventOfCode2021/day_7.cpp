#include "day_7.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>

std::vector<int> read_positions(std::fstream& input)
{
	std::vector<int> positions{};

	int position{};
	char ch{};

	input >> position;
	positions.push_back(position);

	while (input >> ch >> position)
	{
		positions.push_back(position);
	}
	return positions;
}

void Day_7::run_part_1() const
{
	std::cout << "[Day 7] [Part 1]\n";

	std::fstream example_input{ read_input("day_7_example.txt") };
	std::fstream actual_input{ read_input("day_7_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_7::run_part_1(std::fstream& input) const
{
	std::vector<int> positions{ read_positions(input) };

	std::sort(positions.begin(), positions.end());

	const int middle_position{ positions.at(positions.size() / 2) };

	int total_fuel{};

	for (int position : positions)
	{
		total_fuel += abs(position - middle_position);
	}

	return std::to_string(total_fuel);
}

void Day_7::run_part_2() const
{
	std::cout << "[Day 7] [Part 2]\n";

	std::fstream example_input{ read_input("day_7_example.txt") };
	std::fstream actual_input{ read_input("day_7_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_7::run_part_2(std::fstream& input) const
{
	std::vector<int> positions{ read_positions(input) };

	std::sort(positions.begin(), positions.end());

	int total_positions{};

	for (int position : positions)
	{
		total_positions += position;
	}

	const int middle_position{ (int)(total_positions / (double)positions.size()) };

	double total_fuel{};

	for (int position : positions)
	{
		const double position_change{ (double)abs(position - middle_position) };

		total_fuel += 0.5 * (position_change * position_change) + (0.5 * position_change);
	}

	return std::to_string((int)total_fuel);
}
