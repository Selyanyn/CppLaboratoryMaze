#include <iostream>
#include "Maze.h"

int main()
{
	auto maze = Maze(5, 5);
	for (int i = 0; i < 4; i++)
	{
		maze.makeConnection(i, i, i + 1, i);
		maze.makeConnection(i + 1, i, i + 1, i + 1);
	}
	maze.printMaze();
}
