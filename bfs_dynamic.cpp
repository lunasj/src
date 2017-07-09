#include <algorithm>
#include <queue>

#include "bfs_dynamic.h"

extern array<Node, L> Result;

int bfs(int s, array<vector<int>, L > g, int length)
{
	queue<Node> Q;

	// initialize
	for (int n = 0; n < length; n++)
	{
		Node node;
		node.n = n;
		node.pi = -1;
		if (n != s)
		{
			node.color = WHITE;
			node.distance = INT_MAX;
		}
		else
		{
			node.color = GRAY;
			node.distance = 0;
			Q.push(node);
		}
		Result[n] = node;
	}

	while (!Q.empty())
	{
		Node node = Q.front();
		Q.pop();
		for (size_t i = 0; i < g[node.n].size(); i++)
		{
			int n_num = g[node.n].at(i);
			if (Result[n_num].color == WHITE)
			{
				Result[n_num].distance = Result[node.n].distance + 1;
				Result[n_num].pi = node.n;
				Result[n_num].color = GRAY;
				Q.push(Result[n_num]);
			}
		}
		Result[node.n].color = BLACK;
	}
	return 1;
}