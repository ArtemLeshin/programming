#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#include <sys/time.h>
struct Book{
    char name[100];
    char author[30];
    int number_of_pages;
    int year_of_publication;
};
double get_time_diff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + 
           (end.tv_usec - start.tv_usec) / 1000000.0;
}
size_t get_data_size(struct Book *array,int size) {
    return sizeof(struct Book) * size;
}
void random_filling(struct Book *array,int size){
    char authors[10][30]={"Толстой", "Достоевский", "Пушкин", "Чехов", "Булгаков", 
                        "Оруэлл", "Хемингуэй", "Ремарк", "Брэдбери", "Толкин"};
    char names[10][100]={"Война и мир", "Сто лет одиночества", "Мастер и Маргарита", "Преступление и наказание","Хоббит", "Вишневый сад", 
                        "Старик и море", "Три товарища", "451 градус по Фаренгейту", "Мертвые души"};
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int author_index = rand() % 10;
        int name_index = rand() % 10;
    
        strcpy(array[i].author, authors[author_index]);
        strcpy(array[i].name, names[name_index]);
    
        array[i].number_of_pages = 100 + rand() % 500;  
        array[i].year_of_publication = 1900 + rand() % 125;  
    }
}
void print_struct(struct Book *array_struct,int size){
    char s[60]="----------------------------------------------";
    for (int i = 0; i < size; i++) {
    printf("%s\n",s);
        printf("%d %s %s %d %d\n", 
               i + 1,
               array_struct[i].name,
               array_struct[i].author,
               array_struct[i].number_of_pages,
               array_struct[i].year_of_publication);
    }
    printf("%s\n",s);
}
void sorting1(struct Book *array,int size){
    struct Book help;
    for (int i=0;i<size-1;i++){
        for (int j=0;j<size-i-1;j++){
            if (array[j].year_of_publication>array[j+1].year_of_publication){
                help=array[j];
                array[j]=array[j+1];
                array[j + 1] = help;
            }
        }
    }
}
void sorting2(struct Book *array,int size){
    struct Book help;
    for (int i=0;i<size-1;i++){
        for (int j=0;j<size-i-1;j++){
            if (array[j].number_of_pages>array[j+1].number_of_pages){
                help=array[j];
                array[j]=array[j+1];
                array[j + 1] = help;
            }
        }
    }
}

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
    printf("Время сортировки: %f секунд\n", time_taken);
    print_struct(array_struct,N);

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
