#ifndef KITOMORITES_H
#define KITOMORITES_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//#include "debugmalloc.h"

typedef struct Kod {
    char betu;
    int meret;
    char kod[8];
} Kod;

int kod_tabla_meret(char *t);

Kod *kodok_beolvas(char *s);

char *tomoritett_szoveg_beolvas(char *s, int meret);

void dekodol(Kod *kod_tabla, int k_meret, char *s, int s_meret);

void kitomorit(char opcio, char *tomoritett_fajl, char *visszaallitott_fajl);

#endif