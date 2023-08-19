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
    printf("Add %d : %p\n", A, &A);
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
    return RCSmalloc();
}

int RCSmallocFREE()
{
    if (globalD == 0)
    {
        return 1;
    }
    globalD -= 1;
    char *mallocD = (char *)malloc(5 * sizeof(char));
    printf("malloc D (free) : %p\n", &mallocD[0]);
    free(mallocD);
    return RCSmallocFREE();
}

int main()
{
    printf("global A : %p\n", &globalA);
    printf("global B : %p\n", &globalB);
    printf("global C : %p\n", &globalC);
    printf("global D : %p\n", &globalD);

    int localA = 10;
    int localB = 20;
    char *mallocA = (char *)malloc(5 * sizeof(char));
    int *mallocB = (int *)malloc(5 * sizeof(int));
    char *mallocC = (char *)malloc(5 * sizeof(char));

    printf("localA : %p\n", &localA);
    printf("localB : %p\n", &localB);
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
    RCSmallocFREE();
    free(mallocA);
    free(mallocB);
}