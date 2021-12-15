#pragma once

#include <fstream>
#include <string>
#include <iostream>

inline std::fstream read_input(const std::string& file)
{
	std::fstream input{ file, std::ios_base::in };

	if (!input.is_open())
	{
		std::cerr << "Could not open " << file << '\n';
		throw std::runtime_error("failed to read file: " + file);
	}

	return input;
}
