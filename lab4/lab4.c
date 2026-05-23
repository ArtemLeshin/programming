#include <stdio.h>
int main() {
    int chiclo;
    
    printf("Введите число: ");
    scanf("%d", &chiclo);
    
    int new = 0;
    int pos = 1;
    
        while (chiclo > 0) {
            int triada = chiclo & 7; 
            new += triada * pos;
            chiclo = chiclo >> 3;
            pos *= 10;
        }
    
    
    printf("Восьмеричное представление: %d\n", new);
    return 0;
}
