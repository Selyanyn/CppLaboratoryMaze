#include "Maze.h"
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <tuple>
#include <map>

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

bool Maze::areAdjacent(int i1, int i2, int j1, int j2)
{
	return ((i1 >= 0 && i1 < m_width && i2 >= 0 && i2 < m_height
		&& j1 >= 0 && j1 < m_width && j2 >= 0 && j2 < m_height)
		&& (abs(j1 - i1) + abs(j2 - i2) == 1));
}

bool Maze::hasConnection(int i1, int i2, int j1, int j2)
{
	if (areAdjacent(i1, i2, j1, j2))
	{
		if (j2 == i2 && j1 - i1 == 1)
			return cell(i1, i2).right();
		if (j2 - i2 == 1 && j1 == i1)
			return cell(i1, i2).down();
	}
	return false;
}

bool Maze::modifyConnection(int i1, int i2, int j1, int j2, bool type)
{
	if (areAdjacent(i1, i2, j1, j2))
	{
		if (j2 == i2 && j1 - i1 == 1)
		{
			m_field[i1 * m_width + i2].m_right = type;
			return true;
		}
		if ((j2 - i2 == 1 && j1 == i1))
		{
			m_field[i1 * m_width + i2].m_down = type;
			return true;
		}
	}
	return false;
}

bool Maze::makeConnection(int i1, int i2, int j1, int j2)
{
	return modifyConnection(i1, i2, j1, j2, true);
}

bool Maze::removeConnection(int i1, int i2, int j1, int j2)
{
	return modifyConnection(i1, i2, j1, j2, false);
}

map<tuple<bool, bool, bool, bool>, char> pathToSymbol = { {make_tuple(false, false, false, false), char(248)},
														  {make_tuple(false, false, true, true), char(218)},
														  {make_tuple(false, true, false, true), char(179)},
														  {make_tuple(false, true, true, false), char(192)},
														  {make_tuple(false, true, true, true), char(195)},
														  {make_tuple(true, false, true, false), char(196)},
														  {make_tuple(true, false, false, true), char(191)},
														  {make_tuple(true, false, true, true), char(194)},
														  {make_tuple(true, true, false, false), char(217)},
														  {make_tuple(true, true, false, true), char(180)},
														  {make_tuple(true, true, true, false), char(193)},
														  {make_tuple(true, true, true, true), char(197)} };

void Maze::printMaze()
{
	for (int j = 0; j < m_height; j++)
	{
		for (int i = 0; i < m_width; i++)
		{
			auto paths = make_tuple(hasConnection(i - 1, j, i, j), hasConnection(i, j - 1, i, j),
				hasConnection(i, j, i + 1, j), hasConnection(i, j, i, j + 1));
			auto pair = pathToSymbol.find(paths);
			if (pair == pathToSymbol.end())
				cout << char(248);
			else
				cout << pair->second;
		}
		cout << '\n';
	}
}