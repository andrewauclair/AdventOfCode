#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <map>
#include <list>

#include <cmath>

constexpr int EXECUTION_COUNT{
#ifdef _DEBUG
	1
#else
	50
#endif
};

#pragma region Utils

struct execution_result
{
	std::chrono::nanoseconds time{};
	int execution_count{};

	std::chrono::nanoseconds time_per_execution() const
	{
		return time / execution_count;
	}

	std::string raw_time() const
	{
		return std::to_string(time.count()) + "ns";
	}

	std::string display() const
	{
		const std::chrono::duration<double, std::nano> display_time{ time / (double)execution_count };

		std::ostringstream ss{};

		if (display_time.count() < 1000)
		{
			ss << display_time.count() << "ns";
			return ss.str();
		}

		const auto us{ std::chrono::duration_cast<std::chrono::microseconds>(display_time) };

		if (us.count() < 1000)
		{
			ss << us.count() << "us";
			return ss.str();
		}
		
		const auto ms{ std::chrono::duration_cast<std::chrono::milliseconds>(display_time) };

		if (ms.count() < 1000)
		{
			ss << ms.count() << "ms";
			return ss.str();
		}

		const auto seconds{ std::chrono::duration_cast<std::chrono::seconds>(display_time) };

		if (seconds.count() < 1000)
		{
			ss << seconds.count() << "sc";
			return ss.str();
		}

		const auto minutes{ std::chrono::duration_cast<std::chrono::minutes>(display_time) };

		ss << minutes.count() << "mn";
		return ss.str();
	}
};

struct point_2d
{
	int x{};
	int y{};

	auto operator<=>(const point_2d&) const = default;

	int operator[](int index) const
	{
		if (index == 0)
		{
			return x;
		}
		return y;
	}
};

struct point_3d
{
	int x{};
	int y{};
	int z{};

	auto operator<=>(const point_3d&) const = default;

	int operator[](int index) const
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		}
		return z;
	}
};

inline std::fstream read_input_from_file(const std::string& file)
{
	std::fstream input{ file, std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open " << file << '\n';
		throw std::runtime_error("failed to read file: " + file);
	}

	return input;
}

inline void verify_answer(auto answer, auto expected)
{
	if (answer != expected)
	{
		throw std::runtime_error("solution has failed!");
	}
}

#pragma endregion Utils

#pragma region Advent of Code - 2015

#pragma region Day 1

std::string day_1_2015__read_input()
{
	std::fstream input{ read_input_from_file("../input/2015/day_1.txt") };

	std::string data{};
	input >> data;

	return data;
}

void day_1_2015__execute__part1(const std::string& data)
{
	int floor{};

	for (size_t i = 0; i < data.size(); i++)
	{
		const char ch{ data.at(i) };

		if (ch == '(')
		{
			floor++;
		}
		else if (ch == ')')
		{
			floor--;
		}
	}

	verify_answer(floor, 280);
}

void day_1_2015__execute__part2(const std::string& data)
{
	int floor{};

	for (size_t i = 0; i < data.size(); i++)
	{
		const char ch{ data.at(i) };

		if (ch == '(')
		{
			floor++;
		}
		else if (ch == ')')
		{
			floor--;
		}

		if (floor == -1)
		{
			verify_answer(i + 1, 1797);
			break;
		}
	}
}

execution_result day_1_2015__time()
{
	std::string input{ day_1_2015__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_1_2015__execute__part1(input);
		day_1_2015__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start), EXECUTION_COUNT };
}

#pragma endregion Day 1

#pragma region Day 2

struct day_2_2015_data
{
	int length{};
	int width{};
	int height{};
};

std::vector<day_2_2015_data> day_2_2015__read_input()
{
	std::fstream input{ read_input_from_file("../input/2015/day_2.txt") };

	std::vector<day_2_2015_data> data{};

	std::string line{};

	while (getline(input, line))
	{
		size_t pos{ line.find('x') };

		day_2_2015_data value{};

		value.length = atoi(line.substr(0, pos).c_str());
		line = line.substr(pos + 1);
		pos = line.find('x');

		value.width = atoi(line.substr(0, pos).c_str());
		line = line.substr(pos + 1);
		pos = line.find('x');

		value.height = atoi(line.substr(0, pos).c_str());

		data.push_back(value);
	}

	return data;
}

void day_2_2015__execute__part1(const std::vector<day_2_2015_data>& data)
{
	int total_paper{};

	for (const day_2_2015_data& value : data)
	{
		const int side_1{ value.length * value.width };
		const int side_2{ value.width * value.height };
		const int side_3{ value.height * value.length };

		int smallest{ side_1 };

		if (side_2 < smallest)
		{
			smallest = side_2;
		}

		if (side_3 < smallest)
		{
			smallest = side_3;
		}

		total_paper += smallest + ((2 * side_1) + (2 * side_2) + (2 * side_3));
	}
	
	verify_answer(total_paper, 1606483);
}

void day_2_2015__execute__part2(const std::vector<day_2_2015_data>& data)
{
	int total_ribbon_feet{};

	for (const day_2_2015_data& value : data)
	{
		const int side_1{ value.length * value.width };
		const int side_2{ value.width * value.height };
		const int side_3{ value.height * value.length };

		int smallest{ side_1 };
		int side_num{ 1 };

		if (side_2 < smallest)
		{
			smallest = side_2;
			side_num = 2;
		}

		if (side_3 < smallest)
		{
			smallest = side_3;
			side_num = 3;
		}

		switch (side_num)
		{
		case 1:
			total_ribbon_feet += value.length + value.length + value.width + value.width;
			break;
		case 2:
			total_ribbon_feet += value.width + value.width + value.height + value.height;
			break;
		case 3:
			total_ribbon_feet += value.height + value.height + value.length + value.length;
		}

		total_ribbon_feet += value.length * value.width * value.height;
	}

	verify_answer(total_ribbon_feet, 3842356);
}

execution_result day_2_2015__time()
{
	unsigned volatile int keep_this_function = 0;

	std::vector<day_2_2015_data> input{ day_2_2015__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_2_2015__execute__part1(input);
		day_2_2015__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 2

#pragma endregion Advent of Code - 2015

#pragma region Advent of Code - 2016
#pragma endregion Advent of Code - 2016

#pragma region Advent of Code - 2017
#pragma endregion Advent of Code - 2017

#pragma region Advent of Code - 2018
#pragma endregion Advent of Code - 2018

#pragma region Advent of Code - 2019
#pragma endregion Advent of Code - 2019

#pragma region Advent of Code - 2020
#pragma endregion Advent of Code - 2020

#pragma region Advent of Code - 2021

#pragma region Day 1

std::vector<int> day_1_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_1.txt") };

	std::vector<int> data{};

	int depth{};

	while (input >> depth)
	{
		data.push_back(depth);
	}

	return data;
}

void day_1_2021__execute__part1(const std::vector<int>& data)
{
	int depth_increases{};

	int last_depth{ data.at(0) };

	for (size_t i = 1; i < data.size(); i++)
	{
		const int depth{ data.at(i) };

		if (depth > last_depth)
		{
			depth_increases++;
		}
		last_depth = depth;
	}

	verify_answer(depth_increases, 1195);
}

void day_1_2021__execute__part2(const std::vector<int>& data)
{
	std::array<int, 3> window{};

	window.at(0) = data.at(0);
	window.at(1) = data.at(1);
	window.at(2) = data.at(2);

	int sum{ window.at(0) + window.at(1) + window.at(2) };

	int depth_increases{};

	for (size_t i = 3; i < data.size(); i++)
	{
		const int previous_sum{ sum };

		window.at(0) = window.at(1);
		window.at(1) = window.at(2);
		window.at(2) = data.at(i);

		sum = window.at(0) + window.at(1) + window.at(2);

		if (sum > previous_sum)
		{
			depth_increases++;
		}
	}

	verify_answer(depth_increases, 1235);
}

execution_result day_1_2021__time()
{
	std::vector<int> input{ day_1_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_1_2021__execute__part1(input);
		day_1_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 1

#pragma region Day 2

enum class day_2_2021__command_type
{
	forward,
	down,
	up
};

struct day_2_2021__command
{
	day_2_2021__command_type type{};
	int units{};
};

std::vector<day_2_2021__command> day_2_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_2.txt") };

	std::vector<day_2_2021__command> data{};

	std::string command{};
	int units{};

	while (input >> command)
	{
		input >> units;

		if (command.compare("forward") == 0)
		{
			data.emplace_back(day_2_2021__command_type::forward, units);
		}
		else if (command.compare("down") == 0)
		{
			data.emplace_back(day_2_2021__command_type::down, units);
		}
		else if (command.compare("up") == 0)
		{
			data.emplace_back(day_2_2021__command_type::up, units);
		}
	}

	return data;
}

void day_2_2021__execute__part1(const std::vector<day_2_2021__command>& data)
{
	int horizontal_position{};
	int depth_position{};

	for (const day_2_2021__command& command : data)
	{
		switch (command.type)
		{
		case day_2_2021__command_type::forward:
			horizontal_position += command.units;
			break;
		case day_2_2021__command_type::down:
			depth_position += command.units;
			break;
		case day_2_2021__command_type::up:
			depth_position -= command.units;
			break;
		}
	}

	const int result{ horizontal_position * depth_position };
	verify_answer(result, 1746616);
}

void day_2_2021__execute__part2(const std::vector<day_2_2021__command>& data)
{
	int horizontal_position{};
	int depth_position{};
	int aim_position{};

	for (const day_2_2021__command& command : data)
	{
		switch (command.type)
		{
		case day_2_2021__command_type::forward:
			horizontal_position += command.units;

			depth_position += aim_position * command.units;
			break;
		case day_2_2021__command_type::down:
			aim_position += command.units;
			break;
		case day_2_2021__command_type::up:
			aim_position -= command.units;
			break;
		}
	}

	verify_answer(horizontal_position * depth_position, 1741971043);
}

execution_result day_2_2021__time()
{
	std::vector<day_2_2021__command> input{ day_2_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_2_2021__execute__part1(input);
		day_2_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 2

#pragma region Day 3

struct day_3_2021__data
{
	std::vector<int> numbers{};
	int length{};
};

day_3_2021__data day_3_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_3.txt") };

	day_3_2021__data data{};

	std::string line{};

	while (input >> line)
	{
		data.numbers.push_back(std::stoi(line, nullptr, 2));
	}
	data.length = (int)line.size();

	return data;
}

void day_3_2021__execute__part1(const day_3_2021__data& data)
{
	int length{ data.length };

	std::array<int, 5> ones{};
	std::vector<int> ones_counts(length);

	for (int value : data.numbers)
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

	int count{ (int)data.numbers.size() };

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

	verify_answer(gamma_rate * epsilon_rate, 1071734);
}

void day_3_2021__execute__part2(const day_3_2021__data& data)
{
	const int bit_count{ data.length };


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

	std::vector<int> oxygen_rating{ data.numbers };
	std::vector<int> CO2_rating{ data.numbers };

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

	verify_answer(oxygen_rating.at(0) * CO2_rating.at(0), 6124992);
}

execution_result day_3_2021__time()
{
	day_3_2021__data input{ day_3_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_3_2021__execute__part1(input);
		day_3_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 3

#pragma region Day 4

constexpr int BOARD_SIZE = 5;

struct day_4_2021__bingo_board
{
	std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> numbers{};
	std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> marked{};

	int win_order{};

	void mark(int number)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (numbers[i][j] == number)
				{
					marked[i][j] = true;
				}
			}
		}
	}

	bool has_won() const
	{
		// check rows
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			bool won{ true };

			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[i][j])
				{
					won = false;
					break;
				}
			}
			if (won)
			{
				return true;
			}
		}
		// check columns
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			bool won{ true };

			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[j][i])
				{
					won = false;
					break;
				}
			}
			if (won)
			{
				return true;
			}
		}
		return false;
	}

	int sum_unmarked() const
	{
		int sum{};

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[i][j])
				{
					sum += numbers[i][j];
				}
			}
		}
		return sum;
	}
};

struct day_4_2021__file_results
{
	std::vector<int> numbers_to_draw{};

	std::vector<day_4_2021__bingo_board> boards{};

	size_t next_number_index{};

	void draw()
	{
		const int number_drawn{ numbers_to_draw[next_number_index++] };

		for (day_4_2021__bingo_board& board : boards)
		{
			bool won{ board.has_won() };
			board.mark(number_drawn);

			if (!won && board.has_won())
			{
				board.win_order = boards_remaining();
			}
		}
	}

	bool has_a_winner() const
	{
		for (const day_4_2021__bingo_board& board : boards)
		{
			if (board.has_won())
			{
				return true;
			}
		}
		return false;
	}

	int boards_remaining() const
	{
		int count{ (int)boards.size() };

		for (const day_4_2021__bingo_board& board : boards)
		{
			if (board.has_won())
			{
				count--;
			}
		}
		return count;
	}

	int final_score() const
	{
		const int number_drawn{ numbers_to_draw.at(next_number_index - 1) };

		for (const day_4_2021__bingo_board& board : boards)
		{
			if (board.has_won())
			{
				return board.sum_unmarked() * number_drawn;
			}
		}
		return 0;
	}

	int final_score_last_board()
	{
		const int number_drawn{ numbers_to_draw.at(next_number_index - 1) };

		for (const day_4_2021__bingo_board& board : boards)
		{
			if (board.win_order == 0)
			{
				return board.sum_unmarked() * number_drawn;
			}
		}
		return 0;
	}
};

day_4_2021__file_results day_4_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_4.txt") };

	day_4_2021__file_results results{};

	std::string numbers{};
	input >> numbers;

	std::stringstream ss{ numbers };
	for (int i{}; ss >> i;)
	{
		results.numbers_to_draw.push_back(i);
		if (ss.peek() == ',')
		{
			ss.ignore();
		}
	}

	while (!input.eof())
	{
		day_4_2021__bingo_board board{};

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				input >> board.numbers[i][j];
			}
		}

		results.boards.push_back(board);
	}

	return results;
}

void day_4_2021__execute__part1(const day_4_2021__file_results& data)
{
	day_4_2021__file_results results{ data };
	
	while (!results.has_a_winner())
	{
		results.draw();
	}

	verify_answer(results.final_score(), 33462);
}

void day_4_2021__execute__part2(const day_4_2021__file_results& data)
{
	day_4_2021__file_results results{ data };

	while (results.boards_remaining() > 0)
	{
		results.draw();
	}

	verify_answer(results.final_score_last_board(), 30070);
}

execution_result day_4_2021__time()
{
	day_4_2021__file_results input{ day_4_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_4_2021__execute__part1(input);
		day_4_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 4

#pragma region Day 5

namespace _2021_5
{
	struct line
	{
		point_2d start{};
		point_2d end{};

		bool is_straight_line() const
		{
			//return false;
			return (start.x == end.x) || (start.y == end.y);
		}

		bool on_line(const point_2d& a, const point_2d& b, const point_2d& c) const {
			const float slope = (b.y - a.y) / (float)(b.x - a.x);

			const bool on_infinite_line = (c.y - a.y) == (int)(slope * (c.x - a.x));

			if (on_infinite_line)
			{
				const bool within_x_range = (a.x <= c.x && c.x <= b.x) || (a.x >= c.x && c.x >= b.x);
				const bool within_y_range = (a.y <= c.y && c.y <= b.y) || (a.y >= c.y && c.y >= b.y);

				return within_x_range && within_y_range;
			}
			return false;
		}

		bool intersects_point(const point_2d& point) const
		{
			if (is_straight_line())
			{
				if (start.x == point.x)
				{
					return (start.y <= point.y && point.y <= end.y) ||
						(start.y >= point.y && point.y >= end.y);
				}
				if (start.y == point.y)
				{
					return (start.x <= point.x && point.x <= end.x) ||
						(start.x >= point.x && point.x >= end.x);
				}
			}
			return on_line(start, end, point);
		}

		void plot(std::map<point_2d, int>& grid)
		{
			const int rise{ end.y - start.y };
			const int run{ end.x - start.x };
			const point_2d offset{ run == 0 ? 0 : run < 0 ? -1 : 1, rise == 0 ? 0 : rise < 0 ? -1 : 1 };

			point_2d point{ start };

			while (point != end)
			{
				grid[point]++;

				point.x += offset.x;
				point.y += offset.y;
			}
			grid[end]++;
		}
	};

	std::vector<line> read_input()
	{
		std::fstream input{ ::read_input_from_file("../input/2021/day_5.txt") };
		
		std::vector<line> lines{};

		std::string str{};

		while (getline(input, str))
		{
			line line{};

			sscanf_s(str.c_str(), "%d,%d -> %d,%d", &line.start.x, &line.start.y, &line.end.x, &line.end.y);

			lines.push_back(line);
		}

		return lines;
	}

	void execute_part1(const std::vector<line>& data)
	{
		int largest_x{};
		int largest_y{};

		for (auto line : data)
		{
			if (line.start.x > largest_x)
			{
				largest_x = line.start.x;
			}

			if (line.start.y > largest_y)
			{
				largest_y = line.start.y;
			}

			if (line.end.x > largest_x)
			{
				largest_x = line.end.x;
			}

			if (line.end.y > largest_y)
			{
				largest_y = line.end.y;
			}
		}

		std::vector<line> lines{ data };

		std::map<point_2d, int> grid{};

		for (line& line : lines)
		{
			if (line.is_straight_line())
			{
				line.plot(grid);
			}
		}

		int points_with_multiple_lines{};

		for (auto& point : grid)
		{
			if (point.second > 1)
			{
				points_with_multiple_lines++;
			}
		}
		//for (int y = 0; y <= largest_y; y++)
		//{
		//	for (int x = 0; x <= largest_x; x++)
		//	{
		//		if (grid.contains({ x,y }) && grid.at({ x,y }) > 1)
		//		{
		//			points_with_multiple_lines++;
		//		}
		//		/*point_2d point{ x, y };

		//		int line_count{};

		//		for (const line& line : data)
		//		{
		//			if (line.is_straight_line() && line.intersects_point(point))
		//			{
		//				line_count++;
		//			}
		//		}

		//		if (line_count > 1)
		//		{
		//			points_with_multiple_lines++;
		//		}*/
		//	}
		//}

		verify_answer(points_with_multiple_lines, 5442);
	}

	void execute_part2(const std::vector<line>& data)
	{
		int largest_x{};
		int largest_y{};

		for (auto line : data)
		{
			if (line.start.x > largest_x)
			{
				largest_x = line.start.x;
			}

			if (line.start.y > largest_y)
			{
				largest_y = line.start.y;
			}

			if (line.end.x > largest_x)
			{
				largest_x = line.end.x;
			}

			if (line.end.y > largest_y)
			{
				largest_y = line.end.y;
			}
		}

		std::vector<line> lines{ data };

		std::map<point_2d, int> grid{};

		for (line& line : lines)
		{
			line.plot(grid);
		}

		int points_with_multiple_lines{};

		for (auto& point : grid)
		{
			if (point.second > 1)
			{
				points_with_multiple_lines++;
			}
		}

		verify_answer(points_with_multiple_lines, 19571);
	}

	execution_result time()
	{
		auto input{ read_input() };

		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 1; i++)
		{
			execute_part1(input);
			execute_part2(input);
		}

		auto stop = std::chrono::high_resolution_clock::now();

		return { stop - start, 1 };
	}
}

#pragma endregion Day 5

#pragma region Day 18

namespace _2021_17
{
	struct input_data
	{
		int target_x_min{};
		int target_x_max{};
		int target_y_min{};
		int target_y_max{};
	};

	int calculate_x_velocity(int x_pos, bool less_than)
	{
		int x_vel{};

		int starting_vel{ 1 };

		while (x_vel < x_pos)
		{
			x_vel += starting_vel++;
		}

		starting_vel--;

		if (less_than)
		{
			starting_vel--;
		}

		return starting_vel;
	}

	bool does_y_vel_hit_target(int x_vel, int y_vel, int target_y_min, int target_y_max)
	{
		int x_pos{};
		int y_pos{};
		int max_height{};

		while (y_pos > target_y_min)
		{
			x_pos += x_vel;
			y_pos += y_vel;

			if (y_pos > max_height) max_height = y_pos;

			if (y_pos >= target_y_min && y_pos <= target_y_max) return true;

			if (x_vel > 0) x_vel--;

			y_vel--;
		}

		return false;
	}

	bool does_vel_hit_target(int x_vel, int y_vel, int target_x_min, int target_x_max, int target_y_min, int target_y_max)
	{
		int x_pos{};
		int y_pos{};

		while (x_vel != 0 || (x_pos >= target_x_min && x_pos <= target_x_max))
		{
			x_pos += x_vel;
			y_pos += y_vel;

			if (x_pos >= target_x_min && x_pos <= target_x_max &&
				y_pos >= target_y_min && y_pos <= target_y_max)
			{
				return true;
			}
			else if (x_vel == 0 && y_pos < target_y_min) return false;

			if (x_vel > 0) x_vel--;

			y_vel--;
		}
		return false;
	}

	int calculate_max_height(int x_vel, int y_vel, int target_y_min, int target_y_max)
	{
		int x_pos{};
		int y_pos{};
		int max_height{};

		while (y_pos > target_y_min)
		{
			x_pos += x_vel;
			y_pos += y_vel;

			if (y_pos > max_height) max_height = y_pos;

			if (y_pos >= target_y_min && y_pos <= target_y_max) return max_height;

			if (x_vel > 0) x_vel--;

			y_vel--;
		}

		return max_height;
	}

	int calculate_y_velocity(int x_vel, int target_y_min, int target_y_max)
	{
		int y_vel = x_vel;
		int consecutive_misses{};

		int max_match{};

		while (true)
		{
			const bool match = does_y_vel_hit_target(x_vel, y_vel, target_y_min, target_y_max);

			if (!match)
			{
				consecutive_misses++;

				if (consecutive_misses > abs(target_y_max - target_y_min) * 2) break;
			}

			if (match)
			{
				max_match = y_vel;
			}

			y_vel++;
		}

		return max_match;
	}

	int count_initial_velocities(int target_x_min, int target_x_max, int target_y_min, int target_y_max)
	{
		int count{};

		for (int x_vel = 0; x_vel < target_x_max + 1; x_vel++)
		{
			for (int y_vel = target_y_min; y_vel < abs(target_y_min) + 1; y_vel++)
			{
				if (does_vel_hit_target(x_vel, y_vel, target_x_min, target_x_max, target_y_min, target_y_max))
				{
					count++;
				}
			}
		}

		return count;
	}
}

_2021_17::input_data day_17_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_17.txt") };

	std::string line{};
	getline(input, line);

	_2021_17::input_data data{};

	sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &data.target_x_min, &data.target_x_max, &data.target_y_min, &data.target_y_max);

	return data;
}

void day_17_2021__execute__part1(const _2021_17::input_data& data)
{
	int start_vel_min{ _2021_17::calculate_x_velocity(data.target_x_min, false) };
	int start_vel_max{ _2021_17::calculate_x_velocity(data.target_x_max, true) };

	int y_vel_x_min{ _2021_17::calculate_y_velocity(start_vel_min, data.target_y_min, data.target_y_max) };
	int y_vel_x_max{ _2021_17::calculate_y_velocity(start_vel_max, data.target_y_min, data.target_y_max) };

	int y_max_min{ _2021_17::calculate_max_height(start_vel_min, y_vel_x_min, data.target_y_min, data.target_y_max) };
	int y_max_max{ _2021_17::calculate_max_height(start_vel_max, y_vel_x_max, data.target_y_min, data.target_y_max) };

	const int answer{ y_max_min > y_max_max ? y_max_min : y_max_max };

	verify_answer(answer, 19503);
}

void day_17_2021__execute__part2(const _2021_17::input_data& data)
{
	int answer{ _2021_17::count_initial_velocities(data.target_x_min, data.target_x_max, data.target_y_min, data.target_y_max) };

	verify_answer(answer, 5200);
}

execution_result day_17_2021__time()
{
	_2021_17::input_data input{ day_17_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_17_2021__execute__part1(input);
		day_17_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { stop - start, EXECUTION_COUNT };
}

#pragma endregion Day 18

#pragma region Day 19

struct day_19_2021__beacon_distances
{
	point_3d beacon{};
	std::vector<int> distances{};
	std::vector<int> scanners_seen_by{};
};

struct day_19_2021__scanner
{
	std::set<point_3d> beacons{};
};

struct day_19_2021__scanner_processed_data
{
	day_19_2021__scanner scanner{};
	std::vector<day_19_2021__beacon_distances> beacon_distances{};
};

constexpr int DAY_19_2021__THRESHOLD = 12;


std::vector<day_19_2021__scanner> day_19_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_19.txt") };

	std::vector<day_19_2021__scanner> data{};

	std::string line{};
	day_19_2021__scanner scanner{};

	getline(input, line); // skip first scanner line

	while (getline(input, line))
	{
		if (line.empty()) continue;

		if (strcmp(line.substr(0, 3).c_str(), "---") == 0)
		{
			data.push_back(scanner);

			// new scanner
			scanner = {};
		}
		else
		{
			point_3d beacon{};

			size_t pos{ line.find(',') };

			beacon.x = atoi(line.substr(0, pos).c_str());
			line = line.substr(pos + 1);
			pos = line.find(',');

			beacon.y = atoi(line.substr(0, pos).c_str());
			line = line.substr(pos + 1);
			pos = line.find(',');

			beacon.z = atoi(line.substr(0, pos).c_str());

			scanner.beacons.insert(beacon);
		}
	}

	data.push_back(scanner); // add the last scanner

	return data;
}

//int day_19_2021__distances_in_common(const day_19_2021__beacon_distances& one, const day_19_2021__beacon_distances& two)
//{
//	int count{};
//
//	for (auto i : one.distances)
//	{
//		if (std::find(two.distances.begin(), two.distances.end(), i) != two.distances.end())
//		{
//			count++;
//		}
//	}
//	return count;
//}
//
//int day_19_2021__rotation_needed(const day_19_2021__scanner_processed_data& scanner0, const day_19_2021__scanner_processed_data& two)
//{
//	int count{};
//
//	point_3d common_one[2];
//	point_3d common_two[2];
//	int num{};
//
//	for (const auto& a : scanner0.beacon_distances)
//	{
//		for (const auto& b : two.beacon_distances)
//		{
//			if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//			{
//				count++;
//
//				common_one[num] = a.beacon;
//				common_two[num] = b.beacon;
//				num++;
//
//				if (num > 1)
//				{
//					break;
//				}
//			}
//		}
//	}
//
//	if (count < 2)
//	{
//		return -1; // not overlapping
//	}
//
//
//
//	std::cout << "points in common: " << count << '\n';
//	return count;
//}

//void day_19_2021__mark_common_beacons(int src_index, day_19_2021__scanner_processed_data& one, day_19_2021__scanner_processed_data& two)
//{
//
//	for (auto& a : one.beacon_distances)
//	{
//		for (auto& b : two.beacon_distances)
//		{
//			if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//			{
//				b.scanners_seen_by.push_back(src_index);
//			}
//		}
//	}
//}

//int day_19_2021__count_points(std::vector<day_19_2021__scanner_processed_data>& data)
//{
//	int total_beacons{};
//
//	//for (day_19_2021__scanner_processed_data& scanner1 : data)
//	for (int i = 0; i < (int)data.size(); i++)
//	{
//		day_19_2021__scanner_processed_data& scanner1{ data.at(i) };
//
//		total_beacons += (int)scanner1.beacon_distances.size();
//
//		for (day_19_2021__scanner_processed_data& scanner2 : data)
//		{
//			//day_19_2021__mark_common_beacons(i, scanner1, scanner2);
//		}
//	}
//
//	std::cout << "starting beacon count: " << total_beacons << '\n';
//
//	int unique_beacons{};
//	std::vector<int> common_beacons{};
//	int extra_counts{};
//
//	//for (day_19_2021__scanner_processed_data& scanner : data)
//	for (int i = 0; i < (int)data.size(); i++)
//	{
//		day_19_2021__scanner_processed_data& scanner1{ data.at(i) };
//
//		for (auto& beacon : scanner1.beacon_distances)
//		{
//			if (beacon.scanners_seen_by.size() > 0)
//			{
//				unique_beacons++;
//			}
//		}
//
//		// remove this scanner from all the points in the other scanners
//		for (auto& a : scanner1.beacon_distances)
//		{
//			for (int j = 0; j < (int)data.size(); j++)
//			{
//				if (i == j) continue;
//
//				for (auto& b : data.at(j).beacon_distances)
//				{
//					if (day_19_2021__distances_in_common(a, b) >= DAY_19_2021__THRESHOLD)
//					{
//						/*auto find = std::find(b.scanners_seen_by.begin(), b.scanners_seen_by.end(), i);
//
//						if (find != b.scanners_seen_by.end())
//						{
//							b.scanners_seen_by.erase(find);
//						}*/
//						b.scanners_seen_by = {}; // clear the list, we already counted this point
//					}
//				}
//			}
//		}
//	}
//
//	return unique_beacons;
//}

std::vector<point_3d> create_delta_positions(const std::set<point_3d>& points, const point_3d& position, point_3d& delta_point, int rx, int ry, int rz, int sx, int sy, int sz)
{
	std::vector<point_3d> deltas{};

	for (const point_3d& point : points)
	{
		deltas.push_back({ sx * (point[rx] - position[rx]), sy * (point[ry] - position[ry]), sz * (point[rz] - position[rz]) });
	}
	delta_point = { -sx * position[rx], -sy * position[ry], -sz * position[rz] };

	return deltas;
}

bool day_19_2021__attempt_merge(day_19_2021__scanner& merged_scanner, const day_19_2021__scanner& scanner_to_merge, point_3d& scanner_position)
{
	//  [facing, up, right, sign_f, sign_u, sign_r]
	static const std::vector<std::array<int, 6>> rotations {
		{0, 1, 2, 1, 1, 1},    //  x  y  z
		{0, 1, 2, 1, -1, -1},  //  x -y -z
		{0, 2, 1, 1, 1, -1},   //  x  z -y
		{0, 2, 1, 1, -1, 1},   //  x -z  y
		{0, 1, 2, -1, 1, -1},  // -x  y -z
		{0, 1, 2, -1, -1, 1},  // -x -y  z
		{0, 2, 1, -1, 1, 1},   // -x  z  y
		{0, 2, 1, -1, -1, -1}, // -x -z -y
	};

	// create all 24 orientations that we have to try
	std::vector<std::array<int, 6>> rotations_to_try{};

	for (int i = 0; i < 3; i++)
	{
		for (const auto& rots : rotations)
		{
			rotations_to_try.push_back({ (i + rots[0]) % 3, (i + rots[1]) % 3, (i + rots[2]) % 3, rots[3], rots[4], rots[5] });
		}
	}

	for (const auto& beacon : scanner_to_merge.beacons)
	{
		for (const auto& rotation : rotations_to_try)
		{
			point_3d delta_position{};

			std::vector<point_3d> delta{ create_delta_positions(scanner_to_merge.beacons, beacon, delta_position, rotation[0], rotation[1], rotation[2], rotation[3], rotation[4], rotation[5]) };

			for (const auto& merged_beacon : merged_scanner.beacons)
			{
				// check matches
				int matches{};

				for (const point_3d& delta_point : delta)
				{
					matches += merged_scanner.beacons.count({ delta_point.x + merged_beacon.x, delta_point.y + merged_beacon.y, delta_point.z + merged_beacon.z });

					if (matches >= 12) break;
				}

				if (matches >= 12)
				{
					// merge
					for (const point_3d& delta_point : delta)
					{
						merged_scanner.beacons.insert({ delta_point.x + merged_beacon.x, delta_point.y + merged_beacon.y, delta_point.z + merged_beacon.z });
					}

					scanner_position = { delta_position.x + merged_beacon.x, delta_position.y + merged_beacon.y, delta_position.z + merged_beacon.z };

					return true;
				}
				
			}
		}
	}
	return false;
}

// inspired by codefrommars
void day_19_2021__execute__part1(const std::vector<day_19_2021__scanner>& data)
{
	std::vector<int> scanners_to_merge{};

	for (int i = 1; i < (int)data.size(); i++)
	{
		scanners_to_merge.push_back(i);
	}

	day_19_2021__scanner merged_scanner{ data.at(0) };

	while (scanners_to_merge.size() > 0)
	{
		for (int i = 0; i < scanners_to_merge.size(); i++)
		{
			point_3d scanner_pos{};

			// try to merge, if successful, erase from scanners_to_merge
			if (day_19_2021__attempt_merge(merged_scanner, data.at(scanners_to_merge.at(i)), scanner_pos))
			{
				scanners_to_merge.erase(scanners_to_merge.begin() + i);
				break;
			}
		}
	}

	std::cout << "total beacons: " << merged_scanner.beacons.size() << '\n';
}

void day_19_2021__execute__part2(const std::vector<day_19_2021__scanner>& data)
{
	std::vector<int> scanners_to_merge{};

	for (int i = 1; i < (int)data.size(); i++)
	{
		scanners_to_merge.push_back(i);
	}

	day_19_2021__scanner merged_scanner{ data.at(0) };

	std::vector<point_3d> scanner_positions{};

	while (scanners_to_merge.size() > 0)
	{
		for (int i = 0; i < scanners_to_merge.size(); i++)
		{
			point_3d scanner_pos{};

			// try to merge, if successful, erase from scanners_to_merge
			if (day_19_2021__attempt_merge(merged_scanner, data.at(scanners_to_merge.at(i)), scanner_pos))
			{
				scanner_positions.push_back(scanner_pos);

				scanners_to_merge.erase(scanners_to_merge.begin() + i);
				break;
			}
		}
	}

	int max_manhattan_distance{};

	for (const point_3d& pos1 : scanner_positions)
	{
		for (const point_3d& pos2 : scanner_positions)
		{
			const int x_diff{ std::abs(pos2.x - pos1.x) };
			const int y_diff{ std::abs(pos2.y - pos1.y) };
			const int z_diff{ std::abs(pos2.z - pos1.z) };

			const int distance{ x_diff + y_diff + z_diff };

			if (distance > max_manhattan_distance)
			{
				max_manhattan_distance = distance;
			}
		}
	}

	std::cout << "max manhattan distance: " << max_manhattan_distance << '\n';
}

double day_19_2021__time()
{
	std::vector<day_19_2021__scanner> input{ day_19_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 1; i++)
	{
		day_19_2021__execute__part1(input);
		day_19_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() / (1 * 1000.0);
}

#pragma endregion Day 19

#pragma region Day 20

struct day_20_2021__data
{
	std::string image_enhancer{};
	std::vector<std::string> input_image{};

	int width{};
	int height{};
};

day_20_2021__data day_20_2021__read_input()
{
	std::fstream input{ read_input_from_file("../input/2021/day_20.txt") };

	day_20_2021__data data{};

	getline(input, data.image_enhancer);
	std::string line{};

	getline(input, line); // skip blank line
	getline(input, line); // first line of real data, used to size next lines

	data.width = (int)line.size();

	for (int i = 0; i < 1; i++)
	{
		data.input_image.push_back(std::string(line.size() + 2, '.'));
	}

	data.input_image.push_back("." + line + ".");

	while (getline(input, line))
	{
		data.input_image.push_back("." + line + ".");
		data.height++;
	}

	for (int i = 0; i < 1; i++)
	{
		data.input_image.push_back(std::string(line.size() + 2, '.'));
	}
	return data;
}

std::vector<std::string> day_20_2021__create_output_image(const day_20_2021__data& input)
{
	std::vector<std::string> output_image{};
	
	constexpr int EXTRA_PADDING_PER_ITERATION{ 1 };

	const std::string fill(input.input_image.at(0).size() + (EXTRA_PADDING_PER_ITERATION * 2), '.');// input.image_enhancer.at(0));

	for (size_t i = 0; i < input.input_image.size() + (EXTRA_PADDING_PER_ITERATION * 2); i++)
	{
		output_image.push_back(fill);
	}

	for (size_t y = 0; y < input.input_image.size(); y++)
	{
		const std::string& prev_line{ y < 1 ? input.input_image.at(y) : input.input_image.at(y - 1) };
		const std::string& curr_line{ input.input_image.at(y) };
		const std::string& next_line{ y >= input.input_image.size() - 1 ? input.input_image.at(y) : input.input_image.at(y + 1) };

		for (size_t x = 0; x < curr_line.size(); x++)
		{
			const bool top_left = prev_line.at(x == 0 ? x : x - 1) == '#';
			const bool top = prev_line.at(x) == '#';
			const bool top_right = prev_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';
			const bool left = curr_line.at(x == 0 ? x : x - 1) == '#';
			const bool center = curr_line.at(x) == '#';
			const bool right = curr_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';
			const bool bottom_left = next_line.at(x == 0 ? x : x - 1) == '#';
			const bool bottom = next_line.at(x) == '#';
			const bool bottom_right = next_line.at(x >= curr_line.size() - 1 ? x : x + 1) == '#';

			const int top_binary{ ((top_left ? 1 : 0) << 8) | ((top ? 1 : 0) << 7) | ((top_right ? 1 : 0) << 6) };
			const int middle_binary{ ((left ? 1 : 0) << 5) | ((center ? 1 : 0) << 4) | ((right ? 1 : 0) << 3) };
			const int bottom_binary{ ((bottom_left ? 1 : 0) << 2) | ((bottom ? 1 : 0) << 1) | (bottom_right ? 1 : 0) };
		
			const int index{
				top_binary | middle_binary | bottom_binary
			};

			const char output{ input.image_enhancer.at(index) };

			output_image.at(y + EXTRA_PADDING_PER_ITERATION).at(x + EXTRA_PADDING_PER_ITERATION) = output;
		}
	}

	// fix the extra padding we added around the edge. it's infinite space and should match the layer inside of it
	const char fill_char{ output_image.at(1).at(1) };
	const size_t width{ output_image.at(0).size() };
	const size_t height{ output_image.size() };

	for (size_t x = 0; x < output_image.size(); x++)
	{
		output_image.at(0).at(x) = fill_char;
		output_image.at(height - 1).at(x) = fill_char;
	}

	for (size_t y = 0; y < output_image.size(); y++)
	{
		output_image.at(y).at(0) = fill_char;
		output_image.at(y).at(width - 1) = fill_char;
	}

	return output_image;
}

void day_20_2021__execute__part1(const day_20_2021__data& data)
{
	day_20_2021__data second{};
	second.image_enhancer = data.image_enhancer;
	second.input_image = day_20_2021__create_output_image(data);
	

	const std::vector<std::string> final_image{ day_20_2021__create_output_image(second) };

	int pixels_lit{};

	for (const auto& line : final_image)
	{
		for (const auto& pixel : line)
		{
			if (pixel == '#')
			{
				pixels_lit++;
			}
		}
	}
	verify_answer(pixels_lit, 5218);
}

void day_20_2021__execute__part2(const day_20_2021__data& data)
{
	day_20_2021__data second{};
	second.image_enhancer = data.image_enhancer;
	second.input_image = data.input_image;


	for (int i = 0; i < 50; i++)
	{
		second.input_image = day_20_2021__create_output_image(second);
	}

	int pixels_lit{};

	for (const auto& line : second.input_image)
	{
		for (const auto& pixel : line)
		{
			if (pixel == '#')
			{
				pixels_lit++;
			}
		}
	}
	
	verify_answer(pixels_lit, 15527);
}

execution_result day_20_2021__time()
{
	day_20_2021__data input{ day_20_2021__read_input() };

	auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < EXECUTION_COUNT; i++)
	{
		day_20_2021__execute__part1(input);
		day_20_2021__execute__part2(input);
	}

	auto stop = std::chrono::high_resolution_clock::now();

	return { std::chrono::duration_cast<std::chrono::microseconds>(stop - start), EXECUTION_COUNT };
}

#pragma endregion Day 20

#pragma region Day 21

namespace _2021_21
{
	struct starting_positions
	{
		int player1{};
		int player2{};
	};

	struct universe
	{
		int position_player1{};
		int position_player2{};

		int score_player1{};
		int score_player2{};

		int roll1_player1{ -1 };
		int roll2_player1{ -1 };
		int roll3_player1{ -1 };

		int roll1_player2{ -1 };
		int roll2_player2{ -1 };
		int roll3_player2{ -1 };
	};

	struct game
	{
		int position_player1{};
		int position_player2{};

		int score_player1{};
		int score_player2{};

		auto operator<=>(const game&) const = default;
	};

	struct results
	{
		uint64_t wins_player1{};
		uint64_t wins_player2{};

		results& operator+=(const results& other)
		{
			wins_player1 += other.wins_player1;
			wins_player2 += other.wins_player2;
			return *this;
		}
	};

	starting_positions read_input()
	{
		std::fstream input{ read_input_from_file("../input/2021/day_21.txt") };

		std::string player_1{};
		getline(input, player_1);

		std::string player_2{};
		getline(input, player_2);

		starting_positions data{};

		sscanf_s(player_1.c_str(), "Player 1 starting position: %d", &data.player1);
		sscanf_s(player_2.c_str(), "Player 2 starting position: %d", &data.player2);

		return data;
	}

	void execute_part1(const starting_positions& data)
	{
		int die{ 1 };
		int total_rolls{};

		const auto roll_die = [&die, &total_rolls]()
		{
			const int roll{ die };
			
			die++;
			total_rolls++;

			if (die > 100)
			{
				die = 1;
			}
			return roll;
		};

		int score_player1{};
		int score_player2{};

		int position_player1{ data.player1 };
		int position_player2{ data.player2 };

		while (score_player1 < 1000 && score_player2 < 1000)
		{
			const int roll1_player1{ roll_die() };
			const int roll2_player1{ roll_die() };
			const int roll3_player1{ roll_die() };
			const int roll_player1{ roll1_player1 + roll2_player1 + roll3_player1 };

			position_player1 += roll_player1;

			if (position_player1 > 10)
			{
				position_player1 = position_player1 % 10;
				if (position_player1 == 0) position_player1 = 10;
			}

			score_player1 += position_player1;

			//printf("player 1, score: %d, roll: {%d, %d, %d}, pos: %d\n", score_player1, roll1_player1, roll2_player1, roll3_player1, position_player1);
			if (score_player1 >= 1000)
			{
				break;
			}

			const int roll1_player2{ roll_die() };
			const int roll2_player2{ roll_die() };
			const int roll3_player2{ roll_die() };
			const int roll_player2{ roll1_player2 + roll2_player2 + roll3_player2 };

			position_player2 += roll_player2;

			if (position_player2 > 10)
			{
				position_player2 = position_player2 % 10;
				if (position_player2 == 0) position_player2 = 10;
			}

			score_player2 += position_player2;

			//printf("player 2, score: %d, roll: {%d, %d, %d}, pos: %d\n", score_player2, roll1_player2, roll2_player2, roll3_player2, position_player2);

			if (score_player2 >= 1000)
			{
				break;
			}
		}

		const int answer{ (score_player1 > score_player2 ? score_player2 : score_player1) * total_rolls };
		
		//verify_answer(answer, 752745);
	}

	results count_wins(const std::map<int, uint64_t>& games, int score_player1, int score_player2, int position_player1, int position_player2, int roll1, int roll2)
	{
		if (score_player1 >= 21)
		{
			return { games.at(roll1), 0 };
			//return { 1, 0 };
		}
		else if (score_player2 >= 21)
		{
			return { 0, games.at(roll2) };
			//return { 0, 1 };
		}
		else
		{
			results result{};

			for (int i = 3; i < 10; i++)
			{
				int new_pos_player1{ position_player1 + i };

				if (new_pos_player1 > 10)
				{
					new_pos_player1 %= 10;
					if (new_pos_player1 == 0) new_pos_player1 = 10;
				}

				const int new_score_player1{ score_player1 + new_pos_player1 };

				if (new_score_player1 < 21)
				{
					results winner{ count_wins(games, new_score_player1, score_player2, new_pos_player1, position_player2, i, 0) };

					if (roll1 != 0 && winner.wins_player1 > 0) winner.wins_player1 *= games.at(roll1);
					if (roll2 != 0 && winner.wins_player2 > 0) winner.wins_player2 *= games.at(roll2);

					result += winner;



					for (int j = 3; j < 10; j++)
					{
						int new_pos_player2{ position_player2 + j };


						if (new_pos_player2 > 10)
						{
							new_pos_player2 %= 10;
							if (new_pos_player2 == 0) new_pos_player2 = 10;
						}

						const int new_score_player2{ score_player2 + new_pos_player2 };

						winner = count_wins(games, new_score_player1, new_score_player2, new_pos_player1, new_pos_player2, i, j);

						if (roll1 != 0 && winner.wins_player1 > 0) winner.wins_player1*= games.at(roll1);
						if (roll2 != 0 && winner.wins_player2 > 0) winner.wins_player2*= games.at(roll2);

						result += winner;
					}
				}
				else
				{
					if (roll1 != 0)
					{
						result += {games.at(i)* games.at(roll1), 0};
					}
					else
					{
						result += {games.at(i), 0};
					}
				}
			}
			return result;
		}
	}

	void execute_part2(const starting_positions& data)
	{
		results result{};

		std::map<int, uint64_t> games{};

		for (int i = 1; i <= 3; i++)
		{
			for (int j = 1; j <= 3; j++)
			{
				for (int k = 1; k <= 3; k++)
				{
					games[i + j + k]++;
				}
			}
		}
		//for (int i = 3; i < 10; i++)
		{
			result += count_wins(games, 0, 0, data.player1, data.player2, 0, 0);
		}
		std::cout << "player1 wins: " << result.wins_player1 << ", player2 wins: " << result.wins_player2 << '\n';

		// possible game states: 10 positions, 21 scores, 2 players, (10 * 21) ^ 2
		// every roll (3 dice): 3 - 9 points, 7 * 2 = 14
		/*or (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 21; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					game_counts[game{ i, j, k }] = 0;
				}
			}
		}*/

		//std::list<universe> universes{};

		//uint64_t total_universes{ 1 };

		//universes.push_back({ data.player1, data.player2 });

		//while (universes.size() > 0)
		//{
		//	universe* uni{ &universes.front() };

		//	_ASSERT(uni->score_player1 >= 0);
		//	_ASSERT(uni->score_player2 >= 0);

		//	if (uni->roll1_player1 == -1)
		//	{
		//		uni->roll1_player1 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}
		//	if (uni->roll2_player1 == -1)
		//	{
		//		uni->roll2_player1 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}
		//	if (uni->roll3_player1 == -1)
		//	{
		//		uni->roll3_player1 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}

		//	const int roll_player1{ uni->roll1_player1 + uni->roll2_player1 + uni->roll3_player1 };

		//	uni->position_player1 += roll_player1;

		//	if (uni->position_player1 > 10)
		//	{
		//		uni->position_player1 = uni->position_player1 % 10;
		//		if (uni->position_player1 == 0) uni->position_player1 = 10;
		//	}

		//	uni->score_player1 += uni->position_player1;

		//	_ASSERT(uni->score_player1 >= 0);

		//	//printf("player 1, score: %d, roll: {%d, %d, %d}, pos: %d\n", score_player1, roll1_player1, roll2_player1, roll3_player1, position_player1);
		//	if (uni->score_player1 >= 21)
		//	{
		//		wins_player1++;
		//		universes.erase(universes.begin());
		//		continue;
		//	}

		//	if (uni->roll1_player2 == -1)
		//	{
		//		uni->roll1_player2 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}
		//	if (uni->roll2_player2 == -1)
		//	{
		//		uni->roll2_player2 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, uni->roll1_player2, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, uni->roll1_player2, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}
		//	if (uni->roll3_player2 == -1)
		//	{
		//		uni->roll3_player2 = 1;
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, uni->roll1_player2, uni->roll2_player2, 2 });// uni = &universes.at(0);
		//		universes.push_back({ uni->position_player1, uni->position_player2, uni->score_player1, uni->score_player2, uni->roll1_player1, uni->roll2_player1, uni->roll3_player1, uni->roll1_player2, uni->roll2_player2, 3 });// uni = &universes.at(0);

		//		total_universes += 2;
		//	}

		//	const int roll_player2{ uni->roll1_player2 + uni->roll2_player2 + uni->roll3_player2 };

		//	uni->position_player2 += roll_player2;

		//	if (uni->position_player2 > 10)
		//	{
		//		uni->position_player2 = uni->position_player2 % 10;
		//		if (uni->position_player2 == 0) uni->position_player2 = 10;
		//	}

		//	uni->score_player2 += uni->position_player2;

		//	_ASSERT(uni->score_player2 >= 0);

		//	//printf("player 1, score: %d, roll: {%d, %d, %d}, pos: %d\n", score_player1, roll1_player1, roll2_player1, roll3_player1, position_player1);
		//	if (uni->score_player2 >= 21)
		//	{
		//		wins_player2++;
		//		universes.erase(universes.begin());
		//		continue;
		//	}

		//	uni->roll1_player1 = -1;
		//	uni->roll2_player1 = -1;
		//	uni->roll3_player1 = -1;
		//	uni->roll1_player2 = -1;
		//	uni->roll2_player2 = -1;
		//	uni->roll3_player2 = -1;
		//}

		//std::cout << "most wins: " << (wins_player1 > wins_player2 ? wins_player1 : wins_player2) << '\n';
		//std::cout << "total universes: " << total_universes << '\n';
	}

	execution_result time()
	{
		auto input{ read_input() };

		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < 1; i++)
		{
			execute_part1(input);
			execute_part2(input);
		}

		auto stop = std::chrono::high_resolution_clock::now();

		return { std::chrono::duration_cast<std::chrono::microseconds>(stop - start), 1 };
	}
}
#pragma endregion Day 21

#pragma endregion Advent of Code - 2021

int main()
{
	std::array<std::array<execution_result, 25>, 7> times{};
	
	for (int i = 0; i < times.size(); i++)
	{
		for (int j = 0; j < times.at(i).size(); j++)
		{
			times.at(i).at(j).execution_count = 0;
		}
	}

	const auto year = [](auto num) { return num - 2015; };
	const auto day = [](auto num) { return num - 1; };

	auto& y2015{ times.at(year(2015)) };

	y2015.at(day(1)) = day_1_2015__time();
	y2015.at(day(2)) = day_2_2015__time();

	auto& y2021{ times.at(year(2021)) };
	
	y2021.at(day(1)) = day_1_2021__time();
	y2021.at(day(2)) = day_2_2021__time();
	y2021.at(day(3)) = day_3_2021__time();
	y2021.at(day(4)) = day_4_2021__time();
	y2021.at(day(5)) = _2021_5::time();

	y2021.at(day(17)) = day_17_2021__time();

	y2021.at(day(20)) = day_20_2021__time();
	y2021.at(day(21)) = _2021_21::time();

	std::cout << "           2015    2016    2017    2018    2019    2020    2021\n";

	for (int i = 0; i < 25; i++)
	{
		std::cout << "day ";
		std::cout << std::setw(2) << (i + 1);
		std::cout << "    ";


		for (int j = 0; j < times.size(); j++)
		{
			
			if (times.at(j).at(i).execution_count > 0)
			{
				//printf("%llums  ", times.at(j).at(i));
				std::cout << std::setw(5);
				std::cout << times.at(j).at(i).display();
				//std::cout << " (" << times.at(j).at(i).raw_time() << ")";
				
			}
			else
			{
				std::cout << "     ";
			}
			std::cout << "   ";
		}
		std::cout << '\n';
	}

	std::cout << '\n';
	std::cout << "total     ";
	std::cout << std::setw(2);

	execution_result all_time_total{};
	all_time_total.execution_count = 1;

	for (size_t i = 0; i < times.size(); i++)
	{
		execution_result year_total{};

		for (int day = 0; day < 25; day++)
		{
			if (times.at(i).at(day).execution_count > 0)
			{
				year_total.time += times.at(i).at(day).time_per_execution();
				all_time_total.time += times.at(i).at(day).time_per_execution();
				year_total.execution_count = 1;
			}
		}

		if (year_total.execution_count > 0)
		{
			std::cout << std::setw(5);
			std::cout << year_total.display();
		}
		else
		{
			std::cout << "     ";
		}
		std::cout << "   ";
	}
	std::cout << all_time_total.display();
	std::cout << '\n';

	return 0;
}
