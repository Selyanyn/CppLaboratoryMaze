#pragma once
#include "MCell.h"

class Maze
{
private:
	MCell* m_field;
	int m_width;
	int m_height;
public:
	Maze(int n, int m);
	~Maze();
	const MCell& cell(int i, int j) const;
	bool hasConnection(int i1, int i2, int j1, int j2);
	bool makeConnection(int i1, int i2, int j1, int j2);
	bool removeConnection(int i1, int i2, int j1, int j2);
	void printMaze();
};

