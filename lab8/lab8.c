#include <stdio.h>
#include <stdlib.h>
void add_average(int **matrix,int n){
    if (matrix == NULL){
        return; 
    }
    for (int i=0; i<n;i++){
        int summa=0,count=0;
        for (int j=0;j<n;j++){
            if (matrix[i][j]>0){
                count++;
                summa+=matrix[i][j];
            }
        }
        int average = (count>0) ? summa/count : 0;
        for (int j =0; j<n;j++){
            matrix[i][j]+=average;
        }
    }
}

int summa(int **matrix,int n){
    if (matrix == NULL){
        return 0;
    }
    int summ=0;
    for (int i=0; i<n;i++){
        for (int j=0;j<n;j++){
                summ+=matrix[i][j];
            }
        }
    return summ;
}

void scan(int **matrix, int n){
    if (matrix == NULL){
        return;
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            scanf("%d", &matrix[i][j]);
        }
    }
}

void print(int **matrix, int n){
    if (matrix == NULL){
        return;
    }
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            printf("%d ",matrix[i][j]);
        }
    printf("\n");
    }
}
int negative(int **matrix, int n){
    if (matrix == NULL){
        return 0;
    }
    int negativ=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (matrix[i][j]<0){
                negativ+=1;
            }
        }
    }
    return negativ;

}
void massiv(int **matrix, int n){
    if (matrix == NULL){
        return;
    }

    int  count=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i<j && i+j<n-1){
                count++;
            }              
        }
    }
    int *new_massiv=malloc(count*sizeof(int));
    if (new_massiv == NULL){
        return;
    }

    int index=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            if (i<j && i+j<n-1){
                new_massiv[index]=matrix[i][j];
                index++;
            }
        }
    }

    printf("Массив из элементов выше главной и побочной диагоналей:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", new_massiv[i]);
    }
    printf("\n");
    free(new_massiv);
}


int main(){
    int n;
    printf("Введите размер матрицы\n");
    scanf("%d", &n);

    int **matrix=malloc(n*sizeof(int*));
    if (matrix == NULL){
        return 0;
    }

    for (int i=0;i<n;i++){
        matrix[i]=malloc(n*sizeof(int));    
    }

    printf("Введите элементы расширенной матрицы:\n");
    scan(matrix,n);
    printf("Рфсширенная матрица до увеличения:\n");
    print(matrix,n);
    printf("Отрицательных чисел: %d\n",negative(matrix,n));;
    int sum1=summa(matrix,n);
    printf("Сумма элементов до увеличения: %d\n",sum1);
    add_average(matrix,n);
    printf("Рфсширенная матрица после увеличения:\n");
    print(matrix,n);
    int sum2=summa(matrix,n);
    printf("Сумма элементов после увеличения: %d\n",sum2);
    massiv(matrix,n);

    for ( int i=0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
}