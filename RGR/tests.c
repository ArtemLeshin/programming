#include <assert.h>
#include <string.h>
#include <stdio.h>

int valid_name(const char *name);
void generate_keys(char text[]);

void test_valid_name(){
    assert(valid_name("Alex")==1);
    assert(valid_name("A")==0);
    assert(valid_name("Alex123")==0);
}

void test_keys(){
    char text[16];
    generate_keys(text);
    assert(strlen(text)==15);
}

int main(){
    test_valid_name();
    test_keys();
    printf("TESTS OK\n");
    return 0;
}