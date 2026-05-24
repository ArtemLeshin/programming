#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int turn = 0;
void* daughter_pt(void* arg) {
    for (int i=1; i<=5; i++) {
        pthread_mutex_lock(&m);
        while (turn!=1) { 
            pthread_cond_wait(&cond, &m);
        }
        printf("Дочерний поток: %d\n", i);
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void Matrix(int n, int **A,int **B,int **C){
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            C[i][j]=0;
            for (int k=0;k<n;k++){
                C[i][j]+=A[i][k]*B[k][i];
            }
        }
    }
}
void printMatrix(int n, int **matrix,char *name){
    printf("Matrix: %s\n",name);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    pthread_t text;
    pthread_create(&text, NULL, daughter_pt, NULL);

    for (int i=1; i<=5; i++) {
        pthread_mutex_lock(&m);   
        while (turn != 0) { 
            pthread_cond_wait(&cond, &m);
        }
        printf("Родительский поток: строка %d\n", i);
        turn =1; 
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&m);
    }

    pthread_join(text, NULL);
    int n;
    printf("Input: N\n");
    scanf("%d",&n);
    int **A = malloc(n*sizeof(int *));
    int **B = malloc(n*sizeof(int *));
    int **C = malloc(n*sizeof(int *));
    for (int i=0;i<n;i++){
        A[i]=malloc(n*sizeof(int));
        B[i]=malloc(n*sizeof(int));
        C[i]=malloc(n*sizeof(int));
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            A[i][j]=1;
            B[i][j]=1;
        }
    }
    Matrix(n,A,B,C);
    if (n < 5) {
        printMatrix(n, A, "A");
        printMatrix(n, B, "B");
        printMatrix(n, C, "C");
    } else {
        printf("Для N=%d результат в каждой ячейке C будет равен %d.\n", n, n);
    }
}
