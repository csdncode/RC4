#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RC4.h"

int main(int argc, char* argv[])
{
    if(argc == 1)
        return 0;
    char password[1025];
    printf("password:");
    scanf("%s", password);
    printf("please wait...");
    int i;
    for(i = 1; i < argc; i++)
        RC4(argv[i], password);
    return 0;
}
