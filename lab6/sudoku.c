#include <stdio.h>
#define SIZE 9

int check_rows(int sudoku[SIZE][SIZE]){
    for (int i=0;i<SIZE;i++){
        int range[SIZE+1]={0};
        for (int j=0;j<SIZE;j++){
            int number=sudoku[i][j];
            if (range[number]>0){
                return 0;
            }
            range[number]=1;
        }
    }
    return 1;
}
int check_columns(int sudoku[SIZE][SIZE]){
    for (int j=0;j<SIZE;j++){
        int range[SIZE+1]={0};
        for (int i=0;i<SIZE;i++){
            int number=sudoku[i][j];
            if (range[number]>0){
                return 0;
            }
            range[number]=1;
        }
    }
    return 1;
}

int check_squares(int sudoku[SIZE][SIZE]){

    for (int k=0;k<3;k++){
        for (int l=0;l<3;l++){
            int range[10] = {0};
    
            for (int i=k*3;i<k*3+3;i++){
                for (int j=l*3;j<l*3+3;j++){
                    int number=sudoku[i][j];
                    if (range[number]>0){
                        return 0;
                    }
                    range[number]=1;
                }
            }
        }
    }
    return 1;
}
int is_valid_sudoku(int sudoku[SIZE][SIZE]){
    return check_rows(sudoku) && check_columns(sudoku) && check_squares(sudoku);

}

int main(){
int sudoku[SIZE][SIZE] = {
{5, 3, 3, 6, 7, 8, 9, 1, 2},
{6, 7, 2, 1, 9, 5, 3, 4, 8},
{1, 9, 8, 3, 4, 2, 5, 6, 7},
{8, 5, 9, 7, 6, 1, 4, 2, 3},
{4, 2, 6, 8, 5, 3, 7, 9, 1},
{7, 1, 3, 9, 2, 4, 8, 5, 6},
{9, 6, 1, 5, 3, 7, 2, 8, 4},
{2, 8, 7, 4, 1, 9, 6, 3, 5},
{3, 4, 5, 2, 8, 6, 1, 7, 9}
};
if (is_valid_sudoku(sudoku)==1) {
        printf("Правильное судоку!\n");
    } else {
        printf("Неправильное судоку!\n");
    }
}