#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <random>

class Board {
	sf::Vector2f grid_size;
	const int x, y;
	int** board_old;
	int** board_new;

private:
	int calculate_neighbors(const std::vector<sf::RectangleShape>& grid, const int i, const int j)
	{
		int total = 0;
		int pos_x = -1;
		int pos_y = -1;
		for (int k = -1; k < 2; ++k)
		{
			for (int l = -1; l < 2; ++l)
			{
				pos_x = (i + k + x) % x;
				pos_y = (j + l + y) % y;
				total += board_old[pos_x][pos_y];
			}
		}

		total -= board_old[i][j];

		return total;
	}

	int calculate_neighbors2(const std::vector<sf::RectangleShape>& grid, const int pos_cell)
	{
		int total = 0;
		//POSITIONS -> [N, S, W, E]
		int positions[4];

		//North
		positions[0] = pos_cell - x;
		//South
		positions[1] = pos_cell + x;
		//West
		positions[2] = pos_cell - 1;
		//East
		positions[3] = pos_cell + 1;

		if (positions[0] >= 0)
		{
			//North
			grid[positions[0]].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if(positions[1] < x*y)
		{
			//South
			grid[positions[1]].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if (pos_cell % x != 0)
		{
			//West
			grid[positions[2]].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if ((pos_cell + 1) % x != 0)
		{
			//East
			grid[positions[3]].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if ((positions[0] - 1 >= 0) && (pos_cell % x != 0))
		{
			//North-West
			grid[positions[0] - 1].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if ((positions[0] + 1 >= 0) && ((pos_cell + 1) % x != 0))
		{
			//North-East
			grid[positions[0] + 1].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if ((positions[1] + x < x*y) && ((pos_cell+1) % x != 0))
		{
			//South-East
			grid[positions[1] - 1].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		if ((positions[1] + x < x * y) && (pos_cell % x != 0))
		{
			//South-East
			grid[positions[1] + 1].getFillColor() == sf::Color::White ? total += 1 : total + 0;
		}
		
		//int center_score = grid[pos_cell].getFillColor() == sf::Color::White ? 1 : 0;
		//total -= center_score;

		return total;
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

	void next_generation(std::vector<sf::RectangleShape>& rw)
	{
		std::vector<sf::RectangleShape> rect_vec = rw;
		int state = -1;
		int state1 = -1;
		int neighbors_score = 0;
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				//state = board_old[i][j];
				state1 = rw[j * x + i].getFillColor() == sf::Color::White ? 1 : 0;
				neighbors_score = calculate_neighbors2(rw, j*x + i);
				std::cout << neighbors_score << " ";
				if (state1 == 0 && neighbors_score == 3)
				{
					board_new[i][j] = 1;
					rect_vec[j * x + i].setFillColor(sf::Color::White);
				}
				else if (state1 == 1 && (neighbors_score < 2 || neighbors_score > 3))
				{
					board_new[i][j] = 0;
					rect_vec[j * x + i].setFillColor(sf::Color::Black);
				}
				else
				{
					board_new[i][j] = state1;
					rect_vec[j * x + i].setFillColor(rw[j * x + i].getFillColor());

				}
			}
		}

		//std::swap(board_old, board_new);
		std::swap(rw, rect_vec);
	}

	std::vector<sf::RectangleShape> setup_grid(const sf::Vector2u& rw)
	{
		grid_size = sf::Vector2f(rw.x / x, rw.y / y);

		std::vector<sf::RectangleShape> grid;

		for (int k = 0; k < x; ++k)
		{
			for (int j = 0; j < y; ++j)
			{
				sf::RectangleShape cell(grid_size);
				cell.setFillColor(sf::Color::Black);
				cell.setOutlineColor(sf::Color::Black);
				cell.setOutlineThickness(1.5f);
				cell.setPosition(grid_size.x * k, grid_size.y * j);
				grid.push_back(cell);
			}
		}

		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				if (board_old[j][i] == 1)
				{
					grid[i*x + j].setFillColor(sf::Color::White);
				}
			}
		}

		return grid;
	}
};
