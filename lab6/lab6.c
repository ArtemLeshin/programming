#include <stdio.h>
#define MAX_SIZE 10
int N;

void input(float Z[MAX_SIZE][MAX_SIZE+1]){
    printf("Введите размер системы N: ");
    scanf("%d", &N);
    printf("Введите уравнения матрицы в расширенном виде\n");
    for (int i=0;i<N;i++){
        for (int j=0;j<N+1;j++){
            scanf("%f",&Z[i][j]);
        }
    }
}

void print(float Z[MAX_SIZE][MAX_SIZE+1]){
    printf("\nРасширенная матрица (%dx%d):\n", N, N + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%.2f ", Z[i][j]);
        }
        printf("\n");
    }
}

float det(float matrix[MAX_SIZE][MAX_SIZE], int n){
    if (n==1){
        return matrix[0][0];
    }
    if (n==2){
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    }

    float det_sign=0;
    float minor[MAX_SIZE][MAX_SIZE];

    for (int x=0;x<n;x++){
        int indexI=0;
        for (int i=1;i<n;i++){
            int indexJ=0;
            for (int j=0; j<n;j++){
                if (j==x){
                    continue;
                }
                minor[indexI][indexJ]=matrix[i][j];
                indexJ++;
            

            }
            indexI++;
        }
        float det_minora=det(minor,n-1);
        if (x%2==0){
            det_sign+=matrix[0][x]*det_minora;
        } else {
            det_sign-=matrix[0][x]*det_minora;
        }

    }
    return det_sign;

}

void replace(float original[MAX_SIZE][MAX_SIZE+1], float new_matrix[MAX_SIZE][MAX_SIZE], int poz){  
    for (int i=0;i<N;i++){
        for (int j=0; j<N;j++){
            if (j==poz){
                new_matrix[i][j]=original[i][N];
            } else{
                new_matrix[i][j]=original[i][j];
            }
        }
    }
}

void cramer(float Z[MAX_SIZE][MAX_SIZE+1]){
    float main_matrix[MAX_SIZE][MAX_SIZE];

    for (int i=0;i<N;i++){
        for (int j=0; j<N;j++){
            main_matrix[i][j]=Z[i][j];
        }
    }

    float main_Det=det(main_matrix,N);
    if (main_Det==0){
        printf("Нет единственного решения!\n");
        return;
    }

    for (int k=0;k<N;k++){
        float mod_matrix[MAX_SIZE][MAX_SIZE];
        replace(Z,mod_matrix,k);

        float mod_det=det(mod_matrix,N);
        float answer=mod_det/main_Det;

        printf("x%d = %.2f / %.2f = %.2f\n", k + 1, mod_det, main_Det, answer);
    }


}
int main(){
    float Z[MAX_SIZE][MAX_SIZE+1];
    input(Z);
    print(Z);
    cramer(Z);

}