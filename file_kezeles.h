#ifndef FILE_KEZELES_H
#define FILE_KEZELES_H

#include <stdio.h>

FILE *fajl_letrehoz(char *fajlnev);

int fajlmeret(FILE *fajlp);

char *fajl_olvas(char *fajlnev);

int fajl_ir(char *fajlnev, char *tartalom);

#endif