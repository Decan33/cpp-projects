#pragma once
#include <iostream>
#include <random>

class Board {
	const int x, y;
	int** board_old;
	int** board_new;
private:
	int calculate_neighbors(const int i, const int j)
	{
		int total = 0;
		if (i == 0 && j == 0)
		{
			total += board_old[i][j+1];
			total += board_old[i + 1][j + 1];
			total += board_old[i + 1][j];

			return total;
		}
		else if (i == (x-1) && j == 0)
		{
			total += board_old[i][j + 1];
			total += board_old[i - 1][j + 1];
			total += board_old[i - 1][j];

			return total;
		}
		else if (i == (x-1) && j == (y-1))
		{
			total += board_old[i][j - 1];
			total += board_old[i - 1][j - 1];
			total += board_old[i - 1][j];

			return total;
		}
		else if (i == 0 && j == (y-1))
		{
			total += board_old[i][j - 1];
			total += board_old[i + 1][j - 1];
			total += board_old[i + 1][j];

			return total;
		}
		else if (i == 0 && j > 0)
		{
			total += board_old[i][j-1];
			total += board_old[i][j + 1];
			total += board_old[i + 1][j + 1];
			total += board_old[i + 1][j];
			total += board_old[i+1][j-1];

			return total;
		}
		else if (i > 0 && j == 0)
		{
			total += board_old[i-1][j];
			total += board_old[i-1][j + 1];
			total += board_old[i][j + 1];
			total += board_old[i + 1][j+1];
			total += board_old[i + 1][j];

			return total;
		}
		else if (i == (x-1) && j > 0)
		{
			total += board_old[i - 1][j];
			total += board_old[i - 1][j + 1];
			total += board_old[i][j + 1];
			total += board_old[i - 1][j - 1];
			total += board_old[i][j - 1];

			return total;
		}
		else if(i > 0 && j == (y-1))
		{
			total += board_old[i - 1][j];
			total += board_old[i - 1][j - 1];
			total += board_old[i][j - 1];
			total += board_old[i + 1][j - 1];
			total += board_old[i + 1][j];

			return total;
		}
		else
		{
			total += board_old[i][j - 1];
			total += board_old[i][j + 1];
			total += board_old[i - 1][j];
			total += board_old[i + 1][j];
			total += board_old[i - 1][j - 1];
			total += board_old[i - 1][j + 1];
			total += board_old[i + 1][j - 1];
			total += board_old[i + 1][j + 1];

			return total;
		}
	}

public:
	Board(const int x, const int y)
		:x(x), y(y)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> d(0, 1);

		board_old = new int*[x];
		board_new = new int*[x];

		for (int k = 0; k < x; ++k)
		{
			board_old[k] = new int[y];
		}

		for (int k = 0; k < x; ++k)
		{
			for (int i = 0; i < y; ++i)
			{
				board_old[k][i] = d(gen);
			}
		}

		for (int k = 0; k < x; ++k)
		{
			board_new[k] = new int[y];
		}

		for (int k = 0; k < x; ++k)
		{
			for (int i = 0; i < y; ++i)
			{
				board_new[k][i] = 0;
			}
		}
	}
	void show_board()
	{
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				std::cout << board_old[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}

	void next_generation()
	{
		int state = -1;
		int neighbors_score = 0;
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				state = board_old[i][j];
				neighbors_score = calculate_neighbors(i, j);
				if (state == 0 && neighbors_score == 3)
				{
					board_new[i][j] = 1;
				}
				else if (state == 1 && (neighbors_score < 2 || neighbors_score > 3))
				{
					board_new[i][j] = 0;
				}
				else
				{
					board_new[i][j] = state;
				}
			}
		}

		std::swap(board_old, board_new);
	}
};
