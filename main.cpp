#include "proceduralmaze.h"

int main(void) {
	ProceduralMaze maze = ProceduralMaze(39, 29);
	maze.generate();
	maze.print();
	return 0;
}
