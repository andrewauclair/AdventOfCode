#pragma once

#include <fstream>
#include <string>
#include <iostream>

class Day
{
public:
	virtual ~Day() = default;

	void run() const
	{
		run_part_1();
		run_part_2();
	}

protected:
	std::fstream read_input(const std::string& file) const
	{
		std::fstream input{ file, std::ios_base::in };

		if (!input.is_open())
		{
			std::cerr << "Could not open " << file << '\n';
			throw std::runtime_error("failed to read file.");
		}

		return input;
	}

	virtual void run_part_1() const = 0;
	virtual void run_part_2() const = 0;
};