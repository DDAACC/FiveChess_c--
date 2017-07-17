#include"CEveluation.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

static BYTE p[15][15];
static CEveluation eve;
static int difficult;

struct ChessPos {
	int x;
	int y;
};

static ChessPos RES;

void go(int x, int y)
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ChessDisplay(BYTE Board[15][15])
{
	cout << "  ";
	for (int i = 0; i < 9; i++)
	{
		cout << i + 1 << " ";
	}
	cout << "a b c d e f";
	cout << endl;
	for (int j = 1; j <= 9; j++)
	{
		cout << j << endl;
	}
	cout << "a" << endl << "b" << endl << "c" << endl << "d" << endl << "e" << endl << "f";
	for (int i = 0; i < 15; i++)
	{
		go(3, i + 2);
		for (int j = 0; j < 15; j++)
		{
			if (Board[i][j] == 1)
			{
				cout << "X ";
			}
			if (Board[i][j] == 0xff)
			{
				cout << "+ ";
			}
			if (Board[i][j] == 0)
			{
				cout << "0 ";
			}
		}
	}
	cout << endl;

}


int AlphaBeta(int depth, int alpha, int beta, int turn) {
	if (depth == 0) {
		if (difficult == 1 || difficult==3)
		{
			return eve.Eveluate(p, 1);
		}
		else
		{
			return eve.Eveluate(p, 0);
		}
	}
	//GenerateLegalMoves();
	int best = -9999999;
	vector<ChessPos> Moves;
	Moves.swap(vector<ChessPos>());
	int maxX = 0, maxY = 0, minX = 14, minY = 14;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (p[i][j] != 0xff)
			{
				if (i >= maxX)
					maxX = i;
				if (i <= minX)
					minX = i;
				if (j >= maxY)
					maxY = j;
				if (j <= minY)
					minY = j;
			}
		}
	}

	int Li, Ri, Tj, Bj;
	Li = minX - 1;
	Ri = maxX + 1;
	Bj = maxY + 1;
	Tj = minY - 1;
	if (Li < 0)
		Li = 0;
	if (Ri > 14)
		Ri = 14;
	if (Tj < 0)
		Tj = 0;
	if (Bj > 14)
		Bj = 14;
	for (int i = Li; i <= Ri; i++)
	{
		for (int j = Tj; j <= Bj; j++)
		{
			if (p[i][j] == 0xFF)
			{
				ChessPos temp;
				temp.x = i;
				temp.y = j;
				Moves.push_back(temp);
			}
		}
	}
	while (!Moves.empty())
	{
		//MakeNextMove();
		int mx = (*(Moves.end() - 1)).x;
		int my = (*(Moves.end() - 1)).y;
		Moves.erase(Moves.end() - 1);
		p[mx][my] = turn;
		int temp;
		if (turn == 0)
			temp = 1;
		if (turn == 1)
			temp = 0;

		int val = -AlphaBeta(depth - 1, -beta, -alpha, temp);
		if (depth == difficult&&val > best)
		{
			best = val;
			RES.x = mx;
			RES.y = my;
		}
		//UnmakeMove();
		p[mx][my] = 0xFF;
		if (val >= beta) {
			return beta;
		}
		if (val > alpha) {
			alpha = val;
		}
	}
	return alpha;
}


int main()
{

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			p[i][j] = 0xFF;
	int x, y;
	int flag = 0;
	cout << "请选择难度(1-4)" << endl;
	cout << "1 简单的电脑" << endl;
	cout << "2 中等的电脑" << endl;
	cout << "3 令人发狂的电脑" << endl;
	cout << "4 不可战胜的电脑" << endl;
	cin >> difficult;
	while (difficult < 1 || difficult>4)
	{
		cout << "请重新输入一个1-4之间的数字" << endl;
		cin >> difficult;
	}
	int final;
	while (1)
	{
		BYTE board[15][15];
		system("cls");
		ChessDisplay(p);
		if (flag != 0)
		{
			cout << "电脑落子: (" << RES.x + 1 << "," << RES.y + 1 << ")  ";
		}
		cout << "你的回合,输入落子的坐标 x,y (0-14):" << endl;
		cin >> x >> y;
		p[x - 1][y - 1] = 1;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
				board[i][j] = p[i][j];
		}
		system("cls");
		ChessDisplay(p);
		final = AlphaBeta(difficult, -9999999, 9999999, 0);
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
				p[i][j] = board[i][j];
		}
		if (final > 5000 || final < -5000)
		{
			break;
		}
		int t = RES.x;
		int n = RES.y;
		p[t][n] = 0;
		flag++;
	}
	if (final < -9000)
	{
		cout << "恭喜,你战胜了电脑";
	}
	if (final > 9000)
	{
		int t = RES.x;
		int n = RES.y;
		p[t][n] = 0;
		system("cls");
		ChessDisplay(p);
		cout << "电脑落子 (" << t+1 << "," << n+1 << ") 你失败了!!";
	}
	system("pause");

}

