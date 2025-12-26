#include <stdio.h>
#include <stdlib.h> // C version

int test1(int a, int b)
{
    a = 10;
    b = 20;
    return a + b;
}

int test2(int *a, int *b)
{
    *a = 30;
    *b = 40;
    return *a + *b;
}

int test3(int &a, int &b)
{
    a = 50;
    b = 60;
    return a + b;
}

int test4(int *a, int *b)
{
    // int *c = malloc(sizeof(int)), *d = malloc(sizeof(int));
    int e = 70, f = 80;
    a = &e, b = &f;
    return *a + *b;
}

int test5(int *&a, int *&b)
{
    int e = 90, f = 100;
    a = &e, b = &f;
    return *a + *b;
}

int test6(int *&a, int *&b)
{
    int *e = (int *)malloc(sizeof(int)), *f = (int *)malloc(sizeof(int));
    *e = 110, *f = 120;
    a = e, b = f;
    return *a + *b;
}

int main()
{
    int a1 = 100, b1 = 200;
    int *c = (int *)malloc(sizeof(int));
    int *d = (int *)malloc(sizeof(int));
    *c = 1000;
    *d = 2000;
    int *g = c, *h = d;

    printf("%d\n", test1(a1, b1));
    printf("%d\n", a1);
    printf("%d\n", b1);

    printf("%d\n", test2(&a1, &b1));
    printf("%d\n", a1);
    printf("%d\n", b1);

    printf("%d\n", test3(a1, b1));
    printf("%d\n", a1);
    printf("%d\n", b1);

    printf("%d\n", test4(c, d));
    printf("%d\n", *c);
    printf("%d\n", *d);

    printf("%d\n", test5(c, d));
    printf("%d\n", *c);
    printf("%d\n", *d);

    printf("%d\n", test6(c, d));
    printf("%d\n", *c);
    printf("%d\n", *d);

    free(c);
    free(d);
    free(g);
    free(h);
}
