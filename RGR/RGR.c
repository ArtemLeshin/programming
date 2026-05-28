#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"
#include "config.h"

#define MAX_TEXT 512
#define FILE_NAME "leaderboard.txt"
struct Statistic{
    char name[50];
    char mode[50];
    int correct;
    int mistakes;
    double time_spent;
};

const char *easy_words[]={
    "переменная","цикл","массив","указатель","компилятор",
    "функция","структура","процессор","алгоритм","отладка",
    "итерация","память","рекурсия","буфер","сборка",
    "интерфейс","модуль","библиотека","поток","синтаксис",
    "объект","класс","наследование","полиморфизм","инкапсуляция",
    "команда","терминал","консоль","компиляция","отладчик"
};

const char *sentences[]={
    "Функция сортировки массива работает быстрее после оптимизации.",
    "Компилятор обнаружил ошибку в указателе на структуру.",
    "Алгоритм поиска данных использует двоичное дерево.",
    "Цикл обработки файлов завершился без ошибок.",
    "Программа успешно выделила память для массива.",
    "Итерация по массиву выполняется с помощью цикла for.",
    "Указатель хранит адрес ячейки памяти.",
    "Структура данных упрощает организацию информации.",
    "Отладчик помогает находить ошибки в программе.",
    "Рекурсия используется для решения сложных задач.",
    "Буфер обмена временно хранит данные.",
    "Сборка проекта прошла без ошибок компиляции.",
    "Модуль программы отвечает за отдельную функцию.",
    "Библиотека содержит набор готовых функций.",
    "Поток выполнения управляет процессами программы.",
    "Синтаксис языка должен соблюдаться строго.",
    "Объект хранит данные и методы их обработки.",
    "Класс описывает структуру будущих объектов.",
    "Наследование позволяет переиспользовать код.",
    "Полиморфизм упрощает работу с разными типами.",
    "Инкапсуляция скрывает внутреннюю реализацию.",
    "Консоль выводит результаты выполнения программы.",
    "Команда компиляции запускает процесс сборки.",
    "Терминал используется для ввода команд.",
    "Алгоритм оптимизирован для быстрой работы."
};

struct Statistic *journal=NULL;
int journal_count=0;
int journal_capacity=0;
char current_user[50];

void clear_input(){
    while(getchar()!='\n');
}

int valid_name(const char *name){
    int len=strlen(name);
    if(len<2 || len>20) return 0;

    for(int i=0;i<len;i++){
        char c=name[i];
        if(!((c>='a' && c<='z') || (c>='A' && c<='Z'))) return 0;
    }
    return 1;
}

int input_number(){
    char buffer[100];
    int number;
    fgets(buffer,sizeof(buffer),stdin);
    if(sscanf(buffer,"%d",&number)!=1) return -1;
    return number;
}

void ensure_capacity(){
    if(journal_count>=journal_capacity){
        journal_capacity=(journal_capacity==0)?10:journal_capacity*2;
        journal=realloc(journal,journal_capacity*sizeof(struct Statistic));
        if(!journal){
            printf("Ошибка памяти\n");
            log_error("Ошибка выделения памяти");
            exit(1);
        }
    }
}

void save_to_file(){
    FILE *f=fopen(FILE_NAME,"w");
    if(!f){
        printf("Ошибка открытия файла\n");
        log_error("Не удалось открыть leaderboard.txt");
        return;
    }
    for(int i=0;i<journal_count;i++){
        fprintf(f,"%s %s %d %d %.2f\n",
            journal[i].name,
            journal[i].mode,
            journal[i].correct,
            journal[i].mistakes,
            journal[i].time_spent);
    }
    fclose(f);
}

void load_from_file(){
    FILE *f=fopen(FILE_NAME,"r");
    if(!f){
        log_warning("Файл leaderboard.txt не найден");
        return;
    }
    while(1){
        ensure_capacity();
        if(fscanf(f,"%49s %49s %d %d %lf",
            journal[journal_count].name,
            journal[journal_count].mode,
            &journal[journal_count].correct,
            &journal[journal_count].mistakes,
            &journal[journal_count].time_spent)!=5) break;
        journal_count++;
    }
    fclose(f);
}

void save_statistic(const char name[],const char mode[],int correct,int mistakes,double time_spent){
    ensure_capacity();
    strcpy(journal[journal_count].name,name);
    strcpy(journal[journal_count].mode,mode);
    journal[journal_count].correct=correct;
    journal[journal_count].mistakes=mistakes;
    journal[journal_count].time_spent=time_spent;
    journal_count++;
    save_to_file();
}

void show_journal(){
    printf("\n===== ЖУРНАЛ ПОПЫТОК =====\n\n");
    printf("%-3s %-12s %-15s %-10s %-10s %-10s\n","№","Имя","Режим","Верно","Ошибки","Время");
    printf("------------------------------------------------------------------\n");
    if(journal_count==0){
        printf("Журнал пуст\n");
        return;
    }
    for(int i=0;i<journal_count;i++){
        printf("%-3d %-12s %-15s %-10d %-10d %-10.2f\n",
            i+1,
            journal[i].name,
            journal[i].mode,
            journal[i].correct,
            journal[i].mistakes,
            journal[i].time_spent);
    }
}

void typing_test(const char *text,int time_limit,const char *mode){
    char input[MAX_TEXT];
    int correct=0,mistakes=0;
    printf("\n%s\n",text);
    printf("Начинайте ввод:\n");
    time_t start=time(NULL);
    fgets(input,MAX_TEXT,stdin);
    input[strcspn(input,"\n")]='\0';
    if(strlen(input)==0){
        printf("Ошибка: пустой ввод\n");
        log_warning("Пустой ввод");
        return;
    }
    time_t end=time(NULL);
    double elapsed=difftime(end,start);
    if(elapsed > time_limit){
        printf("\nВремя вышло! Результат не засчитан.\n");
        log_warning("Превышен лимит времени");
        correct = 0;
        mistakes = strlen(text);
        save_statistic(current_user, mode, correct, mistakes, elapsed);
        return;
    }
    int len=strlen(text);
    int in_len=strlen(input);
    int max_len=len>in_len?len:in_len;
    for(int i=0;i<max_len;i++){
        if(i<len && i<in_len && text[i]==input[i]) correct++;
        else mistakes++;
    }
    printf("\nПользователь: %s\n",current_user);
    printf("Верно: %d\n",correct);
    printf("Ошибок: %d\n",mistakes);
    printf("Время: %.2f\n",elapsed);
    log_info("Тест завершен");
    save_statistic(current_user,mode,correct,mistakes,elapsed);
}

void generate_words_text(char text[]){
    text[0]='\0';
    for(int i=0;i<WORDS_COUNT;i++){
        strcat(text,easy_words[rand()%30]);
        if(i<WORDS_COUNT-1){
            strcat(text," ");
        }
    }
}

void generate_sentences_text(char text[]){
    text[0]='\0';
    for(int i=0;i<SENTENCES_COUNT;i++){
        strcat(text,sentences[rand()%25]);
        if(i<SENTENCES_COUNT-1){
            strcat(text," ");
        }
    }
}

void word_training(){
    char text[MAX_TEXT];
    generate_words_text(text);
    typing_test(text,TIME_LIMIT,"Слова");
}

void sentence_training(){
    char text[MAX_TEXT];
    generate_sentences_text(text);
    typing_test(text,TIME_LIMIT,"Предложения");
}

void snake_mode(){
    printf("\n===== ЗМЕЙКА =====\n");
    char text[MAX_TEXT]="";
    for(int level=1;level<=3;level++){
        if(level>1){
            strcat(text," ");
        }
        strcat(text,sentences[rand()%25]);
        printf("\nУровень %d\n",level);
        typing_test(text,TIME_LIMIT,"Змейка");
    }
}

void generate_keys(char text[]){
    const char symbols[]="abcdefghijklmnopqrstuvwxyz0123456789";
    int len=strlen(symbols);
    for(int i=0;i<15;i++){
        text[i]=symbols[rand()%len];
    }
    text[15]='\0';
}

void key_training(){
    char text[16];
    char input[16];
    generate_keys(text);
    printf("\nПовторите последовательность:\n");
    printf("%s\n",text);
    printf("Ввод:\n");
    time_t start=time(NULL);
    fgets(input,16,stdin);
    input[strcspn(input,"\n")]='\0';

    if(strlen(input)==0){
        printf("Ошибка: пустой ввод\n");
        log_warning("Пустой ввод в режиме клавиш");
        return;
    }
    time_t end=time(NULL);
    double elapsed=difftime(end,start);

    int correct=0;
    int mistakes=0;

    for(int i=0;i<15;i++){
        if(input[i]==text[i]){
            correct++;
        }else{
            mistakes++;
        }
    }
    printf("\nРЕЗУЛЬТАТ:\n");
    printf("Верно: %d\n",correct);
    printf("Ошибок: %d\n",mistakes);
    printf("Время: %.2f\n",elapsed);
    log_info("Режим клавиш завершен");
    save_statistic(current_user,"Клавиши",correct,mistakes,elapsed);
}
#ifndef TEST_BUILD
int main(){
    srand(time(NULL));
    load_config();
    log_info("Программа запущена");
    load_from_file();
    char temp[50];
    while(1){
        printf("Имя: ");
        scanf("%49s",temp);
        clear_input();
        if(valid_name(temp)){
            strcpy(current_user,temp);
            log_info("Имя пользователя принято");
            break;
        }else{
            printf("Ошибка: имя должно содержать только латиницу (2-20 символов)\n");
            char msg[128];
            snprintf(msg,sizeof(msg),"Некорректное имя: %s",temp);
            log_error(msg);
        }
    }
    int choice;
    do{
        printf("\n1.Слова\n");
        printf("2.Предложения\n");
        printf("3.Змейка\n");
        printf("4.Клавиши\n");
        printf("5.Журнал\n");
        printf("0.Выход\n");
        choice=input_number();
        if(choice==-1){
            printf("Ошибка: введите число\n");
            log_warning("Некорректный ввод меню");
            continue;
        }
        switch(choice){
            case 1:
                word_training();
                break;
            case 2:
                sentence_training();
                break;
            case 3:
                snake_mode();
                break;
            case 4:
                key_training();
                break;
            case 5:
                show_journal();
                break;
            case 0:
                printf("Выход из программы\n");
                log_info("Программа завершена");
                break;
            default:
                printf("Ошибка: неверный пункт меню\n");
                log_warning("Выбран неверный пункт меню");
        }
    }while(choice!=0);
    free(journal);
    return 0;
}
#endif