#include "day_1.h"

#include <fstream>
#include <iostream>
#include <string>

#include <vector>

std::vector<int> read_values(std::fstream& input)
{
	std::vector<int> values{};
	int value{};

	while (input >> value)
	{
		values.push_back(value);
	}
	return values;
}

void Day_1::run_part_1() const
{
	std::cout << "[Day 1] [Part 1]\n";

	std::fstream example_input{ read_input("day_1_example.txt") };
	std::fstream actual_input{ read_input("day_1_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_1::run_part_1(std::fstream& input) const
{
	const std::vector<int> values{ read_values(input) };

	for (int a : values)
	{
		for (int b : values)
		{
			if (a + b == 2020)
			{
				return std::to_string(a * b);
			}
		}
	}
	return "error";
}

void Day_1::run_part_2() const
{
	std::cout << "[Day 1] [Part 2]\n";

	std::fstream example_input{ read_input("day_1_example.txt") };
	std::fstream actual_input{ read_input("day_1_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_1::run_part_2(std::fstream& input) const
{
	const std::vector<int> values{ read_values(input) };

	return "error";
}
