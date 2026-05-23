#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int start_row;
    int end_row;
    int n;
    int **A;
    int **B;
    int **C;
} Thread;

void* multiply_part(void* arg) {
    Thread* data = arg;
    for (int i=data->start_row; i<data->end_row; i++) {
        for (int j=0; j<data->n; j++) {
            data->C[i][j]=0;
            for (int k=0; k<data->n; k++) {
                data->C[i][j] += data->A[i][k] * data->B[k][j];
            }
        }
    }
    return NULL;
}

void printMatrix(int n, int **matrix, char *name) {
    printf("Matrix: %s\n", name);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int count_thread = atoi(argv[2]);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); 

    int **A = malloc(n*sizeof(int *));
    int **B = malloc(n*sizeof(int *));
    int **C = malloc(n*sizeof(int *));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n*sizeof(int));
        B[i] = malloc(n*sizeof(int));
        C[i] = malloc(n*sizeof(int));
        for (int j = 0; j < n; j++) {
            A[i][j] = 1; 
            B[i][j] = 1;
        }
    }
    

    pthread_t threads[count_thread];
    Thread thread_data[count_thread];
    int rows = n / count_thread;

    for (int i = 0; i < count_thread; i++) {
        thread_data[i].n = n;
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].start_row = i * rows;
        thread_data[i].end_row = (i + 1) * rows; 
        pthread_create(&threads[i], NULL, multiply_part, &thread_data[i]);
    }

    for (int i = 0; i < count_thread; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    float time = (end.tv_sec - start.tv_sec) * 1000; 
    time += (end.tv_nsec - start.tv_nsec) / 1000000; 
   
    FILE *f = fopen("data.txt", "a"); 
    fprintf(f, "%d %d %.3f\n", n, count_thread, time);
    fclose(f);



    if (n < 5) {
        printMatrix(n, A, "A");
        printMatrix(n, B, "B");
        printMatrix(n, C, "C");
    } else {
        printf("Готово! Для N=%d результат в C[0][0] = %d.\n", n, C[0][0]);
    }
}
