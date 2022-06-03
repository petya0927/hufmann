#ifndef BETOMORITES_H
#define BETOMORITES_H

#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"

typedef struct Gyakorisag {
    char betu;
    int gyakorisag;
} Gyakorisag;

FILE *fajl_letrehoz(char *fajlnev);

int fajlmeret(FILE *fajlp);

char *fajl_olvas(FILE *f);

int fajl_ir(char *fajlnev, char *tartalom);

char *szoveg_olvas();

void tomorites(char *szoveg, char *kimeneti_fajl);

void bemenet_eldont(char opcio, char *arg1, char *arg2, char *arg3);

Gyakorisag *rendezes_struct(Gyakorisag *t, int meret);

Gyakorisag *tombelem_torol_struct(Gyakorisag *t, int p, int meret);

char *tombelem_torol_char(char *t, int p, int meret);

void tomb_kiir(int *n, int meret);

char *tomb_megnovel(char *t);

#endif