#include <stdio.h>
#include <stdlib.h>

#include "file_kezeles.h"

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
char *fajl_olvas(char *fajlnev){
    FILE *fajl = fopen(fajlnev, "r");

    if (fajl == NULL)
        return NULL;

    char *string = (char*) malloc(fajlmeret(fajl) * sizeof(char));          /* A fájlméretnek megfelelő méretű tömb lefoglalása a mem.ben */
    char c;
    int i = 0;
    for (c = getc(fajl); c != EOF; c = getc(fajl)){
        if (c != '\n'){
            string[i] = c;              /* A tömbbe másolja a beolvasott karaktert */
            i += 1;
        }
    }
    string[i] = '\0';
    fclose(fajl);
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
    FILE *fajl = fopen(fajlnev, "w");

    if (fajl == NULL)
        return 0;
    
    int kar_count = fwrite(tartalom, sizeof(char), strlen(tartalom), fajl);         /* Fájlbaírja a tartalmat és eltárolja a fájlba írt byteok számát */
    fclose(fajl);
    return kar_count;
}