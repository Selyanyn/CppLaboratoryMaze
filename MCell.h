#pragma once
class Maze;

class MCell
{
	friend Maze;
private:
	MCell();
	bool m_down = false;
	bool m_right = false;
public:
	bool down() const;
	bool right() const;
};

