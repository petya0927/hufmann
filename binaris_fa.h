#ifndef BINARIS_FA_H
#define BINARIS_FA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "betomorites.h"
#include "debugmalloc.h"

typedef struct Binfa{
    int szam;
    char betu;
    char *ut;
    struct Binfa *bal, *jobb;
} Binfa;

Binfa *lefoglal(int szam);

void sorban_kiir(Binfa *gyoker);

void felszabadit(Binfa *gyoker);

bool level(Binfa *gyoker);

Binfa *beszur(Binfa *gyoker, int a, int b, char ca, char cb);

Binfa *rekurziv_tomb(Gyakorisag *n, int meret);

void binaris_fajl_ir(char *t, FILE *f);

void kodok_fileba(Binfa *gyoker, FILE *f);

char *faban_keres(Binfa *gyoker, char c, char *t, FILE *f);

Gyakorisag* gyak_szamol(char *szoveg, int *cel_meret);

Gyakorisag *tombelem_torol_struct(Gyakorisag *t, int p, int meret);

char *tombelem_torol_char(char *t, int p, int meret);

char *tomb_megnovel(char *t);

#endif