#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#include "pcg_basic.h"
#include "pcg_basic.c"

#include "words.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: wtf <arg>\n");
        exit(-1);
    }
    pcg32_srandom(time(0), 1);
    printf("%s: ", argv[1]);
    for (size_t i = 0; argv[1][i] != '\0'; i++) {
        if (0 <= argv[1][i] - 'a' && argv[1][i] - 'a' < 26) {
            size_t r = pcg32_boundedrand(words[argv[1][i] - 'a'].len);
            printf("%s ", words[argv[1][i] - 'a'].words[r]);
        }
        else {
            printf("Invalid character %c\n", argv[1][i]);
        }
    }
    return 0;
}
