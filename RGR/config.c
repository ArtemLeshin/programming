#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "config.h"

int WORDS_COUNT=7;
int SENTENCES_COUNT=2;
int TIME_LIMIT=30;

void load_config(){
    FILE *f=fopen("config.txt","r");

    if(!f){
        return;
    }

    char line[100];

    while(fgets(line,sizeof(line),f)){

        char key[50];
        char value[50];

        if(sscanf(line,"%49[^=]=%49s",key,value)==2){

            if(strcmp(key,"WORDS_COUNT")==0){
                WORDS_COUNT=atoi(value);
            }

            else if(strcmp(key,"SENTENCES_COUNT")==0){
                SENTENCES_COUNT=atoi(value);
            }

            else if(strcmp(key,"TIME_LIMIT")==0){
                TIME_LIMIT=atoi(value);
            }
        }
    }

    fclose(f);
}