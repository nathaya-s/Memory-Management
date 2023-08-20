#include <stdio.h>
#include <stdlib.h>

int globalA;
char globalB;
int globalC = 5;
int globalD = 5;

int recursive(int A)
{
    if (A == 0)
    {
        return 1;
    }
    printf("local variable A : %p\n", &A);
    return recursive(A - 1);
}

int RCSmalloc()
{
    if (globalC == 0)
    {
        return 1;
    }
    globalC -= 1;
    char *mallocC = (char *)malloc(5 * sizeof(char));
    printf("malloc C : %p\n", &mallocC[0]);
    free(mallocC);
    return RCSmalloc();
}

int main()
{
    printf("global variable A : %p\n", &globalA);
    printf("global variable B : %p\n", &globalB);
    printf("global variable C : %p\n", &globalC);
    printf("global variable D : %p\n", &globalD);

    int localA = 10;
    int localB = 20;
    char *mallocA = (char *)malloc(5 * sizeof(char));
    int *mallocB = (int *)malloc(5 * sizeof(int));

    printf("local variable A : %p\n", &localA);
    printf("local variable B : %p\n", &localB);
    recursive(localA);

    for (int i = 0; i < 5; i++)
    {
        printf("molloc A #%d : %p\n", i + 1, &mallocA[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        printf("molloc B #%d : %p\n", i + 1, &mallocB[i]);
    }
    
    RCSmalloc();
    free(mallocA);
    free(mallocB);
}