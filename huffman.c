#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "betomorites.h"
#include "kitomorites.h"
#include "debugmalloc.h"

/*
 * A használati útmutató megjelenítése, parancsok és beállítás opciók kiírása argumentumokkal.

 * Argumentumok: -
 * Visszatérési érték: -
*/
void help_screen(){
    printf("~ HASZNALATI UTMUTATO ~\n"
           "Hasznalat: huffman <tomorites tipus> [kimeneti file]\n"
           "BETOMORITES TIPUSOK:\n"
           "\t-if <bemeneti file> [kimeneti file]: egy szoveges file tartalmat tomoriti be egy .hcf fileba\n"
           "\t-is \"<sztring>\" [kimeneti file]: egy begepelt szoveges tartalmat tomorit egy .hcf fileba\n"
           "VISSZAALLITAS TIPUSOK:\n"
           "\t-rf <tomoritett file> [kimeneti file]: visszaallitja a tomoritett file-t az eredeti, tomoritetlen fileba\n"
           "\t-rs <tomoritett file> [kimeneti file]: visszaallitja a begepelt sztringet\n"
           "KIMENETI FILE:\n\t-o <kimeneti file>: egyedi kiemeneti file beallitasa,\n\tha ures, a tomorites tipusa hatarozza meg az alapertelmezest\n"
           "SEGITSEG:\n\t-h: kiirja ezt a szoveget\n");
}

void main(int argc, char *argv[]) {

    if (argv[1] == NULL){
        help_screen();
        return;
    }

    char *kimeneti_file = "tomoritett.hcf";
    if (argv[3] != NULL && argv[4] != NULL){
        if (strcmp(argv[3], "-o") == 0)
            kimeneti_file = argv[4];
        else{
            perror("HIANYZO VAGY HIBAS ARGUMENTUM");
            return;
        }
    }
    else if (argv[4] == NULL){
        perror("HIANYZO VAGY HIBAS ARGUMENTUM");
        return;
    }

    switch (argv[1][1]){
        case 'i':;
            bemenet_eldont(argv[1][2], argv[2], argv[3], kimeneti_file);
            break;

        /*
        case 'r':;
            kitomorit(argv[1][2], argv[2], argv[3]);
            break;
        */

        case 'h':;
        default:;
            help_screen();
            break;
    }

    return;
}