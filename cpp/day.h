#pragma once

#include <string>

class Day
{
public:
	virtual ~Day() = default;

	void run() const;

protected:
	virtual int day() const = 0;

	virtual std::string run_part_1() const = 0;
	virtual std::string run_part_2() const = 0;
};

class Unimplemented_Day : public Day
{
	std::string run_part_1() const override;
	std::string run_part_2() const override;
};
