#include <algorithm>
#include <queue>
#include <array>
#include "bfs.h"

enum COLOR { WHITE, GRAY, BLACK };
using namespace std;

struct Node
{
	int n;
	COLOR color;
	int distance;
	int pi;
};

// int bfs(int s, int g[][N], int length)
int bfs(int s, int g[][N + 1], int length)
{
	queue<Node> Q;
	array<Node, N + 1> L;

	// initialize
	for (int n = 1; n <= length; n++)
	{
		Node node;
		if (n != s)
		{
			node.n = n;
			node.color = WHITE;
			node.distance = INT_MAX;
			node.pi = -1;
		}
		else
		{
			node.n = n;
			node.color = GRAY;
			node.distance = 0;
			node.pi = -1;
			Q.push(node);
		}
		L[n] = node;
	}

	while (!Q.empty())
	{
		Node node = Q.front();
		Q.pop();
		for (int i = 1; i <= length; i++)
		{
			if (g[node.n][i] == 1)
			{
				if (L[i].color == WHITE)
				{
					L[i].distance = L[node.n].distance + 1;
					L[i].pi = node.n;
					L[i].color = GRAY;
					Q.push(L[i]);
				}
			}
		}
		L[node.n].color = BLACK;
	}
	return 1;
}