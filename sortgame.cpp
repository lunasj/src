#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <array>

#include <map>
#include <limits.h>
#include <math.h>

#define N_MAX	(8)
#define L		(8*7*6*5*4*3*2*1)	// 40320

using namespace std;

enum COLOR { WHITE, GRAY, BLACK };

struct Node
{
	int n;
	COLOR color;
	int distance;
	int pi;
};

array<vector<int>, L> graph;
array<Node, L> Result;
map<int, int> graph_map;

int seq = 0;

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

int getValue(vector<int> perm)
{
	int value = 0;
	for (auto x : perm)
	{
		value = value * 10 + x;
	}
	return value;
}

int getMappedValue(vector<int> perm)
{
	int curr;
	int value;
	map<int, int>::iterator it;

	value = getValue(perm);
	if ((it = graph_map.find(value)) == graph_map.end())
	{
		curr = seq;
		graph_map[value] = seq++;
	}
	else
	{
		curr = it->second;
	}
	return curr;
}

void precalc(int n)
{
	int value;
	map<vector<int>, int> q_map;

	vector<int> perm(n);
	value = 0;
	for (int i = 0; i < n; i++)
	{
		perm[i] = i;
	}
	queue<vector<int>> q;
	q.push(perm);
	q_map[perm] = 1;

	getMappedValue(perm);

	while (!q.empty())
	{
		int size = q.size();
		while (size--)
		{
			vector<int> here = q.front();
			q.pop();

			map<vector<int>, int>::iterator it;
			int curr = getMappedValue(here);

			if (graph[curr].size() != 0)
				continue;

			for (int i = 0; i < n; i++)
			{
				for (int j = i + 2; j <= n; j++)
				{
					reverse(here.begin() + i, here.begin() + j);

					if ((it = q_map.find(here)) == q_map.end())
					{
						q.push(here);
						q_map[here] = 1;
					}
					int map_value = getMappedValue(here);
					graph[curr].push_back(map_value);
					reverse(here.begin() + i, here.begin() + j);
				}
			}
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	precalc(N_MAX);

	vector<int> eight = { 0,1,2,3,4,5,6,7 };
	bfs(getMappedValue(eight), graph, L);

	while (T--)
	{
		int N;
		scanf("%d", &N);

		vector<int> a(N);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &a[i]);
		}

		vector<int> b(N_MAX);
		for (int i = 0; i < N; i++)
		{
			int small = 0;
			for (int j = 0; j < N; j++)
				if (a[j] < a[i])
					small++;
			b[i] = small;
		}
		for (int i = N; i < N_MAX; i++)
		{
			b[i] = i;
		}

		printf("%d\n", Result[getMappedValue(b)].distance);
	}
	//	system("pause");
	return 0;
}
