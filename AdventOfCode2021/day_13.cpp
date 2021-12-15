#include "day_13.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>
#include <deque>
#include <set>

struct point_day13
{
	int x{};
	int y{};

	auto operator<=>(const point_day13&) const = default;
};

struct fold_position
{
	char type{}; // 0 - x, 1 - y
	int pos{}; 
};

struct day13_data
{
	std::set<point_day13> points{};

	std::vector<fold_position> folds{};

	int height{};
	int width{};
};

day13_data read_day_13_strings(std::fstream& input)
{
	day13_data data{};

	std::string str{};

	bool reading_folds{};

	while (getline(input, str))
	{
		if (str.empty())
		{
			reading_folds = true;
			continue;
		}
		else if (!reading_folds)
		{
			point_day13 p{};
			sscanf_s(str.c_str(), "%d,%d", &p.x, &p.y);

			if (p.x > data.width)
			{
				data.width = p.x;
			}
			if (p.y > data.height)
			{
				data.height = p.y;
			}
			data.points.insert(p);
		}
		else
		{
			fold_position fold{};
			sscanf_s(str.c_str(), "fold along %c=%d", &fold.type, 1, &fold.pos);

			data.folds.push_back(fold);
		}
	}

	return data;
}

void Day_13::run_part_1() const
{
	std::cout << "[Day 13] [Part 1]\n";

	std::fstream example_input{ read_input("day_13_example.txt") };
	std::fstream actual_input{ read_input("day_13_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_13::run_part_1(std::fstream& input) const
{
	const day13_data data{ read_day_13_strings(input) };

	// execute first fold
	//const fold_position fold{ data.folds.at(0) };

	std::set<point_day13> points{ data.points };

	for (size_t i = 0; i < 1; i++)//data.folds.size(); i++)
	{
		const fold_position fold{ data.folds.at(i) };
		std::set<point_day13> new_points{};

		for (auto it = points.begin(); it != points.end(); ++it)
		{
			const point_day13& point{ *it };

			if (fold.type == 'y') // y
			{
				_ASSERT(point.y != fold.pos);

				if (point.y > fold.pos)
				{
					

					const point_day13 new_point{ point.x, point.y - ((point.y - fold.pos) * 2) };

					new_points.insert(new_point);

					/*if (std::find(points.begin(), points.end(), new_point) == points.end() &&
						std::find(new_points.begin(), new_points.end(), new_point) == new_points.end())
					{
						new_points.push_back(new_point);
						
					}*/
					//it = points.erase(it);
					continue;
				}
				else
				{
					new_points.insert(point);
				}
			}
			else // x
			{
				_ASSERT(point.x != fold.pos);

				if (point.x > fold.pos)
				{
					
					const point_day13 new_point{ point.x - ((point.x - fold.pos) * 2), point.y };

					_ASSERT(new_point.x >= 0 && new_point.y >= 0);

					new_points.insert(new_point);
				
					/*if (std::find(points.begin(), points.end(), new_point) == points.end() &&
						std::find(new_points.begin(), new_points.end(), new_point) == new_points.end())
					{
						new_points.push_back(new_point);
					}
					it = points.erase(it);*/
					continue;
				}
				else
				{
					new_points.insert(point);
				}
			}
		}

		points = new_points;
	}


	return std::to_string(points.size());
}

void Day_13::run_part_2() const
{
	std::cout << "[Day 13] [Part 2]\n";

	std::fstream example_input{ read_input("day_13_example.txt") };
	std::fstream actual_input{ read_input("day_13_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_13::run_part_2(std::fstream& input) const
{
	const day13_data data{ read_day_13_strings(input) };

	// execute first fold
	//const fold_position fold{ data.folds.at(0) };

	std::set<point_day13> points{ data.points };
	int width{ data.width };
	int height{ data.height };

	for (size_t i = 0; i < data.folds.size(); i++)
	{
		const fold_position fold{ data.folds.at(i) };
		std::set<point_day13> new_points{};

		for (auto it = points.begin(); it != points.end(); ++it)
		{
			const point_day13& point{ *it };

			if (fold.type == 'y') // y
			{
				_ASSERT(point.y != fold.pos);

				if (point.y > fold.pos)
				{


					const point_day13 new_point{ point.x, point.y - ((point.y - fold.pos) * 2) };

					new_points.insert(new_point);

					/*if (std::find(points.begin(), points.end(), new_point) == points.end() &&
						std::find(new_points.begin(), new_points.end(), new_point) == new_points.end())
					{
						new_points.push_back(new_point);

					}*/
					//it = points.erase(it);
					continue;
				}
				else
				{
					new_points.insert(point);
				}
			}
			else // x
			{
				_ASSERT(point.x != fold.pos);

				if (point.x > fold.pos)
				{

					const point_day13 new_point{ point.x - ((point.x - fold.pos) * 2), point.y };

					_ASSERT(new_point.x >= 0 && new_point.y >= 0);

					new_points.insert(new_point);

					/*if (std::find(points.begin(), points.end(), new_point) == points.end() &&
						std::find(new_points.begin(), new_points.end(), new_point) == new_points.end())
					{
						new_points.push_back(new_point);
					}
					it = points.erase(it);*/
					continue;
				}
				else
				{
					new_points.insert(point);
				}
			}
		}

		points = new_points;

		if (fold.type == 'y') // y
			height = fold.pos ;
		else
			width = fold.pos ;

	}
	std::cout << '\n';

	// visual dots
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (points.contains(point_day13{ x, y }))
			{
				std::cout << '#';
			}
			else
			{
				std::cout << '.';
			}
		}
		std::cout << '\n';
	}

	return std::to_string(points.size());
}
