#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "funkciok.h"

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

/*
 * Függvény egy szövegben található karakterek előfordulásának a megszámolására.
 * A függvény argumentumként átveszi a szöveget, megszámolja, milyen karakterekből mennyi található meg benne,
 * majd visszatér egy Gyakorisag típusú tömbbel, amelyben az egyes elemei
 * tartalmazzák a karaktert és annak gyakoriságát.
 * 
 * Argumentumok: char *szoveg: a szövegtömb;
 * Visszatérési érték: sikertelen címátadáskor: NULL pointer;
 *                     sikeres műveletkor: a Gyakorisagok típusú tömb (tartalma: char karakter, int gyakorisag).
 */
Gyakorisag *gyak_szamol(char *szoveg){
    if (szoveg == NULL)
        return NULL;

    int meret = strlen(szoveg);
    int beolvasva = -1;
    int *elofordulas = (int*) malloc(meret * sizeof(int));              /* Lefoglal a memóriában egy helyet az elofordulasok tarolasara */

    /* Végigiterál a szövegen és ha azonos betűk vannak, a számlálóhoz ad egyet*/
    for (int i = 0; i < meret; i++){
        int szamol = 1;
        for (int j = i + 1; j < meret; j++){
            if (szoveg[i] == szoveg[j]){
                szamol++;
                elofordulas[j] = -1;                    /* Ha azonos betűt talált, jelzi, hogy ne számoljuk meg újra */
            }
        }

        if (elofordulas[i] != -1)
            elofordulas[i] = szamol;                    /* Eltárolja a gyakoriságot */
    }

    int j = 0;
    Gyakorisag *cel = (Gyakorisag*) malloc(sizeof(Gyakorisag));         /*Lefoglal egy területet a végelges tömbnek*/

    for (int i = 0; i < meret; i++){
        if (elofordulas[i] != -1){
            Gyakorisag *uj = (Gyakorisag*) malloc((j + 1) * sizeof(Gyakorisag));         /* Lefoglal egyel nagyobb tömböt a gyakoriságok tárolására */
            for (int k = 0; k < j; ++k)
                uj[k] = cel[k];                     /* Átmásolja az eddigi elemeket az új tömbbe*/
            free(cel);
            cel = uj;
            cel[j].betu = szoveg[i];                /* Eltárolja a karaktert*/
            cel[j].gyakorisag = elofordulas[i];     /* Eltárolja a karakter előfordulásának számát */
            printf("%c:%d\n", cel[j].betu, cel[j].gyakorisag);
            j++;
        }
    }
    printf("===============\n");
    return cel;
    /* MÉG NINCS KÉSZ, EGYELŐRE BUGOS, HIBÁS TÖMBBEL TÉR VISSZA */
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
void bemenet_eldont(char opcio, char *arg1, char *arg2, char *arg3){
    switch (opcio){
        case 's':                              /* Begépelt stringből várja a bementet */
            printf("STRINGBOL\n");
            char *szoveg_be = arg1;

            Gyakorisag *szoveg_gyakorisagok = gyak_szamol(szoveg_be);                  /* Átveszi a megszámolt gyakoriságokat Gyakorisag típusba */
            free(szoveg_be);
            int szoveg_meret = sizeof(szoveg_gyakorisagok);

            szoveg_gyakorisagok = rendezes_struct(szoveg_gyakorisagok, szoveg_meret);                /* Átveszi a rendezett gyakorisági tömböt */

            for (int i = 0; i < szoveg_meret; i++)
                printf("%c:%d\n", szoveg_gyakorisagok[i].betu, szoveg_gyakorisagok[i].gyakorisag);

            /*
            KELL MÉG:
                - bináris fa felépítése
                - bináris fa alapján a betűk kódolásának eltárolása fileban
                - kódolt szöveg elátrolása fileban
            */
            break;

        case 'f':;                              /* Fileból várja a bemenetet */
            printf("FILEBOL\n");
            char *file_be = fajl_olvas(arg1);
            printf("%s", file_be);
            free(file_be);
            Gyakorisag *file_gyakorisagok = gyak_szamol(file_be);                  /* Átveszi a megszámolt gyakoriságokat Gyakorisag típusba */
            int file_meret = sizeof(file_gyakorisagok);

            file_gyakorisagok = rendezes_struct(file_gyakorisagok, file_meret);                /* Átveszi a rendezett gyakorisági tömböt */

            for (int i = 0; i < file_meret; i++)
                printf("%c:%d\n", file_gyakorisagok[i].betu, file_gyakorisagok[i].gyakorisag);

            /*
            KELL MÉG:
                - bináris fa felépítése
                - bináris fa alapján a betűk kódolásának eltárolása fileban
                - kódolt szöveg elátrolása fileban
            */
            
            break;

        default:;
            printf("NINCS ELEG ARGUMENTUM");
            break;
    }
}

/*
 * Függvény egy Gyakorisag típusú tömb rendezésére, a közvetlen kiválasztás algoritmusával.
 * A .gyakorisag paraméter szerint rendezi az argumentumként kapott tömböt, kisebbtől a nagyobbig,
 * a betűkkel együtt, majd visszatér egy ilyen típusú tömbbel.
 * Argumentumok:
 *          Gyakorisag *t: a rendezendő tömb;
 *          int meret: a tömb mérete.
 * Visszatérési érték:
 *          Gyakorisag *t: a rendezett tömb.

 */
Gyakorisag *rendezes_struct(Gyakorisag *t, int meret){
    for (int i = 0; i < meret - 1; ++i) {
        int minindex = i;
        for (int j = i + 1; j < meret; ++j)
            if (t[j].gyakorisag < t[minindex].gyakorisag)
                minindex = j;
 
        if (minindex != i) {
            int gyak_temp = t[minindex].gyakorisag;
            char betu_temp = t[minindex].betu;
            t[minindex].gyakorisag = t[i].gyakorisag;
            t[minindex].betu = t[i].betu;
            t[i].gyakorisag = gyak_temp;
            t[i].betu = betu_temp;
        }
    }
    return t;
}

/*
 * Függvény egy int tömb rendezésére, kisebbtől a nagyobbig,
 * közvetlen kiválasztás módszerével.
 * Argumentumok:
 *          int *t: a számokat tartalmazó tömb.
 * Visszatérési érték:
 *          int *t: a rendezett tömb.
 */
int *rendezes_int(int *t){
    int meret = sizeof(t) / sizeof(t[0]);
    for (int i = 0; i < meret - 1; ++i){
        int minindex = i;
        for (int j = i + 1; j < meret; ++j)
            if (t[j] < t[minindex])
                minindex = j;
        if (minindex != i){
            int temp = t[minindex];
            t[minindex] = t[i];
            t[i] = t[minindex];
        }
    }
    return t;
}

/*
 * Függvény egy meret méretű tömb poz-adik elemének a kitörlésére.
 Argumentumként megkapja a tömböt és a törlés után visszatér a módosított tömbbel.
 * Argumentumok:
 *          int *tomb: számokból álló tömb;
 *          int poz: a pozíció, ahonnan ki kell törölni az elemet;
 *          int meret: a tömb mérete.
 * Visszatérési réték:
 *          int *tomb: a módosított tömb.
 */
int *tombelem_torol(int *tomb, int poz, int meret){
    for (int k = poz - 1; k < meret - 1; k++)
        tomb[k] = tomb[k + 1];
    return tomb;
}

/*
 * Függvény egy tömb kiírására.
 * Argumentumok:
 *          int *n: a számokból álló tömb;
 *          int meret: a tömb mérete.
 * Visszatérési érték: -
 */
void tomb_kiir(int *n, int meret){
    for (int i = 0; i < meret; i++)
        printf("%d ", n[i]);
    printf("\n");
}

/*
 * A használati útmutató megjelenítése, parancsok és beállítás opciók kiírása argumentumokkal.

 * Argumentumok: -
 * Visszatérési érték: -
*/
void help_screen(){
    printf("/// HASZNALATI UTMUTATO ///\n"
           "Hasznalat: huffman <tomorites tipus> [kimeneti file]\n"
           "BETOMORITES TIPUSOK:\n"
           "\t-if <bemeneti file> [kimeneti file]: egy szoveges file tartalmat tomoriti be egy .hcf fileba\n"
           "\t-is \"<sztring>\" [kimeneti file]: egy begepelt szoveges tartalmat tomorit egy .hcf fileba\n"
           "VISSZAALLITAS TIPUSOK:\n"
           "\t-rf <tomoritett file> [kimeneti file]: visszaallitja a tomoritett file-t az eredeti, tomoritetlen fileba\n"
           "\t-rs <tomoritett file> [kimeneti file]: visszaallitja a begepelt sztringet\n"
           "KIMENETI FILE:\n\t-o <kimeneti file>: egyedi kiemeneti file beallitasa,\n\tha ures, a tomorites tipusa hatarozza meg az alapertelmezest"
           "SEGITSEG:\n\t-h: kiirja ezt a szoveget\n");
}

Binfa *uj_adatpont(Binfa *gyoker, int szam){
    if (gyoker == NULL){
        Binfa *uj = (Binfa*) malloc(sizeof(Binfa));         /* Lefoglal egy Binfa méretű helyet a memóriában */
        uj->szam = szam;
        uj->bal = uj->jobb = NULL;
        return uj;
    }

    if (gyoker->jobb == NULL)
        gyoker->jobb = uj_adatpont(gyoker->jobb, szam);     /* Beilleszti az adatot a jobb oldali gyerekbe */
    else if (gyoker->bal == NULL)
        gyoker->bal = uj_adatpont(gyoker->bal, szam);       /* Beilleszti az adatot a bal oldali gyerekbe */
 
    return gyoker;
}

Binfa *rekurziv_tomb_osszeg(int *n, int meret){
    if (meret == 0){
        Binfa *fa = NULL;
        fa = uj_adatpont(fa, n[0]);             /* Létrehoz egy bináris fát */
        return fa;
    }
    //tomb_kiir(n, meret);
    // ÖSSZEGALKOTÁS
    int osszeg = n[0] + n[1];
    n[1] = osszeg;
    n = tombelem_torol(n, 0, meret);            /* Törli a 0.ik elemet a tömbből */
    meret -= 1;
    rendezes_int(n);                            /* Rendezi a tömböt */
    // A FÜGGVÉNY REKURZÍV MEGHÍVÁSA
    Binfa *fa = rekurziv_tomb_osszeg(n, meret); /* Meghívja önmagát */
    printf("%d\n", meret);
    /* BUGOS, NEM ILLESZTI BE A FÁBA AZ ADATOKAT!!! */
    
    return fa;
}

void sorban_kiir(Binfa *gyoker) {
    if (gyoker == NULL)
       return;

    printf("%d\n", gyoker->szam);
    printf("bal\n");
    sorban_kiir(gyoker->bal);
    printf("jobb\n");
    sorban_kiir(gyoker->jobb);
}