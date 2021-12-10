#pragma once

#include "day.h"

#include <vector>

class Day_9 : public Day
{
public:
	struct Point
	{
		size_t row{};
		size_t col{};

		int value{};

		auto operator<=>(const Point&) const = default;
	};

	enum Direction
	{
		up,
		left,
		down,
		right
	};

	size_t size_from_basin(Point start, const std::vector<std::vector<Point>>& grid) const;

	void add_points(Point point, Direction ignore, std::vector<Point>& points, const std::vector<std::vector<Point>>& grid) const;

public:
	void run_part_1() const override;
	std::string run_part_1(std::fstream& input) const;

	void run_part_2() const override;
	std::string run_part_2(std::fstream& input) const;
};
