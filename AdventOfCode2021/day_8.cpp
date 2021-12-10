#include "day_8.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <array>
#include <algorithm>
#include <sstream>

struct Digit
{
	Digit(std::string raw)
		: raw(raw)
	{
	}

	std::string raw{};
	int value{ -1 };
};

struct Read_Outs
{
	std::vector<Digit> digits{};
	std::vector<Digit> display{};

	std::map<char, char> segment_mapping{};
};

std::vector<Read_Outs> read_data(std::fstream& input)
{
	std::vector<Read_Outs> read_outs{};

	std::string str{};

	while (getline(input, str))
	{
		Read_Outs read_out{};

		std::string digits{ str.substr(0, str.find('|') - 1) };
		std::string displays{ str.substr(str.find('|') + 1) };

		std::stringstream ss_digits{ digits };
		std::stringstream ss_displays{ displays };

		std::string item{};

		while (getline(ss_digits, item, ' '))
		{
			if (!item.empty())
			{
				read_out.digits.push_back(item);
			}
		}

		while (getline(ss_displays, item, ' '))
		{
			if (!item.empty())
			{
				read_out.display.push_back(item);
			}
		}

		read_outs.push_back(read_out);
	}
	return read_outs;
}

void Day_8::run_part_1() const
{
	std::cout << "[Day 8] [Part 1]\n";

	std::fstream example_input{ read_input("day_8_example.txt") };
	std::fstream actual_input{ read_input("day_8_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_8::run_part_1(std::fstream& input) const
{
	const std::vector<Read_Outs> read_outs{ read_data(input) };

	int unique_count{};

	for (const Read_Outs read_out : read_outs)
	{
		for (const Digit& display : read_out.display)
		{
			const size_t digit_size{ display.raw.size() };

			if (digit_size == 2 || digit_size == 3 || digit_size == 4 || digit_size == 7)
			{
				unique_count++;
			}
		}
	}

	return std::to_string(unique_count);
}

void Day_8::run_part_2() const
{
	std::cout << "[Day 8] [Part 2]\n";

	std::fstream example_input{ read_input("day_8_example.txt") };
	std::fstream actual_input{ read_input("day_8_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_8::run_part_2(std::fstream& input) const
{
	std::vector<Read_Outs> read_outs{ read_data(input) };

	int total{};

	for (Read_Outs& read_out : read_outs)
	{
		// 1 4 7 8 can be determined manually
		for (Digit& digit : read_out.digits)
		{
			switch (digit.raw.size())
			{
			case 2:
				digit.value = 1;
				break;
			case 3:
				digit.value = 7;
				break;
			case 4:
				digit.value = 4;
				break;
			case 7:
				digit.value = 8;
				break;
			}
		}

		const auto find_digit = [&](int num) -> Digit& {
			for (Digit& digit : read_out.digits)
			{
				if (digit.value == num)
				{
					return digit;
				}
			}
			throw std::runtime_error("no digit");
		};

		const auto find_char_diff = [](const std::string& search, const std::string& find) -> char {
			for (char ch : search)
			{
				if (find.find(ch) == std::string::npos)
				{
					return ch;
				}
			}
			return ' ';
		};

		const auto count_digits_with_segment = [&](char segment) -> int {
			int count{};

			for (const Digit& digit : read_out.digits)
			{
				if (digit.raw.find(segment) != std::string::npos)
				{
					count++;
				}
			}
			return count;
		};

		const auto string_erase_char = [](std::string& str, char ch) {
			str.erase(str.find(ch), 1);
		};

		// now that we found 1 4 7 8 we can figure out some segments
		Digit& digit_4{ find_digit(4) };
		Digit& digit_7{ find_digit(7) };
		Digit& digit_8{ find_digit(8) };

		// segment "aaaa" (0) can be figured out by finding the segment that is in 7 but not in 4
		const char a_segment{ find_char_diff(digit_7.raw, digit_4.raw) };
		read_out.segment_mapping[a_segment] = 'a';

		std::string digit7_raw{ digit_7.raw };
		string_erase_char(digit7_raw, a_segment);

		// count the number of digits that have the 2nd segment from 7
		const int digit_7_segment_2_count{ count_digits_with_segment(digit7_raw.at(0)) };

		read_out.segment_mapping[digit7_raw.at(0)] = digit_7_segment_2_count == 8 ? 'c' : 'f';
		read_out.segment_mapping[digit7_raw.at(1)] = digit_7_segment_2_count == 8 ? 'f' : 'c';

		std::string digit4_raw{ digit_4.raw };
		string_erase_char(digit4_raw, digit7_raw.at(0));
		string_erase_char(digit4_raw, digit7_raw.at(1));

		const int digit_4_segment_1_count{ count_digits_with_segment(digit4_raw.at(0)) };
		// b = 6, d = 7

		read_out.segment_mapping[digit4_raw.at(0)] = digit_4_segment_1_count == 6 ? 'b' : 'd';
		read_out.segment_mapping[digit4_raw.at(1)] = digit_4_segment_1_count == 6 ? 'd' : 'b';

		std::string digit8_raw{ digit_8.raw };
		string_erase_char(digit8_raw, a_segment);
		string_erase_char(digit8_raw, digit4_raw.at(0));
		string_erase_char(digit8_raw, digit4_raw.at(1));
		string_erase_char(digit8_raw, digit7_raw.at(0));
		string_erase_char(digit8_raw, digit7_raw.at(1));

		// e and g from digit 8
		const int digit_8_segment_4_count{ count_digits_with_segment(digit8_raw.at(0)) };

		read_out.segment_mapping[digit8_raw.at(0)] = digit_8_segment_4_count == 4 ? 'e' : 'g';
		read_out.segment_mapping[digit8_raw.at(1)] = digit_8_segment_4_count == 4 ? 'g' : 'e';

		int multiply{ 1000 };
		int value{};

		// we now have a mapping of all of the digits
		for (Digit& digit : read_out.display)
		{
			std::string corrected{};

			for (char ch : digit.raw)
			{
				corrected += read_out.segment_mapping.at(ch);
			}

			std::sort(corrected.begin(), corrected.end());

			if (corrected.compare("abcefg") == 0)
			{
				digit.value = 0;
			}
			else if (corrected.compare("cf") == 0)
			{
				digit.value = 1;
			}
			else if (corrected.compare("acdeg") == 0)
			{
				digit.value = 2;
			}
			else if (corrected.compare("acdfg") == 0)
			{
				digit.value = 3;
			}
			else if (corrected.compare("bcdf") == 0)
			{
				digit.value = 4;
			}
			else if (corrected.compare("abdfg") == 0)
			{
				digit.value = 5;
			}
			else if (corrected.compare("abdefg") == 0)
			{
				digit.value = 6;
			}
			else if (corrected.compare("acf") == 0)
			{
				digit.value = 7;
			}
			else if (corrected.compare("abcdefg") == 0)
			{
				digit.value = 8;
			}
			else if (corrected.compare("abcdfg") == 0)
			{
				digit.value = 9;
			}
			else
			{
				throw std::runtime_error("unknown");
			}

			value += digit.value * multiply;
			multiply /= 10;
		}
		total += value;
	}

	return std::to_string(total);
}
