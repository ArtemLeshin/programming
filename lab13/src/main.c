#include "smarthome.h"
#include <stdio.h>
#include <stdlib.h>
int main(){
    struct Book *array_struct=malloc(N*sizeof(struct Book));

    struct timeval start, end;
    double time_taken;
    printf("Размер данных: %zu байт\n", get_data_size(array_struct,N));
    printf("\nДо сортировки\n");

    random_filling(array_struct,N);
    print_struct(array_struct,N);
    printf("\nОтсортировано по году издания\n");
    gettimeofday(&start, NULL);
    sorting1(array_struct,N);
    gettimeofday(&end, NULL);
    time_taken = get_time_diff(start, end);
    print_struct(array_struct,N);
    printf("Время сортировки: %f секунд\n", time_taken);


    printf("\nОтсортировано по количествам страниц\n");
    random_filling(array_struct,N);
    gettimeofday(&start, NULL);
    sorting2(array_struct,N);
    gettimeofday(&end, NULL);
    print_struct(array_struct,N);
    time_taken = get_time_diff(start, end);
    printf("Время сортировки: %f секунд\n", time_taken);
    free(array_struct);
}
