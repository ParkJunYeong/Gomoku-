#include "MCTS.h"

TreeNode::TreeNode(TreeNode* parent, double prior)
	: Parent(parent), P(prior), Visits(0), Q(0), U(prior)
{
}

void TreeNode::Expansion(std::vector<Action>& actions)
{
	for (auto& it : actions)
	{
		if (Children.find(it.action) == Children.end())
		{
			Children[it.action] = new TreeNode(this, it.prob);
		}
	}
}

double TreeNode::Selection()
{
	double now_max = -999;

	for (auto& pr : Children)
	{
		if (pr.second->ToValue() > now_max)
		{
			now_max = pr.second->ToValue();
		}
	}

	return now_max;
}

void TreeNode::Update(double leaf, double uct)
{
	Visits++;
	
	double mean_V = Q * (Visits - 1);
	Q = (mean_V + leaf) / Visits;
	U = uct * P * std::sqrt(Parent->Visits) / (Visits + 1);
}

double TreeNode::ToValue()
{
	return Q + U;
}