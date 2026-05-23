#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int simple(int simpl) {
    if (simpl < 2) {
        return 0; 
    }
    
    for (int del = 2; del < simpl; del++) {
        if (simpl % del == 0) {
            return 0;
        } 
    } 
    return 1;  
}




void print(int n, int array[n]){
    for (int d=0;d<n;d++){
        if (simple(array[d])==1){
            printf("Z[%d] = %d-Простое\n", d, array[d]);
        }
        else{
            printf("Z[%d] = %d-Не простое\n", d, array[d]);
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    int m;
    printf("Введите размер массива\n");
    scanf("%d",&m);
    

    int Z[m]={};
    for (int g=0;g<m;g++){
    Z[g]=(rand()%50 + 2);
    }
    print(m,Z);
    int count=0;
    int count_len=0;
    int start=-1, end =-1;

    for (int i =0; i<m; i++){
        if (simple(Z[i])==1){
            count+=1;
            if (count==2){
            count_len+=1;
            start=i-count_len;
            end=i;
            } 
        
        } else {
            count=0;
        }
    }
    if (count_len>=1) {
        printf("Массив содержит серии из подряд стоящий простых чисел\n");
        printf("Колисество серий: %d\n", count_len);
    } else {
        printf("Массив не содержит серии из подряд стоящий простых чисел\n");
    }

    if (start != -1) {
        for (int i = start; i <= end; i++) {
            Z[i] = 0;
        }
        printf("Обнулили серию с %d по %d\n", start, end);
    }
    print(m,Z);
}