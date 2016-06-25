#include <algorithm>
#include <ctime>
#include <iostream>
#include <list>
#include <cmath>
#include "proceduralmaze.h"

ProceduralMaze::ProceduralMaze(int width, int height)
{
	std::srand(std::time(NULL));

	this->width = width % 2 == 0 ? width + 1 : width;
	this->height = height % 2 == 0 ? height + 1 : height;

	clearGrid();
}

void ProceduralMaze::generate()
{
	clearGrid();
	int x = std::rand() % (width - 2) + 1;
	int y = std::rand() % (height - 2) + 1;

	// Odd start numbers to make sure we have borders
	x = x % 2 == 0 ? x + 1 : x;
	y = y % 2 == 0 ? y + 1 : y;

	std::pair<int, int> cell_pos = std::make_pair(x, y);
	grid[cell_pos] = Tile::EMPTY;

	std::vector<std::pair<int, int>> frontiers = getAdjCells(cell_pos, Tile::WALL);
	while (!frontiers.empty()) {
		int index = std::rand() % frontiers.size();
		cell_pos = frontiers[index];
		frontiers.erase(frontiers.begin() + index);

		std::vector<std::pair<int, int>> neighboors = getAdjCells(cell_pos, Tile::EMPTY);
		if (neighboors.empty()) {
			continue;
		}

		index = std::rand() % neighboors.size();
		std::pair<int, int> neighboor = neighboors[index];
		int passage_x = (neighboor.first - cell_pos.first)/2 + cell_pos.first;
		int passage_y = (neighboor.second - cell_pos.second)/2 + cell_pos.second;

		grid[std::make_pair(passage_x, passage_y)] = Tile::EMPTY;
		grid[cell_pos] = Tile::EMPTY;
		for (auto value : getAdjCells(cell_pos, Tile::WALL)) {
			if (std::find(frontiers.begin(), frontiers.end(), value) == frontiers.end()) {
				frontiers.push_back(value);
			}
		}
	}

	std::pair<int, int> entry_pos = std::make_pair(1, 0);
	grid[entry_pos] = Tile::ENTRY;

	std::pair<int, int> exit_pos = std::make_pair(width - 2, height - 1);
	grid[exit_pos] = Tile::EXIT;
}

void ProceduralMaze::clearGrid()
{
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			grid[std::make_pair(x, y)] = Tile::WALL;
		}
	}
}

std::vector<std::pair<int, int>> ProceduralMaze::getAdjCells(std::pair<int, int> center, Tile tile_state)
{
	const std::vector<std::pair<int, int>>& pos = {
		std::make_pair(center.first, center.second - 2),
		std::make_pair(center.first + 2, center.second),
		std::make_pair(center.first, center.second + 2),
		std::make_pair(center.first - 2, center.second),
	};

	std::vector<std::pair<int, int>> result;
	for (auto adj_pos : pos) {
		try {
			if (grid.at(adj_pos) == tile_state) {
				result.push_back(adj_pos);
			}
		} catch (std::out_of_range) { }
	}

	return result;
}

void ProceduralMaze::print() {
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			char c = ' ';
			switch (grid[std::make_pair(x, y)]) {
				case Tile::ENTRY:
					c = 'E';
					break;
				case Tile::EXIT:
					c = 'S';
					break;
				case Tile::WALL:
					c = '#';
					break;
				case Tile::EMPTY:
					c = ' ';
					break;
				default:
					break;
			}

			std::cout << c;
		}
		std::cout << std::endl;
	}
}
