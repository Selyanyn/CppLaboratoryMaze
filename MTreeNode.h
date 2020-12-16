#pragma once
#include <vector>

class MTreeNode
{
public:
	int i() const;
	int j() const;
	const MTreeNode* parent();
	const MTreeNode* child(int i);
	int distance() const;
	int childCount() const;
	bool addChild(int i, int j);
	MTreeNode* hasChild(int i, int j);
	static MTreeNode* beginTree(int i, int j);
private:
	int m_i;
	int m_j;
	MTreeNode* m_parent;
	std::vector<MTreeNode*> m_children;
	int m_distance;
	MTreeNode(MTreeNode* parent);
};