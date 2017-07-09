#pragma once
#include <array>
#include <list>
#include <vector>
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


int bfs(int s, array<vector<int>, L > g, int length);
