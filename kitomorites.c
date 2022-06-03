#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "debugmalloc.h"

typedef struct Kod {
    char betu;
    int meret;
    char kod[8];
} Kod;

typedef struct Binfa {
    char betu;
    struct Binfa *bal, *jobb;
} Binfa;

int fajlmeret(FILE *fajlp){
    fseek(fajlp, 0, SEEK_END);          /* A fájlmutatót a pointer végére mozgatja a fájlméret meghatározásához*/
    int fajlmeret = ftell(fajlp);   
    fseek(fajlp, 0, SEEK_SET);          /* A fájlmutatót a fájl elejére mozgatja a fájl beolvasásához */
    return fajlmeret;
}

int kod_tabla_meret(char *t){
    int i = 0;
    int j = 0;
    while (t[i] != '\n'){
        i += 3;
        j += 1;
    }
    return j;
}

Kod *kodok_beolvas(char *s){
    int i = 0;
    int k = 0;
    char maszk = 1;
    Kod *kodok = (Kod*) malloc(sizeof(Kod) * kod_tabla_meret(s));
    while (s[i] != '\n'){
        strncpy(&kodok[k].betu, &s[i], 1);
        //printf("%c", kodok[k].betu);

        //kodok[k].kod = (char*) malloc(sizeof(char) * 8);
        // NEM NYÚLSZ HOZZÁ!!!
        char byte = s[i + 2];
        char bitek[8];
        int j = 0;
        for (j = 0; j < 8 && j < s[i + 1] - '0'; j++)
            kodok[k].kod[j] = (byte & (maszk << (7 - j))) != 0;
        kodok[k].kod[j + 1] = '\0';
        kodok[k].meret = j;
        // NEM NYÚLSZ HOZZÁ!!!

        i += 3;
        k++;
    }
    return kodok;
}

char *tomoritett_szoveg_beolvas(char *s, int meret){
    char maszk = 1;
    int i = 0;
    int k = 0;
    while (s[i] != '\n'){
        //printf("%c", s[i]);
        i++;
    }
    i++;
    char *t = (char*) malloc(sizeof(char) * 10);
    while (meret - i > 0){
        for (int j = 0; j < 8; j++){
            t[k] = (s[i] >> (7 - j)) & maszk;
            k++;
        }
        i++;
    }
    return t;
}

char *dekodol(Kod *kod_tabla, int k_meret, char *s, int s_meret){

    char *t = (char*) malloc(sizeof(char) + 1);
    t[0] = '\0';
    int k = 0;
    bool talalt = false;

    for (int i = 0; i < s_meret; i++){

        talalt = false;
        t[k] = s[i];
        t[k + 1] = '\0';
        
        
        for (int j = 0; j < k; j++)
            printf("%d", t[j]);
        printf("k:%d t[k]:%d\n", k, t[k]);
        

        for (int j = 0; j < k_meret; j++){
            printf("vizsgalt betu: %c\n", kod_tabla[j].betu);
            if ((strncmp(kod_tabla[j].kod, t, kod_tabla[j].meret) == 0) && (kod_tabla[j].meret == k + 1)){
                printf("karakter: %c\n", kod_tabla[j].betu);
                talalt = true;
                break;
            }
        }

        printf("talalt: %d\n", talalt);

        if (talalt){
            //t = (char*) realloc(t, 1);
            t[0] = '\0';
            k = 0;
            talalt = false;
        }
        
        else{
            t = (char*) realloc(t, k + 2);
            k++;
        }
        printf("\n");
    }
}

void kitomorit(char opcio, char *tomoritett_fajl, char *visszaallitott_fajl){

    FILE *fajl = fopen(tomoritett_fajl, "rb");
    int fmeret = fajlmeret(fajl);
    char *file_be = (char*) malloc(sizeof(char) * fmeret);
    fread(file_be, sizeof(char), fmeret, fajl);
    fclose(fajl);
    Kod *kod_tabla = kodok_beolvas(file_be);
    char *tomoritett_szoveg = tomoritett_szoveg_beolvas(file_be, fmeret);
    char *visszaallitott_szoveg = dekodol(kod_tabla, kod_tabla_meret(file_be), tomoritett_szoveg, strlen(tomoritett_szoveg) * 8);

    switch (opcio){
        case 's':;
            for (int i = 0; i < strlen(tomoritett_szoveg); i++)
                printf("%c", tomoritett_szoveg[i]);
            break;

        case 'f':;
            FILE *fajl_ki = fopen(visszaallitott_fajl, "w");
            fwrite(visszaallitott_szoveg, sizeof(char), strlen(visszaallitott_szoveg), fajl_ki);
            fclose(fajl_ki);
        
        default:
            perror("HIANYZO VAGY HIBAS ARGUMENTUM");
            break;
        }

    for (int i = 0; i < kod_tabla_meret(file_be); i++){
        printf("%c", kod_tabla[i].betu);
        printf("%d", kod_tabla[i].meret);
        for (int j = 0; j < kod_tabla[i].meret; j++){
            printf("%d", kod_tabla[i].kod[j]);
        }
        printf("\n");
    }
}