#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct Kod {
    char betu;
    int meret;
    char *kod;
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

        kodok[k].kod = (char*) malloc(sizeof(char) * 8);
        /// NEM NYÚLSZ HOZZÁ!!!
        char byte = s[i + 2];
        char bitek[8];
        int j = 0;
        for (j = 0; j < 8 && j < s[i + 1] - '0'; j++)
            kodok[k].kod[j] = (byte & (maszk << (7 - j))) != 0;
        kodok[k].meret = j;
        /// NEM NYÚLSZ HOZZÁ!!!

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

void dekodol(Kod *kod_tabla, char *s, int meret){
    char *t = malloc(sizeof(char));
    for (int i = 0; i < meret; i++){
        t[i] = s[i];
        
        for (int j = 0; j < meret; j++)
            if (strcmp(kod_tabla[j].kod, t) == 0){
                printf("%c", kod_tabla[j].betu);
                t = '\0';
                break;
            }
        
        char *uj = (char*) malloc(sizeof(char) * (strlen(t) + 1));
        for (int j = 0; j < strlen(t); j++)
            uj[j] = t[j];
        free(t);
        t = uj;
        

    }
}


int main(){
    FILE *fajl = fopen("tomoritett.hcf", "rb");
    int fmeret = fajlmeret(fajl);
    char *file_be = (char*) malloc(sizeof(char) * fmeret);
    fread(file_be, sizeof(char), fmeret, fajl);
    Kod *kod_tabla = kodok_beolvas(file_be);
    char *tomoritett_szoveg = tomoritett_szoveg_beolvas(file_be, fmeret);
    dekodol(kod_tabla, tomoritett_szoveg, strlen(tomoritett_szoveg) * 8);
    /*
    for (int i = 0; i < kod_tabla_meret(file_be); i++){
        printf("%c", kod_tabla[i].betu);
        for (int j = 0; j < kod_tabla[i].meret; j++){
            printf("%d", kod_tabla[i].kod[j]);
        }
        printf("\n");
    }
    */

    fclose(fajl);
    return 0;
}