#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <time.h>

void* daughter_pt(void* five) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний: %d\n", i);
        sleep(1);
    }
    return NULL;
}
void goodbye(void *name){
    printf("Поток %s завершился\n",(char*)name);
}

void* print(void* name){
    pthread_cleanup_push(goodbye, name);
    for (int i=0; i<5;i++){
        printf("%s:%d\n", (char*)name,i+1);
        sleep(1);
    }
    pthread_cleanup_pop(0); 
    return NULL;
}

void* sleep_sort(void* numb){
    int val = *(int*)numb;
    usleep(val*10000);
    printf("%d ",val);

    return NULL;
}
int main() {
    srand(time(NULL));
    pthread_t text;
    pthread_create(&text, NULL, daughter_pt, NULL); 
    pthread_join(text, NULL);
    
    for (int i=1; i<=5; i++) {
        printf("Родительский: строка %d\n", i);
    }
    pthread_t text1,text2,text3,text4;
    char a[]="Вася";
    char b[]="Песя";
    char c[]="Дася";
    char d[]="Ваня";

    pthread_create(&text1,NULL,&print,a);
    pthread_create(&text2,NULL,&print,b);
    pthread_create(&text3,NULL,&print,c);
    pthread_create(&text4,NULL,&print,d);
    
    sleep(2);
    pthread_cancel(text1);
    pthread_cancel(text2);
    pthread_cancel(text3);
    pthread_cancel(text4);
    
    pthread_join(text1, NULL);
    pthread_join(text2, NULL);
    pthread_join(text3, NULL);
    pthread_join(text4, NULL);
    printf("Sleepsort:\n");

    int arr[50];
    pthread_t pthread[50];
    for (int i =0;i<50;i++){
        arr[i]=rand()%100;
        pthread_create(&pthread[i], NULL, sleep_sort, &arr[i]);    
    }
    for (int i=0; i<50; i++) {
        pthread_join(pthread[i], NULL);
    }
}
