#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include <time.h>


#define clear() printf("\033[H\033[J")
#define BLUE "\x1b[34;47m"
#define RED "\x1b[31;47m"

#define R(piece) "\033[31m"#piece"\033[0m"//紅色棋子
//#define B(piece) "\033[30m"#piece"\033[0m"//黑色棋子
#define B(piece) "\033[36m"#piece"\033[0m"//藍色棋子


bool isStandard = 1;//是否符合規則，初始值1，符合
bool gameOverSign = 1;//遊戲是否結束，0結束
bool restart = 0;

int curr_row,curr_col;//目前位置
int new_row,new_col;//移動的目標位置
int save; //存取棋子
int load; //讀取棋子

//判斷遊戲結束
void isGameOver();
//判斷是否有旗子
int isFlag(int x,int y);  
void save_game();
void load_game();
void push();
struct Chessboard *pop();
void undo();
void redo();
char* c[9][9];
struct Stack undo_stack;
struct Stack redo_stack;




struct Square {
    char *piece;
    char *color;
    struct Square *up;
    struct Square *down;
    struct Square *left;
    struct Square *right;
};

struct Chessboard {
    struct Square *first;
};

void init_chessboard(struct Chessboard *chessboard) {


    
    int i, j;
    struct Square *current, *prev, *firstofFile, *first,*lastrank;
    chessboard->first = (struct Square *)malloc(sizeof(struct Square));
    firstofFile = chessboard->first;
    //Create First Node
    current = chessboard->first;
    current->left = NULL;
    //Create Right Node 
    current->right = (struct Square *)malloc(sizeof(struct Square));
    // Double link
    current->right->left = current;
    //up,down and left is Null
    current->up = NULL;
    current->left = NULL;
    current->down = NULL;



    for (i = 0; i < 9; i++) {

        for (j = 0; j < 9; j++) {
            if (i == 0){
            //only create right node
            prev = current;
            //move to right
            current = current->right;
            //sturct right and connect
            current->right = (struct Square *)malloc(sizeof(struct Square));

            current->right->left = current;
           


            current->right->up = NULL;
            current->right->down = NULL;
            current->right->right = NULL;
        }
            else if(i == 8){
            // struct right node and connect up
            prev = current;
            //move to right
            current = current->right;
            current->right = (struct Square *)malloc(sizeof(struct Square));
            current->right->left = current;
            current->right->up = lastrank;
            current->right->down = NULL;
            current->right->right = NULL;
            }
            else{
            // create right node and connect up
            prev = current;
            //move to right
            current = current->right;
            lastrank = lastrank -> right;
            //sturct right and connect  
            current->right = (struct Square *)malloc(sizeof(struct Square));
            current->right->left = current;
            //connect up and down
            current->up = lastrank;
            lastrank -> down = current;


            }
        }

        if (i != 9) {
            prev = current;
            lastrank =firstofFile;
            current = firstofFile;
            //create down node
            current->down = (struct Square *)malloc(sizeof(struct Square));
            current->down->up = current;
            current->down->right = NULL;
            current->down->left = NULL;
            current->down->down = NULL;
            firstofFile = current->down;

            //prev->down = current->down;
            current->down->left = NULL;
            current->down->right = (struct Square *)malloc(sizeof(struct Square));
            current->down->right->left = current->down;
            current = current->down;

        }
    }
    firstofFile = chessboard->first;
    current = chessboard->first;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (i == 0) {
                if (j == 0 || j == 8) {
                    current->piece = R(香);
                    current->color = "r";

                } else if (j == 1 || j == 7) {
                    current->piece = R(桂);
                    current->color = "r";

                } else if (j == 2 || j == 6) {
                    current->piece = R(銀);
                    current->color = "r";

                } else if (j == 3|| j == 5) {
                    current->piece = R(金);
                    current->color = "r";

                } else if (j == 4) {
                    current->piece = R(將);
                    current->color = "r";

                }
            } 
            else if (i==1){
                if(j == 1){
                    current->piece = R(飛);
                    current->color = "r";
                    
                }
                else if(j == 7){
                    current->piece = R(角);
                    current->color = "r";
                    
                }
                else{
                    current->piece = "  ";
                    current->color = "n";
                }
            }
            else if (i == 2) {
                current->piece = R(兵);
                current->color = "r";
                

            } 
            else if (i == 8) {
                if (j == 0 || j == 8) {
                    current->piece = B(香);
                    current->color = "b";
                    
                } else if (j == 1 || j == 7) {
                    current->piece = B(桂);
                    current->color = "b";
                    
                } else if (j == 2 || j == 6) {
                    current->piece = B(銀);
                    current->color = "b";
                    
                } else if (j == 3 || j == 5) {
                    current->piece = B(金);
                    current->color = "b";
                    
                } else if (j == 4) {
                    current->piece = B(將);
                    current->color = "b";
                    
                }
            } 

            else if (i == 7) {
                if(j == 1){
                    current->piece = B(角);
                    current->color = "b";
                    
                }
                else if(j == 7){
                    current->piece = B(飛);
                    current->color = "b";
                    
                }
                else{
                    current->piece = "  ";
                    current->color = "n";
                }
            }
            else if (i == 6){
                current->piece = B(兵);
                current->color = "b";
                
                }
            else{
                current->piece = "  ";
                current->color = "n";
            }
            current = current->right;
        
        }
    current = firstofFile->down;
    firstofFile = current;
    }
    }   
    
    

void print_chessboard(struct Chessboard *chessboard) {
    clear();

    printf("        日本將棋        \n\n\n\n");
    printf("1  2  3  4  5  6  7  8  9 \n");
    
    int i, j;
    struct Square *current;
    struct Square *firstofFile;
    current = chessboard->first;
    firstofFile = chessboard->first;
    for (i = 0; i < 9; i++) {
        ;
        for (j = 0; j < 9; j++) {

            printf( "%s ",current->piece);
            current = current->right;
        }
        printf("%d",i+1);
        printf("\n");
        current = firstofFile->down;
        firstofFile = current;
        
    }
    printf("\x1b[0m");
}


void move_piece(struct Chessboard *chessboard, int curr_row, int curr_col, int new_row, int new_col) {
    struct Square *current = chessboard->first;
    struct Square *current1 = chessboard->first;
    int i, j;
    char* piece_to_move, *color_to_move;

    push(&undo_stack, chessboard);
    // Find the current position of the piece
    for (i = 0; i < curr_row; i++) {
        current = current->down;
    }
    for (j = 0; j < curr_col; j++) {
        current = current->right;
    }


    // Save the piece and color to move
    piece_to_move = current->piece;
    color_to_move = current->color;

    // Move to the new position

    for (i = 0; i < new_row; i++) {
        current1 = current1->down;
    }
    for (j = 0; j < new_col; j++) {
        current1 = current1->right;
    }


    if (current1->color == color_to_move) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 1;
    }
    else{
    // Clear the current position
        current->piece = "  ";
        current->color = "n";
    // Update the new position
        current1->piece = piece_to_move;
        current1->color = color_to_move;
    }
}



bool BorR(struct Chessboard *chessboard, int curr_row, int curr_col)
{ struct Square *current = chessboard->first;
    struct Square *current1 = chessboard->first;
    int i, j;
    char* piece_to_move, *color_to_move;
    // Find the current position of the piece
    for (i = 0; i < curr_row; i++) {
        current = current->down;
    }
    for (j = 0; j < curr_col; j++) {
        current = current->right;
    }
    // Save the piece and color to move
    piece_to_move = current->piece;
    color_to_move = current->color;
    if (color_to_move == "b"){
        return 1;
    }
    else if (color_to_move == "r"){
        return 0;
    }

}

//紅棋移動
void redMove(struct Chessboard *chessboard)
{
    if (restart) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 0;
    }

    
    int curr_row,curr_col,new_row,new_col,save;
    
    printf("[紅棋]請輸入你要移動的棋子:\n");
    scanf("%d %d",&curr_row ,&curr_col);
    curr_col = curr_col - 1;
    curr_row = curr_row - 1;

    if (BorR(chessboard,curr_row,curr_col) == 0){;
    }
    else {       

        restart = 1;
    }
    printf("[紅棋]請輸入你要放置的位置:\n");
    scanf("%d %d",&new_row,&new_col);
    new_col = new_col-1;
    new_row = new_row-1;

    //chessrule();   

    move_piece(chessboard,curr_row,curr_col,new_row,new_col);
    
    print_chessboard(chessboard);
}

//藍棋移動
void blueMove(struct Chessboard *chessboard)
{
    if (restart) {
        printf("違反遊戲規則，請重新輸入\n");
        restart = 0;
    }

    
    printf("[藍棋]請輸入你要移動的棋子:\n");
    scanf("%d %d",&curr_row,&curr_col);
    curr_col = curr_col - 1;
    curr_row = curr_row - 1;

    if (BorR(chessboard,curr_row,curr_col) == 1){;
    }
    else {restart = 1;
    }
    printf("[藍棋]請輸入你要放置的位置:\n");
    scanf("%d %d",&new_row,&new_col);
    new_col = new_col-1;
    new_row = new_row-1;
    if (save == 1){
        save_game(chessboard,c);
    }
    else if (save == 0){
        printf("棋盤未儲存\n");
    }
    else{
        printf("輸入錯誤\n");
    }
    //chessrule();
    move_piece(chessboard,curr_row,curr_col,new_row,new_col);

    print_chessboard(chessboard);

}






int main() {
    struct Chessboard chessboard;

    init_chessboard(&chessboard);
    
    printf("\033[40m");
    printf("Do you want to load the game?(1:yes 0:no)\n 維修中 請輸入 0 : ");
    scanf("%d",&load);
    if (load == 1){
        load_game(&chessboard,"oldchessboard.txt");
    }
    else if (load == 0){
        printf("New game\n");
    }
    else{
        printf("輸入錯誤\n");
    }
    print_chessboard(&chessboard);
    int turn = -1;//紀錄輪到誰下棋，1為紅方，-1為黑方
    while (gameOverSign) {
        isStandard = 1;
        turn *= (-1);//雙方交替下棋
        switch (turn) {
            case 1:
                redMove(&chessboard);
                turn = (restart) ? (turn*-1) : turn;
            printf("是否要儲存棋盤或悔棋?(2:undo 1:儲存 0:否)\n");
            scanf("%d",&save); 
            if (save == 1){
            save_game(&chessboard,c);
            }
            else if (save == 0){
            printf("棋盤未儲存\n");
            }
            else if (save == 2){
            undo(&chessboard);
            }
            else{
            printf("輸入錯誤\n");
            }               
                
                break;
            case -1:
                blueMove(&chessboard);
                turn = (restart) ? (turn*-1) : turn;
            printf("是否要儲存棋盤?(2: undo 1:儲存 0:否)\n");
            scanf("%d",&save); 
            if (save == 1){
            save_game(&chessboard,c);
            }
            else if (save == 0){
            printf("棋盤未儲存\n");
            }
            else if (save == 2){
                undo(&chessboard);
            }
            else{
            printf("輸入錯誤\n");
            }  
            break;
        }
        isGameOver(&chessboard);

        
    }
    printf("遊戲結束!\n");


    return 0;
}
 




void isGameOver(struct Chessboard *chessboard)
{
    bool sign_r = 0;
    bool sign_b = 0;
    struct Square *current, *firstofFile;
    current= chessboard->first;
    firstofFile = current;
    for (int i = 0; i < 9; i ++) {
        for (int j = 0; j < 9; j ++) {
            if (current ->piece == R(將)) {
                sign_r = 1;
            }
            else if (current ->piece == B(將))
            {
                sign_b = 1;
            }
            current = current->right;
        }
        current = firstofFile->down;
        firstofFile = current;
    }
    if ((sign_r == 0)||(sign_b == 0)) {
        gameOverSign = 0;
    }
    
}




















//Rules of all kinds of chess pieces

void chessrule(struct Chessboard *chessboard, int curr_row, int curr_col, int new_row, int new_col){

    struct Square *current = chessboard->first;
    int i, j;
    char* piece_to_move, *color_to_move;
    // Find the current position of the piece
    for (i = 0; i < curr_row; i++) {
        current = current->down;
    }
    for (j = 0; j < curr_col; j++) {
        current = current->right;
    }
    // Save the piece and color to move
    piece_to_move = current->piece;
    color_to_move = current->color;
    if (piece_to_move == R(兵)){
        if (new_row == curr_row + 1 && new_col == curr_col){
            isStandard = 1;
        }
        
        else{
            isStandard = 0;
            restart = 1;
        }
        }
    else if (piece_to_move == B(兵)){
        if (new_row == curr_row - 1 && new_col == curr_col){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
    }
    else if (piece_to_move == R(香)){
        if (new_col == curr_col){
            if (new_row > curr_row){
                isStandard = 1;
            }
            else{
                isStandard = 0;
                restart = 1;
 
            }
        }
    }
    else if (piece_to_move == B(香)){
        if (new_col == curr_col){
            if (new_row < curr_row){
                isStandard = 1;
            }
            else{
                isStandard = 0;
                restart = 1;}

 
        }
    }
    else if (piece_to_move == R(桂)){
        if ((new_row == curr_row + 2 && new_col == curr_col + 1) || (new_row == curr_row + 2 && new_col == curr_col - 1) || (new_row == curr_row - 2 && new_col == curr_col + 1) || (new_row == curr_row - 2 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col + 2) || (new_row == curr_row + 1 && new_col == curr_col - 2) || (new_row == curr_row - 1 && new_col == curr_col + 2) || (new_row == curr_row - 1 && new_col == curr_col - 2)){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
    }
    else if (piece_to_move == B(桂)){
        if ((new_row == curr_row + 2 && new_col == curr_col + 1) || (new_row == curr_row + 2 && new_col == curr_col - 1) || (new_row == curr_row - 2 && new_col == curr_col + 1) || (new_row == curr_row - 2 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col + 2) || (new_row == curr_row + 1)){

        }
    }
    else if (piece_to_move == R(銀)){
        if ((new_row == curr_row + 1 && new_col == curr_col + 1) || (new_row == curr_row + 1 && new_col == curr_col - 1) || (new_row == curr_row - 1 && new_col == curr_col + 1) || (new_row == curr_row - 1 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col) || (new_row == curr_row - 1 && new_col == curr_col)){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
    }
    else if (piece_to_move == B(銀)){
        if ((new_row == curr_row + 1 && new_col == curr_col + 1) || (new_row == curr_row + 1 && new_col == curr_col - 1) || (new_row == curr_row - 1 && new_col == curr_col + 1) || (new_row == curr_row - 1 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col) || (new_row == curr_row - 1 && new_col == curr_col)){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
    }
    else if (piece_to_move == R(金)){
        if ((new_row == curr_row + 1 && new_col == curr_col + 1) || (new_row == curr_row + 1 && new_col == curr_col - 1) || (new_row == curr_row - 1 && new_col == curr_col + 1) || (new_row == curr_row - 1 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col) || (new_row == curr_row - 1 && new_col == curr_col)){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
    }
    else if (piece_to_move == B(金)){
        if ((new_row == curr_row + 1 && new_col == curr_col + 1) || (new_row == curr_row + 1 && new_col == curr_col - 1) || (new_row == curr_row - 1 && new_col == curr_col + 1) || (new_row == curr_row - 1 && new_col == curr_col - 1) || (new_row == curr_row + 1 && new_col == curr_col) || (new_row == curr_row - 1 && new_col == curr_col)){
            isStandard = 1;
        }
        else{
            isStandard = 0;
            restart = 1;
        }
        }
    else if (piece_to_move == R(角)){
    }
    else if (piece_to_move == B(角)){

    }
    else if (piece_to_move == R(飛)){

    }
    else if (piece_to_move == B(飛)){

    }
    else if (piece_to_move == R(將)){

    }
    else if (piece_to_move == B(將) ) {

    }

}




void save_game(struct Chessboard *chessboard,char* c[9][9]) {
    int i, j;
    struct Square *current = chessboard->first;
    struct Square *firstofFile = chessboard->first;
    FILE *file = fopen("oldchessgame.txt", "w");
    char *a, *b;
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            a = current->piece;
            b = current->color;

            if (strcmp(a, " ") == 0) {
                fprintf(file, "%s ", a);
            }
            else {
                fprintf(file, "%s ", a);
            }
           
            current = current->right;
        }
        fprintf(file, "\n");
        current = firstofFile->down;
        firstofFile = firstofFile->down;
    }
    fclose(file);
}




void translate(){


    int i, j;
    char *a, *b;
    char *c[9][9];
    FILE *file = fopen("oldchessgame.txt", "r");

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(file, "%s ", c[i][j]);

}
    }
}


void load_game(struct Chessboard *chessboard, char *file_name) {
    int i, j;
    struct Square *current = chessboard->first;
    struct Square *firstofFile = chessboard->first;
    FILE *file = fopen(file_name, "r");

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            fscanf(file, "%s ", current->piece);
            current = current->right;
        }
    current = firstofFile->down;
    firstofFile = firstofFile->down;       
    }

    fclose(file);
}




struct Move {
    struct Chessboard *chessboard;
    struct Move *next;
};

struct Stack {
    struct Move *top;
};



void push(struct Stack *stack, struct Chessboard *chessboard) {
    struct Move *move = (struct Move *)malloc(sizeof(struct Move));
    move->chessboard = chessboard;
    move->next = stack->top;
    stack->top = move;
}

struct Chessboard *pop(struct Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    struct Chessboard *chessboard = stack->top->chessboard;
    struct Move *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return chessboard;
}

void undo() {
    struct Chessboard *chessboard = pop(&undo_stack);
    if (chessboard == NULL) {
        printf("No more moves to undo\n");
        return;
    }


    push(&redo_stack, chessboard);

    print_chessboard(chessboard);
}

void redo() {
    struct Chessboard *chessboard = pop(&redo_stack);
    if (chessboard == NULL) {
        printf("No more moves to redo\n");
        return;
    }

    struct Chessboard * current_chessboard;
    push(&undo_stack, current_chessboard);
    current_chessboard = chessboard;
    print_chessboard(current_chessboard);
}
