#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "betomorites.h"
#include "binaris_fa.h"

/*
 * Funkció egy fájl létrehozására.
 * Létrehoz egy fájlpointerbe az argumentunmként kapott
 * elérési útvonalon egy adott nevű fájlt, majd visszatér a fájlpointerrel.
 * 
 * Argumentumok: char *fajlnev: a fájl elérési útvonala.
 * VIsszatérési érték: FILE *fajl: a létrehozott fájlpointer.
 */
FILE *fajl_letrehoz(char *fajlnev){
    FILE *fajl = fopen(fajlnev, "w");               /* fájlmegnyitás write módban */
    if (fajl == NULL)
        return NULL;
    fclose(fajl);
    return fajl;
}

/*
 * Funkció egy argumentumként kapott, pointerben eltárolt fájl méretének meghatározására.
 * Megszámolja a fájl méretét byteokban és ezzel a számmal tér vissza.
 * 
 * Argumentumok: FILE *fajlp: megnyitott és egy pointerben eltárolt fájl.
 * Visszatérési érték: int fajlmeret: a fajl byte-okban számolt mérete.
 */
int fajlmeret(FILE *fajlp){
    fseek(fajlp, 0, SEEK_END);          /* A fájlmutatót a pointer végére mozgatja a fájlméret meghatározásához*/
    int fajlmeret = ftell(fajlp);   
    fseek(fajlp, 0, SEEK_SET);          /* A fájlmutatót a fájl elejére mozgatja a fájl beolvasásához */
    return fajlmeret;
}

/*
 * Funkció szöveges fájlok olvasására.
 * Megniytja a fájlt egy pointerbe, majd karakterenként beolvassa a file tartalmát
 * és ezzel tér vissza.
 * 
 * Argumentumok: char *fajlnev : a fajl elérési útvonala.
 * Visszatérési érték: sikertelen fájlmegnyitáskor : NULL pointer;
 *                     sikeres fájlbaíráskor: a szöveget tartalmazó pointer
 */
char *fajl_olvas(FILE *f){
    char *string = (char*) malloc(fajlmeret(f) * sizeof(char));          /* A fájlméretnek megfelelő méretű tömb lefoglalása a mem.ben */
    char c;
    int i = 0;
    for (c = getc(f); c != EOF; c = getc(f)){
        string[i] = c;              /* A tömbbe másolja a beolvasott karaktert */
        i += 1;
    }
    string[i] = '\0';
    return string;
}

/*
 * Funkció a egy tartalom fájlbaírására.
 * Megnyitja az argumentumként kapott fájlt és beleírja az argumentumként kapott char típusú tömböt.
 * Sikeres írsánál visszatér a fileba írt byteok számával.
 * 
 * Argumentumok: char *fajlnev: a fájl elérési útvonala; char *tartalom: a fájlba írandó szöveges tartalom.
 * Visszatérési érték: sikertelen fájlmegniytáskor: int 0;
 *                     sikeres fájlbaíráskor:int kar_count: a fájlba írt byteok száma.
 */
int fajl_ir(char *fajlnev, char *tartalom){
    FILE *fajl = fopen(fajlnev, "wb");

    if (fajl == NULL)
        return 0;
    
    int kar_count = fwrite(tartalom, sizeof(char), strlen(tartalom), fajl);         /* Fájlbaírja a tartalmat és eltárolja a fájlba írt byteok számát */
    fclose(fajl);
    return kar_count;
}

void tomorites(char *szoveg, char *kimeneti_fajl){
    Gyakorisag *elofordulasok = (Gyakorisag*) malloc(sizeof(Gyakorisag));
    int meret  = 0;
    elofordulasok = gyak_szamol(szoveg, &meret);
    rendezes_struct(elofordulasok, meret);

    Binfa *fa = rekurziv_tomb(elofordulasok, meret);

    FILE *fajl = fopen(kimeneti_fajl, "wb");

    kodok_fileba(fa, fajl);
    fwrite("\n", sizeof(char), 1, fajl);

    char *t = (char*) malloc(sizeof(char) * 1000);
    *t = '\0';
    for (int i = 0; i < strlen(szoveg); i++){
        t = faban_keres(fa, szoveg[i], t, fajl);
    }
    binaris_fajl_ir(t, fajl);
    fclose(fajl);
    free(fa);
}

/*
 * Függvény a betömörítés kezelésére és vezérlésére. Ezt a függvényt hívja meg a huffman.c fájl main függvénye,
 * amikor a betömörítés típusát dönti el. Egy switch segítségével a bemeneti parancs alapján eldönti, hogy file-ból
 * vagy vagy user inputból várja a tömörítendő szöveget. a rendezés_struct vagy rendezes_int segítségével megszámolja 
 * a betűk gyakoriságát, majd más függvények segítségével elvégzi a tömörítést.
 * MÉG HIÁNYOS, NEM TELJES A KÓD, EGYELŐRE CSAK A BEOLVASÁS ÉS GYAKORISÁG SZÁMOLÁS TALÁLHATÓ MEG BENNE!
 * Argumentumok:
 *          char opcio: a user parancsa, a betömörítés iránya kapcsolóban a második karakter (file-ból vagy begépelt szövegből várja a bemenetet)
 *          char *arg1: a begépelt szöveg, vagy file elérési útvonala
 *          char *arg2: a kimeneti file opció parancsa, ha üres, az alapértelmezett helyre menti el a kimeneti file-t
 *          char *arg3: az egyedi kimeneti file elérési útvonala
 * Visszatérési érték: -

 */
void bemenet_eldont(char opcio, char *arg1, char *arg2, char *kimeneti_fajl){
    int meret = 0;

    switch (opcio){
        case 's':;                              /* Begépelt stringből várja a bementet */
            char *szoveg_be = arg1;
            fajl_ir("tomoritetlen.txt", szoveg_be);
            tomorites(szoveg_be, kimeneti_fajl);
            break;

        case 'f':;                              /* Fileból várja a bemenetet */
            FILE *fajl_olv = fopen(arg1, "r");
            if (fajl_olv == NULL)
                printf("Nem sikerült megnyitni a fajlt, kilepes...");
            char *fajl_be = fajl_olvas(fajl_olv);
            fclose(fajl_olv);
            fajl_ir("tomoritetlen.txt", fajl_be);
            tomorites(fajl_be, kimeneti_fajl);
            break;

        default:;
            printf("NINCS ELEG ARGUMENTUM");
            break;
    }
}