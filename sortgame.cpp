#include <iostream>
#include <queue>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <math.h>
#include "bfs_dynamic.h"

using namespace std;

array<vector<int>, L> graph;
array<Node, L> Result;
map<int, int> graph_map;

int seq = 0;

int getValue(vector<int> perm)
{
	int value = 0;
	for (auto x: perm)
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

	//for (int i = 1; i <= 8; i++)
		precalc(N_MAX);

	std::map<int, int>::iterator it;
	it = graph_map.find(1234567);
	bfs(it->second, graph, L);

	while (T--)
	{
		int N;
		scanf("%d", &N);

		vector<int> a(N);
		list<int> s;
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &a[i]);
			s.push_back (a[i]);
		}
		s.sort();

		int value = 0;
		int index = 0;
		int norm = 0;
		for (auto& x : s)
		{
			index = (int)pow(10, N);
			for (int i = 0; i < N; i++)
			{
				index /= 10;
				if (a[i] == x)
				{
					value = value + (norm * index);
					break;
				}
			}
			norm++;
		}
		for (int i = N; i < N_MAX; i++)
		{
			value = value * 10 + i;
		}
		it = graph_map.find(value);
		printf("%d\n", Result[it->second].distance);
	}
	system("pause");
	return 0;
}