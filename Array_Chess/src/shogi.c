

#include "head.h"
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




//retract last move
void retract()
{
    if (head->first == NULL) {
        printf("沒有棋子可以悔棋!\n");
        return;
    }
    Chess* temp = head->last;
    head->last = temp->next;
    free(temp);
    printChess(head);
}



//**************************主函數******************************
int main()
{   
    
    //load chessboard from file
    loadChessboard();
    //判斷是否有棋盤
    if (array[0][0] == NULL) {
        //生成棋盤
        chessboardBuilding();
    }
    //生成棋盤
    //打印棋盤
    printChessboard();
    //開始下棋
    int turn = -1;
    while (gameOverSign) {
        isStandard = 1;
        turn *= (-1);//雙方交替下棋
        switch (turn) {
            case 1:
                redMove();
                turn = (restart) ? (turn*-1) : turn;
                break;
            case -1:
                blackMove();
                turn = (restart) ? (turn*-1) : turn;
                break;
        }
        isGameOver();
        
    }
    printf("遊戲結束!\n");
    
  
    
}


struct node {
    int num;
    struct node* left;
    struct node* right;
};

//生成棋盤
void chessboardBuilding()
{

    for (int i = 0; i < NumberofChess; i ++) {
        for (int j = 0; j < 9 ; j ++) {
            array[i][j] = CROSS;

        }
        printf("\n");
    }
    

    array[0][0] = array[0][8] = R(香);
    array[0][1] = array[0][7] = R(桂);
    array[0][2] = array[0][6] = R(銀);
    array[0][3] = array[0][5] = R(金);
    array[0][4] = R(將);
    array[1][1] = R(飛);
    array[1][7] = R(角);
    for(int i=0;i<NumberofChess;i++){
        array[2][i] = R(兵);
    }

    
    array[8][0] = array[8][8] = B(香);
    array[8][1] = array[8][7] = B(桂);
    array[8][2] = array[8][6] = B(銀);
    array[8][3] = array[8][5] = B(金);
    array[8][4] = B(將);
    array[7][7] = B(飛);
    array[7][1] = B(角);
  for(int i=0;i<NumberofChess;i++){
        array[6][i] = B(兵);
    }
}

//棋盤

void printChessboard()
{   system("clear");
    printf("   1  2  3  4  5  6  7  8  9\n");
    for (int i = 0; i < NumberofChess; i++)
    {
        printf("%d", i + 1);
        for (int j = 0; j < 9; j++)
        {
            printf(" %s", array[i][j]);
        }
        printf("\n");
    }
}


//判斷是紅棋還是藍棋,紅旗返回1,藍棋返回-1,否則返回0
int redOrBlack(int x,int y)
{
    if (array[x][y] == R(香) || array[x][y] == R(桂) || array[x][y] == R(銀) || array[x][y] == R(金) || array[x][y] == R(將) || array[x][y] == R(角) ||array[x][y] == R(飛)|| array[x][y] == R(兵))
    {
        return  1;
    }
    else if (array[x][y] == B(香) || array[x][y] == B(桂) || array[x][y] == B(銀) || array[x][y] == B(金) || array[x][y] == B(將) || array[x][y] == B(角)|| array[x][y] == R(飛) || array[x][y] == B(兵))
    {
        return -1;
    }
    else
        return 0;
}

//紅棋移動
void redMove()
{
    if (restart) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 0;
    }
    
    printf("[紅棋]請輸入你要移動的棋子:\n");
    scanf("%d %d",&xi,&yi);
    printf("[紅棋]請輸入你要放置的位置:\n");
    scanf("%d %d",&xj,&yj);
    printf("是否要儲存棋盤?(1:是 0:否)\n");
    scanf("%d",&save);
    rulesOfAllKindsOfChessPieces();
    printChessboard();
    if (save) {
        saveChessboard();
    }
}

//藍棋移動
void blackMove()
{
    if (restart) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 0;
    }
    printf("[藍棋]請輸入你要移動的棋子:\n");
    scanf("%d %d",&xi,&yi);
    printf("[藍棋]請輸入你要放置的位置:\n");
    scanf("%d %d",&xj,&yj);
    printf("是否要儲存棋盤?(1:是 0:否)\n");
    scanf("%d",&save);
    rulesOfAllKindsOfChessPieces();
    printChessboard();
    if (save){
        saveChessboard();
    }
}

//判斷遊戲結束
void isGameOver()
{
    bool sign_r = 0;
    bool sign_b = 0;
    for (int i = 0; i < NumberofChess; i ++) {
        for (int j = 0; j < 9; j ++) {
            if (array[i][j] == R(將)) {
                sign_r = 1;
            }
            else if (array[i][j] == B(將))
            {
                sign_b = 1;
            }
        }
    }
    if ((sign_r == 0)||(sign_b == 0)) {
        gameOverSign = 0;
    }
    
}

//每種棋子的規則
void rulesOfAllKindsOfChessPieces()
{
//R（香）----------------------------------------
    if (array[xi][yi] == R(香))
    {
        if (yi == yj)//列坐標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目標位置之間有棋子，則不符合規則
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[xi][yi] != CROSS)
                    isStandard = 0;
            }
        }

        
        if ((yi == yj)&& isStandard && (redOrBlack(xj, yj) != 1))//如果棋子直行、沒有犯規且落點不是紅棋，可以移動
        {
            
            array[xi][yi] = CROSS;
            array[xj][yj] = R(香);
        }
        else
        {
            restart = 1;
        }
    }


//B（香）----------------------------------------
    else if (array[xi][yi] == B(香))
    {
        
        if (yi == yj)//列坐標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {

                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目標位置之間有棋子，則不符合規則
            }
            for (int i = xi-1; i > xj; i --)
            {
 
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }

        if (( yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、沒有犯規且落點不是紅棋，可以移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(香);
        }
        else
        {
            restart = 1;
        }
    }

//R（桂）----------------------------------------
    else if (array[xi][yi] == R(桂))
    {
        if ((redOrBlack(xj, yj) != 1) && ( (xj == xi+2 && yj == yi-1) || (xj == xi+2 && yj == yi+1)))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(桂);
        }
        else
        {
            restart = 1;
        }
    }
    
//B（桂）----------------------------------------
    else if (array[xi][yi] == B(桂))
    {
        if ((redOrBlack(xj, yj) != -1) && ( (xj == xi-2 && yj == yi+1 ) || (xj == xi-2 && yj == yi-1)))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(桂);
        }
        else
        {
            restart = 1;
        }
    }
    

//R (角)----------------------------
    else if (array[xi][yi] == R(角))
    {

        for (int i ; i < 5;i++){
            ( (xj == xi-i && yj == yi-i ) || (xj == xi+i && yj == yi+i));
        }
        if ((redOrBlack(xj, yj) != -1) )//如果棋子斜行、沒有犯規且落點不是紅棋，可以移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(角);
        }
        else
        {
            restart = 1;
        }
    }
    

//B (角)
    else if (array[xi][yi] == B(角))
    {
        int count = 0;//起始位置間棋子的個數
        if (yi == yj)//列坐標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (redOrBlack(i, yi) != 0)
                    count++;
                
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (redOrBlack(i, yi) != 0)
                    count++;
            }
        }
        else if (xi == xj)//行坐標不變，同行移動
        {
            for (int i = yi+1; i < yj; i ++)
                if (redOrBlack(xi, i) != 0)
                    count++;
            for (int i = yi-1; i > yj; i --)
                if (redOrBlack(xi, i) != 0)
                    count++;
        }
        
        if ((xi == xj || yi == yj)&& (count <= 1) && redOrBlack(xj, yj) != -1)//如果棋子直行、沒有犯規且落點不是紅棋，可以移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(角);
        }
        else
        {
            restart = 1;
        }
    }
//R(飛)
     else if (array[xi][yi] == R(飛))
    {
        
        if (yi == yj)//列坐標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目標位置之間有棋子，則不符合規則
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐標不變，同行移動
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、沒有犯規且落點不是紅棋，可以移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(飛);
        }
        else
        {
            restart = 1;
        }
    }
//B(飛)
    else if (array[xi][yi] == B(飛))
    {
        
        if (yi == yj)//列坐標不變，同列移動
        {
            for (int i = xi+1; i < xj; i ++)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[i][yi] != CROSS)
                    isStandard = 0;//如果初始位置和目標位置之間有棋子，則不符合規則
            }
            for (int i = xi-1; i > xj; i --)
            {
                if (i == 5)
                    continue;//如果行等於5，跳過
                if (array[i][yi] != CROSS)
                    isStandard = 0;
            }
        }
        else if (xi == xj)//行坐標不變，同行移動
        {
            for (int i = yi+1; i < yj; i ++)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
            for (int i = yi-1; i > yj; i --)
                if (array[xi][i] != CROSS)
                    isStandard = 0;
        }
        if ((xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != -1)//如果棋子直行、沒有犯規且落點不是紅棋，可以移動
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(飛);
        }
        else
        {
            restart = 1;
        }
    }
    
//R（兵）----------------------------------------
    else if (array[xi][yi] == R(兵))
    {
        if (xi > xj)
            isStandard = 0;

        if (xi > 4) {
            if ((xj == xi+1 && yi ==yj)|| (xj == xi && yi ==yj+1)||(xj == xi && yi ==yj-1))
            {
                
            }
            else
                isStandard = 0;
        }
        if (xj == xi+1 && (xi == xj || yi == yj)&& isStandard && redOrBlack(xj, yj) != 1)//
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R (兵);
        }
        else
        {
            restart = 1;
        }
    }
    
//B（兵）----------------------------------------
    else if (array[xi][yi] == B(兵))
    {
        if (xi < xj)
            isStandard = 0;//如果倒退，則不符合規範

        if (xi < 4) {
            if ((xj == xi-1 && yi ==yj)|| (xj == xi && yi ==yj+1)||(xj == xi && yi ==yj-1))
            {
                
            }
            else
                isStandard = 0;
        }
        if (xj == xi-1 && isStandard && redOrBlack(xj, yj) != -1)//
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(兵);
        }
        else
        {
            restart = 1;
        }
    }

//R（銀）----------------------------------------
    else if (array[xi][yi] == R(銀))
    {
        if ((xj == xi+1 && yj == yj+1 )&&(redOrBlack(xj, yj) != 1)  || (xj == xi+1 && yj == yi &&redOrBlack(xj, yj) != 1) || (xj == xi+1 && yj == yi-1 &&redOrBlack(xj, yj) != 1) || (xj == xi-1 && yj == yi-1 &&redOrBlack(xj, yj) != 1)|| (xj == xi-1 && yj == yi+1 &&redOrBlack(xj, yj) != 1))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(銀);
        }
        else
        {
            restart = 1;
        }
    }
    
//B（銀）----------------------------------------
    else if (array[xi][yi] == B(銀))
    {
        if (xj == xi-1 && yj == yi+1 && (redOrBlack (xj,yj)!=1)||xj == xi-1 && yj == yi-1 && ( redOrBlack (xj,yj)!=1)||xj == xi-1 && yj == yi && (redOrBlack (xj,yj)!=1) ||xj == xi+1 && yj+1 == yi && (redOrBlack (xj,yj)!=1)|| xj == xi+1 && yj-1 == yi && (redOrBlack (xj,yj)!=1) )
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(銀);
        }
        else
        {
            restart = 1;
        }
    }

//R（金）----------------------------------------
    else if (array[xi][yi] == R(金))
    {
        if (xj == xi+1 && yj == yi+1 && (redOrBlack(xj,yj)!=1)||xj == xi+1 && yj == yi-1 && (redOrBlack(xj,yj)!=1)||xj == xi+1 && yj == yi && (redOrBlack(xj,yj)!=1) ||xj == xi && yj+1 == yi && (redOrBlack(xj,yj)!=1) ||xj == xi && yj-1 == yi && (redOrBlack (xj,yj)!=1) ||xj == xi-1 && yj == yi && (redOrBlack (xj,yj)!=1) )
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(金);
        }
        else
        {
            restart = 1;
        }
    }

//B（金）----------------------------------------
    else if (array[xi][yi] == B(金))
    {	//八方除了斜後方
        if (xj == xi-1 && yj == yi+1 && (redOrBlack (xj,yj)!=-1)||xj == xi-1 && yj == yi-1 && (redOrBlack (xj,yj)!=-1)||xj == xi-1 && yj == yi && (redOrBlack (xj,yj)!=-1) ||xj == xi && yj+1 == yi && (redOrBlack (xj,yj)!=-1) ||xj == xi && yj-1 == yi && (redOrBlack (xj,yj)!=-1) ||xj == xi+1 && yj == yi && (redOrBlack (xj,yj)!=-1) )
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(金);
        }
        else
        {
            restart = 1;
        }
    }

//R（將）----------------------------------------
    else if (array[xi][yi] == R(將))
    {
        if ((xj <= 2 && yj <= 5 && yj >=3)&&(redOrBlack(xj, yj) != 1) && (((xj == xi)&&(yj == yi + 1 || yj == yi - 1))||((yj == yi)&&(xj == xi + 1 || xj == xi - 1))))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = R(將);
        }
        else
        {
            restart = 1;
        }
    }

//B（將）----------------------------------------
    else if (array[xi][yi] == B(將))
    {
        if ((xj >= 8 && yj <= 5 && yj >=3)&&(redOrBlack(xj, yj) != -1) && (((xj == xi)&&(yj == yi + 1 || yj == yi - 1))||((yj == yi)&&(xj == xi + 1 || xj == xi - 1))))
        {
            array[xi][yi] = CROSS;
            array[xj][yj] = B(將);
        }
        else
        {
            restart = 1;
        }
    }
        else {
        restart = 1;
        }
}


void saveChessboard()
{
    FILE *fp;
    fp = fopen("chessboard.txt", "w");
    for (int i = 0; i < NumberofChess; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%s", array[i][j]);
        }
    }
    fclose(fp);}

void loadChessboard()
{   
    int load;
    scanf("Do you wanna load file: %d", &load);
    if (load == 1){
    FILE *fp;
    fp = fopen("chessboard.txt", "r");
    for (int i = 0; i < NumberofChess; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fscanf(fp, "%s", array[i][j]);
        }
    }
    fclose(fp);
    }
    else{
        printf("Please start a new game");
    }
}
void restartgame()
{
    if (restart == 1)
    {
        printf("Invalid move, please try again\n");
        restart = 0;
    }
}

