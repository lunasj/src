#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BOARDSIZE 5
#define WORDLEN 10
using namespace std;

char board[BOARDSIZE+1][BOARDSIZE+1];
bool cache[BOARDSIZE][BOARDSIZE][WORDLEN + 1];

int direction[8][2] = { {-1, -1}, {-1,0}, {-1, 1}, {0, -1}, {0, 1}, {1,-1}, {1,0},{1,1} };


void initBoard()
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			board[i][j] = getchar();
		}
		getchar();
	}
}

bool inRange(int y, int x)
{
	if (x >= 0 && x < BOARDSIZE && y >= 0 && y < BOARDSIZE)
		return true;
	else
		return false;
	
}

bool hasWord(int y, int x, char *word)
{
	int nextY;
	int nextX;

	if (!cache[y][x][strlen(word)])
		return false;
	if (!inRange(y, x))
		return false;

	if (board[y][x] != word[0])
		return false;

	if (strlen(word) == 1)
		return true;

	for (int i = 0; i < 8; i++)
	{
		nextY = y + direction[i][0];
		nextX = x + direction[i][1];

		if (hasWord(nextY, nextX, word + 1))
			return true;
	}

	cache[y][x][strlen(word)] = false;
	return false;
}

bool boggle(char *searchWord)
{
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (hasWord(i, j, searchWord))
				return true;
		}
	}
	return false;
}

int main()
{
	int T;
	scanf("%d\n", &T);

	while (T--)
	{

		initBoard();

		int N;
		scanf("%d\n", &N);

		char testWord[10][WORDLEN + 2];

		for (int i = 0; i < N; i++)
		{
			scanf("%s", testWord[i]);
			
		}
		for (int i = 0; i < N; i++)
		{
			memset(cache, 1, BOARDSIZE * BOARDSIZE * (WORDLEN + 1));
			printf("%s %s\n",testWord[i],boggle(testWord[i])?"YES":"NO");
		}
		getchar();
	}

	return 0;
}