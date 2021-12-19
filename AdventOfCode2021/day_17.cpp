#include "day_17.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>

void Day_17::run_part_1() const
{
	std::cout << "[Day 17] [Part 1]\n";

	std::fstream example_input{ read_input("day_17_example.txt") };
	std::fstream actual_input{ read_input("day_17_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

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
		bool match = does_y_vel_hit_target(x_vel, y_vel, target_y_min, target_y_max);

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

	/*_ASSERT(does_vel_hit_target(23, -10, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -7, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	8, 0, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -10, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -6, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -10, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	8, 1, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -10, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 5, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	23, -5, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -10, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	8, -2, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -9, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -6, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -6, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, -1, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	13, -2, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	15, -4, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	23, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	23, -6, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 2, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -5, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -5, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -8, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 7, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 3, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	9, -2, target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	11, -3 , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	13, -4 , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -8 , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -10 														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -6  														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 8    														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -10 														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	8, -1  															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -8 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	15, -2 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 6   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 0   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	10, -2 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -8 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -6 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	11, -2 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 7   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	12, -2 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 1   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -6  														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	9, -1  															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	11, -1 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -7  														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -5   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 4   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 2   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	15, -3   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -9  														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	23, -9  														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	11, -4   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	10, -1   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -9   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -10   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -9   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	9, 0    														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -10   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 1    														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -7   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -5   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	12, -3   														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 0    														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	12, -4 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	14, -2 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 9   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	20, -6 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 3   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	14, -4 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	30, -10 														  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -8 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -6 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -10															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	26, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	22, -9 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 6   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 9   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	24, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	28, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -6 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	14, -3 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	25, -8 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	23, -7 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	27, -6 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	7, 4   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	6, 5   															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	13, -3 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	21, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	_ASSERT(does_vel_hit_target(	29, -5 															  , target_x_min, target_x_max, target_y_min, target_y_max));
	*/
	for (int x_vel = 0; x_vel < target_x_max + 1; x_vel++)
	{
		for (int y_vel = target_y_min; y_vel < abs(target_y_min) + 1; y_vel++)
		{
			if (does_vel_hit_target(x_vel, y_vel, target_x_min, target_x_max, target_y_min, target_y_max))
			{
				count++;
				does_vel_hit_target(x_vel, y_vel, target_x_min, target_x_max, target_y_min, target_y_max);
			}
		}
	}

	return count;
}

std::string Day_17::run_part_1(std::fstream& input) const
{
	std::string line{};
	getline(input, line);

	int target_x_min{};
	int target_x_max{};
	int target_y_min{};
	int target_y_max{};

	sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &target_x_min, &target_x_max, &target_y_min, &target_y_max);

	int start_vel_min{ calculate_x_velocity(target_x_min, false) };
	int start_vel_max{ calculate_x_velocity(target_x_max, true) };

	int y_vel_x_min{ calculate_y_velocity(start_vel_min, target_y_min, target_y_max) };
	int y_vel_x_max{ calculate_y_velocity(start_vel_max, target_y_min, target_y_max) };

	int y_max_min{ calculate_max_height(start_vel_min, y_vel_x_min, target_y_min, target_y_max) };
	int y_max_max{ calculate_max_height(start_vel_max, y_vel_x_max, target_y_min, target_y_max) };

	return std::to_string(y_max_min > y_max_max ? y_max_min : y_max_max);
}

void Day_17::run_part_2() const
{
	std::cout << "[Day 17] [Part 2]\n";

	std::fstream example_input{ read_input("day_17_example.txt") };
	std::fstream actual_input{ read_input("day_17_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_17::run_part_2(std::fstream& input) const
{
	std::string line{};
	getline(input, line);

	int target_x_min{};
	int target_x_max{};
	int target_y_min{};
	int target_y_max{};

	sscanf_s(line.c_str(), "target area: x=%d..%d, y=%d..%d", &target_x_min, &target_x_max, &target_y_min, &target_y_max);


	return std::to_string(count_initial_velocities(target_x_min, target_x_max, target_y_min, target_y_max));
}
