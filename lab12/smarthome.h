#define N 10
#include <sys/time.h>

struct Book{
    char name[100];
    char author[30];
    int number_of_pages;
    int year_of_publication;
};

void random_filling(struct Book *array,int size);
void print_struct(struct Book *array_struct,int size);
void sorting1(struct Book *array,int size);
void sorting2(struct Book *array,int size);
double get_time_diff(struct timeval start, struct timeval end);
size_t get_data_size(struct Book *array,int size);