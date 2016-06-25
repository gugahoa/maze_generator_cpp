#ifndef __PROCEDURALMAZE_H__
#define __PROCEDURALMAZE_H__

#include <map>
#include <vector>

enum Tile {
	EMPTY,
	WALL,
	ENTRY,
	EXIT,
};

class ProceduralMaze
{
	private:
		int width;
		int height;
		std::map<std::pair<int, int>, Tile> grid;

		void generateLight();
		void clearGrid();
		std::vector<std::pair<int, int>> getAdjCells(std::pair<int, int> center, Tile tile_state);

	public:
		ProceduralMaze(int width, int height);

		void generate();
		void print();

		std::map<std::pair<int, int>, Tile> getGrid() { return grid; }
};

#endif
