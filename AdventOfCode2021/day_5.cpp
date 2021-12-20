#include "day_5.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>

struct Point
{
	int x{};
	int y{};
};

struct Line
{
	Point start{};
	Point end{};

	bool is_straight_line() const
	{
		//return false;
		return (start.x == end.x) || (start.y == end.y);
	}

	bool on_line(Point a, Point b, Point c) const {
		const float slope = (b.y - a.y) / (float)(b.x - a.x);

		const bool on_infinite_line = (c.y - a.y) == slope * (c.x - a.x);

		if (on_infinite_line)
		{
			const bool within_x_range = (a.x <= c.x && c.x <= b.x) || (a.x >= c.x && c.x >= b.x);
			const bool within_y_range = (a.y <= c.y && c.y <= b.y) || (a.y >= c.y && c.y >= b.y);

			return within_x_range && within_y_range;
		}
		return false;
	}

	bool intersects_point(Point point) const
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
};

std::vector<Line> read_lines(std::fstream& input)
{
	std::vector<Line> lines{};

	std::string str{};

	while (getline(input, str))
	{
		Line line{};

		sscanf_s(str.c_str(), "%d,%d -> %d,%d", &line.start.x, &line.start.y, &line.end.x, &line.end.y);

		lines.push_back(line);
	}

	return lines;
}

void Day_5::run_part_1() const
{
	std::cout << "[Day 5] [Part 1]\n";

	std::fstream example_input{ read_input("day_5_example.txt") };
	std::fstream actual_input{ read_input("day_5_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_5::run_part_1(std::fstream& input) const
{
	const std::vector<Line> lines{ read_lines(input) };

	int largest_x{};
	int largest_y{};

	for (auto line : lines)
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

	int points_with_multiple_lines{};

	for (int y = 0; y <= largest_y; y++)
	{
		for (int x = 0; x <= largest_x; x++)
		{
			Point point{ x, y };

			int line_count{};

			for (const Line& line : lines)
			{
				if (line.is_straight_line() && line.intersects_point(point))
				{
					line_count++;
				}
			}

			if (line_count > 1)
			{
				points_with_multiple_lines++;
			}
		}
	}

	return std::to_string(points_with_multiple_lines);
}

void Day_5::run_part_2() const
{
	std::cout << "[Day 5] [Part 2]\n";

	std::fstream example_input{ read_input("day_5_example.txt") };
	std::fstream actual_input{ read_input("day_5_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_5::run_part_2(std::fstream& input) const
{
	const std::vector<Line> lines{ read_lines(input) };

	int largest_x{};
	int largest_y{};

	for (auto line : lines)
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

	int points_with_multiple_lines{};

	for (int y = 0; y <= largest_y; y++)
	{
		for (int x = 0; x <= largest_x; x++)
		{
			Point point{ x, y };

			int line_count{};

			for (const Line& line : lines)
			{
				if (line.intersects_point(point))
				{
					line_count++;
				}
			}

			if (line_count > 1)
			{
				points_with_multiple_lines++;
			}
		}
	}

	return std::to_string(points_with_multiple_lines);
}
