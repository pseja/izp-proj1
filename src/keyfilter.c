#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Nepasnul jsi žádný parametr\n");
        return 1;
    }

    printf("prvni argument je %s\n", argv[1]);
    return 0;
}