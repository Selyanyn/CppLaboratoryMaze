#include <iostream>
#include <queue>
#include "Maze.h"
#include "MTreeNode.h"

using namespace std;

MTreeNode buildTree(Maze maze)
{
	auto tree = MTreeNode::beginTree(0, 0);
	auto nodeQueue = queue<MTreeNode*>();
	nodeQueue.push(tree);
	while (nodeQueue.size() != 0)
	{
		auto current = nodeQueue.front();
		if (maze.hasConnection(current->i(), current->j(), current->i(), current->j() + 1))
		{
			current->addChild(current->i(), current->j() + 1);
			nodeQueue.push(current->hasChild(current->i(), current->j() + 1));
		}
		if (maze.hasConnection(current->i(), current->j(), current->i() + 1, current->j()))
		{
			current->addChild(current->i() + 1, current->j());
			nodeQueue.push(current->hasChild(current->i() + 1, current->j()));
		}
		nodeQueue.pop();
	}
	return *tree;
}

void printTree(MTreeNode tree)
{
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0 && j == 0)
			{
				cout << '0';
				continue;
			}
			auto node = tree.hasChild(i, j);
			if (node)
				cout << node->distance();
			else
				cout << 'X';
		}
		cout << '\n';
	}
}

int main()
{
	auto treeMaze = Maze(5, 5);
	for (int n = 0; n < 4; n++)
	{
		for (int i = n; i < 5; i++)
		{
			treeMaze.makeConnection(n, i, n, i + 1);
			treeMaze.makeConnection(i, n, i + 1, n);
		}
		treeMaze.makeConnection(n + 1, n, n + 1, n + 1);
	}
	treeMaze.printMaze();
	auto tree = buildTree(treeMaze);
	printTree(tree);
}
