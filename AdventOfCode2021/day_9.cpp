#include "day_9.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>

std::vector<std::vector<Day_9::Point>> read_grid_values(std::fstream& input)
{
	std::vector<std::vector<Day_9::Point>> grid{};

	std::string str{};

	size_t row{};

	while (getline(input, str))
	{
		std::vector<Day_9::Point> line{};
		size_t col{};

		for (char ch : str)
		{
			line.push_back(Day_9::Point{ row, col++, static_cast<int>(ch - '0') });
		}

		grid.push_back(line);
		row++;
	}

	return grid;
}

size_t Day_9::size_from_basin(Point start, const std::vector<std::vector<Point>>& grid) const
{
	std::vector<Point> points{};
	points.push_back(start);

	add_points(start, (Direction)-1, points, grid);

	return points.size();
}

void Day_9::add_points(Point point, Direction ignore, std::vector<Point>& points, const std::vector<std::vector<Point>>& grid) const
{
	const auto try_add = [&](int value, Point p, Direction direction) {
		if (p.value != 9 && p.value > value && std::find(points.begin(), points.end(), p) == points.end())
		{
			points.push_back(p);

			add_points(p, direction, points, grid);
		}
	};

	if (point.row > 0 && ignore != Direction::up)
	{
		Point up_point{ grid[point.row - 1][point.col] };

		try_add(point.value, up_point, Direction::down);
	}

	if (point.row < grid.size() - 1 && ignore != Direction::down)
	{
		Point down_point{ grid[point.row + 1][point.col] };

		try_add(point.value, down_point, Direction::up);
	}

	if (point.col > 0 && ignore != Direction::left)
	{
		Point left_point{ grid[point.row][point.col - 1] };

		try_add(point.value, left_point, Direction::right);
	}

	if (point.col < grid[point.row].size() - 1 && ignore != Direction::right)
	{
		Point right_point{ grid[point.row][point.col + 1] };

		try_add(point.value, right_point, Direction::left);
	}
}

void Day_9::run_part_1() const
{
	std::cout << "[Day 9] [Part 1]\n";

	std::fstream example_input{ read_input("day_9_example.txt") };
	std::fstream actual_input{ read_input("day_9_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_9::run_part_1(std::fstream& input) const
{
	const std::vector<std::vector<Point>> grid{ read_grid_values(input) };

	int total_risk{};

	for (size_t row = 0; row < grid.size(); row++)
	{
		for (size_t col = 0; col < grid[row].size(); col++)
		{
			const int value{ grid[row][col].value };

			const bool first_row{ row == 0 };
			const bool last_row{ row == grid.size() - 1 };

			const bool first_col{ col == 0 };
			const bool last_col{ col == grid[row].size() - 1 };

			bool low{ true };

			if (row > 0 && value >= grid[row - 1][col].value)
			{
				low = false;
			}

			if (row < grid.size() - 1 && value >= grid[row + 1][col].value)
			{
				low = false;
			}

			if (col > 0 && value >= grid[row][col - 1].value)
			{
				low = false;
			}

			if (col < grid[row].size() - 1 && value >= grid[row][col + 1].value)
			{
				low = false;
			}

			if (low)
			{
				total_risk += value + 1;
			}
		}
	}

	return std::to_string(total_risk);
}

void Day_9::run_part_2() const
{
	std::cout << "[Day 9] [Part 2]\n";

	std::fstream example_input{ read_input("day_9_example.txt") };
	std::fstream actual_input{ read_input("day_9_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_9::run_part_2(std::fstream& input) const
{
	const std::vector<std::vector<Point>> grid{ read_grid_values(input) };

	std::vector<Point> lowest_points{};

	for (size_t row = 0; row < grid.size(); row++)
	{
		for (size_t col = 0; col < grid[row].size(); col++)
		{
			const int value{ grid[row][col].value };

			const bool first_row{ row == 0 };
			const bool last_row{ row == grid.size() - 1 };

			const bool first_col{ col == 0 };
			const bool last_col{ col == grid[row].size() - 1 };

			bool low{ true };

			if (row > 0 && value >= grid[row - 1][col].value)
			{
				low = false;
			}

			if (row < grid.size() - 1 && value >= grid[row + 1][col].value)
			{
				low = false;
			}

			if (col > 0 && value >= grid[row][col - 1].value)
			{
				low = false;
			}

			if (col < grid[row].size() - 1 && value >= grid[row][col + 1].value)
			{
				low = false;
			}

			if (low)
			{
				lowest_points.push_back(Point{ row, col });
			}
		}
	}

	std::vector<int> basin_sizes{};

	for (const Point& low_point : lowest_points)
	{
		basin_sizes.push_back(size_from_basin(low_point, grid));
	}

	std::sort(basin_sizes.rbegin(), basin_sizes.rend());

	int total{ 1 };

	for (int i = 0; i < 3; i++)
	{
		total *= basin_sizes.at(i);
	}
	return std::to_string(total);
}
