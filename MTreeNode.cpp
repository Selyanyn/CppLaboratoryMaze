#include "MTreeNode.h"
#include <math.h>
using namespace std;

MTreeNode::MTreeNode(MTreeNode* parent)
{
	m_parent = parent;
	if (parent)
		m_distance = m_parent->distance() + 1;
	else
		m_distance = 0;
	m_children = vector<MTreeNode*>();
}

int MTreeNode::i() const
{
	return m_i;
}

int MTreeNode::j() const
{
	return m_j;
}

int MTreeNode::distance() const
{
	return m_distance;
}

const MTreeNode* MTreeNode::parent()
{
	return m_parent;
}

int MTreeNode::childCount() const
{
	return m_children.size();
}

const MTreeNode* MTreeNode::child(int i)
{
	return m_children[i];
}

bool MTreeNode::addChild(int i, int j)
{
	if ((abs(m_i - i) == 1) ^ (abs(m_j - j) == 1))
	{
		auto child = new MTreeNode(this);
		child->m_i = i;
		child->m_j = j;
		m_children.push_back(child);
		return true;
	}
	else
		return false;
}

MTreeNode* MTreeNode::hasChild(int i, int j)
{
	for (int c = 0; c < m_children.size(); c++)
		if (m_children[c]->m_i == i && m_children[c]->m_j == j)
			return m_children[c];
		else
		{
			auto result = m_children[c]->hasChild(i, j);
			if (result)
				return result;
		}
	return nullptr;
}

MTreeNode* MTreeNode::beginTree(int i, int j)
{
	auto tree = new MTreeNode(nullptr);
	tree->m_i = i;
	tree->m_j = j;
	return tree;
}