#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funkciok.h"

int main(int argc, char *argv[]) {

    if (argv[1] == NULL){
        help_screen();
        return 0;
    }

    switch (argv[1][1]){
        case 'i':
            printf("BETOMORITES ");
            bemenet_eldont(argv[1][2], argv[2], argv[3], argv[4]);
            break;

        case 'r':
            printf("VISSZAALLITAS\n");
            switch (argv[1][2]){
                case 's':
                    printf("STRING\n");
                    break;
                case 'f':
                    printf("FILE\n");
                    break;
                default:
                    printf("NINCS ELÉG ARGUMENTUM");
                    break;
            }
            break;

        case 'h':
        default:
            help_screen();
            break;
    }

    return 0;
}