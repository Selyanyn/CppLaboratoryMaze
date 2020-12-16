#include "Maze.h"
#include <algorithm>
#include <iostream>

using namespace std;

Maze::Maze(int n, int m)
{
	m_field = new MCell[n * m];
	m_width = n;
	m_height = m;
}

Maze::~Maze()
{
	delete[] m_field;
}

const MCell& Maze::cell(int i, int j) const
{
	return m_field[i * m_width + j];
}

bool Maze::hasConnection(int i1, int i2, int j1, int j2)
{
	if ((i1 >= 0 && i1 < m_width && i2 >= 0 && i2 < m_height
		&& j1 >= 0 && j1 < m_width && j2 >= 0 && j2 < m_height))
	{
		if (j2 == i2 && j1 - i1 == 1)
			return cell(i1, i2).right();
		if (j2 - i2 == 1 && j1 == i1)
			return cell(i1, i2).down();
	}
	return false;
}

bool Maze::makeConnection(int i1, int i2, int j1, int j2)
{
	if ((i1 >= 0 && i1 < m_width && i2 >= 0 && i2 < m_height
		&& j1 >= 0 && j1 < m_width && j2 >= 0 && j2 < m_height))
	{
		if (j2 == i2 && abs(j1 - i1) == 1)
		{
			m_field[min(i1, j1) * m_width + i2].m_right = true;
			return true;
		}
		if (abs(j2 - i2) == 1 && j1 == i1)
		{
			m_field[i1 * m_width + min(i2, j2)].m_down = true;
			return true;
		}
	}
	return false;
}

bool Maze::removeConnection(int i1, int i2, int j1, int j2)
{
	if ((i1 >= 0 && i1 < m_width && i2 >= 0 && i2 < m_height
		&& j1 >= 0 && j1 < m_width && j2 >= 0 && j2 < m_height))
	{
		if (j2 == i2 && abs(j1 - i1) == 1)
		{
			m_field[min(i1, j1) * m_width + i2].m_right = false;
			return true;
		}
		if (abs(j2 - i2) == 1 && j1 == i1)
		{
			m_field[i1 * m_width + min(i2, j2)].m_down = false;
			return true;
		}
	}
	return false;
}

enum Directions
{
	None = 0,
	Left = 1,
	Up = 2,
	Right = 4,
	Down = 8,
	LeftUp = 3,
	LeftRight = 5,
	UpRight = 6,
	LeftUpRight = 7,
	LeftDown = 9,
	UpDown = 10,
	LeftUpDown = 11,
	RightDown = 12,
	LeftRightDown = 13,
	UpRightDown = 14,
	LeftUpRightDown = 15,
};

char pathToSymbol[16] = { char(248), char(248), char(248), char(217),
						  char(248), char(196), char(192), char(193), 
						  char(248), char(191), char(179), char(180), 
						  char(218), char(194), char(195), char(197), };

void Maze::printMaze()
{
	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			auto paths = Directions(hasConnection(i - 1, j, i, j) + 2 * hasConnection(i, j - 1, i, j) +
				4 * hasConnection(i, j, i + 1, j) + 8 * hasConnection(i, j, i, j + 1));
			cout << pathToSymbol[paths];
		}
		cout << '\n';
	}
}