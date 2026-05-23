# include <stdio.h>
//обьявлчем стуктуру
struct fraction {
    int a;
    int b;
};
//инициализируем
struct fraction init(int a1, int b1) {
    struct fraction fr;
    fr.a=a1;
    fr.b=b1;
    return fr;
}
// умножение
struct fraction multiplication(struct fraction d1, struct fraction d2){
    struct fraction result;
    result.a=d1.a*d2.a;
    result.b=d1.b*d2.b;
    return result;
}
//delenie
struct fraction division(struct fraction d1, struct fraction d2){
    struct fraction result;
    result.a=d1.a*d2.b;
    result.b=d1.b*d2.a;
    return result;
}
//выводим
void print_func(struct fraction frac){
    printf("%d/%d\n",frac.a, frac.b);
}

int main() {
    struct fraction fraction1 = init(2,4);
    struct fraction fraction2 = init(3,6);
    print_func(fraction1);
    print_func(fraction2);
    struct fraction multi= multiplication(fraction1,fraction2);
    print_func(multi);
    struct fraction div= division(fraction1,fraction2);
    print_func(div);
}

