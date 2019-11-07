#include <stdio.h>
#include <stdlib.h>

extern int pow2(int n);
extern unsigned long long int pow2long(unsigned long long int n);


int
main(int argc, char **argv)
{
    int n = atoi(argv[1]);
    printf("f(%d) = %d\n", n, pow2(n));

    unsigned long long int n_long = atoll(argv[1]);
    printf("f(%llu) = %llu\n", n_long, pow2long(n_long));

    return 0;
}