#include "fraction.h"
int main() {
    printf("Напишите числитель и знаменатель первой дроби через пробел\n");
    int a,b;
    scanf("%d %d", &a,&b);
    printf("Напишите числитель и знаменатель второй дроби через пробел\n");
    int a1,b1;
    scanf("%d %d", &a1,&b1);
    struct fraction *fraction1 = init(a,b);
    struct fraction *fraction2 = init(a1,b1);
    printf("Первая дробь: ");
    print_func(fraction1);
    printf("Вторая дробь: ");
    print_func(fraction2);
    struct fraction *multi= multiplication(fraction1,fraction2);
    printf("Умножение дробей: ");
    print_func(multi);
    struct fraction *div= division(fraction1,fraction2);
    printf("Деление дробь: ");
    print_func(div);
    free(fraction1);
    free(fraction2);
    free(multi);
    free(div);
}
