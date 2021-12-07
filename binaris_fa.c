#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binaris_fa.h"

Gyakorisag *rendezes_struct(Gyakorisag *t, int meret){
    for (int i = 0; i < meret - 1; ++i) {
        int minindex = i;
        for (int j = i + 1; j < meret; ++j){
            if (t[j].gyakorisag < t[minindex].gyakorisag){
                minindex = j;
            }
        }
 
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

Gyakorisag *tombelem_torol_struct(Gyakorisag *t, int p, int meret){
    for (int k = p - 1; k < meret - 1; k++)
        t[k] = t[k + 1];
    return t;
}

void sorban_kiir(Binfa *gyoker) {
    if (gyoker == NULL){
        printf("NULL\n");
        return;
    }

    printf("%c %d %s\n", gyoker->betu, gyoker->szam, gyoker->ut);
    printf("bal\n");
    sorban_kiir(gyoker->bal);
    printf("jobb\n");
    sorban_kiir(gyoker->jobb);
}

Binfa *lefoglal(int szam){
    Binfa *uj = (Binfa*) malloc(sizeof(Binfa));
    uj->szam = szam;
    uj->betu = (char) 0;
    uj->ut = (char*) 0;
    uj->bal = uj->jobb = NULL;
    return uj;
}

bool level(Binfa *gyoker){
    return gyoker->bal == NULL && gyoker->jobb == NULL;
}

char *tomb_megnovel(char *t){
    int meret = sizeof(t) / sizeof(t[0]);
    char *uj = (char*) malloc((meret + 2) * sizeof(char));
    return uj;
}

Binfa *beszur(Binfa *gyoker, int a, int b, char ca, char cb){
    if (gyoker == NULL)
        return NULL;

    int osszeg = a + b;
    if (level(gyoker)){        
        if (gyoker->szam == osszeg && gyoker->betu == '\0'){
            gyoker->jobb = lefoglal(a);
            gyoker->jobb->betu = ca;

            if (gyoker->ut == NULL)
                gyoker->jobb->ut = "1";

            else{
                gyoker->jobb->ut = tomb_megnovel(gyoker->jobb->ut);
                strcpy(gyoker->jobb->ut, gyoker->ut);
                gyoker->jobb->ut = strcat(gyoker->jobb->ut, "1");
            }
            
            gyoker->bal = lefoglal(b);
            gyoker->bal->betu = cb;

            if (gyoker->ut == NULL)
                gyoker->bal->ut = "0";

            else{
                gyoker->bal->ut = tomb_megnovel(gyoker->bal->ut);
                strcpy(gyoker->bal->ut, gyoker->ut);
                gyoker->bal->ut = strcat(gyoker->bal->ut, "0");
            }
            return gyoker;
        }
        else
            return NULL;
    }

    else
        if (!beszur(gyoker->bal, a, b, ca, cb))
            if (!beszur(gyoker->jobb, a, b, ca, cb))
                return NULL;

    return gyoker;
}

Binfa *rekurziv_tomb(Gyakorisag *n, int meret){
    if (meret == 1){
        Binfa *fa = NULL;
        fa = lefoglal(n[0].gyakorisag);
        fa->betu = n[0].betu;
        fa->ut = NULL;
        return fa;
    }
    
    Gyakorisag *m = (Gyakorisag*) malloc(meret * sizeof(Gyakorisag));
    memcpy(m, n, meret * sizeof(Gyakorisag));

    int osszeg = n[0].gyakorisag + n[1].gyakorisag;
    n[1].gyakorisag = osszeg;
    n[1].betu = '\0';
    n = tombelem_torol_struct(n, 0, meret);
    meret -= 1;
    n = rendezes_struct(n, meret);

    Binfa *r = rekurziv_tomb(n, meret);
    r = beszur(r, m[1].gyakorisag, m[0].gyakorisag, m[1].betu, m[0].betu);
    
    return r;
}

void binaris_fajl_ir(char *t, FILE *f){
    char resz[8];
    int meret = strlen(t);
    for (int n = 0; n < meret; n += 8){
        for (int i = 0; i < 8; i++){
            if (n + i < meret)
                resz[i] = t[n + i];
            else
                resz[i] = '0';
        }
        resz[8] = '\0';
        long int l = strtol(resz, 0, 2);
        unsigned char b = l & 0xffl;
        if (b == 0)
            fwrite("0", sizeof(char), 1, f);
        else
            fwrite(&b, 1, 1, f);
    }
}

void kodok_fileba(Binfa *gyoker, FILE *f){
    if (gyoker == NULL)
        return;

    if (level(gyoker)){
        fwrite(&gyoker->betu, sizeof(char), 1, f);
        fprintf(f, "%d", strlen(gyoker->ut));
        binaris_fajl_ir(gyoker->ut, f);
    }

    kodok_fileba(gyoker->jobb, f);
    kodok_fileba(gyoker->bal, f);
}

char *faban_keres(Binfa *gyoker, char c, char *t, FILE *f){
    if (gyoker == NULL)
        return NULL;

    if (gyoker->betu == c){
        strcat(t, gyoker->ut);
        return gyoker->ut;
    }
    
    faban_keres(gyoker->bal, c, t, f);
    faban_keres(gyoker->jobb, c, t, f);
    return t;
}

Gyakorisag* gyak_szamol(char *szoveg, int *cel_meret){
    if (szoveg == NULL)
        return 0;

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
    Gyakorisag *cel = (Gyakorisag*) malloc(sizeof(Gyakorisag));
    for (int i = 0; i < meret; i++){
        if (elofordulas[i] != -1){
            Gyakorisag *uj = (Gyakorisag*) malloc((j + 1) * sizeof(Gyakorisag));         /* Lefoglal egyel nagyobb tömböt a gyakoriságok tárolására */
            for (int k = 0; k < j; ++k)
                uj[k] = cel[k];                     /* Átmásolja az eddigi elemeket az új tömbbe*/
            free(cel);
            cel = uj;
            cel[j].betu = szoveg[i];                /* Eltárolja a karaktert*/
            cel[j].gyakorisag = elofordulas[i];     /* Eltárolja a karakter előfordulásának számát */
            j++;
        }
    }

    *cel_meret = j;

    return cel;
}