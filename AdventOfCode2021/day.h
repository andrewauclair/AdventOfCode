#pragma once

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
	virtual void run_part_1() const = 0;
	virtual void run_part_2() const = 0;
};