#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define NumberofChess 9
#define R(piece) "\033[31m"#piece"\033[0m"//紅色棋子
//#define B(piece) "\033[30m"#piece"\033[0m"//黑色棋子
#define B(piece) "\033[36m"#piece"\033[0m"//藍色棋子
#define CROSS "\033[33m十\033[0m"
#define BCROSS "\033[32m十\033[0m"
#define RCROSS "\033[35m十\033[0m"

//定義外部變量,棋盤坐標
char* array[9][9];
int xi,yi;//要移動的棋子
int xj,yj;//移動的目標位置
bool isStandard = 1;//是否符合規則，初始值1，符合
bool gameOverSign = 1;//遊戲是否結束，0結束
bool restart = 0;