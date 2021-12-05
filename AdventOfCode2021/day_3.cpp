#include "day_3.h"

#include <fstream>
#include <iostream>
#include <string>

#include <vector>
#include <array>

#include <algorithm>

void Day_3::run_part_1() const
{
	std::cout << "[Day 3] [Part 1]\n";

	std::fstream input{ "day_3.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_3.txt\n";
		return;
	}

	std::vector<int> data{};
	std::string line{};

	while (input >> line)
	{
		data.push_back(std::stoi(line, nullptr, 2));
	}

	int length{ (int)line.size() };

	std::array<int, 5> ones{};
	std::vector<int> ones_counts(length);

	for (int value : data)
	{
		int mask{ 1 };

		for (int i = 0; i < length; i++)
		{
			if (value & mask)
			{
				ones_counts[i]++;
			}
			mask <<= 1;
		}
	}

	int gamma_rate{};
	int epsilon_rate{};

	int mask{ 1 };

	int count{ (int)data.size() };

	for (int i = 0; i < length; i++)
	{
		if (ones_counts[i] > count / 2)
		{
			gamma_rate |= mask;
		}
		else
		{
			epsilon_rate |= mask;
		}
		mask <<= 1;
	}

	std::cout << std::to_string(gamma_rate * epsilon_rate) << "\n\n";
}

void Day_3::run_part_2() const
{
	std::cout << "[Day 3] [Part 2]\n";

	std::fstream input{ "day_3.txt", std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open day_3.txt\n";
		return;
	}

	std::vector<int> data{};
	std::string line{};

	while (input >> line)
	{
		data.push_back(std::stoi(line, nullptr, 2));
	}

	const int bit_count{ (int)line.size() };


	const auto calculate_common_value = [bit_count](const std::vector<int>& values, int tie_break_value) -> int
	{
		std::array<int, 5> ones{};
		std::vector<int> ones_counts(bit_count);

		for (int value : values)
		{
			int mask{ 1 };

			for (int i = 0; i < bit_count; i++)
			{
				if (value & mask)
				{
					ones_counts[i]++;
				}
				mask <<= 1;
			}
		}

		int common_bits{};

		int mask{ 1 };

		int count{ (int)values.size() };

		for (int i = 0; i < bit_count; i++)
		{
			if (ones_counts[i] == count / 2 && count % 2 == 0)
			{
				if (tie_break_value)
				{
					common_bits |= mask;
				}
			}
			else if (ones_counts[i] > count / 2)
			{
				common_bits |= mask;
			}
			mask <<= 1;
		}

		return common_bits;
	};

	std::vector<int> oxygen_rating{ data };
	std::vector<int> CO2_rating{ data };

	for (int i = 0; i < bit_count; i++)
	{
		const int shift{ bit_count - i - 1 };

		const int mask{ 1 << shift };

		if (oxygen_rating.size() > 1)
		{
			const int common_bits{ calculate_common_value(oxygen_rating, 1) };

			const int common{ (common_bits & mask) >> shift };

			oxygen_rating.erase(
				std::remove_if(
					oxygen_rating.begin(),
					oxygen_rating.end(),
					[mask, common, shift](int val)
			{
				const int result{ (val & mask) >> shift };
				return ((val & mask) >> shift) != common; // erase values that don't match common, this has to be the opposite of what we want to keep
			}),
				oxygen_rating.end()
			);
		}

		if (CO2_rating.size() > 1)
		{
			const int common_bits{ calculate_common_value(CO2_rating, 1) };
			
			const int common{ (common_bits & mask) >> shift };
			
			CO2_rating.erase(
				std::remove_if(
					CO2_rating.begin(),
					CO2_rating.end(),
					[mask, common, shift](int val)
			{
				return ((val & mask) >> shift) == common;
			}),
				CO2_rating.end()
			);
		}
	}

	std::cout << std::to_string(oxygen_rating.at(0) * CO2_rating.at(0)) << "\n\n";

	/*int gamma_rate{};
	int epsilon_rate{};

	int mask{ 1 };

	int count{ (int)data.size() };

	for (int i = 0; i < length; i++)
	{
		if (ones_counts[i] > count / 2)
		{
			gamma_rate |= mask;
		}
		else
		{
			epsilon_rate |= mask;
		}
		mask <<= 1;
	}*/
}
