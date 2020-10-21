#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static int g_count = 0;

int noDanger(int row, int col, int (*chess)[8])
{
	int i, j;
	//判断每一列是否有皇后
	for (i = 0; i < 8; i++) {
		if (chess[i][col] == 1)
			return 0;
	}

	int plus, minus;
	plus = row + col;//同一条右斜线上点特点 横纵坐标和相同
	minus = row - col;//同一条左斜线上点的特点 横纵坐标差相同
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if ((i + j == plus || i - j == minus) && chess[i][j] == 1)
				return 0;
		}
	}

	return 1;
}

void EightQueen(int row, int col, int (*ppChess)[8])
{
	int i, j;
	int chess[8][8];

	// 赋值上一次放置皇后的棋盘
	for (i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess[i][j] = ppChess[i][j];
		}
	}

	if (row == 8) {// 计数
		g_count++;
	} else {
		for (j = 0; j < col; j++) //遍历 ROW 行的每一个元素 进行判断

			if (noDanger(row, j, ppChess)) {

				for (i = 0; i < 8; i++) {
					*(*(chess + row) + i) = 0;
				}

				*(*(chess + row) + j) = 1;

				EightQueen(row + 1, col, chess); //向下一行遍历
			}
	}
}

int main(int argc, char const *argv[])
{
	int i, j;
	int chess[8][8] = {0};

	EightQueen(0, 8, chess);

	printf("%d\n", g_count);

	return 0;
}
