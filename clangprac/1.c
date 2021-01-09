#include <stdio.h>

int main()
{
    char A = 20;
    int B = 30;
    char* p = &A;
    char** p2 = &p;
    char*** p3 = &p2;

    printf("%p\n%p\n%p\n",&A,p,&B);
    printf("%lu\n",sizeof(p));
    printf("%p\n",p2);
    printf("%p\n",p3);
    
    return 0;
}