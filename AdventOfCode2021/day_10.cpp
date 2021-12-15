#include "day_10.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>
#include <deque>

std::vector<std::string> read_day_10_strings(std::fstream& input)
{
	std::vector<std::string> strings{};

	std::string str{};

	while (getline(input, str))
	{
		strings.push_back(str);
	}

	return strings;
}

void Day_10::run_part_1() const
{
	std::cout << "[Day 10] [Part 1]\n";

	std::fstream example_input{ read_input("day_10_example.txt") };
	std::fstream actual_input{ read_input("day_10_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_10::run_part_1(std::fstream& input) const
{
	const std::vector<std::string> strings{ read_day_10_strings(input) };

	const auto check_for_corruption = [](const std::string& str) -> char {
		std::deque<char> stack{};

		for (char ch : str)
		{
			if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
			{
				stack.push_back(ch);
			}
			else
			{
				const char back{ stack.back() };
				stack.pop_back();

				if (back == '(' && ch != ')')
				{
					return ch;
				}
				else if (back == '[' && ch != ']')
				{
					return ch;
				}
				else if (back == '{' && ch != '}')
				{
					return ch;
				}
				else if (back == '<' && ch != '>')
				{
					return ch;
				}
			}
		}

		// line is not corrupted
		return ' ';
	};

	const std::map<char, int> points = { {')', 3 }, { ']', 57 }, { '}', 1197 }, { '>', 25137 } };

	int score{};

	for (const std::string& str : strings)
	{
		const char ch{ check_for_corruption(str) };

		if (ch != ' ')
		{
			score += points.at(ch);
		}
	}

	return std::to_string(score);
}

void Day_10::run_part_2() const
{
	std::cout << "[Day 10] [Part 2]\n";

	std::fstream example_input{ read_input("day_10_example.txt") };
	std::fstream actual_input{ read_input("day_10_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_10::run_part_2(std::fstream& input) const
{
	const std::vector<std::string> strings{ read_day_10_strings(input) };

	const std::map<char, int> points = { {')', 1 }, { ']', 2 }, { '}', 3 }, { '>', 4 } };

	const auto check_for_corruption = [&points](const std::string& str) -> int64_t {
		std::deque<char> stack{};

		for (char ch : str)
		{
			if (ch == '(' || ch == '[' || ch == '{' || ch == '<')
			{
				stack.push_back(ch);
			}
			else
			{
				const char back{ stack.back() };
				stack.pop_back();

				if (back == '(' && ch != ')')
				{
					// line is corrupted
					return 0;
				}
				else if (back == '[' && ch != ']')
				{
					// line is corrupted
					return 0;
				}
				else if (back == '{' && ch != '}')
				{
					// line is corrupted
					return 0;
				}
				else if (back == '<' && ch != '>')
				{
					// line is corrupted
					return 0;
				}
			}
		}

		int64_t score{};

		while (stack.size() > 0)
		{
			const char back{ stack.back() };
			stack.pop_back();

			switch (back)
			{
			case '(':
				score *= 5;
				score += points.at(')');
				break;
			case '[':
				score *= 5;
				score += points.at(']');
				break;
			case '{':
				score *= 5;
				score += points.at('}');
				break;
			case '<':
				score *= 5;
				score += points.at('>');
				break;
			}
		}

		return score;
	};

	std::vector<int64_t> scores{};

	for (const std::string& str : strings)
	{
		const int64_t result{ check_for_corruption(str) };

		if (result != 0)
		{
			scores.push_back(result);
		}
	}

	std::sort(scores.begin(), scores.end());

	return std::to_string(scores.at(scores.size() / 2));
}
