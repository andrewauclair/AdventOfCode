#include "day_4.h"

#include <iostream>
#include <fstream>
#include <string>

#include <array>
#include <vector>
#include <sstream>

constexpr int BOARD_SIZE = 5;

struct Bingo_Board
{
	std::array<std::array<int, BOARD_SIZE>, BOARD_SIZE> numbers{};
	std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> marked{};

	int win_order{};

	void mark(int number)
	{
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (numbers[i][j] == number)
				{
					marked[i][j] = true;
				}
			}
		}
	}

	bool has_won() const
	{
		// check rows
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			bool won{ true };

			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[i][j])
				{
					won = false;
					break;
				}
			}
			if (won)
			{
				return true;
			}
		}
		// check columns
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			bool won{ true };

			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[j][i])
				{
					won = false;
					break;
				}
			}
			if (won)
			{
				return true;
			}
		}
		return false;
	}

	int sum_unmarked() const
	{
		int sum{};

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (!marked[i][j])
				{
					sum += numbers[i][j];
				}
			}
		}
		return sum;
	}
};

struct File_Results
{
	std::vector<int> numbers_to_draw{};

	std::vector<Bingo_Board> boards{};

	size_t next_number_index{};

	void draw()
	{
		const int number_drawn{ numbers_to_draw[next_number_index++] };

		for (Bingo_Board& board : boards)
		{
			bool won{ board.has_won() };
			board.mark(number_drawn);

			if (!won && board.has_won())
			{
				board.win_order = boards_remaining();
			}
		}
	}

	bool has_a_winner() const
	{
		for (const Bingo_Board& board : boards)
		{
			if (board.has_won())
			{
				return true;
			}
		}
		return false;
	}

	int boards_remaining() const
	{
		int count{ (int)boards.size() };

		for (const Bingo_Board& board : boards)
		{
			if (board.has_won())
			{
				count--;
			}
		}
		return count;
	}

	int final_score() const
	{
		const int number_drawn{ numbers_to_draw.at(next_number_index - 1) };

		for (const Bingo_Board& board : boards)
		{
			if (board.has_won())
			{
				return board.sum_unmarked() * number_drawn;
			}
		}
		return 0;
	}

	int final_score_last_board()
	{
		const int number_drawn{ numbers_to_draw.at(next_number_index - 1) };

		for (const Bingo_Board& board : boards)
		{
			if (board.win_order == 0)
			{
				return board.sum_unmarked() * number_drawn;
			}
		}
		return 0;
	}
};

File_Results read_results(std::fstream& input)
{
	File_Results results{};

	std::string numbers{};
	input >> numbers;

	std::stringstream ss{ numbers };
	for (int i{}; ss >> i;)
	{
		results.numbers_to_draw.push_back(i);
		if (ss.peek() == ',')
		{
			ss.ignore();
		}
	}

	while (!input.eof())
	{
		Bingo_Board board{};

		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				input >> board.numbers[i][j];
			}
		}

		results.boards.push_back(board);
	}

	return results;
}

void Day_4::run_part_1() const
{
	std::cout << "[Day 4] [Part 1]\n";

	std::fstream example_input{ read_input("day_4_example.txt") };
	std::fstream actual_input{ read_input("day_4_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_4::run_part_1(std::fstream& input) const
{
	File_Results results{ read_results(input) };

	while (!results.has_a_winner())
	{
		results.draw();
	}

	return std::to_string(results.final_score());
}

void Day_4::run_part_2() const
{
	std::cout << "[Day 4] [Part 2]\n";

	std::fstream example_input{ read_input("day_4_example.txt") };
	std::fstream actual_input{ read_input("day_4_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_4::run_part_2(std::fstream& input) const
{
	File_Results results{ read_results(input) };
	
	while (results.boards_remaining() > 0)
	{
		results.draw();
	}

	return std::to_string(results.final_score_last_board());
}
