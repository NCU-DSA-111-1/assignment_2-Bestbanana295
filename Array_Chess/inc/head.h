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
int save;//存儲棋子

//生成棋盤
void chessboardBuilding();
//打印棋盤
void printChessboard();
//判斷是紅棋還是藍棋,紅旗返回1,藍棋返回-1,否則返回0
int redOrBlack(int x,int y);
//紅棋移動
void redMove();
//藍棋移動
void blackMove();
//每種棋子的規則
void rulesOfAllKindsOfChessPieces();
//判斷遊戲結束
void isGameOver();
//判斷是否有旗子
int isFlag(int x,int y);    

//save chesssboard to file
void saveChessboard();

//load chessboard from file
void loadChessboard();

//restart game
void restartGame();

//Chess linklist 
typedef struct Chess
{
    char* chess;
    struct Chess* next;
}Chess;

//Chess linklist head
typedef struct ChessHead
{
    Chess* first;
    Chess* last;
}ChessHead;




