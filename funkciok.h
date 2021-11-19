#ifndef FUNKCIOK_H
#define FUNKCIOK_h

#include <stdio.h>
#include <stdlib.h>

typedef struct Gyakorisag {
    char betu;
    int gyakorisag;
} Gyakorisag;

typedef struct Binfa{
    int szam;
    struct Binfa *bal, *jobb;
} Binfa;

FILE *fajl_letrehoz(char *fajlnev);

int fajlmeret(FILE *fajlp);

char *fajl_olvas(char *fajlnev);

int fajl_ir(char *fajlnev, char *tartalom);

char *szoveg_olvas();

Gyakorisag *gyak_szamol(char *string);

void bemenet_eldont(char opcio, char *arg1, char *arg2, char *arg3);

Gyakorisag *rendezes_struct(Gyakorisag *t, int meret);

int *rendezes_int(int *t);

int *tombelem_torol(int *tomb, int poz, int meret);

void tomb_kiir(int *n, int meret);

void help_screen();

Binfa *uj_adatpont(Binfa *gyoker, int szam);

Binfa *rekurziv_tomb_osszeg(int *n, int meret);

void sorban_kiir(Binfa *gyoker);

#endif