#pragma once

#include "day_1.h"

#include <array>
#include <iostream>

namespace aoc_2021
{
	const std::array<Day, 25> days
	{
		Day_1{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{},
		Unimplemented_Day{}
	};

	void run_day(const Day* day)
	{
		day->run_part_1();
		day->run_part_2();
	}

	void run()
	{
		std::cout << "[ -- 2021 -- ]\n\n";

		for (const Day& day : days)
		{
			run_day(&day);
		}
	}
}
