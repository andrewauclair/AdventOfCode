#include "day_14.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <array>
#include <functional>

struct point_day14
{
	int x{};
	int y{};

	auto operator<=>(const point_day14&) const = default;
};

struct day_14_instruction
{
	std::string to_replace{};

	char replacement{};
};

struct day14_data
{
	std::string starting_line{};

	std::vector<day_14_instruction> instructions{};
};

day14_data read_day_14_strings(std::fstream& input)
{
	day14_data data{};

	input >> data.starting_line;

	std::string str{};

	while (getline(input, str))
	{
		if (str.empty()) continue;
		auto loc = str.find("->");

		day_14_instruction instruction{};

		instruction.to_replace = str.substr(0, loc - 1);

		instruction.replacement = str.substr(loc + 3).at(0);

		data.instructions.push_back(instruction);
	}

	return data;
}

void Day_14::run_part_1() const
{
	std::cout << "[Day 14] [Part 1]\n";

	std::fstream example_input{ read_input("day_14_example.txt") };
	std::fstream actual_input{ read_input("day_14_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_14::run_part_1(std::fstream& input) const
{
	const day14_data data{ read_day_14_strings(input) };

	std::string value{ data.starting_line };

	std::map<std::string, std::string> replacements{};

	for (const day_14_instruction& instruction : data.instructions)
	{
		std::string str = "  ";
		str[0] = instruction.to_replace.at(0);
		str[1] = instruction.replacement;
		//str[2] = instruction.to_replace.at(1);
		replacements[instruction.to_replace] = str;
	}

	for (int i = 0; i < 10; i++)
	{
		std::string new_value{};

		for (int i = 0; i < value.size() - 1; i++)
		{
			std::string substr = value.substr(i, 2);

			if (replacements.contains(substr))
			{
				new_value += replacements[substr];

				if (i + 2 >= value.size())
				{
					new_value += substr.at(1);
				}
			}
			else
			{
				new_value += substr;
			}
		}
		value = new_value;
	}

	std::array<int64_t, 26> counts{};

	for (size_t i = 0; i < value.size(); i++)
	{
		counts[(int)value.at(i) - 65]++;
	}

	int64_t lowest = 0x7FFFFFFF;
	int64_t highest = 0;

	for (int i = 0; i < 26; i++)
	{
		if (counts[i] == 0) continue;

		if (counts[i] < lowest)
		{
			lowest = counts[i];
		}
		if (counts[i] > highest)
		{
			highest = counts[i];
		}
	}

	return std::to_string(highest - lowest);
}

void Day_14::run_part_2() const
{
	std::cout << "[Day 14] [Part 2]\n";

	std::fstream example_input{ read_input("day_14_example.txt") };
	std::fstream actual_input{ read_input("day_14_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

void Day_14::count_to_depth(const std::string& str, int depth, std::array<int64_t, 26>& counts, const std::unordered_map<std::string, Day_14::expand_pair>& replacements) const
{
	const expand_pair& pair{ replacements.at(str) };

	for (int i = 0; i < depth; i++)
	{
		counts[pair.one.at(0) - 65]++;
		counts[pair.one.at(1) - 65]++;
		counts[pair.two.at(0) - 65]++;
		counts[pair.two.at(1) - 65]++;

		
	}
	if (depth > 0)
	{
		count_to_depth(pair.one, depth - 1, counts, replacements);
		count_to_depth(pair.two, depth - 1, counts, replacements);
	}

	
}

std::string Day_14::run_part_2(std::fstream& input) const
{
	const day14_data data{ read_day_14_strings(input) };

	std::map<std::string, uint64_t> counts{};

	for (auto& a : data.instructions)
	{
		counts[a.to_replace] = {};
	}

	std::map<std::string, expand_pair> replacements{};

	for (const day_14_instruction& instruction : data.instructions)
	{
		expand_pair& pair = replacements[instruction.to_replace];
		pair.one.at(0) = instruction.to_replace.at(0);
		pair.one.at(1) = instruction.replacement;
		pair.two.at(0) = instruction.replacement;
		pair.two.at(1) = instruction.to_replace.at(1);
	}

	for (int i = 0; i < data.starting_line.size() - 1; i++)
	{
		const std::string substr = data.starting_line.substr(i, 2);

		counts[substr]++;
	}

	for (int i = 0; i < 40; i++)
	{
		std::map<std::string, uint64_t> new_counts{};
		for (const auto& count : counts)
		{
			const expand_pair& pair = replacements.at(count.first);

			new_counts[pair.one] += count.second;
			new_counts[pair.two] += count.second;
		}
		counts = new_counts;
	}

	std::array<uint64_t, 26> letter_counts{};

	for (const auto& count : counts)
	{
		letter_counts[count.first.at(0) - 65] += count.second;
		letter_counts[count.first.at(1) - 65] += count.second;
	}

	uint64_t lowest = 0xFFFFFFFFFFFFFFFF;
	uint64_t highest = 0;

	for (int i = 0; i < 26; i++)
	{
		letter_counts[i] = (uint64_t)round(letter_counts[i] / 2.0);
	}

	for (int i = 0; i < 26; i++)
	{
		if (letter_counts[i] == 0) continue;

		if (letter_counts[i] < lowest)
		{
			lowest = letter_counts[i];
		}
		if (letter_counts[i] > highest)
		{
			highest = letter_counts[i];
		}
	}

	return std::to_string(highest - lowest);
}
