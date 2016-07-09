#pragma once

#include <array>
#include <vector>
#include <map>

struct Action
{
	std::array<int, 2> action;
	double prob;
};

class TreeNode
{
public:
	TreeNode(TreeNode* parent, double prior);

	void Expansion(std::vector<Action>& actions);
	double Selection();

	void Update(double leaf, double uct);

	double ToValue();

private:
	TreeNode* Parent;
	int Visits;
	double Q, U, P;

	std::map<std::array<int, 2>, TreeNode*> Children;

	friend class MCTS;
};

class MCTS
{
public:
	MCTS();

	void Simulate(int depth, TreeNode* node);

	std::array<int, 2> GetMove();
};