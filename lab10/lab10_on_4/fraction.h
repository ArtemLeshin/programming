# include <stdio.h>
# include <stdlib.h>
struct fraction {
    int a;
    int b;
};

struct fraction *init(int a1, int b1);
struct fraction *multiplication(struct fraction *d1, struct fraction *d2);
struct fraction *division(struct fraction *d1, struct fraction *d2);
void print_func(struct fraction *frac);