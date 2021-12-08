#include "day_6.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

std::vector<int> read_fish_timers(std::fstream& input)
{
	std::vector<int> fish_timers{};

	int timer{};
	char ch{};

	input >> timer;
	fish_timers.push_back(timer);

	while (input >> ch >> timer)
	{
		fish_timers.push_back(timer);
	}
	return fish_timers;
}

void Day_6::run_part_1() const
{
	std::cout << "[Day 6] [Part 1]\n";

	std::fstream example_input{ read_input("day_6_example.txt") };
	std::fstream actual_input{ read_input("day_6_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_6::run_part_1(std::fstream& input) const
{
	std::vector<int> fish_timers{ read_fish_timers(input) };

	const int days{ 80 };

	for (int day = 0; day < days; day++)
	{
		int fish_to_add{};

		for (int& timer : fish_timers)
		{
			if (timer == 0)
			{
				timer = 6;
				fish_to_add++;
			}
			else
			{
				timer--;
			}
		}

		for (int i = 0; i < fish_to_add; i++)
		{
			fish_timers.push_back(8);
		}
	}

	return std::to_string(fish_timers.size());
}

void Day_6::run_part_2() const
{
	std::cout << "[Day 6] [Part 2]\n";

	std::fstream example_input{ read_input("day_6_example.txt") };
	std::fstream actual_input{ read_input("day_6_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_6::run_part_2(std::fstream& input) const
{
	const std::vector<int> fish_timers{ read_fish_timers(input) };

	std::map<int, int64_t> fish{};

	for (int i = 0; i <= 8; i++)
	{
		fish[i] = 0;
	}

	for (int timer : fish_timers)
	{
		fish[timer]++;
	}

	const int days{ 256 };

	for (int day = 0; day < days; day++)
	{
		int64_t fish_to_add{ fish[0] };

		fish[0] = fish[1];
		fish[1] = fish[2];
		fish[2] = fish[3];
		fish[3] = fish[4];
		fish[4] = fish[5];
		fish[5] = fish[6];
		fish[6] = fish[7] + fish_to_add;
		fish[7] = fish[8];
		fish[8] = fish_to_add;
	}

	int64_t total_fish{};

	for (int i = 0; i <= 8; i++)
	{
		total_fish += fish[i];
	}
	return std::to_string(total_fish);
}
